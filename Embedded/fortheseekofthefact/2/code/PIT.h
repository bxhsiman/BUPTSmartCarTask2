#ifndef __LQ_PIT_H_
#define __LQ_PIT_H_

#include "fsl_pit.h"

/**
  * @brief    PIT��ʱ����ʼ��
  *
  * @param    channel�� PITͨ�� kPIT_Chnl_0 - kPIT_Chnl_3
  * @param    count  �� ��ʱ��ʱ�� us
  *
  * @return   
  *
  * @note     PIT��GPTʹ�� ͬһʱ��Դ Ĭ��IPG/2ʱ�� 75M
  *
  * @example  PIT_InitConfig(kPIT_Chnl_0, 5000);  //����ͨ��0��ʱ���жϣ�ÿ5000us�ж�һ��
  *
  * @date     2019/6/4 ���ڶ�
  */
void PIT_InitConfig(pit_chnl_t channel, uint32_t count);







#endif  
