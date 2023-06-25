// SPDX-FileCopyrightText: 2023 Yuki NAGAKI youjiyongmu4@gmail.com
// SPDX-License-Identifier: GPL-2.0
#include "calculator.hpp"
#include <math.h>

Calculator::Calculator(FileDataReader* reader)
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

#ifdef DEBUG_MODE
            print(data_c, data_u);
#endif // DEBUG_MODE
        }
    }
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

void Calculator::temp(SampleData c, SampleData u)
{
    uint8_t frame_c, frame_u;

    /* initial conditions */
    cumulative_distance_[0][0] = local_distance_[0][0];
    /* boundary conditions */
}

#ifdef DEBUG_MODE
void Calculator::print(SampleData c, SampleData u)
{
    printf("Correct file is %s", c.file_name);
    printf("Correct frame is %hhu\n", c.frame);
    printf("Correct last data is %lf\n", c.data[c.frame-1][COLUMN_SIZE-1]);
    printf("Unknown file is %s", u.file_name);
    printf("Unknown frame is %hhu\n", u.frame);
    printf("Unknown last data is %lf\n", u.data[u.frame-1][COLUMN_SIZE-1]);
    printf("Last local distance is %lf\n", local_distance_[c.frame-1][u.frame-1]);
}
#endif // DEBUG_MODE