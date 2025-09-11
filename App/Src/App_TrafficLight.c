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
static uint8_t lightState = 0;


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == EMERGENCY_BUTTON_Pin)
    {
    	emergencyButton ^= 1;
    }
    if(GPIO_Pin == STOP_BUTTON_Pin)
        stopButton ^= 1;
}


traffic_light_status_e App_TrafficLights(void)
{
    static traffic_light_status_e ret = TRAFFIC_OFF;
    uint32_t now = HAL_GetTick();

    if(stopButton)
    {
        ret = TRAFFIC_ON;

        if(now - lastTick >= 2000)
        {
            lastTick = now;
            lightState = (lightState + 1) % 3;
        }

        if(1 == emergencyButton)
        {
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, lightState == 0 ? GPIO_PIN_SET : GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, lightState == 1 ? GPIO_PIN_SET : GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, lightState == 2 ? GPIO_PIN_SET : GPIO_PIN_RESET);
        }
        else
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
            }
            else if(0 == emergencyButton)
            {
            	ECUAL_LCD_4BitModeClear();
            	ECUAL_LCD_4BitModeWriteString("EMERGENCY");
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
    	}

        lastTick = now;
        ret = TRAFFIC_OFF;
    }

    return ret;
}

