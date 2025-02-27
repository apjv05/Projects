#include <iostream>
#include <string>
#include <algorithm>

//Purpose: Turn a decimal number into binary using recursion

std::string BinaryCalc(int InputNumber, std::string ConvertedNumber) {
    //if the input number equals 0 it returns the number in binary
    if(InputNumber == 0) {
        //reverses the ConvertedNumber variable to correct it
        std::reverse(ConvertedNumber.begin(), ConvertedNumber.end());
        return ConvertedNumber;
    };

    int NewNumber, Remainder;

    //calculate new number
    NewNumber = InputNumber / 2;

    //find out what the remainder is
    Remainder = InputNumber % 2;

    //if it is one add one to the end of the string and loop
    if(Remainder == 1) {
        //convert Remainder into a string because append only accepts strings
        std::string sRemainder = std::to_string(Remainder);

        //put the remainder at the end of the converted number
        ConvertedNumber.append(sRemainder);

        //recursion
        return BinaryCalc(NewNumber, ConvertedNumber);
    }
    //if it is zero add zero to the end of the string and loop
    else {
        //convert Remainder into a string because append only accepts strings
        std::string sRemainder = std::to_string(Remainder);

        //put the remainder at the end of the converted number
        ConvertedNumber.append(sRemainder);

        //recursion
        return BinaryCalc(NewNumber, ConvertedNumber);
    }
}

int main() {
    int UserNumber;
    std::string BinaryNumber;

    std::cout << "What number to do you want to translate into binary?: ";
    std::cin >> UserNumber;
    std::cout << UserNumber << " in binary is: " << BinaryCalc(UserNumber, BinaryNumber);

    return 0;
}