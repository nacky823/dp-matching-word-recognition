// SPDX-FileCopyrightText: 2023 Yuki NAGAKI youjiyongmu4@gmail.com
// SPDX-License-Identifier: GPL-2.0
#ifndef CALCULATOR_HPP_
#define CALCULATOR_HPP_

#include "file_data_reader.hpp"

class Calculator
{
private:
    FileDataReader *reader_;

public:
    Calculator(FileDataReader*);
    void run();

};

#endif // CALCULATOR_HPP_