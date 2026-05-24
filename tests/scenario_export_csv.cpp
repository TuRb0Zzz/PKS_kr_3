#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>
#include "models/TimeSession.h"
#include "strategies/ExportStrategy.h"

int main() {
    std::cout << "=== Scenario: Export Report to CSV ===\n";

    std::vector<TimeSession> sessions;
    sessions.emplace_back(1, 10, 100);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    sessions.back().stop();

    sessions.emplace_back(2, 10, 101);
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    sessions.back().stop();

    sessions.emplace_back(3, 20, 100);
    std::this_thread::sleep_for(std::chrono::milliseconds(700));
    sessions.back().stop();

    CSVExport exporter;
    std::string filename = "scenario_report.csv";
    exporter.exportData(sessions, filename);

    std::cout << "Exported " << sessions.size() << " sessions to " << filename << std::endl;

    std::ifstream file(filename);
    if (file.is_open()) {
        std::cout << "\nFile content:\n";
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << "\n";
        }
        file.close();
    }

    return 0;
}