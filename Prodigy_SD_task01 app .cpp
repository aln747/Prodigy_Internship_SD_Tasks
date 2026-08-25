#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <array>

// Helper function to execute macOS AppleScript popups
std::string runAppleScript(const std::string& script) {
    std::string command = "osascript -e '" + script + "' 2>/dev/null";
    std::array<char, 256> buffer;
    std::string result;
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) return "";
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
    }
    pclose(pipe);
    // Trim newline
    if (!result.empty() && result.back() == '\n') result.pop_back();
    return result;
}

int main() {
    // 1. Popup to enter temperature value
    std::string tempStr = runAppleScript(
        "set dialogResult to display dialog \"Enter the temperature value:\" default answer \"\" with title \"Temperature Converter\"\n"
        "text returned of dialogResult"
    );

    if (tempStr.empty()) {
        return 0; // User canceled
    }

    double temp;
    try {
        temp = std::stod(tempStr);
    } catch (...) {
        runAppleScript("display alert \"Error\" message \"Invalid number entered. Please run again.\"");
        return 1;
    }

    // 2. Popup to choose the scale
    std::string unitChoice = runAppleScript(
        "choose from list {\"Celsius (°C)\", \"Fahrenheit (°F)\", \"Kelvin (K)\"} "
        "with title \"Temperature Converter\" "
        "with prompt \"Select the original unit of measurement:\""
    );

    if (unitChoice == "false" || unitChoice.empty()) {
        return 0; // User canceled
    }

    // 3. Perform conversions
    std::ostringstream resultStream;
    resultStream << std::fixed << std::setprecision(2);

    if (unitChoice.find("Celsius") != std::string::npos) {
        double f = (temp * 9.0 / 5.0) + 32.0;
        double k = temp + 273.15;
        resultStream << "Temperature: " << temp << " °C\\n\\n"
                     << "• Fahrenheit: " << f << " °F\\n"
                     << "• Kelvin: " << k << " K";
    } else if (unitChoice.find("Fahrenheit") != std::string::npos) {
        double c = (temp - 32.0) * 5.0 / 9.0;
        double k = c + 273.15;
        resultStream << "Temperature: " << temp << " °F\\n\\n"
                     << "• Celsius: " << c << " °C\\n"
                     << "• Kelvin: " << k << " K";
    } else if (unitChoice.find("Kelvin") != std::string::npos) {
        double c = temp - 273.15;
        double f = (c * 9.0 / 5.0) + 32.0;
        resultStream << "Temperature: " << temp << " K\\n\\n"
                     << "• Celsius: " << c << " °C\\n"
                     << "• Fahrenheit: " << f << " °F";
    }

    // 4. Show Result Dialog
    std::string resultScript = "display dialog \"" + resultStream.str() + "\" with title \"Conversion Results\" buttons {\"OK\"} default button \"OK\"";
    runAppleScript(resultScript);

    return 0;
}