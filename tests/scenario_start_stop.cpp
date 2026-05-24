#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include "models/Task.h"
#include "models/User.h"
#include "models/TimeSession.h"
#include "commands/Command.h"

int main() {
    std::cout << "=== Start and Stop Timer ===\n";

    Task task(1, 100, "Write report");
    User user(1, "John", "employee");
    std::vector<TimeSession> sessions;
    int nextId = 1;

    std::cout << "Starting timer...\n";
    StartTimerCommand start(&task, &user, sessions, nextId);
    start.execute();

    std::cout << "Working for 2 seconds...\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << "Stopping timer...\n";
    StopTimerCommand stop(sessions[0].getId(), sessions);
    stop.execute();

    std::cout << "Session ID: " << sessions[0].getId() << "\n";
    std::cout << "Duration: " << sessions[0].getDurationSeconds() << " seconds\n";
    std::cout << "Start: " << sessions[0].getStartTimeStr() << "\n";
    std::cout << "End: " << sessions[0].getEndTimeStr() << "\n";

    return 0;
}