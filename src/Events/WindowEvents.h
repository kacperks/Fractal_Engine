#pragma once

#include "Event.h"

// key events
struct WindowEvent : public Event {
    WindowEvent() = default;
    virtual ~WindowEvent() = default;
    inline const EventID GetID() const { return EventTypeID<WindowEvent>(); }
};

// key pressed event
struct WindowCloseEvent : public Event {
    WindowCloseEvent() = default;
    ~WindowCloseEvent() = default;
    inline const EventID GetID() const { return EventTypeID<WindowCloseEvent>(); }
};

// key realesed event
struct WindowResizedEvent : public Event {
    ~WindowResizedEvent() = default;
    WindowResizedEvent(double w, double h): width(w), height(h) { }
    inline const EventID GetID() const { return EventTypeID<WindowResizedEvent>(); }

    inline const double Width() const { return width; }
    inline const double Height() const { return height; }

protected:
    double width, height;
};
