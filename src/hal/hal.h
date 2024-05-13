/*
  Copyright (c) 2024 XDU-IRobot

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

/**
 * @file  hal/hal.h
 * @brief 根据编译宏定义引入不同的芯片型号的HAL库
 */

#ifndef EC_LIB_HAL_WRAPPER_HAL_CONFIG_H
#define EC_LIB_HAL_WRAPPER_HAL_CONFIG_H

#if defined(STM32F407xx)
#include "stm32f407xx.h"
#include "stm32f4xx_hal.h"
#elif defined(STM32H723xx)
#include "stm32h723xx.h"
#include "stm32h7xx_hal.h"
#else
#error "No supported chip defined"
#endif

#endif  // EC_LIB_HAL_CONFIG_H

/* EOF */
