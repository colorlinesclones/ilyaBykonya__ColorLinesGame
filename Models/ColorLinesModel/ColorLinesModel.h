#pragma once
#include "../TilesListModel/TilesListModel.h"
#include "DAL/IRepository/IRepository.h"
#include "Entities/Entities.h"
#include <QAbstractItemModel>
#include <QSharedPointer>
#include <qqml.h>
#include <array>

constexpr qint32 tableLineSize = 9;
constexpr qint32 completedLineSize = 5;
constexpr qint32 completedLineScore = 10;
using TilesRepository = QSharedPointer<IRepository<Coordinate, Tile>>;
using ScoreRepository = QSharedPointer<IRepository<void, std::optional<UserScore>>>;

class ColorLinesModel: public TilesListModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_ADDED_IN_MINOR_VERSION(1)
private:
    Q_PROPERTY(qint32 userScore READ getUserScore NOTIFY userScoreUpdated)
    TilesRepository _tilesRepository;
    ScoreRepository _scoreRepository;
    UserScore _userScore;

public:
    //*******************************************
    ColorLinesModel(TilesRepository tilesRepository = {}, ScoreRepository scoreRepository = {});
    ~ColorLinesModel();
    //*******************************************

    //*******************************************
    //Model elements
    enum ColorLinesModelRoles {
        ModelTileIsBusy = Qt::ItemDataRole::UserRole + 1,
        ModelTileColor
    };
    Q_ENUM(ColorLinesModelRoles)
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex& index, int role) const override;
    //*******************************************

    //*******************************************
    //Game elements
    Q_INVOKABLE void moveToEmptyTile(int sourceRow, int targetRow);
    Q_INVOKABLE void endOfMove();
    Q_INVOKABLE void restartGame();
private:
    bool deleteAllCombinations();
    bool checkTilesLine(Coordinate start, Qt::Orientation orientation) const;
    void deleteTiles(const std::array<Coordinate, completedLineSize>& positions);
    void addRandomTiles();
    bool allAreaIsFilled() const;
    void changeTileState(int row, const Tile& newState);
    //*******************************************

private:
    //Упрощение доступа к элементам через различные типы индексов
    const Tile& tileAt(const QModelIndex& index) const;
    const Tile& tileAt(const Coordinate& index) const;
    Tile& tileAt(const QModelIndex& index);
    Tile& tileAt(const Coordinate& index);


    //*******************************************
public:
    UserScore getUserScore() const;
signals:
    void userScoreUpdated(UserScore newScore);
    //*******************************************
    void gameFinished(quint32 finallyScore);
};

