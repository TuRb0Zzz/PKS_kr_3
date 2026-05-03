#include "models/TimeSession.h"
#include <iomanip>
#include <sstream>
using namespace std::chrono;

TimeSession::TimeSession(int id, int userId, int taskId)
    : id(id), userId(userId), taskId(taskId), active(true) {
    startTime = system_clock::now();
}

void TimeSession::stop() {
    if (active) {
        endTime = system_clock::now();
        active = false;
    }
}
int TimeSession::getId() const { return id; }
int TimeSession::getUserId() const { return userId; }
int TimeSession::getTaskId() const { return taskId; }
long long TimeSession::getDurationSeconds() const {
    if (active) return 0;
    return duration_cast<seconds>(endTime - startTime).count();
}
std::string TimeSession::getStartTimeStr() const {
    auto t = system_clock::to_time_t(startTime);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}
std::string TimeSession::getEndTimeStr() const {
    if (active) return "active";
    auto t = system_clock::to_time_t(endTime);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}