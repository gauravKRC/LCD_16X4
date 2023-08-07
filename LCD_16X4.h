/*
 * LCD_16X4.h
 *  Number of Lines: 4
 *  Number of Characters per Line: 16
 *  Character Size: 5x8 pixels
 *  Module Name:LCD_LM044L
 *  Created on: Jul 30, 2023
 *      Author: indic
 */
#ifndef INC_LCD_16X4_H_
#define INC_LCD_16X4_H_

#include <stdint.h>

// Define the GPIO pins used for RS, EN, and data lines
#define RS GPIO_PIN_0
#define EN GPIO_PIN_1


//Define #rows & #columns
#define LCD_COLS 16
#define LCD_ROWS  4

// Define the LCD commands for 16x4 LCD
#define ML044L_Init_4bit_Mode          0x32  //initialize the LCD in 4-bit mode (This will send two nibbles)
#define ML044L_FunctionSet_4bit_4line  0x28  // Function Set: 4-bit mode, 4 lines, 5x8 font
#define ML044L_FunctionSet_8bit_4line  0x38  // Function Set: 8-bit mode, 4 lines, 5x8 font
#define ML044L_DisplayOffCursorOff     0x08  // Display off, Cursor off, Blinking off
#define ML044L_ClearDisplay            0x01  // Clear display and set cursor to home
#define ML044L_EntryModeSet            0x06  // Entry mode: Increment cursor, No display shift
#define ML044L_DisplayOnCursorOff      0x0C  // Display on, Cursor off, Blinking off
#define ML044L_DisplayOnCursorOn       0x0E  // Display on, Cursor on, Blinking off
#define ML044L_DisplayOnCursorBlink    0x0F  // Display on, Cursor blinking, Blinking on
#define ML044L_CursorShiftLeft         0x10  // Shift cursor left by one position
#define ML044L_CursorShiftRight        0x14  // Shift cursor right by one position
#define ML044L_DisplayShiftLeft        0x18  // Shift the entire display left
#define ML044L_DisplayShiftRight       0x1C  // Shift the entire display right
#define ML044L_SetCursorHome           0x02  // Return cursor to home position
#define ML044L_SetCursorLine1          0x80  // Set cursor to the beginning of the 1st line
#define ML044L_SetCursorLine2          0xC0  // Set cursor to the beginning of the 2nd line
#define ML044L_SetCursorLine3          0x94  // Set cursor to the beginning of the 3rd line
#define ML044L_SetCursorLine4          0xD4  // Set cursor to the beginning of the 4th line

// Function prototypes

/**********helper functions**********/
void write_nibble(uint8_t nibble);
void write_data(uint8_t num);
/**********primary functions********/
void LCD_INIT(void);
void cmd(uint8_t num);
void set_cursor_xy(uint8_t x, uint8_t y);
void display_number(uint8_t row, uint8_t col,uint32_t num);
void Display_float(float num,int precision);
void display_string(uint8_t row, uint8_t col, const char *str);


#endif /* INC_LCD_16X4_H_ */

