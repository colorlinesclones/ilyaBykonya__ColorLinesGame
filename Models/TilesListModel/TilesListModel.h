#pragma once
#include "Entities/Entities.h"
#include <QAbstractItemModel>
#include <QList>

class TilesListModel: public QAbstractItemModel
{
protected:
    QList<Tile> _data;

public:
    TilesListModel() = default;
    TilesListModel(const QList<Tile>& data);

    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const override final;
    virtual QModelIndex parent(const QModelIndex &child) const override final;

    virtual int rowCount(const QModelIndex &parent) const override final;
    virtual int columnCount(const QModelIndex &parent) const override final;

    virtual bool insertRows(int row, int count, const QModelIndex &parent) override final;
    virtual bool insertColumns(int column, int count, const QModelIndex &parent) override final;
    virtual bool removeRows(int row, int count, const QModelIndex &parent) override final;
    virtual bool removeColumns(int column, int count, const QModelIndex &parent) override final;
    virtual bool moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild) override;
    virtual bool moveColumns(const QModelIndex &sourceParent, int sourceColumn, int count, const QModelIndex &destinationParent, int destinationChild) override;

protected:
    bool privateInsertRows(int row, int count);
    bool privateRemoveRows(int row, int count);
    bool privateMoveRows(int sourceRow, int count, int destinationRow);
};

