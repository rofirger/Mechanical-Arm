
#include "zf_common_headfile.h"
#include "dvp.h"
#include "ov.h"
#include "sram.h"

uint8_t dvp_img_finish_flag = 0;
extern __aligned(4) uint16 img_dvp[ROW_TFT_HEIGHT][ROW_TFT_WIDTH / 2];
uint8_t binary_dvp_img[ROW_TFT_HEIGHT][ROW_TFT_WIDTH / 2];
// 直方图
short hist_gram[256];

void Blink(uint16_t _times)
{
    static int i = 0;
    if (i >= _times)
    {
        gpio_toggle_level(E7);
        i = 0;
    }
    i++;
}

typedef enum
{
    FlASH_192_SRAM_128 = 0,
    FLASH_224_SRAM_96,
    FLASH_256_SRAM_64,
    FLASH_288_RAM_32
} FLASH_SRAM_DEFIN;

//note: this operation will take effect after reset
void Config_Flash_SRAM(FLASH_SRAM_DEFIN SetFlashSRAM)
{
    uint8_t UserByte = FLASH_GetUserOptionByte() & 0xff; //get user option byte

    switch(SetFlashSRAM)
    {
    case 0:
        UserByte &= ~(0xc0); // SRAM_CODE_MODE = 00
        break;
    case 1:
        UserByte &= ~(0xc0); // SRAM_CODE_MODE = 00
        UserByte |= 0x7f;    // SRAM_CODE_MODE = 01
        break;
    case 2:
        UserByte &= ~(0xc0); // SRAM_CODE_MODE = 00
        UserByte |= 0xbf;    // SRAM_CODE_MODE = 10
        break;
    case 3:
        UserByte |= 0xff;    // SRAM_CODE_MODE = 11
        break;
    default:
        break;
    }

    FLASH_Unlock();
    FLASH_ProgramOptionByteData(0x1ffff802, UserByte);
    FLASH_Lock();
}

// 获取图片的直方图
void GetHistGram (uint8_t width, uint8_t height)
{
    for (int i_ = 0; i_ < 256; ++i_)
    {
        hist_gram[i_] = 0;
    }
    for (int i_ = 0; i_ < height; ++i_)
    {
        for (uint8_t j_ = 0; j_ < width; ++j_)
        {
            hist_gram[binary_dvp_img[i_][j_]]++;
        }
    }
}

// 大津法获取阈值
unsigned char OTSUThreshold ()
{
    int X, Y, amount = 0;
    int pixel_back = 0, pixel_fore = 0, pixel_integral_back = 0, pixel_integral_fore = 0, pixel_integral = 0;
    double OmegaBack, OmegaFore, MicroBack, MicroFore, SigmaB, Sigma; // 类间方差;
    int pixel_min_value, pixel_max_value;
    int threshold = 0;

    for (pixel_min_value = 0; pixel_min_value < 256 && hist_gram[pixel_min_value] == 0; pixel_min_value++)
        ;
    for (pixel_max_value = 255; pixel_max_value > pixel_min_value && hist_gram[pixel_max_value] == 0; pixel_max_value--)
        ;
    if (pixel_max_value == pixel_min_value)
        return pixel_max_value; // 图像中只有一个颜色
    if (pixel_min_value + 1 == pixel_max_value)
        return pixel_min_value; // 图像中只有二个颜色

    for (Y = pixel_min_value; Y <= pixel_max_value; Y++)
        amount += hist_gram[Y]; //  像素总数

    pixel_integral = 0;
    for (Y = pixel_min_value; Y <= pixel_max_value; Y++)
        pixel_integral += hist_gram[Y] * Y;
    SigmaB = -1;
    for (Y = pixel_min_value; Y < pixel_max_value; Y++)
    {
        pixel_back = pixel_back + hist_gram[Y];
        pixel_fore = amount - pixel_back;
        OmegaBack = (double) pixel_back / amount;
        OmegaFore = (double) pixel_fore / amount;
        pixel_integral_back += hist_gram[Y] * Y;
        pixel_integral_fore = pixel_integral - pixel_integral_back;
        MicroBack = (double) pixel_integral_back / pixel_back;
        MicroFore = (double) pixel_integral_fore / pixel_fore;
        Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore);
        if (Sigma > SigmaB)
        {
            SigmaB = Sigma;
            threshold = Y;
        }
    }
    return threshold;
}

/*
 * 二值化函数
 */
void BinaryzationProcess (int rows, int cols, unsigned int threshold_value)
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            binary_dvp_img[i][j] = binary_dvp_img[i][j] > threshold_value ? 255 : 0;
        }
    }
}

void ToGray()
{
    uint32_t r, g, b;
    uint16_t src_cols = ROW_TFT_WIDTH / 2;
    for (uint16_t i = 0; i < ROW_TFT_HEIGHT; i++)
    {
        for (uint16_t j = 0; j < src_cols; ++j)
        {
            r = img_dvp[i][j]>>11;
            g = (img_dvp[i][j]>>5)&0x3f;
            b = img_dvp[i][j]&0x1f;
            binary_dvp_img[i][j] = (r*19595 + g*38469 + b*7472) >> 16;
        }
    }

}


void Init(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    tft180_init();
    // CAN初始化
    //CAN_Mode_Init( CAN_SJW_1tq, CAN_BS2_5tq, CAN_BS1_6tq, 12, CAN_Mode_Normal );
    gpio_init(E7, GPO, GPIO_LOW, GPO_PUSH_PULL);
    // 舵机初始化
    pwm_init(TIM5_PWM_CH1_A0, 50, 1000);
    // FSMC_SRAM_Init();
}

int main(void)
{
    interrupt_global_disable();             // 关闭总中断
    Config_Flash_SRAM(FLASH_256_SRAM_64);
    clock_init(SYSTEM_CLOCK_144M);          // 务必保留，设置系统时钟。
    debug_init();                           // 务必保留，本函数用于初始化MPU 时钟 调试串口
    //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    Init();
    interrupt_global_enable();              // 总中断最后开启
    while (OV2640_Init())
    {
        printf("Camera Err\r\n");
        Delay_Ms(1000);
    }
    RGB565_Mode_Init();
    DVP_OV_Init();
    tft180_show_string(0, 0, "hello world!");

    uint8_t px;
    uint8_t pxbuf[30];
    while(1)
    {

        if (dvp_img_finish_flag)
        {
            tft180_show_rgb565_image(0, 0, img_dvp[0], ROW_TFT_WIDTH / 2, ROW_TFT_HEIGHT, ROW_TFT_WIDTH / 2, ROW_TFT_HEIGHT, 1);
            //ToGray();
            //GetHistGram(ROW_TFT_WIDTH / 2, ROW_TFT_HEIGHT);
            //uint8_t thredshold = OTSUThreshold();
            //BinaryzationProcess(ROW_TFT_HEIGHT, ROW_TFT_WIDTH / 2, thredshold);
            //tft180_show_gray_image(0, 0, binary_dvp_img[0], ROW_TFT_WIDTH / 2, ROW_TFT_HEIGHT, ROW_TFT_WIDTH / 2, ROW_TFT_HEIGHT, 0);
            //Zbar_Test(binary_dvp_img[0], ROW_TFT_WIDTH / 2, ROW_TFT_HEIGHT);
            dvp_img_finish_flag = 0;
        }
        system_delay_ms(2);
        //px = CAN_Receive_Msg((char*)pxbuf);
        //if( px )
        //{
          //  tft180_show_string(0, 0, pxbuf);
        //}
    }
}







