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

#include "lcdlib/util.h"
#include "HAL_LCD_I2C_Ctrl.h"
#include "HAL/HAL_I2C.h"


void LCDinit(char addr)
{
    LCDsendCommand(addr, LCD_4BIT_MODE | LCD_2_LINES | LCD_FONT_5x10);
    LCDsendCommand(addr, LCD_ENTRY_MODE);
    LCDdisplayOn(addr);
    LCDclear(addr);
};


void LCDenablePulse(char addr, char data)
{
    I2CWrite(addr, data | LCD_PIN_E);

    // delay >450ns
    delay_us(0.5);

    I2CWrite(addr, data & ~LCD_PIN_E);

    // delay >450ns
    delay_us(0.5);
};


void LCDsendCommand(char addr, char cmd)
{
    char up_bites = (cmd & 0xF0) & ~LCD_PIN_RS;
    char low_bites = (cmd << 4) & ~LCD_PIN_RS;

    LCDenablePulse(addr, up_bites);

    LCDenablePulse(addr, low_bites);
};


void LCDsendData(char addr, char data)
{
    char up_bites = (data & 0xF0) | LCD_PIN_RS;
    char low_bites = (data << 4) | LCD_PIN_RS;

    LCDenablePulse(addr, up_bites);

    LCDenablePulse(addr, low_bites);
};



void LCDsetCursorPosition(char addr, char line, char col)
{
    char address;

    if (line == 0)
        address = LCD_LINE_1;
    else if (line==1)
        address = LCD_LINE_2;
    else if (line==2)
        address = LCD_LINE_3;
    else if (line==3)
        address = LCD_LINE_4;
    else
        address = LCD_LINE_1;


    address |= col;

    LCDsendCommand(addr, 0x80 | address);
};


void LCDclear(char addr)
{
    LCDsendCommand(addr, LCD_DISP_CLEAR);
    LCDhome(addr);
};


void LCDhome(char addr)
{
    LCDsendCommand(addr, LCD_RETURN_HOME);
};


void LCDcursorBlink(char addr)
{
    LCDsendCommand(addr, LCD_CURSOR_BLINK);
};


void LCDcursorOff(char addr)
{
    LCDsendCommand(addr, LCD_DISP_ON);
};


void LCDcursorOn(char addr)
{
    LCDsendCommand(addr, LCD_CURSOR_ON);
};


void LCDdisplayOff(char addr)
{
    LCDsendCommand(addr, LCD_DISP_OFF);
};


void LCDdisplayOn(char addr)
{
    LCDsendCommand(addr, LCD_DISP_ON);
};

void LCDbacklightON(char addr)
{
    I2CWrite(addr, LCD_PIN_P3);
};


void LCDbacklightOFF(char addr)
{
    I2CWrite(addr, 0x00);
};


void LCDprint(char addr, char *text)
{
    char *c;
    c = text;

    while ((c != 0) && (*c != 0))
        {
            LCDsendData(addr, *c);
            c++;
        }
};




