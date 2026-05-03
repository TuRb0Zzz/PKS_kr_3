#include "commands/Command.h"
#include <iostream>
StartTimerCommand::StartTimerCommand(Task* t, User* u, std::vector<TimeSession>& s, int& nid)
    : task(t), user(u), sessions(s), nextId(nid), createdSessionId(-1) {}
void StartTimerCommand::execute() {
    createdSessionId = nextId++;
    sessions.emplace_back(createdSessionId, user->getId(), task->getId());
    std::cout << "[START] Timer started for task '" << task->getTitle() << "'\n";
}
void StartTimerCommand::undo() {
    if (createdSessionId != -1) {
        sessions.erase(std::remove_if(sessions.begin(), sessions.end(),
            [this](const TimeSession& s) { return s.getId() == createdSessionId; }),
            sessions.end());
        std::cout << "[UNDO] Removed session " << createdSessionId << "\n";
    }
}

StopTimerCommand::StopTimerCommand(int sid, std::vector<TimeSession>& s)
    : sessionId(sid), sessions(s), oldDuration(0), wasActive(false) {}
void StopTimerCommand::execute() {
    for (auto& sess : sessions) {
        if (sess.getId() == sessionId) {
            wasActive = true;
            oldDuration = sess.getDurationSeconds();
            sess.stop();
            std::cout << "[STOP] Timer stopped. Duration: " << sess.getDurationSeconds() << " sec\n";
            break;
        }
    }
}
void StopTimerCommand::undo() {
    // Undo not fully implemented for simplicity
    std::cout << "[UNDO] Cannot undo stop without restoring time\n";
}