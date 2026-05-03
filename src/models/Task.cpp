#include "models/Task.h"
Task::Task(int id, int projectId, const std::string& title) : id(id), projectId(projectId), title(title) {}
int Task::getId() const { return id; }
int Task::getProjectId() const { return projectId; }
std::string Task::getTitle() const { return title; }