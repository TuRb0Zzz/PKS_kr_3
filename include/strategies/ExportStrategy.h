#pragma once
#include <vector>
#include <string>
#include "models/TimeSession.h"

class ExportStrategy {
public:
    virtual void exportData(const std::vector<TimeSession>& sessions, const std::string& dest) = 0;
    virtual ~ExportStrategy() = default;
};

class ConsoleExport : public ExportStrategy {
public:
    void exportData(const std::vector<TimeSession>& sessions, const std::string& dest) override;
};

class CSVExport : public ExportStrategy {
public:
    void exportData(const std::vector<TimeSession>& sessions, const std::string& dest) override;
};