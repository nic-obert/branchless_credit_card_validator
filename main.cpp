#include <iostream>
#include <string>

#include "bless.hh"
#include "bcstring.hh"

using namespace std;
using namespace utils;


bool isNumberString(const char* str) {
    usize len = bcstring::strlen(str);

    bfor(usize i = 0, i < len, i++, {

        bif(str[i] < '0' || str[i] > '9', {
            return false;
        });

    });

    return true;
}


int main() {

    string ccNumber;

    cout << "This program uses the Luhn Algorigthm to validate a CC number." << endl;
    cout << "You can enter 'exit' anytime to quit." << endl;
    
    loop:

        cout << "Please enter a CC number to validate: ";
        cin >> ccNumber;

        bif(ccNumber == "exit", {
            return 0;
        });

        bif(!isNumberString(ccNumber.c_str()), {

            cout << "Bad input! ";
            goto loop;

        });

        usize len = bcstring::strlen(ccNumber.c_str());
        int doubleEvenSum = 0;

        // Step 1 is to double every second digit, starting from the right. If it
        // results in a two digit number, add both the digits to obtain a single
        // digit number. Finally, sum all the answers to obtain 'doubleEvenSum'.

        bfor(int i = len - 2, i >= 0, i -= 2, {

            int dbl = ((ccNumber[i] - 48) * 2);

            bool x = dbl > 9;
            doubleEvenSum += dbl * !x + ((dbl / 10) + (dbl % 10)) * x;

        });

        // Step 2 is to add every odd placed digit from the right to the value
        // 'doubleEvenSum'.

        bfor(int i = len - 1, i >= 0, i -= 2, {

            doubleEvenSum += ccNumber[i] - 48;

        });

        // Step 3 is to check if the final 'doubleEvenSum' is a multiple of 10.
        // If yes, it is a valid CC number. Otherwise, not.

        const char* outputs[2] = {
            "invalid\0",
            "valid\0"
        };

        const char* output = outputs[doubleEvenSum % 10 == 0];

        cout << "CC number is " << output << endl;

        goto loop;
}

