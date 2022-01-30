#pragma once


class GameStarter
{
public:
    static bool makeValidConfiguration();

private:
    static bool makeSqliteFile();
    static bool makeDatabaseConnection();
    static bool makeTableConfiguration();
    static bool makeTableData();
};

