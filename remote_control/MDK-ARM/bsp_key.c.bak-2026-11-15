#include "bsp_key.h"

uint8_t key_state[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

// 内部使用的映射表，不需要暴露给外部
static uint16_t key_map[3][3] = {
  {0, 1, 2},
  {3, 4, 5},
  {6, 7, 8}
};

void Key_Scan(void)
{
  uint16_t row_pins[3] = {GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7};
  uint16_t col_pins[3] = {GPIO_PIN_4, GPIO_PIN_8, GPIO_PIN_9};
  uint8_t temp_state[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      HAL_GPIO_WritePin(GPIOB, row_pins[i], (j == i) ? GPIO_PIN_RESET : GPIO_PIN_SET);
    }
    HAL_Delay(1); // 阻塞延迟，后续建议优化为定时器中断扫描

    for (int j = 0; j < 3; j++) {
      if (HAL_GPIO_ReadPin(GPIOB, col_pins[j]) == GPIO_PIN_RESET) {
        temp_state[key_map[i][j]] = 1;
      }
    }
  }

  for (int j = 0; j<3; j++) {
    HAL_GPIO_WritePin(GPIOB, row_pins[j], GPIO_PIN_SET);
  }

  static uint8_t last_temp[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (int i = 0; i < 9; i++) {
    if (temp_state[i] == last_temp[i]) {
      key_state[i] = temp_state[i];
    }
    last_temp[i] = temp_state[i];
  } 
}
