#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

//Purpose: Turn a decimal number into binary using recursion

string BinaryCalc(int InputNumber, string ConvertedNumber) {
    if(InputNumber == 0) {
        //reverses the ConvertedNumber variable to correct it
        reverse(ConvertedNumber.begin(), ConvertedNumber.end());
        return ConvertedNumber;
    };

    int Remainder;

    Remainder = InputNumber % 2;

    string sRemainder = to_string(Remainder);
    ConvertedNumber.append(sRemainder);

    return BinaryCalc(InputNumber / 2, ConvertedNumber);
}

int main() {
    int UserNumber;
    string BinaryNumber;

    cout << "What number to do you want to translate into binary?: ";
    cin >> UserNumber;
    cout << UserNumber << " in binary is: " << BinaryCalc(UserNumber, BinaryNumber);

    return 0;
}