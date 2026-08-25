#include <iostream>
#include <iomanip>  3
#include <cctype>   

using namespace std;

int main() {
    double temp;
    char unit;

    cout << "=== Temperature Converter ===\n";
    
    // Prompt for temperature value
    cout << "Enter the temperature value: ";
    if (!(cin >> temp)) {
        cout << "Error: Invalid input. Please enter a numerical value.\n";
        return 1; // Exit with an error code
    }

    // Prompt for the unit
    cout << "Enter the original unit (C for Celsius, F for Fahrenheit, K for Kelvin): ";
    cin >> unit;
    unit = toupper(unit); // Convert to uppercase to handle 'c', 'f', or 'k'

    // Format output to 2 decimal places
    cout << fixed << setprecision(2);
    
    // Perform conversions based on the unit
    if (unit == 'C') {
        double fahrenheit = (temp * 9.0 / 5.0) + 32.0;
        double kelvin = temp + 273.15;
        
        cout << "\nResult for " << temp << " °C:\n";
        cout << "• " << fahrenheit << " °F\n";
        cout << "• " << kelvin << " K\n";
    } 
    else if (unit == 'F') {
        double celsius = (temp - 32.0) * 5.0 / 9.0;
        double kelvin = celsius + 273.15;
        
        cout << "\nResult for " << temp << " °F:\n";
        cout << "• " << celsius << " °C\n";
        cout << "• " << kelvin << " K\n";
    } 
    else if (unit == 'K') {
        if (temp < 0) {
            cout << "\nWarning: Kelvin values do not physically exist below absolute zero (0 K).\n";
        }
        
        double celsius = temp - 273.15;
        double fahrenheit = (celsius * 9.0 / 5.0) + 32.0;
        
        cout << "\nResult for " << temp << " K:\n";
        cout << "• " << celsius << " °C\n";
        cout << "• " << fahrenheit << " °F\n";
    } 
    else {
        cout << "\nError: Invalid unit entered. Please use C, F, or K.\n";
    }

    return 0; // Successful execution
}