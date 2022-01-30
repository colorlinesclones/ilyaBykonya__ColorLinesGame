#pragma once
#include "../../IRepository/IRepository.h"
#include "Entities/Entities.h"

class ColorLinesTilesSQLiteRepository: public IRepository<Coordinate, Tile>
{
public:
    virtual Tile getValue(const Coordinate &key) override;
    virtual void setValue(const Coordinate &key, const Tile &value) override;
};

