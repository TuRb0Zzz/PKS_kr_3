#pragma once
#include <string>
class Project {
public:
    Project(int id, const std::string& name);
    int getId() const;
    std::string getName() const;
private:
    int id;
    std::string name;
};