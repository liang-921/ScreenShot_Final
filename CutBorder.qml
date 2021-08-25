import QtQuick 2.0

Rectangle {
    property var target
    property int focusWidth: smallRect.width
    property int focusHeight: smallRect.height

    width: parent.width
    height: parent.height
    color: "transparent"
    border.width: 4
    border.color: "#000"

    FocusRect {
        id:smallRect
        mouseStyle: mouseLeftTop
        onPosChange: {

            if (target.x + x < target.x + target.width) {
                target.x += x
            }
            if (target.y + y < target.y + target.height) {
                target.y += y
            }
            if (target.width - x > 0) {
                target.width -= x
            }
            if (target.height - y > 0) {
                target.height -= y
            }
        }
    }

    FocusRect {
        mouseStyle: mouseTop
        x: (parent.width - width) / 2
        onPosChange: {
            if (target.y + y < target.y + target.height) {
                target.y += y
            }
            if (target.height - y > 0) {
                target.height -= y
            }
        }
    }

    FocusRect {
        mouseStyle: mouseRightTop
        x: parent.width - width
        onPosChange: {
            if (target.width + x > 0) {
                target.width += x
            }
            if (target.height - y > 0) {
                target.height -= y
            }
            if (target.y + y < target.y + target.height) {
                target.y += y
            }
        }
    }

    FocusRect {
        mouseStyle: mouseLeft
        y: (parent.height - height) / 2
        onPosChange: {
            if (target.x + x < target.x + target.width) {
                target.x += x
            }
            if (target.width - x > 0) {
                target.width -= x
            }
        }
    }

    FocusRect {
        mouseStyle: mouseRight
        x: parent.width - width
        y: (parent.height - height) / 2
        onPosChange: {
            if (target.width + x > 0) {
                target.width += x
            }
        }
    }

    FocusRect {
        mouseStyle: mouseLeftBottom
        y: parent.height - height
        onPosChange: {
            if (target.x + x < target.x + target.width) {
                target.x += x
            }
            if (target.width - x > 0) {
                target.width -= x
            }
            if (target.height + y > 0) {
                target.height += y
            }
        }
    }

    FocusRect {
        mouseStyle: mouseBottom
        x: (parent.width - width) / 2
        y: parent.height - height
        onPosChange: {
            if (target.height + y > 0) {
                target.height += y
            }
        }
    }

    FocusRect {
        mouseStyle: mouseRightBottom
        x: parent.width - width
        y: parent.height - height
        onPosChange: {
            if (target.width + x > 0) {
                target.width += x
            }
            if (target.height + y > 0) {
                target.height += y
            }
        }
    }
}
