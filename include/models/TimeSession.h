#pragma once
#include <chrono>
#include <string>
class TimeSession {
public:
    TimeSession(int id, int userId, int taskId);
    void stop();
    int getId() const;
    int getUserId() const;
    int getTaskId() const;
    long long getDurationSeconds() const;
    std::string getStartTimeStr() const;
    std::string getEndTimeStr() const;
private:
    int id, userId, taskId;
    std::chrono::system_clock::time_point startTime;
    std::chrono::system_clock::time_point endTime;
    bool active;
};