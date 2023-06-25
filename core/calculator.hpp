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
    double word_distance_[NUM_OF_FILES];
    uint8_t correct_count_;

    FileDataReader *reader_;

    void initializeArray();
    void calculateLocalDistance(SampleData, SampleData);
    void calculateDPMatching(SampleData, SampleData, uint8_t);
    void evaluateMatching(uint8_t);

#ifdef DEBUG_MODE
    void print(SampleData, SampleData, uint8_t);
#endif // DEBUG_MODE

public:
    Calculator(FileDataReader*);
    void run();
};

#endif // CALCULATOR_HPP_