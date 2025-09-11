/*
 * ECUAL_LCD.c
 *
 *  Created on: Sep 5, 2025
 *      Author: archlinux
 */

#include "ECUAL_LCD.h"

void ECUAL_LCD_4BitModeInit()
{
	// waits 50ms till volt rises
	while(HAL_GetTick() < 50);

	// start config
	HAL_GPIO_WritePin(LCD16X2_CfgParam.RS_GPIOx, LCD16X2_CfgParam.RS_PINx, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD16X2_CfgParam.EN_GPIOx, LCD16X2_CfgParam.EN_PINx, GPIO_PIN_RESET);

	// init sequence: 0x03 x3 then 0x02
	ECUAL_LCD_4BitModeSendData(0x03);
	HAL_GPIO_WritePin(LCD16X2_CfgParam.EN_GPIOx, LCD16X2_CfgParam.EN_PINx, GPIO_PIN_SET);
	DELAY_MS(5);
	HAL_GPIO_WritePin(LCD16X2_CfgParam.EN_GPIOx, LCD16X2_CfgParam.EN_PINx, GPIO_PIN_RESET);
	DELAY_MS(5);

	ECUAL_LCD_4BitModeSendData(0x03);
	HAL_GPIO_WritePin(LCD16X2_CfgParam.EN_GPIOx, LCD16X2_CfgParam.EN_PINx, GPIO_PIN_SET);
	DELAY_MS(5);
	HAL_GPIO_WritePin(LCD16X2_CfgParam.EN_GPIOx, LCD16X2_CfgParam.EN_PINx, GPIO_PIN_RESET);
	DELAY_MS(5);

	ECUAL_LCD_4BitModeSendData(0x03);
	HAL_GPIO_WritePin(LCD16X2_CfgParam.EN_GPIOx, LCD16X2_CfgParam.EN_PINx, GPIO_PIN_SET);
	DELAY_MS(5);
	HAL_GPIO_WritePin(LCD16X2_CfgParam.EN_GPIOx, LCD16X2_CfgParam.EN_PINx, GPIO_PIN_RESET);
	DELAY_MS(5);

	ECUAL_LCD_4BitModeSendData(0x02);
	HAL_GPIO_WritePin(LCD16X2_CfgParam.EN_GPIOx, LCD16X2_CfgParam.EN_PINx, GPIO_PIN_SET);
	DELAY_MS(5);
	HAL_GPIO_WritePin(LCD16X2_CfgParam.EN_GPIOx, LCD16X2_CfgParam.EN_PINx, GPIO_PIN_RESET);
	DELAY_MS(5);

	// function set, display on, clear, entry mode
	ECUAL_LCD_4BitModeCMD(0x28);
	ECUAL_LCD_4BitModeCMD(0x0C);
	ECUAL_LCD_4BitModeCMD(0x01);
	DELAY_MS(2);
	ECUAL_LCD_4BitModeCMD(0x06);
}

void ECUAL_LCD_4BitModeSendData(unsigned char data)
{
	if(data & 1) HAL_GPIO_WritePin(LCD16X2_CfgParam.D4_GPIOx, LCD16X2_CfgParam.D4_PINx, GPIO_PIN_SET);
	else HAL_GPIO_WritePin(LCD16X2_CfgParam.D4_GPIOx, LCD16X2_CfgParam.D4_PINx, GPIO_PIN_RESET);

	if(data & 2) HAL_GPIO_WritePin(LCD16X2_CfgParam.D5_GPIOx, LCD16X2_CfgParam.D5_PINx, GPIO_PIN_SET);
	else HAL_GPIO_WritePin(LCD16X2_CfgParam.D5_GPIOx, LCD16X2_CfgParam.D5_PINx, GPIO_PIN_RESET);

	if(data & 4) HAL_GPIO_WritePin(LCD16X2_CfgParam.D6_GPIOx, LCD16X2_CfgParam.D6_PINx, GPIO_PIN_SET);
	else HAL_GPIO_WritePin(LCD16X2_CfgParam.D6_GPIOx, LCD16X2_CfgParam.D6_PINx, GPIO_PIN_RESET);

	if(data & 8) HAL_GPIO_WritePin(LCD16X2_CfgParam.D7_GPIOx, LCD16X2_CfgParam.D7_PINx, GPIO_PIN_SET);
	else HAL_GPIO_WritePin(LCD16X2_CfgParam.D7_GPIOx, LCD16X2_CfgParam.D7_PINx, GPIO_PIN_RESET);
}

void ECUAL_LCD_4BitModeWriteByte(unsigned char data)
{
	unsigned char low, high;
	high = (data >> 4) & 0x0F;
	low  = data & 0x0F;

	HAL_GPIO_WritePin(LCD16X2_CfgParam.RS_GPIOx, LCD16X2_CfgParam.RS_PINx, GPIO_PIN_SET);

	ECUAL_LCD_4BitModeSendData(high);
	HAL_GPIO_WritePin(LCD16X2_CfgParam.EN_GPIOx, LCD16X2_CfgParam.EN_PINx, GPIO_PIN_SET);
	DELAY_MS(1);
	HAL_GPIO_WritePin(LCD16X2_CfgParam.EN_GPIOx, LCD16X2_CfgParam.EN_PINx, GPIO_PIN_RESET);
	DELAY_MS(1);

	ECUAL_LCD_4BitModeSendData(low);
	HAL_GPIO_WritePin(LCD16X2_CfgParam.EN_GPIOx, LCD16X2_CfgParam.EN_PINx, GPIO_PIN_SET);
	DELAY_MS(1);
	HAL_GPIO_WritePin(LCD16X2_CfgParam.EN_GPIOx, LCD16X2_CfgParam.EN_PINx, GPIO_PIN_RESET);
	DELAY_MS(1);
}

void ECUAL_LCD_4BitModeCMD(unsigned char cmd)
{
	unsigned char low, high;
	high = (cmd >> 4) & 0x0F;
	low  = cmd & 0x0F;

	HAL_GPIO_WritePin(LCD16X2_CfgParam.RS_GPIOx, LCD16X2_CfgParam.RS_PINx, GPIO_PIN_RESET);

	ECUAL_LCD_4BitModeSendData(high);
	HAL_GPIO_WritePin(LCD16X2_CfgParam.EN_GPIOx, LCD16X2_CfgParam.EN_PINx, GPIO_PIN_SET);
	DELAY_MS(1);
	HAL_GPIO_WritePin(LCD16X2_CfgParam.EN_GPIOx, LCD16X2_CfgParam.EN_PINx, GPIO_PIN_RESET);
	DELAY_MS(1);

	ECUAL_LCD_4BitModeSendData(low);
	HAL_GPIO_WritePin(LCD16X2_CfgParam.EN_GPIOx, LCD16X2_CfgParam.EN_PINx, GPIO_PIN_SET);
	DELAY_MS(1);
	HAL_GPIO_WritePin(LCD16X2_CfgParam.EN_GPIOx, LCD16X2_CfgParam.EN_PINx, GPIO_PIN_RESET);
	DELAY_MS(1);
}

void ECUAL_LCD_4BitModeClear(void)
{
	ECUAL_LCD_4BitModeCMD(0x01);
	DELAY_MS(2);
}

void ECUAL_LCD_4BitModeWriteString(const char* str)
{
	uint8_t i;
	for(i = 0; str[i] != '\0'; i++)
	{
		ECUAL_LCD_4BitModeWriteByte(str[i]);
	}
}

void ECUAL_LCD_4BitModeSetCursor(uint8_t col, uint8_t row)
{
	unsigned char addr;

	if(row == 0) addr = 0x80 + col;
	else addr = 0xC0 + col;

	ECUAL_LCD_4BitModeCMD(addr);
}
