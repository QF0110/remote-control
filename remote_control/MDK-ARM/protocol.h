#ifndef __PROTOCOL_H
#define __PROTOCOL_H

#include "main.h"

// 声明 ADC 数据数组，供协议发送函数使用
extern uint16_t adc_values[4];

// 声明数据发送函数
void Send_Data(void);

#endif /* __PROTOCOL_H */
