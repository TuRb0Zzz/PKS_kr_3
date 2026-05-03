#include "strategies/ExportStrategy.h"
#include <iostream>
#include <fstream>

void ConsoleExport::exportData(const std::vector<TimeSession>& sessions, const std::string&) {
    std::cout << "\n=== Report ===\n";
    for (const auto& s : sessions) {
        std::cout << "Session " << s.getId() << ": start=" << s.getStartTimeStr()
                  << " end=" << s.getEndTimeStr() << " dur=" << s.getDurationSeconds() << "s\n";
    }
}

void CSVExport::exportData(const std::vector<TimeSession>& sessions, const std::string& filename) {
    std::ofstream file(filename);
    if (!file) return;
    file << "ID,UserID,TaskID,Start,End,DurationSec\n";
    for (const auto& s : sessions) {
        file << s.getId() << "," << s.getUserId() << "," << s.getTaskId() << ","
             << s.getStartTimeStr() << "," << s.getEndTimeStr() << "," << s.getDurationSeconds() << "\n";
    }
    std::cout << "CSV exported to " << filename << std::endl;
}