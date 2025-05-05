#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/***************************************************
Purpose: Convert a Decimal number to a binary number

Parameters: int InputNumber Decimal number that is to 
be converted into a binary number

return: Turns the InputNumber into a binary number
***************************************************/
string DecimalToBinary(int InputNumber) {
    string ConvertedNumber;
    while(InputNumber > 0) {
        int Remainder;

        Remainder = InputNumber % 2;
        InputNumber /= 2;

        string sRemainder = to_string(Remainder);
        ConvertedNumber.append(sRemainder);
    };

    reverse(ConvertedNumber.begin(), ConvertedNumber.end());
    return ConvertedNumber;
}

int main() {
    int UserNumber;

    cout << "What number to do you want to translate into binary?: ";
    cin >> UserNumber;
    cout << UserNumber << " in binary is: " << DecimalToBinary(UserNumber);

    return 0;
}