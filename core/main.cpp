#include "file_data_reader.hpp"

int main()
{
    FileDataReader reader;

    for (uint8_t file_num = 1; file_num <= NUM_OF_FILES; file_num++)
    {
        reader.loadCorrectData(file_num);
    }

    return 0;
}