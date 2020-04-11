#pragma once

#include <vector>

namespace Hive {
    /**
     * @brief This clas represents an AxialPosition.
     * 
     */
    class AxialPosition {
    public:
        /**
         * @brief The unique ID of this Position ranging from 0 to 120 under normal circumstances.
         * 
         */
        unsigned int id;

        /**
         * @brief Constructs a new and empty Position.
         * 
         */
        AxialPosition();

        /**
         * @brief Creates a deep copy of a given Position.
         * 
         * @param axialPosition The Position to deep copy.
         */
        AxialPosition(const AxialPosition &axialPosition);

        /**
         * @brief Constructs a new Position with a given x- and y-position.
         * 
         * @param x The x-position.
         * @param y The y-position.
         */
        AxialPosition(int x, int y);

        /**
         * @brief Constructs a new Position with a given ID.
         * 
         * @param id ID of position.
         */
        AxialPosition(unsigned int id);

        /**
         * @brief Compares two Positions.
         * 
         * @param axialPosition The Position to compare against.
         * @return true If the Positions are equal.
         * @return false If the Positions are not equal.
         */
        bool operator==(const AxialPosition &axialPosition) const;

        /**
         * @brief Compares two Positions.
         * 
         * @param axialPosition The Position to compare against.
         * @return true If the Positions are not equal.
         * @return false If the Positions are equal.
         */
        bool operator!=(const AxialPosition &axialPosition) const;

        /**
         * @brief Gets the x-position of the position.
         * 
         * @return The x-position.
         */
        int GetX() const;

        /**
         * @brief Gets the y-position of the position.
         * 
         * @return The y-position.
         */
        int GetY() const;

        /**
         * @brief Gets the z-position of the Position.
         * 
         * @return The z-position.
         */
        int GetZ() const;

        /**
         * @brief Gets the unique ID of the Position.
         * 
         * @return The unique ID of the Position.
         */
        unsigned int GetID() const;

        /**
         * @brief Gets the distance to a given Position.
         * 
         * @param otherPosition The other Postion to get the distance to.
         * @return The distance between the two Positions.
         */
        int GetDistanceTo(const AxialPosition& otherPosition) const;

        /**
         * @brief Checks whether two Positions are neighbours.
         * 
         * @param otherPosition The other Postion to check against.
         * @return true If the two Positions are neighbours.
         * @return false If the two Positions are not neighbours.
         */
        bool IsNeighbourTo(const AxialPosition& otherPosition) const;

        /**
         * @brief Adds the x- and y-positions of two Positions together.
         * 
         * @param otherPosition The other Position to add.
         * @return The resulting AxialPosition.
         */
        AxialPosition Add(const AxialPosition& otherPosition) const;

        /**
         * @brief Subtracts the x- and y-positions of two Positions from one another.
         * 
         * @param otherPosition The other Position that subtracts.
         * @return The resulting AxialPosition.
         */
        AxialPosition Subtract(const AxialPosition& otherPosition) const;

        /**
         * @brief Gets the neighbouring Positions of the Position.
         * 
         * @return The neighbouring Positions in a vector.
         */
        std::vector<AxialPosition> GetNeighbouringPositions() const;

        /**
         * @brief Gets the neighbouring Positions of the Position including Positions that are not on the board.
         * 
         * @return The neighbouring Positions in a vector.
         */
        std::vector<AxialPosition> GetNeighbouringPositionsIncludingOutsideBoardPositions() const;

        /**
         * @brief Checks whether the Position is at the border of the Board.
         * 
         * @return true If the Position is at the border of the board.
         * @return false If the Position is not at the border of the board.
         */
        bool IsAtBorderOfBoard() const;

        /**
         * @brief Checks whether the Position is on the Board.
         * 
         * @return true If the Position is on the Board.
         * @return false If the Position is not on the Board.
         */
        bool IsOnBoard() const;

        /**
         * @brief Gets a new Position that is the result of subtracting the Position from the given one.
         * 
         * @param otherPosition The other Position to subtract from.
         * @return The resulting Position.
         */
        AxialPosition GetTranslationToOtherPosition(const AxialPosition& otherPosition) const;
    };
}  // namespace Hive