# STM32F446 Timer Output Compare Example

## Overview

This project demonstrates **bare-metal programming** on the **STM32F446 microcontroller**.

The code configures:

* **GPIOA Pin 5 (PA5)**
* **Timer 2 (TIM2)**

to generate a **toggle signal using Output Compare mode**.

The result is a **square wave output on PA5**.

---

# Hardware Used

* STM32F446 Microcontroller
* Nucleo / Discovery Board (optional)
* Onboard LED (often connected to PA5)

---

# Concepts Used

* Memory Mapped Registers
* RCC Clock Configuration
* GPIO Alternate Function Mode
* Timer Output Compare
* Prescaler
* Auto Reload Register

---

# File Structure

```
main.c
stm32f446xx.h
```

---

# Code Walkthrough

---

## Include Libraries

```c
#include <stdint.h>
#include "stm32f446xx.h"
```

### stdint.h

Provides fixed-width integer types.

Example:

```
uint32_t
uint16_t
```

### stm32f446xx.h

CMSIS header defining peripheral registers such as:

```
RCC
GPIOA
TIM2
```

---

# Main Function

```c
int main(void)
```

Entry point of the embedded program.

---

# Enable GPIOA Clock

```c
RCC->AHB1ENR |= (1<<0);
```

Explanation:

* RCC controls peripheral clocks.
* GPIOA must be enabled before use.

Bit0 in `AHB1ENR` corresponds to:

```
GPIOAEN
```

---

# Configure PA5 Mode

```c
GPIOA->MODER |= (1<<11);
GPIOA->MODER &= (~(1<<10));
```

Each GPIO pin has **2 mode bits**.

PA5 uses:

```
MODER[11:10]
```

Mode selected:

```
10 = Alternate Function Mode
```

---

# Configure Alternate Function

```c
GPIOA->AFR[0] |= (1<<20);
GPIOA->AFR[0] &= (~(1<<21));
GPIOA->AFR[0] &= (~(1<<22));
GPIOA->AFR[0] &= (~(1<<23));
```

Each pin has **4 bits for alternate function**.

PA5 uses bits:

```
AFR[23:20]
```

Value:

```
0001 = AF1
```

AF1 connects PA5 to:

```
TIM2_CH1
```

---

# Enable Timer2 Clock

```c
RCC->APB1ENR |= (1<<0);
```

Enables **TIM2 peripheral clock**.

---

# Configure Output Compare Mode

```c
TIM2->CCMR1 |= (1<<4) | (1<<5);
TIM2->CCMR1 &= (~(1<<6));
```

Bits configured:

```
OC1M[6:4] = 011
```

Mode:

```
Toggle on compare match
```

Meaning the output pin toggles whenever:

```
CNT == ARR
```

---

# Enable Output Channel

```c
TIM2->CCER |= (1<<0);
```

Bit:

```
CC1E = Capture Compare Enable
```

This allows timer output to appear on the GPIO pin.

---

# Configure Timer Frequency

```c
TIM2->PSC = 16000-1;
```

Prescaler divides the timer clock.

If CPU clock =

```
16 MHz
```

Then timer frequency becomes:

```
16,000,000 / 16000 = 1000 Hz
```

Timer tick:

```
1 ms
```

---

# Configure Timer Period

```c
TIM2->ARR = 1000-1;
```

Timer counts:

```
0 → 999
```

Total ticks:

```
1000
```

Each tick = 1 ms

Total time:

```
1000 ms = 1 second
```

---

# Reset Timer Counter

```c
TIM2->CNT = 0;
```

Starts counting from zero.

---

# Start Timer

```c
TIM2->CR1 |= (1<<0);
```

Bit0:

```
CEN = Counter Enable
```

This starts the timer.

---

# Infinite Loop

```c
while(1)
{
}
```

The CPU remains here while hardware peripherals operate independently.

---

# Output Result

The timer toggles the output every **1 second**.

Waveform:

```
HIGH for 1 second
LOW for 1 second
```

Frequency:

```
0.5 Hz
```

---

# Learning Outcomes

From this example you learn:

* Register level programming
* Timer configuration
* GPIO alternate function
* Embedded system clock control
* Output compare mode

---

