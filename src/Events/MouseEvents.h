#pragma once

#include "Event.h"

constexpr int MOUSE_LEFT = 0;
constexpr int MOUSE_RIGHT = 1;
constexpr int MOUSE_MIDDLE = 2;

using MouseButton = int;
using MouseButtonState = std::bitset<3>;

struct MouseData : EventData {
    MouseButtonState buttons;
    double scrollX, scrollY = 0;
    double  lastX, lastY, posX, posY = 0;
};

// mouse events
struct MouseEvent : public Event {
    virtual ~MouseEvent() = default;
    MouseEvent(const MouseData& d) : scrollX(d.scrollX), scrollY(d.scrollY),
        lastX(d.lastX), lastY(d.lastY), posX(d.posX), posY(d.posY) { }

    inline const EventID GetID() const { return EventTypeID<MouseEvent>(); }

    inline const double PosX() const { return posX; }
    inline const double PosY() const { return posY; }

    inline const double SrollX() const { return scrollX; }
    inline const double SrollY() const { return scrollY; }

    inline const double DeltaX() const { return (lastX - posX); }
    inline const double DeltaY() const { return (lastY - posY); }

protected:
    double scrollX, scrollY;
    double  lastX, lastY, posX, posY;
};

// mouse down event
struct MousePressEvent : public MouseEvent {
    ~MousePressEvent() = default;
    MousePressEvent(const MouseData& data) : MouseEvent(data) { }
    inline const EventID GetID() const { return EventTypeID<MousePressEvent>(); }
};

// moue up event
struct MouseReleaseEvent : public MouseEvent {
    ~MouseReleaseEvent() = default;
    MouseReleaseEvent(const MouseData& data) : MouseEvent(data) { }
    inline const EventID GetID() const { return EventTypeID<MouseReleaseEvent>(); }
};

// motion event
class MouseMotionEvent : public MouseEvent {
public:
    ~MouseMotionEvent() = default;
    MouseMotionEvent(const MouseData& data) : MouseEvent(data) { }
    inline const EventID GetID() const { return EventTypeID<MouseMotionEvent>(); }
};

// scroll event
class MouseScrollEvent : public MouseEvent {
public:
    ~MouseScrollEvent() = default;
    MouseScrollEvent(const MouseData& data) : MouseEvent(data) { }
    inline const EventID GetID() const { return EventTypeID<MouseScrollEvent>(); }
};