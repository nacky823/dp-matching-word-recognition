// SPDX-FileCopyrightText: 2023 Yuki NAGAKI youjiyongmu4@gmail.com
// SPDX-License-Identifier: GPL-2.0
#include "calculator.hpp"
#include <math.h>

Calculator::Calculator(FileDataReader* reader) : word_distance_(), correct_count_(0)
{
    reader_ = reader;
}

void Calculator::run()
{
    uint8_t file_num_c, file_num_u;
    SampleData data_c, data_u;

    for(file_num_c = 1; file_num_c <= NUM_OF_FILES; file_num_c++)
    {
        reader_->loadCorrectData(file_num_c);

        for(file_num_u = 1; file_num_u <= NUM_OF_FILES; file_num_u++)
        {
            reader_->loadUnknownData(file_num_u);
            data_c = reader_->getCorrectData();
            data_u = reader_->getUnknownData();
            calculateLocalDistance(data_c, data_u);
            calculateDPMatching(data_c, data_u, file_num_u-1);

#ifdef DEBUG_MODE
            print(data_c, data_u, file_num_u-1);
#endif // DEBUG_MODE
        }
        evaluateMatching(file_num_c);
    }
    printf("\nThe accuracy rate is %hhu%%.\n", correct_count_);
}

void Calculator::calculateLocalDistance(SampleData c, SampleData u)
{
    uint8_t frame_c, frame_u, column;

    for(frame_c = 0; frame_c < c.frame; frame_c++)
    {
        for(frame_u = 0; frame_u < u.frame; frame_u++)
        {
            local_distance_[frame_c][frame_u] = 0;
            for(column = 0; column < COLUMN_SIZE; column++)
            {
                local_distance_[frame_c][frame_u] += pow((c.data[frame_c][column] - u.data[frame_u][column]), 2.0);
            }
            local_distance_[frame_c][frame_u] = sqrtl(local_distance_[frame_c][frame_u]);
        }
    }
}

void Calculator::calculateDPMatching(SampleData c, SampleData u, uint8_t file_num)
{
    uint8_t frame_c, frame_u;
    double vertical, diagonal, horizontal, min;

    /* Initial conditions */
    cumulative_distance_[0][0] = local_distance_[0][0];
    /* Boundary conditions */
    for(frame_c = 1; frame_c < c.frame; frame_c++)
    {
        cumulative_distance_[frame_c][0] = cumulative_distance_[frame_c-1][0] + local_distance_[frame_c][0];
    }
    for(frame_u = 1; frame_u < u.frame; frame_u++)
    {
        cumulative_distance_[0][frame_u] = cumulative_distance_[0][frame_u-1] + local_distance_[0][frame_u];
    }
    /* Other conditions */
    for(frame_c = 1; frame_c < c.frame; frame_c++)
    {
        for(frame_u = 1; frame_u < u.frame; frame_u++)
        {
            vertical = cumulative_distance_[frame_c][frame_u-1] + local_distance_[frame_c][frame_u];
            diagonal = cumulative_distance_[frame_c-1][frame_u-1] + (local_distance_[frame_c][frame_u] * WEIGHT);
            horizontal = cumulative_distance_[frame_c-1][frame_u] + local_distance_[frame_c][frame_u];
            min = vertical;
            if(diagonal < min) min = diagonal;
            if(horizontal < min) min = horizontal;
            cumulative_distance_[frame_c][frame_u] = min;
        }
    }
    /* Calculate word distance */
    word_distance_[file_num] = cumulative_distance_[c.frame-1][u.frame-1] / (c.frame + u.frame);
}

void Calculator::evaluateMatching(uint8_t correct_file_num)
{
    double min = word_distance_[0];
    uint8_t matching_file_num = 1;
    uint8_t file_num;

    for(file_num = 0; file_num < NUM_OF_FILES; file_num++)
    {
        if(word_distance_[file_num] < min)
        {
            min = word_distance_[file_num];
            matching_file_num = file_num + 1;
        }
    }
    if(matching_file_num != correct_file_num)
    {
        printf("\n!!! Did not match with the correct answer. !!!\n");
        printResult(correct_file_num, matching_file_num, min);
    }
    else
    {
        correct_count_++;

#ifdef DEBUG_MODE
        printf("\nMatched with the correct answer.\n");
        printResult(correct_file_num, matching_file_num, min);
#endif // DEBUG_MODE
    }
}

void Calculator::printResult(uint8_t correct_file_num, uint8_t matching_file_num, double min)
{
    printf("Correct file : " FILE_NAME_FORMAT "\n", CORRECT, correct_file_num);
    printf("Unknown file : " FILE_NAME_FORMAT "\n", UNKNOWN, matching_file_num);
    printf("Word distance is %f\n\n", min);
}

#ifdef DEBUG_MODE
void Calculator::print(SampleData c, SampleData u, uint8_t file_num)
{
    printf("Correct file is %s", c.file_name);
    printf("Correct frame is %hhu\n", c.frame);
    printf("Correct last data is %lf\n", c.data[c.frame-1][COLUMN_SIZE-1]);
    printf("Unknown file is %s", u.file_name);
    printf("Unknown frame is %hhu\n", u.frame);
    printf("Unknown last data is %lf\n", u.data[u.frame-1][COLUMN_SIZE-1]);
    printf("Last local distance is %lf\n", local_distance_[c.frame-1][u.frame-1]);
    printf("Last cumulative distance is %lf\n", cumulative_distance_[c.frame-1][u.frame-1]);
    printf("Word distance is %lf\n", word_distance_[file_num]);
}
#endif // DEBUG_MODE