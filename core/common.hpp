// SPDX-FileCopyrightText: 2023 Yuki NAGAKI youjiyongmu4@gmail.com
// SPDX-License-Identifier: GPL-2.0
#ifndef COMMON_HPP_
#define COMMON_HPP_

#include <stdint.h>
#include <stdio.h>

#define DEBUG_MODE
// #define SAMPLE_DATA_VISUALIZATION
#define FILE_NAME_SIZE 20
#define WORD_SIZE 50
#define ROW_SIZE 255
#define COLUMN_SIZE 15
#define FILE_NAME_FORMAT "city%03d_%03d.txt"
#define PATH_FORMAT "../city_mcepdata/city%03d/" FILE_NAME_FORMAT
#define CORRECT 11 // file number of the correct data
#define UNKNOWN 21 // file number of the unknown data
#define NUM_OF_FILES 100

struct SampleData
{
    char file_name[FILE_NAME_SIZE];
    char word[WORD_SIZE];
    uint8_t frame;
    double data[ROW_SIZE][COLUMN_SIZE];
};

#endif // COMMON_HPP_