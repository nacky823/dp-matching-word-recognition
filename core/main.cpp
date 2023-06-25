// SPDX-FileCopyrightText: 2023 Yuki NAGAKI youjiyongmu4@gmail.com
// SPDX-License-Identifier: GPL-2.0
#include "calculator.hpp"

int main()
{
    FileDataReader reader;
    Calculator calculator(&reader);

    calculator.run();

    return 0;
}