// SPDX-FileCopyrightText: 2023 Yuki NAGAKI youjiyongmu4@gmail.com
// SPDX-License-Identifier: GPL-2.0
#ifndef FILE_DATA_READER_HPP_
#define FILE_DATA_READER_HPP_

#include "common.hpp"

class FileDataReader
{
private:
    SampleData correct_data_;
    SampleData unknown_data_;

    void showOpenError(uint8_t, uint8_t);
    void loadDataFromFile(uint8_t, uint8_t, SampleData*);

#ifdef DEBUG_MODE
    void print(SampleData*);
#endif // DEBUG_MODE

public:
    void loadCorrectData(uint8_t);
    void loadUnknownData(uint8_t);
    SampleData getCorrectData();
    SampleData getUnknownData();
};

#endif // FILE_DATA_READER_HPP_