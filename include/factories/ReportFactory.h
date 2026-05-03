#pragma once
#include <memory>
#include <string>
#include <vector>
#include "models/TimeSession.h"

class Report {
public:
    virtual void generate(const std::vector<TimeSession>& sessions) = 0;
    virtual ~Report() = default;
};

class SimpleReport : public Report {
public:
    void generate(const std::vector<TimeSession>& sessions) override;
};

class ReportFactory {
public:
    static std::unique_ptr<Report> createReport(const std::string& type);
};