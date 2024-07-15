
/*

/*

Develop this outline into a complete program that meets all the requirements and test it
 with your data set. 

  File Reading: Read the power consumption data from power_data.csv.
Data Storage: Store the data in appropriate data structures for analysis.

Statistical Analysis:
Compute total power consumption for each day, week, and month.
Calculate average, minimum, and maximum power consumption values for each day, week, and month.
Identify peak usage times within each day.

Reporting:
Generate a summary report displaying daily, weekly, and monthly statistics.
Highlight periods of unusually high power consumption.

User Interface:
Provide a simple command-line interface to specify the input file and view the report.

Constraints:
The program should handle large data sets efficiently.
The program should be robust, handling errors in input data gracefully (e.g., missing or malformed records).


Visualize the power consumption data using a plotting library (e.g., matplotlib via C++ bindings).
Allow filtering of data to analyze specific date ranges or time periods.

Provide export options to save the report in different formats (e.g., CSV, JSON).
Hints:

Use standard libraries for file I/O (e.g., <fstream>), string manipulation (e.g., <string>), and date/time handling (e.g., <chrono>).
Consider using data structures like vectors or maps to store and organize the data.
Implement functions to encapsulate different parts of the analysis 
(e.g., reading data, calculating statistics, generating reports).

*/

#if 1

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <chrono>
#include <iomanip>

// Define a structure to hold power consumption data
struct PowerData {
    std::chrono::system_clock::time_point timestamp;
    double power;
};

// Function prototypes
bool readData(const std::string& filename, std::vector<PowerData>& data);
void analyzeData(const std::vector<PowerData>& data);
void generateReport(const std::map<std::string, double>& dailyStats,
                    const std::map<std::string, double>& weeklyStats,
                    const std::map<std::string, double>& monthlyStats);

int main() {
    std::string filename = "powerdata.csv";
    std::vector<PowerData> data;

    if (!readData(filename, data)) {
        std::cerr << "Failed to read data from file: " << filename << std::endl;
        return 1;
    }

    analyzeData(data);

    return 0;
}

bool readData(const std::string& filename, std::vector<PowerData>& data) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string timestampStr, powerStr;
        
        if (!std::getline(ss, timestampStr, ',') || !std::getline(ss, powerStr)) {
            continue;  // Skip malformed lines
        }

        std::tm tm = {};
        std::istringstream ts(timestampStr);
        ts >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");

        double power = std::stod(powerStr);

        PowerData entry;
        entry.timestamp = std::chrono::system_clock::from_time_t(std::mktime(&tm));
        entry.power = power;

        data.push_back(entry);
    }

    return true;
}

void analyzeData(const std::vector<PowerData>& data) {
    // Maps to store aggregated statistics
     

    
}

void generateReport(const std::map<std::string, double>& dailyStats,
                    const std::map<std::string, double>& weeklyStats,
                    const std::map<std::string, double>& monthlyStats) {
    // Print daily statistics
    std::cout << "Daily Power Consumption Report\n";
    for (const auto& [date, power] : dailyStats) {
        std::cout << date << ": " << power << " Watts\n";
    }

    // Print weekly statistics
    std::cout << "\nWeekly Power Consumption Report\n";
    for (const auto& [week, power] : weeklyStats) {
        std::cout << week << ": " << power << " Watts\n";
    }

    // Print monthly statistics
    std::cout << "\nMonthly Power Consumption Report\n";
    for (const auto& [month, power] : monthlyStats) {
        std::cout << month << ": " << power << " Watts\n";
    }
}

#endif
