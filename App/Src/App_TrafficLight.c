/*
 * ECUAL_TrafficLights.c
 *
 *  Created on: Sep 4, 2025
 *      Author: archlinux
 */

#include "../Inc/App_TrafficLight.h"

static volatile uint8_t stopButton = 0;
static volatile uint8_t emergencyButton = 1;
static uint8_t oldStopState = 1;
static uint8_t oldEmergencyState = 0;
static uint32_t lastTick = 0;
static volatile uint8_t lightState = 0;
static volatile float volt = 0;
static volatile uint8_t raw_4bit;
char volt_str[16];

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == EMERGENCY_BUTTON_Pin)
    {
    	emergencyButton ^= 1;
    }
    if(GPIO_Pin == STOP_BUTTON_Pin)
        stopButton ^= 1;
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    if (hadc->Instance == ADC1) {
    	uint16_t raw = HAL_ADC_GetValue(hadc);
        volt = (3.3 * raw) / 4095;
        raw_4bit = raw / 256;
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM2)
    {
        static uint8_t tickCount = 0;

        if(stopButton)
        {
			sprintf(volt_str, "%0.2fV", volt);
			ECUAL_LCD_4BitModeSetCursor(0, 1);
			ECUAL_LCD_4BitModeWriteString("   ");
			ECUAL_LCD_4BitModeSetCursor(0, 1);
			ECUAL_LCD_4BitModeWriteString(volt_str);

			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, raw_4bit & 0b0001);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, raw_4bit & 0b0010);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, raw_4bit & 0b0100);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, raw_4bit & 0b1000);
        }
        else
        {
			ECUAL_LCD_4BitModeSetCursor(0, 1);
			ECUAL_LCD_4BitModeWriteString("    ");
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
        }

        if(stopButton && emergencyButton)
        {
            switch (lightState)
            {
            case 0: HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_12); break;
            case 1: HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13); break;
            case 2: HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14); break;
            }

            tickCount++;
            if(tickCount >= 8)
            {
                tickCount = 0;
                lightState = (lightState + 1) % 3;
            }
        }
        else
        {
            tickCount = 0;
        }
    }
}


traffic_light_status_e App_TrafficLights(void)
{
    static traffic_light_status_e ret = TRAFFIC_OFF;
    uint32_t now = HAL_GetTick();

    if(stopButton)
    {
        ret = TRAFFIC_ON;

        /*if(now - lastTick >= 2000)
        {
            lastTick = now;
            lightState = (lightState + 1) % 3;
        }*/

        /*if(1 == emergencyButton)
        {
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, lightState == 0 ? GPIO_PIN_SET : GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, lightState == 1 ? GPIO_PIN_SET : GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, lightState == 2 ? GPIO_PIN_SET : GPIO_PIN_RESET);
        }*/
        if(0 == emergencyButton)
        {
        	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
        	lastTick = now;
        }

    	if(oldEmergencyState != emergencyButton || oldStopState != stopButton)
    	{
            if(1 == emergencyButton)
            {
            	ECUAL_LCD_4BitModeClear();
            	ECUAL_LCD_4BitModeWriteString("TRAFFIC: RUNNING");
            	TIM3->CCR1 = (TIM3->ARR +1) / 2;
            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
            }
            else if(0 == emergencyButton)
            {
            	ECUAL_LCD_4BitModeClear();
            	ECUAL_LCD_4BitModeWriteString("EMERGENCY");
            	TIM3->CCR1 = 3*(TIM3->ARR +1) / 4;
            }
            oldEmergencyState = emergencyButton;
            oldStopState = 1;
    	}
    }
    else
    {
    	if(oldStopState != stopButton)
    	{
    		ECUAL_LCD_4BitModeClear();
    		ECUAL_LCD_4BitModeWriteString("TRAFFIC: STOPPED");
        	emergencyButton = 1;
            oldEmergencyState = 0;
            oldStopState = stopButton;
            TIM3->CCR1 = 0;
    	}

        lastTick = now;
        ret = TRAFFIC_OFF;
    }


    return ret;
}

