#pragma once

#include <string>

namespace Hive {
    /**
     * @brief This class represents a few Colors for use in the game of Hive.
     * 
     */
    enum class Color {
        Red,
        Blue,
        Undefined,
    };

    /**
     * @brief An array that contains the values of the Color enum as strings.
     * 
     */
    static const std::string colorStrings[] = {"RED", "BLUE", "UNDEFINED"};

    /**
     * @brief Converts a Color to its string representation.
     * 
     * @param color The Color to convert.
     * @return std::string The string representation of the Color.
     */
    std::string ColorToString(Hive::Color color);

    /**
     * @brief Converts a string to a Color.
     * 
     * @param colorAsString The Color in its string representation.
     * @return The Color that corresponds to the string representation.
     */
    Color ColorFromString(std::string colorAsString);
}