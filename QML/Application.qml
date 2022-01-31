import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import CustomElements 1.0


ApplicationWindow {
    width: 360
    height: 450
    visible: true

    header: Rectangle {
        height: 40
        width: parent.width
        ToolBar {
            anchors.fill: parent
            Row {
                anchors.fill: parent
                ToolButton {
                    onClicked: game_model.endOfMove();
                    text: "Skip move"
                }
                ToolButton {
                    onClicked: game_model.restartGame();
                    text: "Restart"
                }
                ToolButton {
                    onClicked: Qt.quit();
                    text: "Quit"
                }
            }
        }
    }
    footer: Rectangle {
        height: 40
        width: parent.width
        NumberDisplay {
            id: score_display
            anchors.fill: parent
            number: game_model.userScore
        }
    }

    //Делегат системы перемещений.
    //Отвечает за вызов функции перемещения
    Item {
        id: move_delegate
        property int firstTarget: -1

        function moveTile(targetRow) {
            if(firstTarget === -1) {
                firstTarget = targetRow;
                grid_view.itemAtIndex(firstTarget).color = "magenta";
            } else {
                grid_view.itemAtIndex(firstTarget).color = grid_view.itemAtIndex(firstTarget).tileColor;
                game_model.moveToEmptyTile(firstTarget, targetRow);
                firstTarget = -1;
            }
        }
    }
    GridView {
        id: grid_view
        clip: false
        boundsBehavior: Flickable.StopAtBounds

        readonly property int viewSize: { parent.width < parent.height ? parent.width : parent.height; }
        readonly property int tileSize: viewSize / 9
        cellHeight: tileSize
        cellWidth: tileSize
        height: viewSize
        width: viewSize

        model: ColorLinesModel{
            id: game_model
            onGameFinished: finish_game_dialog.gameFinished(finallyScore);
        }
        delegate: Rectangle {
            readonly property bool tileIsBusy: model.tile_is_busy
            readonly property color tileColor: model.tile_color

            color: tileColor
            implicitHeight: grid_view.tileSize
            implicitWidth: grid_view.tileSize
            radius: grid_view.tileSize / 2

            MouseArea {
                anchors.fill: parent
                onClicked: move_delegate.moveTile(model.row);


                onEntered: { parent.scale = 1.1; opacity: 0.1; }
                onExited: { parent.scale = 1.0; opacity: 1.0; }
                hoverEnabled: true
            }

            Behavior on scale {
                NumberAnimation { duration: 100 }
            }
            Behavior on color {
                PropertyAnimation { duration: 100 }
            }

            NumberAnimation on scale {
                id: zoom_animation;
                duration: 400
                easing.type: Easing.InOutQuad
                from: 0
                to: 1.0
            }
            NumberAnimation on scale {
                id: shrink_animation;
                duration: 400
                easing.type: Easing.InOutQuad
                from: 1.0
                to: 0
            }
            onTileIsBusyChanged: {
                if(tileIsBusy === true) {
                    zoom_animation.start();
                } else {
                    shrink_animation.start();
                }
            }
        }


        add: Transition {
            NumberAnimation { property: "opacity"; from: 0; to: 1.0; duration: 400 }
            NumberAnimation { property: "scale"; from: 0; to: 1.0; duration: 400 }
        }
        remove: Transition {
            NumberAnimation { property: "opacity"; from: 1.0; to: 0; duration: 400 }
            NumberAnimation { property: "scale"; from: 1.0; to: 0; duration: 400 }
        }
        displaced: Transition {
            NumberAnimation { properties: "x,y"; duration: 400; easing.type: Easing.OutBounce }
        }
        move: Transition {
            SequentialAnimation {
                NumberAnimation { properties: "x,y"; duration: 400 }
                ScriptAction { script: game_model.endOfMove(); }
            }
        }
    }

    //Диалоговое окно оконания хода
    FinishGameDialog{ id: finish_game_dialog }
}

