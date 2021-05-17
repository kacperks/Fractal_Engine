#pragma once

#ifndef FR_APP_EVENTS
#define FR_APP_EVENTS

#include "Event.h"

struct UiEvent : public Event {
    UiEvent() = default;
    virtual ~UiEvent() = default;
    inline const EventID GetID() const { return EventTypeID<UiEvent>(); }
};

struct ViewportResizedEvent : public Event {
    ~ViewportResizedEvent() = default;
    ViewportResizedEvent(double w, double h) : width(w), height(h) { }
    inline const EventID GetID() const { return EventTypeID<ViewportResizedEvent>(); }

    inline const double Width() const { return width; }
    inline const double Height() const { return height; }

protected:
    double width, height;
};

#endif