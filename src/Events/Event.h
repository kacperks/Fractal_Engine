#pragma once

class Event;
using EventID = size_t;

inline EventID CreateEventID() {
    static EventID typeID = 0u;
    return typeID++;
}

template<typename T>
inline EventID EventTypeID() {
    static_assert((std::is_base_of<Event, T>::value && !std::is_same<Event, T>::value), "Invalid template type");
    static const EventID typeID = CreateEventID();
    return typeID;
}

struct EventData {

};

struct Event {
    Event() = default;
    virtual ~Event() = default;
    virtual const EventID GetID() const = 0;
};