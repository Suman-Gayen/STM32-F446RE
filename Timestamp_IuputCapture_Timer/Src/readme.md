# STM32 Timer Output Compare and Input Capture Example

## Overview

This project demonstrates how to use STM32 timers in **Output Compare mode** and **Input Capture mode** using **bare-metal register programming**.

The application performs two tasks:

1. Generate a square wave on **PA5** using **TIM2 Output Compare Toggle mode**
2. Capture the rising edge timestamp on **PA6** using **TIM3 Input Capture**

PA5 must be connected physically to PA6.

---

# Hardware

Microcontroller:

STM32F446

Pins used:

| Pin | Function        |
| --- | --------------- |
| PA5 | TIM2_CH1 Output |
| PA6 | TIM3_CH1 Input  |

Connection required:

PA5 → PA6

---

# Clock Assumptions

System Clock:

16 MHz

Timer clock calculations are based on this value.

---

# Code Explanation

## Header Files

```c
#include <stdint.h>
#include "stm32f446xx.h"
```

`stdint.h`

Provides fixed width integer types.

`stm32f446xx.h`

Contains all register definitions for STM32F446 peripherals.

---

## Global Variable

```c
volatile unsigned int timestamp = 0;
```

Stores captured timer value.

`volatile` ensures the compiler does not optimize away accesses to the variable because it may change due to hardware events.

---

# TIM2 Output Compare Configuration

## Enable GPIOA Clock

```c
RCC->AHB1ENR |= (1<<0);
```

Activates clock for GPIOA.

---

## Configure PA5 as Alternate Function

```c
GPIOA->MODER |= (1<<11);
GPIOA->MODER &= (~(1<<10));
```

Sets PA5 mode to alternate function.

---

## Select Alternate Function AF1

```c
GPIOA->AFR[0] |= (1<<20);
GPIOA->AFR[0] &= (~(1<<21));
GPIOA->AFR[0] &= (~(1<<22));
GPIOA->AFR[0] &= (~(1<<23));
```

AF1 corresponds to TIM2 channel 1.

---

## Enable TIM2 Clock

```c
RCC->APB1ENR |= (1<<0);
```

---

## Configure Toggle Mode

```c
TIM2->CCMR1 |= (1<<4) | (1<<5);
TIM2->CCMR1 &= (~(1<<6));
```

OC1M = 011 → Toggle output on match.

---

## Enable Channel Output

```c
TIM2->CCER |= (1<<0);
```

---

## Configure Timer Frequency

```c
TIM2->PSC = 16000-1;
```

Timer frequency:

```
16 MHz / 16000 = 1 kHz
```

Timer tick:

```
1 ms
```

---

## Set Auto Reload Value

```c
TIM2->ARR = 1000-1;
```

Timer overflow occurs every:

```
1000 ms
```

---

## Reset Counter

```c
TIM2->CNT = 0;
```

---

## Start Timer

```c
TIM2->CR1 |= (1<<0);
```

---

# TIM3 Input Capture Configuration

## Configure PA6 as Alternate Function

```c
GPIOA->MODER |= (1<<13);
GPIOA->MODER &= (~(1<<12));
```

---

## Select AF2 for TIM3

```c
GPIOA->AFR[0] |= (1<<25);
GPIOA->AFR[0] &= (~(1<<24)) & (~(1<<26)) & (~(1<<27));
```

---

## Enable TIM3 Clock

```c
RCC->APB1ENR |= (1<<1);
```

---

## Configure Prescaler

```c
TIM3->PSC = 1600-1;
```

Timer frequency:

```
16 MHz / 1600 = 10 kHz
```

Timer tick:

```
100 µs
```

---

## Configure Channel as Input Capture

```c
TIM3->CCMR1 |= (1<<0);
TIM3->CCMR1 &= (~(1<<0));
```

---

## Capture Rising Edge

```c
TIM3->CCER |= (1<<0);
TIM3->CCER &= (~(1<<1)) & (~(1<<3));
```

---

## Enable Timer

```c
TIM3->CR1 |= (1<<0);
```

---

# Capturing Timestamp

Main loop waits for capture event:

```c
while (!(TIM3->SR & (1<<0)))
```

When a rising edge is detected, the timer value is copied to CCR1:

```c
timestamp = TIM3->CCR1;
```

This value represents the time at which the signal edge occurred.

---

# Result

PA5 generates a square wave with frequency:

```
0.5 Hz
```

TIM3 captures the rising edge timestamps of this signal.

---

# Concepts Demonstrated

* GPIO Alternate Functions
* Timer Output Compare Mode
* Timer Input Capture Mode
* Hardware signal measurement
* Bare-metal embedded programming

---

# Possible Improvements

* Use interrupts instead of polling
* Use HAL or LL drivers
* Measure full signal period
* Send timestamp over UART for debugging

---
