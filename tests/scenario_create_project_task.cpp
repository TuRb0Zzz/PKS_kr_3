#include <iostream>
#include "models/Project.h"
#include "models/Task.h"

int main() {
    std::cout << "=== Scenario: Create Project and Task ===\n";

    Project proj(1, "TimeTracker App");
    Task task1(1, proj.getId(), "Implement login");
    Task task2(2, proj.getId(), "Implement logout");
    Task task3(3, proj.getId(), "Generate reports");

    std::cout << "Project: " << proj.getName() << " (ID=" << proj.getId() << ")\n";
    std::cout << "Tasks:\n";
    std::cout << "  - " << task1.getTitle() << " (ID=" << task1.getId() << ")\n";
    std::cout << "  - " << task2.getTitle() << " (ID=" << task2.getId() << ")\n";
    std::cout << "  - " << task3.getTitle() << " (ID=" << task3.getId() << ")\n";

    return 0;
}