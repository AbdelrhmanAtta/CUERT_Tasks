/*
 * ECUAL_LCD.h
 *
 *  Created on: Sep 5, 2025
 *      Author: archlinux
 */

#ifndef ECUAL_INC_ECUAL_LCD_H_
#define ECUAL_INC_ECUAL_LCD_H_


/* -------------------- INCLUDES -------------------- */
#include "Utils.h"
#include "ECUAL_LCD_Cfg.h"


/* -------------------- FUNCTION DECLARTIONS -------------------- */
/*
 * @brief: 	init lcd in 4bit mode
 * @param:	void
 * @ret:	void
 */
void ECUAL_LCD_4BitModeInit(void);

/*
 * @brief: 	sends data to lcd
 * @param:	data to set
 * @ret:	void
 */
void ECUAL_LCD_4BitModeSendData(unsigned char);

/*
 * @brief: 	sends byte to lcd
 * @param:	byte to display
 * @ret:	void
 */
void ECUAL_LCD_4BitModeWriteByte(unsigned char);

/*
 * @brief: 	sends commands to lcd
 * @param:	command to send
 * @ret:	void
 */
void ECUAL_LCD_4BitModeCMD(unsigned char);

/*
 * @brief: 	sends commands to clear lcd
 * @param:	void
 * @ret:	void
 */
void ECUAL_LCD_4BitModeClear(void);

/*
 * @brief: 	displays strings
 * @param:	pointer to string
 * @ret:	void
 */
void ECUAL_LCD_4BitModeWriteString(const char*);

/*
 * @brief: 	sets cursor (starts from 0)
 * @param:	col
 * 			row
 * @ret:	void
 */
void ECUAL_LCD_4BitModeSetCursor(uint8_t, uint8_t);


#endif /* ECUAL_INC_ECUAL_LCD_H_ */
