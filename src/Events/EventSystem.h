#pragma once

#include "AppEvents.h"
#include "KeyEvents.h"
#include "MouseEvents.h"
#include "WindowEvents.h"
#include "Dispatcher.h"

class EventSystem {
public:
    EventSystem& operator=(const EventSystem&) = delete;
    EventSystem(const EventSystem&) = delete;
    ~EventSystem() = default;

    static EventSystem& Ref() {
        static EventSystem ref;
        return ref;
    }

    inline void Poll() { glfwPollEvents(); }

    inline KeyBoard& KeyboardRef() { return keys; }
    inline MouseData& MouseRef() { return mouse; }

    inline const bool IsKeyPressed(KeyCode key) const { return keys.test(key); }
    inline const bool IsMouseDown(MouseButton button) const { return mouse.buttons.test(button); }

private:
    EventSystem() = default;

private:
    KeyBoard keys;  
    MouseData mouse;
};

static EventSystem& Events = EventSystem::Ref();
