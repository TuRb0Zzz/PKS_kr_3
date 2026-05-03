#include "controllers/TimeTrackerController.h"
#include "strategies/ExportStrategy.h"
#include "factories/ReportFactory.h"
#include <iostream>
#include <chrono>
#include <thread>

TimeTrackerController::TimeTrackerController() : nextSessionId(1) {
    subject.attach(&logger);
}

void TimeTrackerController::addTestData() {
    projects.emplace_back(1, "Web App");
    tasks.emplace_back(1, 1, "Implement login");
    users.emplace_back(1, "Alice", "employee");
}

void TimeTrackerController::runDemo() {
    addTestData();
    Task* task = &tasks[0];
    User* user = &users[0];

    auto startCmd = createStartTimerCommand(task->getId(), user->getId());
    startCmd->execute();

    std::this_thread::sleep_for(std::chrono::seconds(2));

    int lastId = sessions.back().getId();
    auto stopCmd = createStopTimerCommand(lastId);
    stopCmd->execute();

    for (auto& s : sessions) subject.notify("Session completed", s);

    std::unique_ptr<ExportStrategy> consoleExp = std::make_unique<ConsoleExport>();
    consoleExp->exportData(sessions, "");

    std::unique_ptr<ExportStrategy> csvExp = std::make_unique<CSVExport>();
    csvExp->exportData(sessions, "report.csv");

    auto report = ReportFactory::createReport("simple");
    report->generate(sessions);
}

std::unique_ptr<Command> TimeTrackerController::createStartTimerCommand(int taskId, int userId) {
    Task* foundTask = nullptr;
    for (auto& t : tasks) if (t.getId() == taskId) foundTask = &t;
    User* foundUser = nullptr;
    for (auto& u : users) if (u.getId() == userId) foundUser = &u;
    return std::make_unique<StartTimerCommand>(foundTask, foundUser, sessions, nextSessionId);
}

std::unique_ptr<Command> TimeTrackerController::createStopTimerCommand(int sessionId) {
    return std::make_unique<StopTimerCommand>(sessionId, sessions);
}