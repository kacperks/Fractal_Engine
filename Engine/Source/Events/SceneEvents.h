#pragma once

#include "pch.h"
#include "Event.h"

struct AddEntityEvent : public Event {
    AddEntityEvent() = default;
    ~AddEntityEvent() = default;
    AddEntityEvent(std::string name) : _Name(name) { }
    std::string GetName() const { return _Name; }

private:
    std::string _Name;
};