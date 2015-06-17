/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB� Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB� Code Configurator - v2.25
        Device            :  PIC16F1709
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 v1.34
        MPLAB             :  MPLAB X v2.35 or v3.00
*/

/*
Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*/

#include "mcc_generated_files/mcc.h"
#include "oled.h"

#define SPI_Write( x)       SPI_Exchange8bit( x)


void OLED_Command( uint8_t temp){
  OLED_CS_LAT = 0;
  OLED_DC_LAT = 0;
  SPI_Write( temp);
  OLED_CS_LAT = 1;
}


void OLED_Data( uint8_t temp){
  OLED_CS_LAT = 0;
  OLED_DC_LAT = 1;
  SPI_Write( temp);
  OLED_CS_LAT = 1;
}


void OLED_Initialize( void)
{
    OLED_RST_LAT = 0;
    __delay_ms(1000);
    OLED_RST_LAT = 1;
    __delay_ms(1000);
    OLED_Command(SSD1306_DISPLAYOFF);             //0xAE  Set OLED Display Off
    OLED_Command(SSD1306_SETDISPLAYCLOCKDIV);     //0xD5  Set Display Clock Divide Ratio/Oscillator Frequency
    OLED_Command(0x80);
    OLED_Command(SSD1306_SETMULTIPLEX);           //0xA8  Set Multiplex Ratio
    OLED_Command(0x27);
    OLED_Command(SSD1306_SETDISPLAYOFFSET);       //0xD3  Set Display Offset
    OLED_Command(0x00);
    OLED_Command(SSD1306_SETSTARTLINE);           //0x40  Set Display Start Line
    OLED_Command(SSD1306_CHARGEPUMP);             //0x8D  Set Charge Pump
    OLED_Command(0x14);                           //0x14  Enable Charge Pump
    // OLED_Command(SSD1306_SETSTARTLINE | 0x0);     //A0
    OLED_Command(SSD1306_COMSCANDEC);             //0xC8  Set COM Output Scan Direction
    OLED_Command(SSD1306_SETCOMPINS);             //0xDA  Set COM Pins Hardware Configuration
    OLED_Command(0x12);
    OLED_Command(SSD1306_SETCONTRAST);            //0x81   Set Contrast Control
    OLED_Command(0xAF);
    OLED_Command(SSD1306_SETPRECHARGE);           //0xD9   Set Pre-Charge Period
    OLED_Command(0x25);
    OLED_Command(SSD1306_SETVCOMDETECT);          //0xDB   Set VCOMH Deselect Level
    OLED_Command(0x20);
    OLED_Command(SSD1306_DISPLAYALLON_RESUME);    //0xA4   Set Entire Display On/Off
    OLED_Command(SSD1306_NORMALDISPLAY);          //0xA6   Set Normal/Inverse Display
    OLED_Command(SSD1306_DISPLAYON);              //0xAF   Set OLED Display On
} // OLED_Initialize


//Set page adress for Page Addressing Mode
void OLED_SetPage( uint8_t add)
{
    add = 0xB0 | add;
    OLED_Command( add);
}


//Set column adress for Page Addressing Mode
void OLED_SetColumn( uint8_t add)
{
    OLED_Command(( 0x10 | (add >> 4))); // SET_HIGH_COLUMN
    OLED_Command(( 0x0f & add));        // SET LOW_COLUMN
}


//Display picture for Page  Addressing Mode
void OLED_PutPicture( uint8_t *pic)
{
    unsigned char i,j;
    for( i=0; i<5; i++) // 5*8=40 pixel rows (actually 39)
    {
        OLED_SetPage( i);
        // OLED_SetColumn( 0x00);
        OLED_Command( 0x10);
        // SET_STARTLINE
        OLED_Command( 0x40);    // ?
        for( j=0; j<96; j++)  // 96 pixel columns
        {
            OLED_Data( pic[ i * 96 + j]);
        }
    }
}


void OLED_SetContrast( uint8_t temp)
{
    OLED_Command( SSD1306_SETCONTRAST);  
    OLED_Command( temp);                  // contrast step 1 to 256
}


uint8_t pic[]={
0xFF, 0xFF, 0x3F, 0x1F, 0x0F, 0x07, 0x07, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0xE3, 0xE3,
0x03, 0x03, 0x03, 0x03, 0xC3, 0xE3, 0xC3, 0x03, 0x03, 0x03, 0x03, 0xE3, 0xE3, 0x03, 0x03, 0x03,
0x03, 0x03, 0x03, 0x03, 0x03, 0xC3, 0xC3, 0x63, 0x63, 0x63, 0x63, 0x63, 0xE3, 0xE3, 0x03, 0x03,
0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0xE3, 0xE3, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
0x03, 0xE3, 0xE3, 0x03, 0x03, 0x03, 0xC3, 0xC3, 0x63, 0x63, 0x63, 0x63, 0xC3, 0xC3, 0x03, 0x03,
0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x07, 0x07, 0x0F, 0x1F, 0x3F, 0xFF, 0xFF,

0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,
0x1F, 0xF8, 0xC0, 0xFE, 0x1F, 0x00, 0x1F, 0xFE, 0xC0, 0xF8, 0x1F, 0x03, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xC0, 0x80, 0x80, 0x80, 0x80, 0x80, 0xFF, 0xFF, 0x00, 0x00,
0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 0xFF, 0xFF, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80,
0x80, 0xFF, 0xFF, 0x00, 0x00, 0x3F, 0xFF, 0xC0, 0x80, 0x80, 0x80, 0x80, 0xC0, 0xFF, 0x3F, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,

0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
0x80, 0x80, 0x81, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x81, 0x81, 0x01, 0x01, 0x80, 0x80,
0x01, 0x01, 0xC1, 0xC1, 0xC1, 0x81, 0x01, 0x01, 0x01, 0x00, 0x00, 0x81, 0xC1, 0xC1, 0xC1, 0x01,
0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,

0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31,
0x31, 0xFF, 0xFF, 0x00, 0x00, 0xF0, 0xF8, 0x1C, 0x0C, 0x0C, 0x1C, 0xF8, 0xF0, 0x00, 0x0C, 0x0C,
0x18, 0xFC, 0xFC, 0x00, 0x00, 0x04, 0x8C, 0xF8, 0x70, 0xE0, 0xFF, 0xFF, 0x00, 0x00, 0xFD, 0xFD,
0x00, 0x00, 0xFF, 0xFF, 0x03, 0x1F, 0xFC, 0xC0, 0x00, 0xC0, 0xFC, 0x1F, 0x03, 0xFF, 0xFF, 0x00,
0x00, 0x00, 0x00, 0x00, 0x0C, 0x3C, 0xF0, 0xC0, 0x00, 0xC0, 0xF0, 0x3C, 0x0C, 0x00, 0xF0, 0xF8,
0x1C, 0x0C, 0x0C, 0x18, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,

0xFF, 0xFE, 0xF8, 0xF0, 0xE0, 0xC0, 0xC0, 0x80, 0x80, 0x80, 0x86, 0x86, 0x86, 0x86, 0x86, 0x86,
0x86, 0x87, 0x87, 0x80, 0x80, 0x81, 0x83, 0x87, 0x86, 0x86, 0x87, 0x83, 0x81, 0x80, 0x80, 0x80,
0x80, 0x87, 0x87, 0x80, 0x80, 0x86, 0x87, 0x81, 0x80, 0x80, 0x87, 0x87, 0x80, 0x80, 0x87, 0x87,
0x80, 0x80, 0x87, 0x87, 0x80, 0x80, 0x81, 0x87, 0x86, 0x87, 0x81, 0x80, 0x80, 0x87, 0x87, 0x80,
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x81, 0x87, 0x9F, 0xBF, 0xB1, 0xB0, 0x80, 0x80, 0x81, 0x83,
0x87, 0x86, 0x86, 0x83, 0x87, 0x87, 0x80, 0x80, 0x80, 0xC0, 0xC0, 0xE0, 0xF0, 0xF8, 0xFE, 0xFF
};

/*
                         Main application
 */
void main(void)
{
    int i;
    
    // initialize the device
    SYSTEM_Initialize();
    //INTERRUPT_GlobalInterruptEnable();
    //INTERRUPT_PeripheralInterruptEnable();
    OLED_Initialize();

    while (1)
    {
        OLED_PutPicture( pic);
        __delay_ms( 2000);
        OLED_Command( SSD1306_INVERTDISPLAY);
        __delay_ms( 2000);
        OLED_Command( SSD1306_NORMALDISPLAY);
        __delay_ms( 2000);

       for( i=0xAF; i>0x00; i--){
            OLED_SetContrast( i);
            __delay_ms( 20);
       }
       for( i=0x00; i<0xAF; i++){
            OLED_SetContrast( i);
            __delay_ms( 20);
       }

    }
}

    /**
 End of File
*/