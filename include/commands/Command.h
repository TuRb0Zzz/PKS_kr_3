#pragma once
#include <memory>
#include <vector>
#include "models/TimeSession.h"
#include "models/Task.h"
#include "models/User.h"

class Command {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() = default;
};

class StartTimerCommand : public Command {
public:
    StartTimerCommand(Task* task, User* user, std::vector<TimeSession>& sessions, int& nextId);
    void execute() override;
    void undo() override;
private:
    Task* task;
    User* user;
    std::vector<TimeSession>& sessions;
    int& nextId;
    int createdSessionId;
};

class StopTimerCommand : public Command {
public:
    StopTimerCommand(int sessionId, std::vector<TimeSession>& sessions);
    void execute() override;
    void undo() override;
private:
    int sessionId;
    std::vector<TimeSession>& sessions;
    long long oldDuration;
    bool wasActive;
};