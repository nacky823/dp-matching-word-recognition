// SPDX-FileCopyrightText: 2023 Yuki NAGAKI youjiyongmu4@gmail.com
// SPDX-License-Identifier: GPL-2.0
#ifndef CALCULATOR_HPP_
#define CALCULATOR_HPP_

#include "file_data_reader.hpp"

class Calculator
{
private:
    double local_distance_[ROW_SIZE][ROW_SIZE];

    FileDataReader *reader_;

    void localDistance(uint8_t, uint8_t);

public:
    Calculator(FileDataReader*);
    void run();

};

#endif // CALCULATOR_HPP_