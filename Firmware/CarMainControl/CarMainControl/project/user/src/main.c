#include "zf_common_headfile.h"
#include "Config.h"
#include "my_function.h"


//������
//#define ULTRASONIC1_TR                    TIM3_PWM_CH3_B0
//float DATA = 0;

//���
#define PWM_STEER1          TIM1_PWM_CH1_E9
//#define PWM_STEER2          TIM1_PWM_CH2_E11
//#define PWM_STEER3          TIM1_PWM_CH3_E13
//#define PWM_STEER4          TIM1_PWM_CH4_E14
float angle = 0;
float angle_duty = 0;

//������
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

    //�������ʼ��
    // ��ʼ��PWM2 ͨ��1 ʹ������A15  ���PWMƵ��50HZ   ռ�ձ�Ϊ�ٷ�֮ 1000/PWM_DUTY_MAX*100
    //T3�ӿ�
       pwm_init(PWM_T3_1, 5000, 3000);
       pwm_init(PWM_T3_2, 5000, 0);
    //T4�ӿ�
       pwm_init(PWM_T4_3, 5000, 0);
       pwm_init(PWM_T4_4, 5000, 0);
    //T5�ӿ�
       pwm_init(PWM_T5_5, 5000, 0);
       pwm_init(PWM_T5_6, 5000, 0);
    //T6�ӿ�
       pwm_init(PWM_T6_7, 5000, 0);
       pwm_init(PWM_T6_8, 5000, 0);
    //ENʹ��
       gpio_init(MOTOR_EN, GPO, GPIO_LOW, GPO_PUSH_PULL);


    //���������ģ��
//       pwm_init(ULTRASONIC1_TR, 50, 1000);                        //��ʼ�����PWM
//       gpio_init(ULTRASONIC2_TRIG, GPO, GPIO_LOW, GPO_PUSH_PULL); //tigʹ��
//       gpio_init(ULTRASONIC2_ECHO, GPI, GPIO_LOW, GPI_FLOATING_IN);  //��ʼ����������
//       exti_enable(ULTRASONIC2_ECHO);
//       exti_init(ULTRASONIC2_ECHO, EXTI_TRIGGER_RISING);          //��ʼ���ж�

    //�����ʼ��
       pwm_init(PWM_STEER1, 50, 0);
       //pwm_init(PWM_STEER2, 50, 1000);
//       pwm_init(PWM_STEER3, 50, 1000);
//       pwm_init(PWM_STEER4, 50, 1000);


//    // ����ͷ��ʼ��
//       mt9v03x_init_dvp();

    //��������ʼ��
//       encoder_init_dir(ENCODER_DIR, ENCODER_DIR_DIR, ENCODER_DIR_PULSE);          // ��ʼ��������ģ�������� ����������������ģʽ
//       encoder_init_quad(ENCODER_QUADDEC, ENCODER_QUADDEC_A, ENCODER_QUADDEC_B);   // ��ʼ��������ģ�������� �������������ģʽ
}


uint16_t duty = 1000;
int16 encoder_data = 0;

int main(void)
{
    interrupt_global_disable();             // �ر����ж�
    clock_init(SYSTEM_CLOCK_144M);          // ��ر���������ϵͳʱ�ӡ�
    debug_init();                           // ��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���
    Init();
    interrupt_global_enable();              // ���ж������
    gpio_set_level(MOTOR_EN, 1);            //������ʹ��
    tft180_show_string(0,0,"HELLO WORLD!");

    angle = 90;
    angle_duty = angle_set_duty(angle);
    pwm_set_duty(PWM_STEER1,angle_duty);
    system_delay_ms(500);
    pwm_set_duty(PWM_STEER1,0);

    while(1)
    {
        //����ͷ
//        if(mt9v03x_finish_flag_dvp)
//        {
//            //tft180_show_gray_image(0, 0,mt9v03x_image_dvp[0] ,MT9V03X_DVP_W, MT9V03X_DVP_H, MT9V03X_DVP_W, MT9V03X_DVP_H, 0);
//            mt9v03x_finish_flag_dvp = 0;
//        }
//       Blink(1000);

        //������
//        encoder_data = encoder_get_count(ENCODER_DIR);                          // ��ȡ����������
//        encoder_clear_count(ENCODER_DIR);                                       // ��ձ���������
////        printf("ENCODER_DIR counter \t\t%d .\r\n", encoder_data);               // ���������������Ϣ
//        tft180_show_float(0,0,encoder_data,5,5);                              // ���������������Ϣ

//        encoder_data = encoder_get_count(ENCODER_QUADDEC);                          // ��ȡ����������
//        encoder_clear_count(ENCODER_QUADDEC);                                       // ��ձ���������
//        printf("ENCODER_DIR counter \t\t%d .\r\n", encoder_data);               // ���������������Ϣ
//        tft180_show_float(0,0,encoder_data,5,5);                              // ���������������Ϣ

        //������
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

        //���
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







