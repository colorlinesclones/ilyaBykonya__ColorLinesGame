#include "ColorLinesFileModel.h"
#include "DAL/ColorLinesFileRepositories/ColorLinesTilesFileRepository/ColorLinesTilesFileRepository.h"
#include "DAL/ColorLinesFileRepositories/ColorLinesScoreFileRepository/ColorLinesScoreFileRepository.h"

ColorLinesFileModel::ColorLinesFileModel()
    :ColorLinesModel{ QSharedPointer<ColorLinesTilesFileRepository>::create(), QSharedPointer<ColorLinesScoreFileRepository>::create() }
    {
    }
