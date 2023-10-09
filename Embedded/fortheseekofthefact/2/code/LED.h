#ifndef __LQ_LED_H__
#define __LQ_LED_H__

//定义颜色枚举
typedef enum
{
  white = 0,  //白色
  black = 1,  //黑色
  red   = 2,  //红
  green = 3,  //绿
  blue  = 4,  //蓝色 
  yellow= 5,  //黄色
  violet= 6,  //紫色
  cyan  = 7,  //青色
}LED_t;

/*测试LED灯 */
void Test_LED(void);


/*指定颜色闪烁*/
void LED_ColorReverse(LED_t color);


/*    指定颜色的灯亮*/
void LED_Color(LED_t color);


/*RGB灯引脚初始化*/
void LED_Init(void);

#endif  //__LQ_LED_H__
