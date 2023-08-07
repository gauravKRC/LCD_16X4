/*
 *  LCD_16X4.c
 *  Number of Lines: 4
 *  Number of Characters per Line: 16
 *  Character Size: 5x8 pixels
 *  Module Name:LCD_LM044L
 *
 *  Created on: Jul 30, 2023
 *      Author: indic
 */

#include "LCD_16x4.h"
#include "stm32f4xx_hal.h"
#include <math.h>
#include <stdio.h>

void write_nibble(uint8_t nibble) {
    for (uint8_t i = 0; i < 4; i++) {
        if (nibble & (1 << i)) {
            HAL_GPIO_WritePin(GPIOB, 1 << (i + 4), GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(GPIOB, 1 << (i + 4), GPIO_PIN_RESET);
        }
    }
}

void write_data(uint8_t num) {
    write_nibble(num >> 4); // Send higher nibble (D7-D4)
    HAL_GPIO_WritePin(GPIOA, RS, GPIO_PIN_SET); // Set RS for data mode
    HAL_GPIO_WritePin(GPIOA, EN, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(GPIOA, EN, GPIO_PIN_RESET);

    write_nibble(num & 0x0F); // Send lower nibble (D3-D0)
    HAL_GPIO_WritePin(GPIOA, EN, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(GPIOA, EN, GPIO_PIN_RESET);
}

void display_number(uint8_t row, uint8_t col,uint32_t num) {
	set_cursor_xy(row,col);
    // Count the number of digits in the number
    int num_digits = (num == 0) ? 1 : (int)(log10(num) + 1);
    // Ensure num_digits does not exceed the available columns on the LCD
    if (num_digits > LCD_COLS) {
        num_digits = LCD_COLS;
    }
    uint8_t digit[LCD_COLS]; // Array to store each digit
    // Extract individual digits from the number
    for (int i = num_digits - 1; i >= 0; i--) {
        digit[i] = num % 10;
        num /= 10;
    }
    // Convert each digit to its ASCII representation and display them on the LCD
    for (int i = 0; i < num_digits; i++) {
        write_data('0' + digit[i]);
    }
}

void Display_float(float num,int precision) {
	 // Convert the float number to a string representation
	    char num_str[precision + 6]; // +1 for null-terminator, +5 for additional characters
	    snprintf(num_str, sizeof(num_str), "%.*f", precision, num);

	    // Display each character of the string on the LCD
	    for (int i = 0; num_str[i]; i++) {
	        write_data(num_str[i]);
	    }
}

void display_string(uint8_t row, uint8_t col, const char *str) {
    // Set the cursor position for the starting row and column
	set_cursor_xy(row,col);
    // Display each character of the string on the LCD using write_data
    for (int i = 0; str[i]; i++) {
        write_data(str[i]);
    }
}

void cmd(uint8_t num) {
    write_nibble(num >> 4); // Send higher nibble (D7-D4)
    HAL_GPIO_WritePin(GPIOA, RS, GPIO_PIN_RESET); // Set RS for command mode
    HAL_GPIO_WritePin(GPIOA, EN, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(GPIOA, EN, GPIO_PIN_RESET);

    write_nibble(num & 0x0F); // Send lower nibble (D3-D0)
    HAL_GPIO_WritePin(GPIOA, EN, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(GPIOA, EN, GPIO_PIN_RESET);
}

void set_cursor_xy(uint8_t row, uint8_t col) {
    if (row < 4 && col < 16) {
        uint8_t row_offsets[] = {0x80, 0xC0, 0x94, 0xD4};
        cmd(0x80 | (row_offsets[row] + col));
    }
}

void LCD_INIT(void) {
    // Array to store the sequence of commands
    uint8_t commands[] = {
    		ML044L_Init_4bit_Mode,
			ML044L_FunctionSet_4bit_4line,
			ML044L_DisplayOnCursorOff,
			ML044L_EntryModeSet ,
			ML044L_ClearDisplay,
			ML044L_SetCursorLine1
    };
    // Loop to execute each command from the array
    for (size_t i = 0; i < sizeof(commands) / sizeof(commands[0]); i++) {
        cmd(commands[i]);
        HAL_Delay(5);
    }
    HAL_Delay(50);
}


