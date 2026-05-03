#include "factories/ReportFactory.h"
#include <iostream>

void SimpleReport::generate(const std::vector<TimeSession>& sessions) {
    std::cout << "\n--- SIMPLE REPORT ---\n";
    for (const auto& s : sessions) {
        std::cout << "Session " << s.getId() << " duration: " << s.getDurationSeconds() << " seconds\n";
    }
}

std::unique_ptr<Report> ReportFactory::createReport(const std::string& type) {
    if (type == "simple") return std::make_unique<SimpleReport>();
    return nullptr;
}