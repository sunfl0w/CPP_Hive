#pragma once

#include <string.h>

namespace Hive {
    enum class Color {
        Red,
        Blue,
        Undefined,
    };

    static const std::string colorStrings[] = {"RED", "BLUE", "UNDEFINED"};

    std::string ColorToString(Hive::Color color) {
        return colorStrings[(int)color];
    }
}