#pragma once
#include "../../IRepository/IRepository.h"
#include "Entities/Entities.h"
#include <array>

class ColorLinesTilesFileRepository: public IRepository<Coordinate, Tile>
{
private:
    std::array<std::array<Tile, 9>, 9>  _mapData;

public:
    ColorLinesTilesFileRepository();
    ~ColorLinesTilesFileRepository();

    virtual Tile getValue(const Coordinate &key) override;
    virtual void setValue(const Coordinate &key, const Tile &value) override;
};
