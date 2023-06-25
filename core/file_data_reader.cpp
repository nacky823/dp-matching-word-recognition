// SPDX-FileCopyrightText: 2023 Yuki NAGAKI youjiyongmu4@gmail.com
// SPDX-License-Identifier: GPL-2.0
#include "file_data_reader.hpp"
#include <stdlib.h>

void FileDataReader::showOpenError(uint8_t correct_or_unknown, uint8_t file_num)
{
    char file_name[FILE_NAME_SIZE];
    char name_format[] = FILE_NAME_FORMAT;

    sprintf(file_name, name_format, correct_or_unknown, file_num);
    fprintf(stderr, "Failed to open file '%s'.\n", file_name);
}

void FileDataReader::loadDataFromFile(uint8_t correct_or_unknown, uint8_t file_num, SampleData* sample)
{
    char file_path[FILE_NAME_SIZE];
    char path_format[] = PATH_FORMAT;
    FILE* fp;
    uint8_t i, j;

    sprintf(file_path, path_format, correct_or_unknown, correct_or_unknown, file_num);
    fp = fopen(file_path, "r");
    if (fp == NULL)
    {
        showOpenError(correct_or_unknown, file_num);
        exit(EXIT_FAILURE);
    }
    fgets(sample->file_name, sizeof(sample->file_name), fp);
    fgets(sample->word, sizeof(sample->word), fp);
    fscanf(fp, "%hhu", &sample->frame);
    for (i = 0; i < sample->frame; i++)
    {
        for (j = 0; j < COLUMN_SIZE; j++)
        {
            fscanf(fp, "%lf", &sample->data[i][j]);
        }
    }
    fclose(fp);

#ifdef DEBUG_MODE
    print(sample);
#endif // DEBUG_MODE
}

#ifdef DEBUG_MODE
void FileDataReader::print(SampleData *sample)
{
    printf("\nOpened file %s", sample->file_name);
    printf("Word is %s", sample->word);
    printf("frame is %d\n", sample->frame);

#ifdef SAMPLE_DATA_VISUALIZATION
    uint8_t i, j;

    for (i = 0; i < sample->frame; i++)
    {
        for (j = 0; j < COLUMN_SIZE; j++)
        {
            printf("%lf ", sample->data[i][j]);
        }
        printf("\n");
    }
#endif // SAMPLE_DATA_VISUALIZATION
}
#endif // DEBUG_MODE

void FileDataReader::loadCorrectData(uint8_t file_num)
{
    loadDataFromFile(CORRECT, file_num, &correct_data_);
}

void FileDataReader::loadUnknownData(uint8_t file_num)
{
    loadDataFromFile(UNKNOWN, file_num, &unknown_data_);
}

SampleData FileDataReader::getCorrectData()
{
    return correct_data_;
}

SampleData FileDataReader::getUnknownData()
{
    return unknown_data_;
}