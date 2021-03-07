#pragma once

#include "Event.h"

using KeyCode = int;
using KeyBoard = std::bitset<1024>;

// key events
struct KeyEvent : public Event {
    KeyEvent() = default;
    virtual ~KeyEvent() = default;
    inline const EventID GetID() const { return EventTypeID<KeyEvent>(); }
};

// key pressed event
struct KeyPressedEvent : public KeyEvent {
    KeyPressedEvent() = default;
    ~KeyPressedEvent() = default;
    inline const EventID GetID() const { return EventTypeID<KeyPressedEvent>(); }
};

// key realesed event
struct KeyReleasedEvent : public KeyEvent {
    KeyReleasedEvent() = default;
    ~KeyReleasedEvent() = default;
    inline const EventID GetID() const { return EventTypeID<KeyReleasedEvent>(); }
};
