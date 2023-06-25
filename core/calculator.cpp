// SPDX-FileCopyrightText: 2023 Yuki NAGAKI youjiyongmu4@gmail.com
// SPDX-License-Identifier: GPL-2.0
#include "calculator.hpp"

Calculator::Calculator(FileDataReader* reader)
{
    reader_ = reader;
}

void Calculator::run()
{
    for(uint8_t file_num = 1; file_num <= NUM_OF_FILES; file_num++)
    {
        reader_->loadCorrectData(file_num);
    }
}