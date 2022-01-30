#include "ColorLinesScoreSQLiteRepository.h"
#include <QSqlQuery>
#include <QVariant>

std::optional<UserScore> ColorLinesScoreSQLiteRepository::getValue()
{
    QSqlQuery query("select value from GameState where key='score';");
    if(query.next() == false)
        return {};

    bool isValidCast;
    int userScore = query.value(0).toInt(&isValidCast);
    return isValidCast ? userScore : std::optional<UserScore>{};
}
void ColorLinesScoreSQLiteRepository::setValue(const std::optional<UserScore> &value)
{
    QString queryString = "update GameState set value = %1 where key = 'score';";
    if(value.has_value()) {
        queryString = queryString.arg(value.value());
    } else {
        queryString = queryString.arg("null");
    }
    QSqlQuery query(queryString);
}
