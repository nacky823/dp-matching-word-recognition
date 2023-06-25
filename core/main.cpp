#include "calculator.hpp"

int main()
{
    FileDataReader reader;
    Calculator calculator(&reader);

    calculator.run();

    return 0;
}