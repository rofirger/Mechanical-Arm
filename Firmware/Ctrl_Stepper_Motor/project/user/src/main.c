/*
 * @��л����л��ɿƼ�ch32V307��Դ���֧��
*/

#include "Motor.h"
#include "zf_common_headfile.h"
#include "MyCan.h"
#include "stdlib.h"


/*
 * @note:�����������ϵ�LED��˸
*/
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
    // ָʾ��
    gpio_init(INDICATOR, GPO, GPIO_LOW, GPO_PUSH_PULL);
    // ��ʼ�������������GPIO�������
    gpio_init(AP_STEP, GPO, GPIO_LOW, GPO_PUSH_PULL);
    gpio_init(AN_STEP, GPO, GPIO_LOW, GPO_PUSH_PULL);
    gpio_init(BP_STEP, GPO, GPIO_LOW, GPO_PUSH_PULL);
    gpio_init(BN_STEP, GPO, GPIO_LOW, GPO_PUSH_PULL);
    // ��ʼ�������������оƬPWM������ţ����Ƶ��2M
#if (AXIS6 == 0)
    pwm_init(TIM2_PWM_CH1_A0, 20000, 4000);
    pwm_init(TIM1_PWM_CH1_A8, 20000, 4000);
#elif (AXIS6 == 1)
    pwm_init(TIM2_PWM_CH1_A0, 20000, 1500);
    pwm_init(TIM1_PWM_CH1_A8, 20000, 1500);
#endif
    MT6816_Init();
    // TFT��ʼ��
    tft180_init();
    // CAN��ʼ��
    CAN_Mode_Init( CAN_SJW_1tq, CAN_BS2_5tq, CAN_BS1_6tq, 12, CAN_Mode_Normal );
}

// ˳ʱ��
void CV_MotorStep(uint16_t _times, uint16_t _ms_interval)
{
    static uint8_t _motor_status = 0x0C;        // (1100)b
    for (uint16_t _i = 0; _i < _times; ++_i)
    {
        gpio_set_level(AP_STEP, (_motor_status & 0x08) >> 3);
        gpio_set_level(BP_STEP, (_motor_status & 0x04) >> 2);
        gpio_set_level(AN_STEP, (_motor_status & 0x02) >> 1);
        gpio_set_level(BN_STEP, (_motor_status & 0x01));
        _motor_status = (_motor_status >> 1) | ((_motor_status & 0x01) << 3);
        system_delay_ms(_ms_interval);
    }
}

// ��ʱ��
void CCV_MotorStep(uint16_t _times, uint16_t _ms_interval)
{
    static uint8_t _motor_status = 0x0C;        // (1100)b
    for (uint16_t _i = 0; _i < _times; ++_i)
    {
        gpio_set_level(AP_STEP, (_motor_status & 0x1));
        gpio_set_level(BP_STEP, (_motor_status & 0x02) >> 1);
        gpio_set_level(AN_STEP, (_motor_status & 0x04) >> 2);
        gpio_set_level(BN_STEP, (_motor_status & 0x08) >> 3);
        _motor_status = (_motor_status >> 1) | ((_motor_status & 0x01) << 3);
        system_delay_ms(_ms_interval);
    }
}

uint16_t stop_angle = 0;
void ProcessCANMsg(char* _can_msg)
{
    static MT6816_Structure data;
    char* _main_msg = strtok(_can_msg, "#");        // ��������ָ���
    char* _head_cmd = strtok(_main_msg, " ");
    if (_head_cmd)
    {
        if (strcmp(_head_cmd, "S") == 0)
        {
            char* _sec_cmd = strtok(NULL, " ");
            if (strcmp(_sec_cmd, "C") == 0)
            {
                char* _third_cmd = strtok(NULL, " ");
                if (_third_cmd)
                    CV_MotorStep(atoi(_third_cmd), 15);
            }
            else if (strcmp(_sec_cmd, "V") == 0)
            {
                char* _third_cmd = strtok(NULL, " ");
                if (_third_cmd)
                    CCV_MotorStep(atoi(_third_cmd), 15);
            }
            else if (strcmp(_sec_cmd, "J") == 0)
            {
                MT6816_Structure _data;
                MT6816_ReadAngle(&_data);
                uint8_t _send_back_pos[8];
                char _trans_num[8] = {'\0'};
                uint8_t _num = 4;
                _send_back_pos[0] = 'P';
                _send_back_pos[1] = ' ';
                _send_back_pos[2] = (uint8_t)JOINT_INDEX + '0';
                _send_back_pos[3] = ' ';
                itoa(_data._decode_angle, _trans_num, 10);
                for (uint8_t _i = 0; _trans_num[_i] != '\0' && _i < 8; ++_i)
                {
                    _send_back_pos[_num] = _trans_num[_i];
                    ++_num;
                }
                if (_num < 8)
                {
                    _send_back_pos[_num] = '#';
                    CAN_Send_Msg(_send_back_pos, _num);
                }
            }
        }
        else if (strcmp(_head_cmd, "LED") == 0)
        {
            char* _sec_cmd = strtok(NULL, " ");
            if (strcmp(_sec_cmd, "ON") == 0)
            {
                gpio_set_level(INDICATOR, 1);
            }
            else if (strcmp(_sec_cmd, "OFF") == 0)
            {
                gpio_set_level(INDICATOR, 0);
            }
        }
    }
    stop_angle = data._decode_angle;
}

// pid ����
typedef struct PID
{
    float P, I, D;
} PID;

// ����ʽ
typedef struct Error
{
    float currentError;   //��ǰ���
    float lastError;      //��һ�����
    float previoursError; //���ϴ����
} Error;

// λ��ʽ
typedef struct PosErr
{
    Error err;
    float loc_sum;
} PosErr;

/*<!
 *  @brief      λ��ʽPID
 *  *sptr ��������
 *  *pid:  PID����
 *  now_point��ʵ��ֵ
 *  target_point��   ����ֵ
 */
int32_t PID_Pos(PosErr *sptr, PID *pid, float now_point, float target_point)
{
    float pos_;                                                       // λ��
    sptr->err.currentError = target_point - now_point;                // ���㵱ǰ���
    sptr->loc_sum += sptr->err.currentError;                          // �ۼ����
    pos_ = pid->P * sptr->err.currentError                            // ����P
           + pid->I * sptr->loc_sum                                   // ����I
           + pid->D * (sptr->err.currentError - sptr->err.lastError); // ΢��D
    sptr->err.lastError = sptr->err.currentError;                     // �����ϴ����
    return pos_;
}

PID pid = {0.700, 0, 0.905};
PosErr error = {{0, 0, 0}, 0};

void KeepPos()
{
    MT6816_Structure _data;
    MT6816_ReadAngle(&_data);
    float _now_pos = _data._decode_angle;
    int32_t _out = PID_Pos(&error, &pid, _now_pos, stop_angle);
}

int main(void)
{
    interrupt_global_disable();             // �ر����ж�
    clock_init(SYSTEM_CLOCK_144M);          // ��ر���������ϵͳʱ�ӡ�
    debug_init();                           // ��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���

    Init();
    interrupt_global_enable();              // ���ж������
    //MT6816_SetZero();
    MT6816_Structure data;

    uint8_t px;
    uint8_t pxbuf[30];


    tft180_show_string(0, 0, "Hello world.");
    MT6816_ReadAngle(&data);
    stop_angle = data._decode_angle;
    while(1)
    {

/*
        gpio_set_level(AP_STEP, GPIO_HIGH);
        gpio_set_level(BP_STEP, GPIO_HIGH);
        gpio_set_level(AN_STEP, GPIO_LOW);
        gpio_set_level(BN_STEP, GPIO_LOW);
        system_delay_ms(1);

        gpio_set_level(AP_STEP, GPIO_LOW);
        gpio_set_level(BP_STEP, GPIO_HIGH);
        gpio_set_level(AN_STEP, GPIO_HIGH);
        gpio_set_level(BN_STEP, GPIO_LOW);
        system_delay_ms(1);

        gpio_set_level(AP_STEP, GPIO_LOW);
        gpio_set_level(BP_STEP, GPIO_LOW);
        gpio_set_level(AN_STEP, GPIO_HIGH);
        gpio_set_level(BN_STEP, GPIO_HIGH);
        system_delay_ms(1);

        gpio_set_level(AP_STEP, GPIO_HIGH);
        gpio_set_level(BP_STEP, GPIO_LOW);
        gpio_set_level(AN_STEP, GPIO_LOW);
        gpio_set_level(BN_STEP, GPIO_HIGH);
        system_delay_ms(1);
*/
        px = CAN_Receive_Msg((char*)pxbuf);

        if( px )
        {
            tft180_show_string(0, 0, pxbuf);
            ProcessCANMsg(pxbuf);
            //CV_MotorStep(10, 1);
        }

        Blink(1000);
        //system_delay_ms(1);
    }
}







