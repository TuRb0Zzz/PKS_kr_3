#pragma once
#include <string>
class Task {
public:
    Task(int id, int projectId, const std::string& title);
    int getId() const;
    int getProjectId() const;
    std::string getTitle() const;
private:
    int id, projectId;
    std::string title;
};