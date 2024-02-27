/** 
 * ---------------------------------------------------------------+ 
 * @desc        LCD HD44780 8-bit I/O I2C
 * ---------------------------------------------------------------+ 
 *
 * @author      Filipe Goncalves Bernardo
 * @datum       25.02.2024
 * @file        lcd.h
 * @tested      not yet
 *
 * ---------------------------------------------------------------+
 */

#include <stdio.h>


#ifndef __lcd__ 
#define __lcd__

    #define FALSE 0
    #define TRUE 1

    #define LCD_ADRESS          0x27

    #define LCD_PIN_RS          0x01 // Config = 0, Data = 1
    #define LCD_PIN_RW          0x02 // Write = 0, Read = 1
    #define LCD_PIN_E           0x04 // Enable bit
    #define LCD_PIN_P3          0x08 // BKL
    #define LCD_PIN_DB4         0x10
    #define LCD_PIN_DB5         0x20
    #define LCD_PIN_DB6         0x40
    #define LCD_PIN_DB7         0x80

    // HD44780 functions
    // Clear display
    #define LCD_DISP_CLEAR      0x01
    // Return home
    #define LCD_RETURN_HOME     0x02
    // Entry mode set
    #define LCD_ENTRY_MODE      0x06 
    // ON_OFF control
    #define LCD_DISP_OFF        0x08
    #define LCD_DISP_ON         0x0C
    #define LCD_CURSOR_ON       0x0E
    #define LCD_CURSOR_BLINK    0x0F
    // Cursor or display shift
    #define LCD_SHIFT           0x10
    #define LCD_CURSOR          0x00
    #define LCD_DISPLAY         0x08
    #define LCD_LEFT            0x00
    #define LCD_RIGHT           0x04
    // Fct set
    #define LCD_4BIT_MODE       0x20
    #define LCD_8BIT_MODE       0x30
    #define LCD_1_LINE          0x00
    #define LCD_2_LINES         0x08
    #define LCD_FONT_5x8        0x00
    #define LCD_FONT_5x10       0x04
    // First character's position of each line
    #define LCD_LINE_1          0x00
    #define LCD_LINE_2          0x40
    #define LCD_LINE_3          0x14
    #define LCD_LINE_4          0x54


    // Init LCD
    void LCDinit(char addr);

    // Enables data trasmition
    void LCDenablePulse(char addr, char data);

    // Send data
    void LCDsendData(char addr, char data);

    // Send config
    void LCDsendCommand(char addr, char cmd);

    // Settings
    void LCDsetCursorPosition(char addr, char line, char col);
    void LCDclear(char addr);
    void LCDhome(char addr);
    void LCDcursorBlink(char addr);
    void LCDcursorOn(char addr);
    void LCDcursorOff(char addr);
    void LCDdisplayOff(char addr);
    void LCDdisplayOn(char addr);
    void LCDbacklightON(char addr);
    void LCDbacklightOFF(char addr);

    // Print to LCD
    void LCDprint(char addr, char *text);


#endif
