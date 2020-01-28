#pragma once

#include "axialPosition.hpp"
#include "color.hpp"
#include "moveType.hpp"
#include "pieceType.hpp"

namespace Hive {
    /**
     * @brief This class represents a Move that can be performed on a GameState.
     * 
     */
    class Move {
    private:
        /**
         * @brief The MoveType of the Move.
         * 
         */
        MoveType moveType;

        /**
         * @brief The Color of the Piece that is beeing moved. Undefined for SkipMoves.
         * 
         */
        Color color;

        /**
         * @brief The starting Position of the Move. This is (0,0) for DeployMoves and SkipMoves.
         * 
         */
        AxialPosition startPosition;

        /**
         * @brief The destination of the moved Piece. This is (0,0) for SkipMoves.
         * 
         */
        AxialPosition destinationPosition;

        /**
         * @brief The PieceType of the moved Piece. Undefined for SkipMoves.
         * 
         */
        PieceType movedPieceType;

    public:
        /**
         * @brief Constructs a new and empty Move.
         * 
         */
        Move();

        /**
         * @brief Creates a deep copy of a given Move.
         * 
         * @param move The move to deep copy.
         */
        Move(const Move &move);

        /**
         * @brief Construct a new Move with given parameters.
         * 
         * @param moveType The MoveType of the Move.
         * @param color The Color of the Piece that is moved. This is Undefined for SkipMoves.
         * @param startPosition The starting Position of the Move. This is (0,0) for DeployMoves and SkipMoves.
         * @param destinationPosition The destination of the moved Piece. This is (0,0) for SkipMoves.
         * @param movedPieceType The PieceType of the moved Piece. Undefined for SkipMoves.
         */
        Move(const MoveType &moveType, const Color &color, const AxialPosition &startPosition, const AxialPosition &destinationPosition, const PieceType &movedPieceType);

        /**
         * @brief Gets the MoveType.
         * 
         * @return MoveType of the Move.
         */
        MoveType GetMoveType() const;

        /**
         * @brief Gets the Color of the moved Piece.
         * 
         * @return Color of the moved Piece.
         */
        Color GetColor() const;

        /**
         * @brief Gets the PieceType of the moved Piece.
         * 
         * @return PieceType of the moved Piece.
         */
        PieceType GetMovedPieceType() const;

        /**
         * @brief Gets the starting Position of the Move.
         * 
         * @return Starting position as an AxialPosition.
         */
        AxialPosition GetStartPosition() const;

        /**
         * @brief Gets the destination Position of the Move.
         * 
         * @return Destination position as an AxialPosition.
         */
        AxialPosition GetDestinationPosition() const;
    };
}  // namespace Hive