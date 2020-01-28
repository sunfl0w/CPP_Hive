#include "color.hpp"

namespace Hive {
    std::string ColorToString(Hive::Color color) {
        return colorStrings[(int)color];
    }

    Color ColorFromString(std::string colorAsString) {
        if(colorAsString == "RED") {
            return Color::Red;
        } else if(colorAsString == "BLUE") {
            return Color::Blue;
        } else {
            return Color::Undefined;
        }
    }
}