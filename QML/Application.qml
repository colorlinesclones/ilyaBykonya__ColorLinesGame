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
                Text {
                    height: parent.height
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                    width: 100
                    color: "red"
                    text: game_model.userScore
                }
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

    //Делегат системы перемещений. Отвечает за подсветку
    //выбранного элемента и вызов функции перемещения
    Item {
        id: move_delegate
        property int firstTarget: -1

        function moveTile(targetRow) {
            if(firstTarget === -1) {
                firstTarget = targetRow;
            } else {
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
            onGameFinished:
            {
                var value = finallyScore;
                finish_game_dialog.gameFinished(finallyScore);
            }
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
                onClicked: move_delegate.moveTile(model.row)
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
    Dialog {
        modal: true
        id: finish_game_dialog
        standardButtons: DialogButtonBox.Ok
        x: (parent.width - width) / 2
        y: (parent.height - height) / 2


        function gameFinished(finishScore) {
            text_frame.text = "Result score: " + finishScore
            finish_game_dialog.visible = true;
        }

        Text {
            id: text_frame
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
        }
    }
}

