#include "ColorLinesModel.h"
#include <QGuiApplication>
#include <algorithm>
#include <random>
#include <QBrush>
#include <QColor>
#include <QTimer>

ColorLinesModel::ColorLinesModel(TilesRepository tilesRepository, ScoreRepository scoreRepository)
    :_tilesRepository{ tilesRepository },
     _scoreRepository{ scoreRepository }
    {
        bool isFirstStart = true;
        _userScore = _scoreRepository->getValue().value_or(0);
        for(qint32 row = 0; row < tableLineSize; ++row) {
            for(qint32 column = 0; column < tableLineSize; ++column) {
                auto value = _tilesRepository->getValue({ row, column });
                _data.push_back(value);
                if(value.has_value()){ isFirstStart = false; }
            }
        }

        if(isFirstStart) {
            addRandomTiles();
        }
    }
ColorLinesModel::~ColorLinesModel()
{
    _scoreRepository->setValue(_userScore);
    for(qint32 row = 0; row < tableLineSize; ++row)
        for(qint32 column = 0; column < tableLineSize; ++column)
            _tilesRepository->setValue({ row, column }, _data[row * tableLineSize + column]);
}

UserScore ColorLinesModel::getUserScore() const
{
    return _userScore;
}
QVariant ColorLinesModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid() == false)
        return {};

    switch (role)
    {
    case ColorLinesModelRoles::ModelTileColor:
    {
        if(_data[index.row()].has_value()== false)
            return QBrush{ QColor(0, 0, 0, 0) };

        switch (_data[index.row()].value())
        {
            case TileColor::Red: { return QBrush{ QColor(255, 0, 0) }; }
            case TileColor::Green: { return QBrush{ QColor(0, 255, 0) }; }
            case TileColor::Blue: { return QBrush{ QColor(0, 0, 255) }; }
            case TileColor::Yellow: { return QBrush{ QColor(255, 255, 0) }; }
            default: return QBrush{ QColor(0, 0, 0, 0) };
        }
    }
    case ColorLinesModel::ModelTileIsBusy:
    {
        return _data[index.row()].has_value();
    }
    default: return {};
    }
}
QHash<int, QByteArray> ColorLinesModel::roleNames() const
{
    //По этим именам qml будет доставать данные из модели
    QHash<int, QByteArray> roles;
    roles[ColorLinesModelRoles::ModelTileIsBusy] = "tile_is_busy";
    roles[ColorLinesModelRoles::ModelTileColor] = "tile_color";
    return roles;
}



void ColorLinesModel::moveToEmptyTile(int sourceRow, int targetRow)
{
    //Проверяем, чтобы перемещения шли только
    //от имеющих цвет клеток к пустым
    if(sourceRow == targetRow)
        return;
    if(_data[targetRow].has_value() == true)
        return;
    if(_data[sourceRow].has_value() == false)
        return;

    //Такие проверки нужны из-за неизбежных смещений по индексам
    //Я не нашёл сходу универсального способа сделать swap.
    //Хотя он скорее всего есть, над этим я чуть позже подумаю
    if(abs(sourceRow - targetRow) == 1) {
        int maxRow = std::max(targetRow, sourceRow);
        int minRow = std::min(targetRow, sourceRow);

        beginMoveRows({}, maxRow, maxRow, {}, minRow);
        _data[targetRow] = _data[sourceRow];
        _data[sourceRow].reset();
        endMoveRows();
    } else {
        removeRow(targetRow);
        if(targetRow > sourceRow) {
            beginMoveRows({}, sourceRow, sourceRow, {}, targetRow);
            privateMoveRows(sourceRow, 1, targetRow - 1);
            endMoveRows();
        } else {
            moveRow({}, sourceRow - 1, {}, targetRow);
        }
        insertRow(sourceRow);
    }
}
void ColorLinesModel::endOfMove()
{
    deleteAllCombinations();
    addRandomTiles();
    deleteAllCombinations();//Второй раз удаляем на случай, если при добавлении появились новые комбинации
    if(allAreaIsFilled()) {
        restartGame();
    }
}
void ColorLinesModel::restartGame()
{
    emit gameFinished(_userScore);

    _userScore = 0;
    emit userScoreUpdated(_userScore);
    beginResetModel();
        for(int row = 0; row < _data.size(); ++row){ changeTileState(row, {}); }
        addRandomTiles();
    endResetModel();
}

bool ColorLinesModel::deleteAllCombinations()
{
    QList<std::array<Coordinate, completedLineSize>> completedCombinations;
    for(qint32 row_index = 0; row_index < tableLineSize; ++row_index) {
        for(qint32 column_index = 0; column_index < tableLineSize - completedLineSize + 1; ++column_index) {
            if(checkTilesLine({ row_index, column_index }, Qt::Orientation::Horizontal)) {
                std::array<Coordinate, completedLineSize> buffer;
                for(qint32 line_index = 0; line_index < completedLineSize; ++line_index)
                    buffer[line_index] = { row_index, column_index + line_index };

                completedCombinations.push_back(buffer);
            }
        }
    }
    for(qint32 row_index = 0; row_index < tableLineSize - completedLineSize + 1; ++row_index) {
        for(qint32 column_index = 0; column_index < tableLineSize; ++column_index) {
            if(checkTilesLine({ row_index, column_index }, Qt::Orientation::Vertical)) {
                std::array<Coordinate, completedLineSize> buffer;
                for(qint32 line_index = 0; line_index < completedLineSize; ++line_index)
                    buffer[line_index] = { row_index + line_index, column_index };

                completedCombinations.push_back(buffer);
            }
        }
    }

    for(const auto& line: completedCombinations) {
        deleteTiles(line);
        _userScore += completedLineScore;
    }

    if(completedCombinations.size() > 0) {
        emit this->userScoreUpdated(_userScore);
    }

    return (completedCombinations.size() > 0);
}
bool ColorLinesModel::checkTilesLine(Coordinate start, Qt::Orientation orientation) const
{
    if(tileAt(start).has_value() == false)
        return false;

    TileColor sourceColor = tileAt(start).value();
    for(int index = 0; index < completedLineSize; ++index) {
        Coordinate nextCoordinate = start;
        if(orientation == Qt::Orientation::Vertical) {
            nextCoordinate.row += index;
        } else {
            nextCoordinate.column += index;
        }

        if(tileAt(nextCoordinate).has_value() == false)
            return false;
        if(tileAt(nextCoordinate).value() != sourceColor)
            return false;
    }

    return true;
}
void ColorLinesModel::deleteTiles(const std::array<Coordinate, completedLineSize>& positions)
{
    for(const Coordinate& object: positions)
        if(object.row < 0 || object.row > tableLineSize || object.column < 0 || object.column > tableLineSize)
            return;

    for(const Coordinate& object: positions)
        changeTileState(object.row * tableLineSize + object.column, {});
}
void ColorLinesModel::addRandomTiles()
{
    QVector<qint32> freeTiles;
    for(qint32 index = 0; index < _data.size(); ++index)
        if(_data[index].has_value() == false)
            freeTiles.append(index);

    std::mt19937 generator{ std::random_device{}() };
    std::shuffle(freeTiles.begin(), freeTiles.end(), generator);


    for(int freeElementIndex = 0; freeElementIndex < 3 && freeElementIndex < freeTiles.size(); ++freeElementIndex) {
        _data[freeTiles[freeElementIndex]] = static_cast<TileColor>(generator() % 4 + 1);
    }
    dataChanged({}, index(80, 0, {}));
}
bool ColorLinesModel::allAreaIsFilled() const
{
    for(const auto& tile: _data)
        if(tile.has_value() == false)
            return false;

    return true;
}
void ColorLinesModel::changeTileState(int row, const Tile& newState)
{
    removeRow(row);
    insertRow(row);
    _data[row] = newState;
}

const Tile& ColorLinesModel::tileAt(const QModelIndex& index) const
{
    return _data[index.row()];
}
const Tile& ColorLinesModel::tileAt(const Coordinate& index) const
{
    return _data[index.row * tableLineSize + index.column];
}
Tile& ColorLinesModel::tileAt(const QModelIndex& index)
{
    return _data[index.row()];
}
Tile& ColorLinesModel::tileAt(const Coordinate& index)
{
    return _data[index.row * tableLineSize + index.column];
}
