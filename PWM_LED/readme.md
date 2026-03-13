# STM32F446 PWM LED Fade (Bare-Metal Register Programming)

## Overview

This project demonstrates how to generate **PWM (Pulse Width Modulation)** using **TIM2 on the STM32F446 microcontroller** to create a **LED fading effect**.

The code directly manipulates **hardware registers** instead of using HAL or LL libraries.
PWM duty cycle gradually increases and decreases, producing a **breathing/fading LED effect**.

Hardware used:

* MCU: **STM32F446**
* Timer: **TIM2**
* Pin: **PA5 (TIM2_CH1 Alternate Function)**

---


# Line-by-Line Explanation



# Header Files

### `#include <stdint.h>`

**What it does**

Includes standard integer types like:

* `uint8_t`
* `uint16_t`
* `uint32_t`

**Why it is used**

Embedded systems require **precise integer sizes** for hardware registers.

Example:

```
uint32_t
```

ensures a **32-bit register access**, which matches STM32 register width.

---

### `#include "stm32f446xx.h"`

**What it does**

This header contains:

* Register definitions
* Peripheral base addresses
* Register structures

Example inside this file:

```
#define GPIOA ((GPIO_TypeDef*) GPIOA_BASE)
#define TIM2  ((TIM_TypeDef*) TIM2_BASE)
```

**Why it is used**

Allows writing readable code like:

```
GPIOA->MODER
TIM2->PSC
```

instead of raw memory addresses.

---

# Delay Function

### `void delay(){`

Defines a simple delay function.

---

### `for(int i=0;i<10000;i++);`

**What it does**

Creates a **busy-wait loop**.

**Why used**

Slows down PWM duty cycle updates so the LED fade becomes visible.

Without delay the brightness change would be **too fast to see**.

---

# Main Function

### `int main(void)`

Entry point of the program.

All microcontroller programs start execution here after reset.

---

# Enable Peripheral Clocks

### `RCC->AHB1ENR |= (1<<0);`

**What it does**

Enables clock for **GPIOA**.

Register:

```
RCC AHB1 Peripheral Clock Enable Register
```

Bit meaning:

```
Bit 0 = GPIOA clock enable
```

**Why needed**

Peripherals are **disabled by default to save power**.
We must enable the clock before accessing GPIO registers.

---

### `RCC->APB1ENR |= (1<<0);`

**What it does**

Enables clock for **TIM2**.

Register:

```
RCC APB1 Peripheral Clock Enable Register
```

Bit mapping:

```
Bit 0 = TIM2 clock enable
```

**Why needed**

Timer cannot operate without its clock.

---

# Configure PA5 as Alternate Function

### `GPIOA->MODER |= (1<<11);`

Sets **MODER5 bit1**.

---

### `GPIOA->MODER &= (~(1<<10));`

Clears **MODER5 bit0**.

Together these produce:

```
10 = Alternate Function Mode
```

**Why**

PA5 must output **TIM2 PWM signal** instead of GPIO output.

---

# Configure Alternate Function Mapping

### `GPIOA->AFR[0] |= (1<<20);`

Sets AFRL5 bit0.

---

### `GPIOA->AFR[0] &= (~(1<<21)) & (~(1<<22)) & (~(1<<23));`

Clears bits 1–3.

Result:

```
AF = 0001
```

**AF1 corresponds to:**

```
TIM2_CH1
```

**Why**

This connects **TIM2 Channel1 output to PA5 pin**.

---

# Timer Configuration

---

### `TIM2->PSC = (160-1);`

**Prescaler**

Timer clock:

```
Timer Clock / PSC
```

Example if timer clock is 16 MHz:

```
16 MHz / 160 = 100 kHz
```

**Why**

Prescaler slows down the timer counting speed.

---

### `TIM2->ARR = (1000-1);`

Auto Reload Register defines **PWM period**.

Timer counts:

```
0 → 999
```

**PWM frequency**

```
100kHz / 1000 = 100 Hz
```

---

# Configure PWM Mode

### `TIM2->CCMR1 |= (1<<6) | (1<<5);`

Sets bits:

```
OC1M = 110
```

Which means:

```
PWM Mode 1
```

---

### `TIM2->CCMR1 &= (~(1<<4));`

Completes the `110` configuration.

PWM Mode bits:

```
OC1M[2:0] = 110
```

---

### `TIM2->CCMR1 |= (1 << 3);`

Enables **Output Compare Preload**.

**Why**

Updates to duty cycle happen **safely at next timer update**, preventing glitches.

---

# Enable Output

### `TIM2->CCER |= (1<<0);`

Enables **Channel 1 output**.

Without this the PWM signal would not appear on the pin.

---

# Timer Control

### `TIM2->CR1 |= (1<<7);`

Enables **Auto Reload Preload**.

**Why**

Ensures stable PWM when ARR updates occur.

---

### `TIM2->CR1 |= (1<<0);`

Starts the timer counter.

Bit name:

```
CEN = Counter Enable
```

---

# Infinite Loop

### `while(1)`

Embedded systems run **forever** unless reset.

---

# Increase Duty Cycle

```
for(int i=0; i<1000; i++)
```

Counts from **0 to 999**.

---

### `TIM2->CCR1 = i;`

CCR1 controls **PWM duty cycle**.

Duty cycle formula:

```
Duty Cycle = CCR1 / ARR
```

Examples:

| CCR1 | Duty Cycle |
| ---- | ---------- |
| 0    | 0%         |
| 500  | 50%        |
| 999  | ~100%      |

Increasing `CCR1` makes LED **brighter gradually**.

---

# Decrease Duty Cycle

```
for(int i=1000; i>0; i--)
```

Gradually decreases brightness.

Creates **fade-out effect**.

---

# Final Result

The LED connected to **PA5** will:

```
dim → bright → dim → bright
```

continuously.

This is often called:

```
Breathing LED Effect
```

---

# Key Embedded Concepts Demonstrated

* Bare-metal register programming
* Peripheral clock configuration
* GPIO alternate function
* Timer PWM generation
* Duty cycle control
* Hardware timer usage

---

# Possible Improvements

* Replace software delay with **timer-based delay**
* Add **multiple PWM channels**
* Control brightness using **ADC input**
* Implement **DMA PWM waveform**

---

# Author Notes

This project demonstrates **low-level STM32 peripheral control** without abstraction layers such as HAL.

Understanding this approach provides deeper knowledge of:

* STM32 architecture
* Peripheral registers
* Hardware timers
* Embedded system timing
