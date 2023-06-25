// SPDX-FileCopyrightText: 2023 Yuki NAGAKI youjiyongmu4@gmail.com
// SPDX-License-Identifier: GPL-2.0
#include "calculator.hpp"

Calculator::Calculator(FileDataReader* reader)
{
    reader_ = reader;
}

void Calculator::run()
{
    uint8_t file_num_c, file_num_u;

    for(file_num_c = 1; file_num_c <= NUM_OF_FILES; file_num_c++)
    {
        reader_->loadCorrectData(file_num_c);

        for(file_num_u = 1; file_num_u <= NUM_OF_FILES; file_num_u++)
        {
            reader_->loadUnknownData(file_num_u);
        }
    }
}

void Calculator::localDistance(uint8_t correct, uint8_t unknown)
{
    uint8_t frame_c = reader_->getCorrectData();
    uint8_t frame_u = reader_->getUnknownData();

    for(correct = 0; correct < frame_c; correct++)
    {
        for(unknown = 0; unknown < frame_u; unknown++)
        {

        }
    }
}