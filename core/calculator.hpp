// SPDX-FileCopyrightText: 2023 Yuki NAGAKI youjiyongmu4@gmail.com
// SPDX-License-Identifier: GPL-2.0
#ifndef CALCULATOR_HPP_
#define CALCULATOR_HPP_

#include "file_data_reader.hpp"

class Calculator
{
private:
    double local_distance_[ROW_SIZE][ROW_SIZE];
    double cumulative_distance_[ROW_SIZE][ROW_SIZE];

    FileDataReader *reader_;

    void calculateLocalDistance(SampleData, SampleData);
    void temp(SampleData, SampleData);

#ifdef DEBUG_MODE
    void print(SampleData, SampleData);
#endif // DEBUG_MODE

public:
    Calculator(FileDataReader*);
    void run();
};

#endif // CALCULATOR_HPP_