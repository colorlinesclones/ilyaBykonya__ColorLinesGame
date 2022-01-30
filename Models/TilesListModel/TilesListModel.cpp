#include "TilesListModel.h"
#include <QDebug>

TilesListModel::TilesListModel(const QList<Tile>& data)
    :_data{ data }
    {
    }

QModelIndex TilesListModel::index(int row, int column, const QModelIndex &parent) const
{
    if(hasIndex(row, column, parent))
        return createIndex(row, column, nullptr);

    return {};
}
QModelIndex TilesListModel::parent(const QModelIndex &child) const
{
    return {};
}

int TilesListModel::rowCount(const QModelIndex &parent) const
{
    return _data.size();
}
int TilesListModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

bool TilesListModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if(privateInsertRows(row, count) == false)
        return false;

    beginInsertRows(parent, row, row + count - 1);
    endInsertRows();
    return true;
}
bool TilesListModel::moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild)
{
    if(privateMoveRows(sourceRow, count, destinationChild) == false)
        return false;

    beginMoveRows(sourceParent, sourceRow, sourceRow + count - 1, destinationParent, destinationChild);
    endMoveRows();
    return true;
}
bool TilesListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if(privateRemoveRows(row, count) == false)
        return false;

    beginRemoveRows(parent, row, row + count - 1);
    endRemoveRows();
    return true;
}

bool TilesListModel::privateInsertRows(int row, int count)
{
    if(row < 0 || row > _data.size())
        return false;

    for(int count_index = 0; count_index < count; ++count_index) {
        _data.insert(row + count_index, {});
    }
    return true;
}
bool TilesListModel::privateRemoveRows(int row, int count)
{
    if(row < 0 || row - count > _data.size())
        return false;

    for(int count_index = 0; count_index < count; ++count_index) {
        _data.removeAt(row);
    }

    return true;
}
bool TilesListModel::privateMoveRows(int sourceRow, int count, int destinationRow)
{
    if(sourceRow < 0 || sourceRow + count >= _data.size() || destinationRow < 0 || destinationRow + count >= _data.size())
        return false;

    for(int count_index = 0; count_index < count; ++count_index) {
        _data.move(sourceRow + count_index, destinationRow + count_index);
    }

    return true;
}

//Empty methods
bool TilesListModel::insertColumns(int column, int count, const QModelIndex &parent){}
bool TilesListModel::moveColumns(const QModelIndex &sourceParent, int sourceColumn, int count, const QModelIndex &destinationParent, int destinationChild){}
bool TilesListModel::removeColumns(int column, int count, const QModelIndex &parent){}

