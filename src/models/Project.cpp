#include "models/Project.h"
Project::Project(int id, const std::string& name) : id(id), name(name) {}
int Project::getId() const { return id; }
std::string Project::getName() const { return name; }