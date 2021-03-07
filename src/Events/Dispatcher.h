#pragma once

#include "Event.h"


class EventDispatcher {
    using EventCallback = std::function<void(const Event&)>;

public:    
    EventDispatcher& operator=(const EventDispatcher&) = delete;
    EventDispatcher(const EventDispatcher&) = delete;
    ~EventDispatcher() = default;

    static EventDispatcher& Ref() {
        static EventDispatcher ref;
        return ref;
    }

    template<typename T>
    void AddListener(EventCallback&& callback) {
        callbacks[EventTypeID<T>()].push_back(callback);
    }

    template<typename T>
    const T& Cast(const Event& e) {
        return static_cast<const T&>(e);
    }

    template<typename T>
    void Post(const T& e) const {  
        const EventID eventID = EventTypeID<T>();
        if (callbacks.find(eventID) == callbacks.end()) { return; }
        for (auto&& callback : callbacks.at(eventID)) { callback(e); }
    }

private:
    EventDispatcher() = default;

private:
    std::map<EventID, std::vector<EventCallback>> callbacks;
};

static EventDispatcher& Dispatcher = EventDispatcher::Ref();
