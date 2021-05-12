#pragma once

#include "Interpreter.h"

#include <iostream>

namespace FRL {
    void Print(std::string msg) {
        printf(msg.c_str());
    }
}