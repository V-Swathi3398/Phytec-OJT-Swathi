/*
 * led.h
 *
 *  Created on: Apr 5, 2023
 *      Author: swathi
 */


#ifndef LED_H_
#define LED_H_

#define PERIPH_BASE 		(0x40000000UL)
#define AHB1PERIPH_OFFSET	(0x00020000UL)

#define AHB1PERIPH_BASE 	(PERIPH_BASE + AHB1PERIPH_OFFSET)
#define GPIOA_OFFSET			(0x0000UL)

#define GPIOA_BASE			(AHB1PERIPH_BASE + GPIOA_OFFSET)

#define RCC_OFFSET			(0x3800UL)
#define RCC_BASE			(AHB1PERIPH_BASE + RCC_OFFSET)

#define AHB1EN_R_OFFSET		(0x30UL)
#define RCC_AHB1EN_R		(*(volatile unsigned int *)(RCC_BASE + AHB1EN_R_OFFSET))

#define MODE_R_OFFSET		(0X00UL)
#define GPIOA_MODE_R		(*(volatile unsigned int *)(GPIOA_BASE + MODE_R_OFFSET))

#define OD_R_OFFSET			(0X14UL)
#define GPIOA_OD_R			(*(volatile unsigned int *)(GPIOA_BASE + OD_R_OFFSET))

#define GPIOAEN				(1U<<0)

#define PIN5				(1U<<5)
#define LED_PIN				 PIN5

void led_init(void);
void led_tog(void);

#endif /* LED_H_ */
