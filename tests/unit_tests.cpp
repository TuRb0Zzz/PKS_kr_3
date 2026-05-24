#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include "models/User.h"
#include "models/Project.h"
#include "models/Task.h"
#include "models/TimeSession.h"
#include "commands/Command.h"
#include "strategies/ExportStrategy.h"
#include "factories/ReportFactory.h"
#include "observers/Observer.h"
#include "controllers/TimeTrackerController.h"
#include <vector>
#include <thread>
#include <chrono>
#include <fstream>
#include <sstream>

using namespace Catch::Matchers;

TEST_CASE("User class", "[user]") {
    SECTION("Constructor and getters") {
        User u(1, "Alice", "employee");
        REQUIRE(u.getId() == 1);
        REQUIRE(u.getName() == "Alice");
        REQUIRE(u.getRole() == "employee");
    }

    SECTION("Different ids") {
        User u1(10, "Bob", "manager");
        User u2(20, "Charlie", "admin");
        REQUIRE(u1.getId() != u2.getId());
    }

    SECTION("Empty name") {
        User u(2, "", "guest");
        REQUIRE(u.getName().empty());
    }

    SECTION("Long name") {
        std::string longName(100, 'A');
        User u(3, longName, "user");
        REQUIRE(u.getName() == longName);
    }

    SECTION("Role case sensitivity") {
        User u(4, "Dave", "Manager");
        REQUIRE(u.getRole() == "Manager");
    }

    SECTION("Multiple users distinct") {
        std::vector<User> users;
        for (int i = 0; i < 10; ++i) {
            users.emplace_back(i, "User" + std::to_string(i), "role");
        }
        for (int i = 0; i < 10; ++i) {
            REQUIRE(users[i].getId() == i);
        }
    }
}


TEST_CASE("Project class", "[project]") {
    SECTION("Constructor") {
        Project p(1, "Web App");
        REQUIRE(p.getId() == 1);
        REQUIRE(p.getName() == "Web App");
    }

    SECTION("Different projects") {
        Project p1(2, "Mobile");
        Project p2(3, "Backend");
        REQUIRE(p1.getId() != p2.getId());
        REQUIRE(p1.getName() != p2.getName());
    }

    SECTION("Empty name") {
        Project p(4, "");
        REQUIRE(p.getName().empty());
    }

    SECTION("Name with spaces") {
        Project p(5, "  My Project  ");
        REQUIRE(p.getName() == "  My Project  ");
    }

    SECTION("Id zero") {
        Project p(0, "Zero");
        REQUIRE(p.getId() == 0);
    }

    SECTION("Multiple projects") {
        std::vector<Project> projects;
        projects.emplace_back(1, "P1");
        projects.emplace_back(2, "P2");
        REQUIRE(projects.size() == 2);
    }
}

TEST_CASE("Task class", "[task]") {
    SECTION("Constructor") {
        Task t(1, 100, "Implement login");
        REQUIRE(t.getId() == 1);
        REQUIRE(t.getProjectId() == 100);
        REQUIRE(t.getTitle() == "Implement login");
    }

    SECTION("Different tasks") {
        Task t1(2, 200, "Fix bug");
        Task t2(3, 300, "Write docs");
        REQUIRE(t1.getId() != t2.getId());
        REQUIRE(t1.getProjectId() != t2.getProjectId());
    }

    SECTION("Empty title") {
        Task t(4, 400, "");
        REQUIRE(t.getTitle().empty());
    }

    SECTION("Title with special characters") {
        Task t(5, 500, "Task #123!");
        REQUIRE(t.getTitle() == "Task #123!");
    }

    SECTION("Long title") {
        std::string longTitle(200, 'X');
        Task t(6, 600, longTitle);
        REQUIRE(t.getTitle() == longTitle);
    }

    SECTION("Same project multiple tasks") {
        Task t1(7, 700, "Task A");
        Task t2(8, 700, "Task B");
        REQUIRE(t1.getProjectId() == t2.getProjectId());
        REQUIRE(t1.getId() != t2.getId());
    }
}

TEST_CASE("TimeSession class", "[timesession]") {
    SECTION("Constructor creates active session") {
        TimeSession s(1, 10, 20);
        REQUIRE(s.getId() == 1);
        REQUIRE(s.getUserId() == 10);
        REQUIRE(s.getTaskId() == 20);
        REQUIRE(s.getDurationSeconds() == 0);
        REQUIRE(s.getEndTimeStr() == "active");
    }

    SECTION("Stop sets duration") {
        TimeSession s(2, 1, 2);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        s.stop();
        REQUIRE(s.getDurationSeconds() >= 0);
        REQUIRE(s.getEndTimeStr() != "active");
    }

    SECTION("Stop twice does not change duration") {
        TimeSession s(3, 1, 2);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        s.stop();
        auto dur1 = s.getDurationSeconds();
        s.stop();
        auto dur2 = s.getDurationSeconds();
        REQUIRE(dur1 == dur2);
    }

    SECTION("Different sessions have different ids") {
        TimeSession s1(5, 1, 1);
        TimeSession s2(6, 1, 1);
        REQUIRE(s1.getId() != s2.getId());
    }

    SECTION("Start time string format") {
        TimeSession s(7, 1, 1);
        std::string startStr = s.getStartTimeStr();
        REQUIRE_THAT(startStr, Matches(R"(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2})"));
    }

    SECTION("Session not stopped returns zero duration") {
        TimeSession s(8, 1, 1);
        REQUIRE(s.getDurationSeconds() == 0);
    }
}

TEST_CASE("StartTimerCommand", "[command]") {
    SECTION("Execute creates new session") {
        std::vector<TimeSession> sessions;
        int nextId = 1;
        Task task(1, 100, "Test task");
        User user(1, "Tester", "employee");
        StartTimerCommand cmd(&task, &user, sessions, nextId);
        cmd.execute();
        REQUIRE(sessions.size() == 1);
        REQUIRE(sessions[0].getId() == 1);
        REQUIRE(sessions[0].getTaskId() == 1);
        REQUIRE(sessions[0].getUserId() == 1);
    }

    SECTION("Undo removes created session") {
        std::vector<TimeSession> sessions;
        int nextId = 10;
        Task task(1, 100, "Test task");
        User user(1, "Tester", "employee");
        StartTimerCommand cmd(&task, &user, sessions, nextId);
        cmd.execute();
        REQUIRE(sessions.size() == 1);
        cmd.undo();
        REQUIRE(sessions.empty());
    }

    SECTION("Multiple start commands") {
        std::vector<TimeSession> sessions;
        int nextId = 1;
        Task task(1, 100, "Task");
        User user(1, "U", "emp");
        StartTimerCommand cmd1(&task, &user, sessions, nextId);
        StartTimerCommand cmd2(&task, &user, sessions, nextId);
        cmd1.execute();
        cmd2.execute();
        REQUIRE(sessions.size() == 2);
        REQUIRE(sessions[0].getId() == 1);
        REQUIRE(sessions[1].getId() == 2);
    }
}

TEST_CASE("StopTimerCommand", "[command]") {
    SECTION("Execute stops session") {
        std::vector<TimeSession> sessions;
        int nextId = 1;
        Task task(1, 100, "Task");
        User user(1, "U", "emp");
        StartTimerCommand start(&task, &user, sessions, nextId);
        start.execute();
        int sessionId = sessions[0].getId();
        StopTimerCommand stop(sessionId, sessions);
        stop.execute();
        REQUIRE(sessions[0].getDurationSeconds() >= 0);
        REQUIRE(sessions[0].getEndTimeStr() != "active");
    }

    SECTION("Stop non-existent session does nothing") {
        std::vector<TimeSession> sessions;
        StopTimerCommand stop(999, sessions);
        REQUIRE_NOTHROW(stop.execute());
    }

    SECTION("Undo does not crash") {
        std::vector<TimeSession> sessions;
        int nextId = 1;
        Task task(1, 100, "Task");
        User user(1, "U", "emp");
        StartTimerCommand start(&task, &user, sessions, nextId);
        start.execute();
        StopTimerCommand stop(sessions[0].getId(), sessions);
        stop.execute();
        REQUIRE_NOTHROW(stop.undo());
    }
}

TEST_CASE("ConsoleExport", "[export]") {
    SECTION("Export to console does not crash") {
        std::vector<TimeSession> sessions;
        sessions.emplace_back(1, 1, 1);
        ConsoleExport exporter;
        REQUIRE_NOTHROW(exporter.exportData(sessions, ""));
    }

    SECTION("Empty sessions export") {
        std::vector<TimeSession> empty;
        ConsoleExport exporter;
        REQUIRE_NOTHROW(exporter.exportData(empty, ""));
    }
}

TEST_CASE("CSVExport", "[export]") {
    SECTION("Export creates file with correct content") {
        std::vector<TimeSession> sessions;
        sessions.emplace_back(1, 10, 20);
        sessions.back().stop();
        CSVExport exporter;
        exporter.exportData(sessions, "test.csv");
        std::ifstream file("test.csv");
        REQUIRE(file.good());
        std::string line;
        std::getline(file, line);
        REQUIRE(line.find("ID,UserID,TaskID") != std::string::npos);
        std::getline(file, line);
        REQUIRE(line.find("1,10,20") != std::string::npos);
        std::remove("test.csv");
    }

    SECTION("Export empty sessions creates file with header only") {
        std::vector<TimeSession> empty;
        CSVExport exporter;
        exporter.exportData(empty, "empty.csv");
        std::ifstream file("empty.csv");
        std::string line;
        std::getline(file, line);
        REQUIRE(line.find("ID") != std::string::npos);
        REQUIRE(file.peek() == EOF);
        std::remove("empty.csv");
    }
}

TEST_CASE("ReportFactory", "[factory]") {
    SECTION("Create simple report") {
        auto report = ReportFactory::createReport("simple");
        REQUIRE(report != nullptr);
    }

    SECTION("Unknown type returns nullptr") {
        auto report = ReportFactory::createReport("unknown");
        REQUIRE(report == nullptr);
    }

    SECTION("Simple report generate does not crash") {
        auto report = ReportFactory::createReport("simple");
        std::vector<TimeSession> sessions;
        sessions.emplace_back(1, 1, 1);
        REQUIRE_NOTHROW(report->generate(sessions));
    }
}

TEST_CASE("Observer pattern", "[observer]") {
    SECTION("LoggerObserver logs without crash") {
        LoggerObserver logger;
        TimeSession s(1, 1, 1);
        REQUIRE_NOTHROW(logger.update("test event", s));
    }

    SECTION("Subject notifies all observers") {
        Subject subject;
        LoggerObserver logger;
        subject.attach(&logger);
        TimeSession s(1, 1, 1);
        REQUIRE_NOTHROW(subject.notify("event", s));
    }
}

TEST_CASE("TimeTrackerController", "[controller]") {
    SECTION("Add test data creates non-empty projects/tasks/users") {
        TimeTrackerController ctrl;
        ctrl.addTestData();
        auto sessions = ctrl.getSessions();
        REQUIRE(sessions.empty());
        REQUIRE_NOTHROW(ctrl.runDemo());
    }

    SECTION("Create start and stop commands") {
        TimeTrackerController ctrl;
        ctrl.addTestData();
        auto startCmd = ctrl.createStartTimerCommand(1, 1);
        REQUIRE(startCmd != nullptr);
        startCmd->execute();
        auto sessions = ctrl.getSessions();
        REQUIRE(sessions.size() == 1);
        auto stopCmd = ctrl.createStopTimerCommand(sessions[0].getId());
        stopCmd->execute();
        REQUIRE(sessions[0].getDurationSeconds() >= 0);
    }
}