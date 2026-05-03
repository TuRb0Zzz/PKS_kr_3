#pragma once
#include <string>
#include <vector>
#include "models/TimeSession.h"

class IObserver {
public:
    virtual void update(const std::string& event, const TimeSession& session) = 0;
    virtual ~IObserver() = default;
};

class LoggerObserver : public IObserver {
public:
    void update(const std::string& event, const TimeSession& session) override;
};

class Subject {
    std::vector<IObserver*> observers;
public:
    void attach(IObserver* obs);
    void notify(const std::string& event, const TimeSession& session);
};