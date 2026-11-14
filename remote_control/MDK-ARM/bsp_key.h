#ifndef __BSP_KEY_H
#define __BSP_KEY_H

#include "main.h"

// 声明按键状态数组，供其他文件（如协议文件）使用
extern uint8_t key_state[9];

// 声明按键扫描函数
void Key_Scan(void);

#endif /* __BSP_KEY_H */
