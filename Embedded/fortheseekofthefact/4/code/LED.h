#ifndef __LQ_LED_H__
#define __LQ_LED_H__

//������ɫö��
typedef enum
{
  white = 0,  //��ɫ
  black = 1,  //��ɫ
  red   = 2,  //��
  green = 3,  //��
  blue  = 4,  //��ɫ 
  yellow= 5,  //��ɫ
  violet= 6,  //��ɫ
  cyan  = 7,  //��ɫ
}LED_t;

/*����LED�� */
void Test_LED(void);


/*ָ����ɫ��˸*/
void LED_ColorReverse(LED_t color);


/*    ָ����ɫ�ĵ���*/
void LED_Color(LED_t color);


/*RGB�����ų�ʼ��*/
void LED_Init(void);

#endif  //__LQ_LED_H__
