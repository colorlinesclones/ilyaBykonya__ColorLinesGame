import QtQuick 2.15
import QtQuick.Controls 2.15


Dialog {
    modal: true
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
