#pragma once
#include <memory>
#include <vector>
#include "models/Project.h"
#include "models/Task.h"
#include "models/User.h"
#include "models/TimeSession.h"
#include "commands/Command.h"
#include "observers/Observer.h"

class TimeTrackerController {
public:
    TimeTrackerController();
    void addTestData();
    void runDemo();
    std::unique_ptr<Command> createStartTimerCommand(int taskId, int userId);
    std::unique_ptr<Command> createStopTimerCommand(int sessionId);
    std::vector<TimeSession> getSessions() const { return sessions; }
private:
    std::vector<Project> projects;
    std::vector<Task> tasks;
    std::vector<User> users;
    std::vector<TimeSession> sessions;
    int nextSessionId;
    Subject subject;
    LoggerObserver logger;
};