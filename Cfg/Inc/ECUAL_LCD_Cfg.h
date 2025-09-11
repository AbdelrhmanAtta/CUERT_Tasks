/*
 * ECUAL_LCD_Cfg.h
 *
 *  Created on: Sep 5, 2025
 *      Author: archlinux
 */

#ifndef ECUAL_LCD_CFG_H_
#define ECUAL_LCD_CFG_H_


#include "stm32f1xx_hal.h"
#include "Std_DataTypes.h"


typedef struct
{
	// LCD Pin: D4
	GPIO_TypeDef * D4_GPIOx;
	uint16_t D4_PINx;

	// LCD Pin: D5
	GPIO_TypeDef * D5_GPIOx;
	uint16_t D5_PINx;

	// LCD Pin: D6
	GPIO_TypeDef * D6_GPIOx;
	uint16_t D6_PINx;

	// LCD Pin: D7
	GPIO_TypeDef * D7_GPIOx;
	uint16_t D7_PINx;

	// LCD Pin: EN
	GPIO_TypeDef * EN_GPIOx;
	uint16_t EN_PINx;

	// LCD Pin: RS
	GPIO_TypeDef * RS_GPIOx;
	uint16_t RS_PINx;

}LCD16X2_CfgType;

extern const LCD16X2_CfgType LCD16X2_CfgParam;


#endif /* ECUAL_LCD_CFG_H_ */
