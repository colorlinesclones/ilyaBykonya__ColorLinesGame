#pragma once
#include "../ColorLinesModel/ColorLinesModel.h"


/*
Этот класс нужен только из-за пункта 2 в задании: "Модель должна объявлсять в QML.
Но т.к. я не могу создать ColorLinesModel без репозиториев, а тянуть репозитории
в QML -- очень плохое решение, то я принял решение сделать вот такой класс, который
выполнит эту задачу.

Он просто создаст модель с нужными репозиториями в своём конструкторе.
*/
class ColorLinesSQLiteModel: public ColorLinesModel
{
public:
    ColorLinesSQLiteModel();
};

