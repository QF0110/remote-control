#include "protocol.h"
#include "usart.h"     // 包含 huart2 的声明
#include "bsp_key.h"   // 包含 key_state 的声明

// 声明本文件引用的外部全局变量
extern uint16_t adc_values[4];

void Send_Data(void)
{
  uint8_t tx_buf[12];
  tx_buf[0] = 0xAA; // Start byte
  tx_buf[1] = 0x55; // Start byte

  for (int i = 0; i < 4; i++) {
    tx_buf[2 + i * 2] = (uint8_t)(adc_values[i] & 0xFF); // 强制转换消除警告
    tx_buf[3 + i * 2] = (uint8_t)((adc_values[i] >> 8) & 0xFF); 
  }

  uint16_t key_val = 0;
  for (int i = 0; i < 9; i++) {
    if (key_state[i]) key_val |= (1 << i); 
  }
  tx_buf[10] = (uint8_t)(key_val & 0xFF); 
  tx_buf[11] = (uint8_t)((key_val >> 8) & 0xFF); 

  HAL_UART_Transmit(&huart2, tx_buf, 12, 100);
}
