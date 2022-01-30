import QtQuick 2.15
import QtQuick.Extras 1.4

Tumbler {
    id: tumbler_window
    property int number: 0
    TumblerColumn {
        id: tumbler_0
        model: 10
    }
    TumblerColumn {
        id: tumbler_1
        model: 10
    }
    TumblerColumn {
        id: tumbler_2
        model: 10
    }
    TumblerColumn {
        id: tumbler_3
        model: 10
    }
    TumblerColumn {
        id: tumbler_4
        model: 10
    }

    onNumberChanged: {
        tumbler_window.setCurrentIndexAt(0, number % 100000 / 10000, 400);
        tumbler_window.setCurrentIndexAt(1, number % 10000 / 1000, 400);
        tumbler_window.setCurrentIndexAt(2, number % 1000 / 100, 400);
        tumbler_window.setCurrentIndexAt(3, number % 100 / 10, 400);
        tumbler_window.setCurrentIndexAt(4, number % 10 / 1, 400);
    }
}

