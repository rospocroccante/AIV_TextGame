#pragma once

#include <string>

class BaseEntity {
public:
    explicit BaseEntity(std::string name) : name_(std::move(name)) {}
    virtual ~BaseEntity() = default;

    const std::string& getName() const { return name_; }

protected:
    std::string name_;
};
