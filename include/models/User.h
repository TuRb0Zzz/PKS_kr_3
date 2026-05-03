#pragma once
#include <string>

class User {
public:
    User(int id, const std::string& name, const std::string& role);
    int getId() const;
    std::string getName() const;
    std::string getRole() const;
private:
    int id;
    std::string name;
    std::string role;
};