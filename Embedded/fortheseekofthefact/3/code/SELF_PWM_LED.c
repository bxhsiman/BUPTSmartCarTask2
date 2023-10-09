#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "pin_mux.h"
#include "fsl_gpio.h"
#include "LQ_LED.h"
#include "LQ_GPIO.h"
#include "LQ_KEY.h"
#include "SELF_PWM_LED.h"

/*ºôÎüµÆ*/
void PWM_LED(int i,LED_t color){
  LED_Color(color);     
   delayms(i);
   LED_Color(black);
   delayms(10-i);
}
void PWM_LED_TEST(void)
{
  LED_Init();   
  while (1)
  {          
    for(int i=0;i<=10;i++)
      for(int j=0;j<8;j++) 
        PWM_LED(i,green);
    for(int i=10;i>=0;i--)
      for(int j=0;j<8;j++) 
        PWM_LED(i,green);
  }
}