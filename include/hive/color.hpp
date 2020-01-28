#pragma once

#include <string>

namespace Hive {
    enum class Color {
        Red,
        Blue,
        Undefined,
    };

    static const std::string colorStrings[] = {"RED", "BLUE", "UNDEFINED"};

    std::string ColorToString(Hive::Color color);

    Color ColorFromString(std::string colorAsString);
}