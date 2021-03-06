import QtQuick 2.5
import QmlRecentDialog 1.0

Item{
    width: 300
    height: 50

    property string     iconPath: "value"
    property string     title: "title"
    property string     path: "path"
    property bool       isHovered: false
    property bool       isDeleteHovered: false
    property bool       isMoved: false
    property var        currentPos: "0,0"
    property bool       isPositionChanged: false
    property bool       isResult: false
    property string     fullPath

    Rectangle {
        id: hoveredRectangle
        width: parent.width
        height: parent.height
        z: 0
        color: "#0e3e64"
        visible: false
    }
    Timer {
        id: delaytimer
        interval: 500
        running: false
        repeat: false
        onTriggered: setTooltip();
    }
   Rectangle {
        id: tipMessageRectangle
        x: -1000
        width: fullPath.length * 6
        height: 28
        radius: 1
        border.color: "#acacad"
        opacity: 1
        z: 5
        color: "#ffffff"
        Text {
            id: tipText
            y: 5
            color: "#000000"
            text: qsTr(fullPath)
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 12
        }
    }

    Image {
        id: iconImage
        width: 25
        height: 25
        x: 15
        y: (parent.height - height) / 2
        z: 1
        source: iconPath
        fillMode: Image.PreserveAspectFit
    }

    Text {
        id: titleText
        x: iconImage.x + iconImage.width + 10
        y: 6
        z: 1
        color: "#ffffff"
        text: qsTr(title)
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
        font.pixelSize: 17
    }

    Text {
        id: pathText
        x: titleText.x
        y: titleText.y + titleText.height + 1
        z: 1
        width: parent.width - deleteItem.width - 50
        color: "#ffffff"
        text: qsTr(path)
        wrapMode: Text.WordWrap
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
        font.pixelSize: 12
    }

    Item {
        id: deleteItem
        width: 50
        height: 50
        x: parent.width - width
        y: (parent.height - height) / 2
        z: 3
        visible: false

        Rectangle {
            id: deleteHoveredRectangle
            anchors.fill: parent
            color:"#c75050"
            z: 0
            visible: false
        }

        Image {
            id: deleteImage
            width: 28
            height: 28
            x: (parent.width- width) / 2
            y: (parent.height - height) / 2
            z: 1
            fillMode: Image.PreserveAspectFit
            source: "../resources/icon_delete.png"
        }

        MouseArea {
            anchors.fill: parent
            z: 5
            onClicked: {
                var deleteObject = recentList.get(index)
                qmlMainWindow.deleteRecentList(deleteObject.titleText)
                recentList.remove(index)
                qmlMainWindow.saveRecentMgrToINI()
            }
            hoverEnabled: true
            onHoveredChanged: {
                isDeleteHovered = !isDeleteHovered
                if(isDeleteHovered) {
                    deleteItem.visible = true
                    hoveredRectangle.visible = true
                    deleteHoveredRectangle.visible = true
                }
                else {
                    deleteItem.visible = false
                    hoveredRectangle.visible = false
                    deleteHoveredRectangle.visible = false
                }
            }
        }
    }

    MouseArea {
        id: mouseArea
        x: 0
        z: 2
        width: parent.width
        height: parent.height
        hoverEnabled: true
        onHoveredChanged: {
            isHovered = !isHovered

            if(isHovered) {
                qmlMainWindow.sendCurrentIndex(index);
                fullPath = qmlMainWindow.getRecentFullPath()
                hoveredRectangle.visible = true
                deleteItem.visible = true
                delaytimer.restart();
            }
            else {
               delaytimer.stop();
                hoveredRectangle.visible = false
                deleteItem.visible = false
                tipMessageRectangle.x = -500;
            }
        }
        onClicked:{
//            recent.state = "collapsed"
            liveView.visible = true;
            openCameraViews();
            busyTimer.restart()

        }
        onPositionChanged: {
                isPositionChanged = !isPositionChanged;
                if(isPositionChanged){
                    delaytimer.restart();
                }else{
                     onClearHovered();
                }

        }

    }
    Timer {
        id: busyTimer
        interval: 100
        running: false
        repeat: false
        onTriggered:
        {
            onOpenProject();
        }
    }

    function setTooltip(){
        tipMessageRectangle.x = mouseArea.mouseX
        tipMessageRectangle.y = mouseArea.mouseY + 20
    }

    function onClearHovered(){
        tipMessageRectangle.x = -500;
    }
    function onOpenProject(){
        root.isTemplateCheck = false
        root.deleteIndex = qmlMainWindow.recentOpenIniPath(tipText.text)
        if (root.deleteIndex == -2) return;
        recent.state = "collapsed"
        if(root.deleteIndex >= 0)
        {
            recent.deleteRecentListItem()
            recent.setCurrentFile()
        }

        curMode = 1;
        toolbox.clearSelected();
        toolbox.clearSettingBox();
        backItem.visible = true
        forwardItem.visible = false;
        toolbox.showStartIamge();
        var recentFileList = recentList.get(index)
        qmlMainWindow.deleteCameraView()
        qmlMainWindow.deleteStitchView()
        qmlMainWindow.deleteInteractView()
        qmlMainWindow.initProject()
        sphericalBox.clearCombo();
        sphericalBox.getBlendValues();
        //sphericalBox.getCameraList();
        sphericalBox.createBlendViewWindow();
        settingsBox.refreshValues();
        liveView.createCameraWindow();
        sphericalView.createSphericalCameraWindow();
        sphericalView.visible = false;
        interactiveView.createInteractiveCameraWindow();
        interactiveView.visible = false;
        qmlMainWindow.openProject();
        root.titleName = qmlMainWindow.getRecentTitle() + ".ini";
        root.setCurrentTitle(root.titleName);
    }
}
