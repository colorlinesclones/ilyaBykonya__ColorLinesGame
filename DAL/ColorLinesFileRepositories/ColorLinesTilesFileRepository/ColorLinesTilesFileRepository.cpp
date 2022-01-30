#include "ColorLinesTilesFileRepository.h"
#include <QTextStream>
#include <QFile>

ColorLinesTilesFileRepository::ColorLinesTilesFileRepository()
{
    QFile file{ "D:/Work/test/tiles.txt" };
    if(file.open(QIODevice::OpenModeFlag::ReadOnly) == false)
        throw std::runtime_error("Invalide tiles source file");

    QTextStream inStream{ &file };
    for(quint8 row = 0; row < 9; ++row) {
        for(quint8 column = 0; column < 9; ++column) {
            quint32 buffer;
            inStream >> buffer;
            if(buffer != 0)
                _mapData[row][column] = static_cast<TileColor>(static_cast<quint8>(buffer));
        }
    }

    file.close();
}
ColorLinesTilesFileRepository::~ColorLinesTilesFileRepository()
{
    QFile file{ "D:/Work/test/tiles.txt" };
    if(file.open(QIODevice::OpenModeFlag::WriteOnly) == false)
        throw std::runtime_error("Invalide tiles source file");

    QTextStream outStream{ &file };
    for(quint8 row = 0; row < 9; ++row){
        for(quint8 column = 0; column < 9; ++column){
            quint16 value = _mapData[row][column].has_value() ? static_cast<quint16>(_mapData[row][column].value()) : 0;
            outStream << value << ' ';
        }
    }

    file.close();
}

Tile ColorLinesTilesFileRepository::getValue(const Coordinate &key)
{
    if(key.row < 0 || key.column < 0 || key.row > 8 || key.column > 8)
        throw std::runtime_error("Invalid tiles file repository index");

    return _mapData[key.row][key.column];
}
void ColorLinesTilesFileRepository::setValue(const Coordinate &key, const Tile &value)
{
    if(key.row < 0 || key.column < 0 || key.row > 8 || key.column > 8)
        throw std::runtime_error("Invalid tiles file repository index");

    _mapData[key.row][key.column] = value;
}
