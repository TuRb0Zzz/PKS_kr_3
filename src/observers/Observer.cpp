#include "observers/Observer.h"
#include <iostream>

void LoggerObserver::update(const std::string& event, const TimeSession& session) {
    std::cout << "[LOG] " << event << " Session ID=" << session.getId()
              << " User=" << session.getUserId() << " Task=" << session.getTaskId() << std::endl;
}

void Subject::attach(IObserver* obs) { observers.push_back(obs); }
void Subject::notify(const std::string& event, const TimeSession& session) {
    for (auto obs : observers) obs->update(event, session);
}