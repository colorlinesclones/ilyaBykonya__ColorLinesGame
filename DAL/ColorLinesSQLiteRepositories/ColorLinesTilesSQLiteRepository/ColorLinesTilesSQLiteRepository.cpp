#include "ColorLinesTilesSQLiteRepository.h"
#include <QSqlQuery>
#include <QVariant>

Tile ColorLinesTilesSQLiteRepository::getValue(const Coordinate &key)
{
    QSqlQuery query(QString("select value from GameState where key='%1_%2';").arg(key.row).arg(key.column));
    if(query.next() == false)
        return {};

    bool isValidCast;
    int tileColor = query.value(0).toInt(&isValidCast);
    return isValidCast ? static_cast<TileColor>(tileColor) : Tile{};
}

void ColorLinesTilesSQLiteRepository::setValue(const Coordinate &key, const Tile &value)
{
    QString queryString = QString("update GameState set value = %3 where key = '%1_%2';").arg(key.row).arg(key.column);

    if(value.has_value()) {
        queryString = queryString.arg(static_cast<int>(value.value()));
    } else {
        queryString = queryString.arg("null");
    }
    QSqlQuery query(queryString);
}
