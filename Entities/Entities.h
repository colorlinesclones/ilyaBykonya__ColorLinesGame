#pragma once
#include <optional>
#include <QPair>

using UserScore = quint32;
enum class TileColor: quint16 {
    Red = 1,
    Green = 2,
    Blue = 3,
    Yellow = 4,
};
struct Coordinate
{
    qint32 row;
    qint32 column;
};
using Tile = std::optional<TileColor>;
