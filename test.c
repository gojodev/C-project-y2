#include <stdio.h>

unsigned int convertToPositive(int negativeNumber)
{
    unsigned int positiveNumber;

    // Two's complement conversion
    positiveNumber = (unsigned int)(-negativeNumber);

    return positiveNumber;
}

int main()
{
    int negativeNumber = -1547877604;
    unsigned int positiveNumber = convertToPositive(negativeNumber);

    printf("Positive representation of %d is %u\n", negativeNumber, positiveNumber);

    return 0;
}
    