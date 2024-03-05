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
#include "driverlib/sysctl.h"


void LCDinit(char addr)
{
    LCDcommand(addr, LCD_4BIT_MODE | LCD_2_LINES | LCD_FONT_5x10);
    LCDdisplayOff(addr);
    LCDclear(addr);
    SysCtlDelay(SysCtlClockGet() / (5000 * 3)); // Delai d'attente
    LCDcommand(addr, LCD_ENTRY_MODE);
    LCDdisplayOn(addr);
};


void LCDenablePulse(char addr, char data)
{
    I2CWrite(addr, data | LCD_PIN_E);
    //delay >450ns, 200us
    SysCtlDelay(SysCtlClockGet() / (5000 * 3));

    I2CWrite(addr, data & ~LCD_PIN_E);
    //delay >450ns
    SysCtlDelay(SysCtlClockGet() / (5000 * 3));
};


void LCDcommand(char addr, char cmd)
{
    char up_bites = (cmd & 0xF0) & ~LCD_PIN_RS | LCD_PIN_P3;
    char low_bites = (cmd << 4) & ~LCD_PIN_RS | LCD_PIN_P3;

    I2CWrite(addr, up_bites);
    LCDenablePulse(addr, up_bites);

    I2CWrite(addr, low_bites);
    LCDenablePulse(addr, low_bites);
};


void LCDdata(char addr, char data)
{
    char up_bites = (data & 0xF0) |LCD_PIN_RS | LCD_PIN_P3;
    char low_bites = (data << 4) |LCD_PIN_RS | LCD_PIN_P3;

    I2CWrite(addr, up_bites);
    LCDenablePulse(addr, up_bites);

    I2CWrite(addr, low_bites);
    LCDenablePulse(addr, low_bites);
};



void LCDsetCursor(char addr, char line, char col)
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

    LCDcommand(addr, 0x80 | address);
};


void LCDclear(char addr)
{
    LCDcommand(addr, LCD_DISP_CLEAR);
    LCDhome(addr);
};


void LCDhome(char addr)
{
    LCDcommand(addr, LCD_RETURN_HOME);
};


void LCDcursorBlink(char addr)
{
    LCDcommand(addr, LCD_CURSOR_BLINK);
};


void LCDcursorOff(char addr)
{
    LCDcommand(addr, LCD_DISP_ON);
};


void LCDcursorOn(char addr)
{
    LCDcommand(addr, LCD_CURSOR_ON);
};


void LCDdisplayOff(char addr)
{
    LCDcommand(addr, LCD_DISP_OFF);
};


void LCDdisplayOn(char addr)
{
    LCDcommand(addr, LCD_DISP_ON);
};



void LCDprint(char addr, char *text) {
    while (*text) {
        LCDdata(addr, *text++);
    }
}
