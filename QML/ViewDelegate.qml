import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    readonly property bool tileIsBusy: model.tile_is_busy
    readonly property color tileColor: model.tile_color
    function checkTileIsBusy() {
        return tileIsBusy;
    }

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
