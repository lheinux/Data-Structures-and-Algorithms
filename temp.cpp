#include <iostream>

using namespace std;

int main() {
    char input1;
    int input2;


    cout << "Enter 'c' to convert Fahrenheit to Celius. Enter 'f' to convert Celcius to Fahrenheit: ";
    cin >> input1;


    if (input1 == 'c')
    {
      cout << "Input your temperature in Fahrenheit: ";
      cin >> input2;
      cout << endl;
      cout << "Your temperature converted to Celsius is: " << (input2 - 32) * (5.0/9.0) << endl;
    }

    if (input1 == 'f')
  {
    cout << "Input your temperature in Celsius: ";
    cin >> input2;
    cout << "Your temperature converted to Fahrenheit is: " << (input2 * 9.0) / 5.0 + 32 << endl;
  }
  
    return 0;
}