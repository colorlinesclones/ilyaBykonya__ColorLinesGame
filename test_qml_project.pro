QT += quick sql
CONFIG += c++17
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        DAL/ColorLinesFileRepositories/ColorLinesScoreFileRepository/ColorLinesScoreFileRepository.cpp \
        DAL/ColorLinesFileRepositories/ColorLinesTilesFileRepository/ColorLinesTilesFileRepository.cpp \
        DAL/ColorLinesSQLiteRepositories/ColorLinesScoreSQLiteRepository/ColorLinesScoreSQLiteRepository.cpp \
        DAL/ColorLinesSQLiteRepositories/ColorLinesTilesSQLiteRepository/ColorLinesTilesSQLiteRepository.cpp \
        GameStarter/GameStarter.cpp \
        Models/ColorLinesFileModel/ColorLinesFileModel.cpp \
        Models/ColorLinesModel/ColorLinesModel.cpp \
        Models/ColorLinesSQLiteModel/ColorLinesSQLiteModel.cpp\
        Models/TilesListModel/TilesListModel.cpp \
        main.cpp

HEADERS += \
        DAL/IRepository/IRepository.h \
        DAL/ColorLinesFileRepositories/ColorLinesScoreFileRepository/ColorLinesScoreFileRepository.h \
        DAL/ColorLinesFileRepositories/ColorLinesTilesFileRepository/ColorLinesTilesFileRepository.h \
        DAL/ColorLinesSQLiteRepositories/ColorLinesScoreSQLiteRepository/ColorLinesScoreSQLiteRepository.h \
        DAL/ColorLinesSQLiteRepositories/ColorLinesTilesSQLiteRepository/ColorLinesTilesSQLiteRepository.h \
    GameStarter/GameStarter.h \
        Models/ColorLinesFileModel/ColorLinesFileModel.h \
        Models/ColorLinesModel/ColorLinesModel.h \
        Models/ColorLinesSQLiteModel/ColorLinesSQLiteModel.h \
        Models/TilesListModel/TilesListModel.h \
        Entities/Entities.h \

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

