#include "ColorLinesScoreFileRepository.h"
#include <QTextStream>
#include <QFile>

ColorLinesScoreFileRepository::ColorLinesScoreFileRepository()
{
    QFile file{ "D:/Work/test/score.txt" };
    if(file.open(QIODevice::OpenModeFlag::ReadOnly) == false)
        throw std::runtime_error("Invalide score source file");

    bool isValidCast;
    auto result = file.readAll().toULong(&isValidCast);
    if(isValidCast)
        _score = result;

    file.close();
}
ColorLinesScoreFileRepository::~ColorLinesScoreFileRepository()
{
    QFile file{ "D:/Work/test/score.txt" };
    if(file.open(QIODevice::OpenModeFlag::WriteOnly) == false)
        throw std::runtime_error("Invalide score source file");

    QTextStream outStream{ &file };
    outStream << (_score.has_value() ? _score.value() : 0);
    file.close();
}


std::optional<UserScore> ColorLinesScoreFileRepository::getValue()
{
    return _score;
}
void ColorLinesScoreFileRepository::setValue(const std::optional<UserScore> &value)
{
    _score = value;
}
