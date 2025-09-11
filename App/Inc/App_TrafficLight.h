/*
 * ECUAL_TrafficLights.h
 *
 *  Created on: Sep 4, 2025
 *      Author: archlinux
 */

#ifndef ECUAL_TRAFFICLIGHTS_H_
#define ECUAL_TRAFFICLIGHTS_H_


#include "stm32f1xx_hal.h"
#include "Std_DataTypes.h"
#include "ECUAL_LCD.h"
#include "main.h"


typedef enum
{
	TRAFFIC_OFF = 0,
	TRAFFIC_ON
}traffic_light_status_e;


/*
 * brief:   function that controls LED
 * param:   void
 * return:  TRAFFIC_OFF == 0 if off
 * 			TRAFFIC_ON == 1 if on
 */
traffic_light_status_e App_TrafficLights(void);


#endif /* ECUAL_TRAFFICLIGHTS_H_ */
