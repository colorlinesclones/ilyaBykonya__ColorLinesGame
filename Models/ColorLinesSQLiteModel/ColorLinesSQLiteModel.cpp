#include "ColorLinesSQLiteModel.h"
#include "DAL/ColorLinesSQLiteRepositories/ColorLinesTilesSQLiteRepository/ColorLinesTilesSQLiteRepository.h"
#include "DAL/ColorLinesSQLiteRepositories/ColorLinesScoreSQLiteRepository/ColorLinesScoreSQLiteRepository.h"

ColorLinesSQLiteModel::ColorLinesSQLiteModel()
    :ColorLinesModel{ QSharedPointer<ColorLinesTilesSQLiteRepository>::create(), QSharedPointer<ColorLinesScoreSQLiteRepository>::create() }
    {
    }
