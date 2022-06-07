#include "zf_common_headfile.h"
#include "Config.h"
#include "my_function.h"


//超声波
//#define ULTRASONIC1_TR                    TIM3_PWM_CH3_B0
//float DATA = 0;

//舵机
#define PWM_STEER1          TIM1_PWM_CH1_E9
//#define PWM_STEER2          TIM1_PWM_CH2_E11
//#define PWM_STEER3          TIM1_PWM_CH3_E13
//#define PWM_STEER4          TIM1_PWM_CH4_E14
float angle = 0;
float angle_duty = 0;

//编码器
//#define ENCODER_DIR                     TIM8_ENCOEDER
//#define ENCODER_DIR_PULSE               TIM8_CH2_ENCOEDER_C7
//#define ENCODER_DIR_DIR                 TIM8_CH1_ENCOEDER_C6
//
//#define ENCODER_QUADDEC                 TIM8_ENCOEDER
//#define ENCODER_QUADDEC_A               TIM8_CH2_ENCOEDER_C7
//#define ENCODER_QUADDEC_B               TIM8_CH1_ENCOEDER_C6

void Blink(uint16_t _times)
{
    static int i = 0;
    if (i >= _times)
    {
        gpio_toggle_level(INDICATOR);
        i = 0;
    }
    i++;
}



void Init()
{
    gpio_init(INDICATOR, GPO, GPIO_LOW, GPO_PUSH_PULL);
    tft180_init();

    //驱动板初始化
    // 初始化PWM2 通道1 使用引脚A15  输出PWM频率50HZ   占空比为百分之 1000/PWM_DUTY_MAX*100
    //T3接口
       pwm_init(PWM_T3_1, 5000, 3000);
       pwm_init(PWM_T3_2, 5000, 0);
    //T4接口
       pwm_init(PWM_T4_3, 5000, 0);
       pwm_init(PWM_T4_4, 5000, 0);
    //T5接口
       pwm_init(PWM_T5_5, 5000, 0);
       pwm_init(PWM_T5_6, 5000, 0);
    //T6接口
       pwm_init(PWM_T6_7, 5000, 0);
       pwm_init(PWM_T6_8, 5000, 0);
    //EN使能
       gpio_init(MOTOR_EN, GPO, GPIO_LOW, GPO_PUSH_PULL);


    //超声波测距模块
//       pwm_init(ULTRASONIC1_TR, 50, 1000);                        //初始化输出PWM
//       gpio_init(ULTRASONIC2_TRIG, GPO, GPIO_LOW, GPO_PUSH_PULL); //tig使能
//       gpio_init(ULTRASONIC2_ECHO, GPI, GPIO_LOW, GPI_FLOATING_IN);  //初始化输入引脚
//       exti_enable(ULTRASONIC2_ECHO);
//       exti_init(ULTRASONIC2_ECHO, EXTI_TRIGGER_RISING);          //初始化中断

    //舵机初始化
       pwm_init(PWM_STEER1, 50, 0);
       //pwm_init(PWM_STEER2, 50, 1000);
//       pwm_init(PWM_STEER3, 50, 1000);
//       pwm_init(PWM_STEER4, 50, 1000);


//    // 摄像头初始化
//       mt9v03x_init_dvp();

    //编码器初始化
//       encoder_init_dir(ENCODER_DIR, ENCODER_DIR_DIR, ENCODER_DIR_PULSE);          // 初始化编码器模块与引脚 带方向增量编码器模式
//       encoder_init_quad(ENCODER_QUADDEC, ENCODER_QUADDEC_A, ENCODER_QUADDEC_B);   // 初始化编码器模块与引脚 正交解码编码器模式
}


uint16_t duty = 1000;
int16 encoder_data = 0;

int main(void)
{
    interrupt_global_disable();             // 关闭总中断
    clock_init(SYSTEM_CLOCK_144M);          // 务必保留，设置系统时钟。
    debug_init();                           // 务必保留，本函数用于初始化MPU 时钟 调试串口
    Init();
    interrupt_global_enable();              // 总中断最后开启
    gpio_set_level(MOTOR_EN, 1);            //驱动板使能
    tft180_show_string(0,0,"HELLO WORLD!");

    angle = 90;
    angle_duty = angle_set_duty(angle);
    pwm_set_duty(PWM_STEER1,angle_duty);
    system_delay_ms(500);
    pwm_set_duty(PWM_STEER1,0);

    while(1)
    {
        //摄像头
//        if(mt9v03x_finish_flag_dvp)
//        {
//            //tft180_show_gray_image(0, 0,mt9v03x_image_dvp[0] ,MT9V03X_DVP_W, MT9V03X_DVP_H, MT9V03X_DVP_W, MT9V03X_DVP_H, 0);
//            mt9v03x_finish_flag_dvp = 0;
//        }
//       Blink(1000);

        //编码器
//        encoder_data = encoder_get_count(ENCODER_DIR);                          // 获取编码器计数
//        encoder_clear_count(ENCODER_DIR);                                       // 清空编码器计数
////        printf("ENCODER_DIR counter \t\t%d .\r\n", encoder_data);               // 输出编码器计数信息
//        tft180_show_float(0,0,encoder_data,5,5);                              // 输出编码器计数信息

//        encoder_data = encoder_get_count(ENCODER_QUADDEC);                          // 获取编码器计数
//        encoder_clear_count(ENCODER_QUADDEC);                                       // 清空编码器计数
//        printf("ENCODER_DIR counter \t\t%d .\r\n", encoder_data);               // 输出编码器计数信息
//        tft180_show_float(0,0,encoder_data,5,5);                              // 输出编码器计数信息

        //超声波
//        gpio_set_level(ULTRASONIC2_TRIG, 1);
//        system_delay_us(20);
//        gpio_set_level(ULTRASONIC2_TRIG, 0);

//        while(gpio_get_level(ULTRASONIC2_ECHO) == 0);
//        Blink(1);
//        timer_start( TIM_1, TIMER_US);
//
//        while(gpio_get_level(ULTRASONIC2_ECHO) == 1);
//        DATA = (timer_get(TIM_1)*340.0)/20000;
//        timer_stop( TIM_1 );
//        TIM1->CNT = 0;
//        tft180_show_float(0,0,DATA,5,5);

        //舵机
//        gpio_set_level(STEER1_PWM, 1);
//        system_delay_us(1000);
//        gpio_set_level(STEER1_PWM, 0);
//        angle = 45;
//        angle_duty = angle_set_duty(angle);
//        pwm_set_duty(PWM_STEER1,angle_duty);

        tft180_show_string(0,0,"ZongJie is SB!!!");
        system_delay_ms(500);
        Blink(1);
    }
}







