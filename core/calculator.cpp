// SPDX-FileCopyrightText: 2023 Yuki NAGAKI youjiyongmu4@gmail.com
// SPDX-License-Identifier: GPL-2.0
#include "calculator.hpp"

Calculator::Calculator(FileDataReader* reader)
{
    reader_ = reader;
}

void Calculator::run()
{
    uint8_t file_num_a, file_num_b;

    for(file_num_a = 1; file_num_a <= NUM_OF_FILES; file_num_a++)
    {
        reader_->loadCorrectData(file_num_a);

        for(file_num_b = 1; file_num_b <= NUM_OF_FILES; file_num_b++)
        {
            reader_->loadUnknownData(file_num_b);
        }
    }
}