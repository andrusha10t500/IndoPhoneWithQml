import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.4


ApplicationWindow {
    id: mainWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("InfoPhone")

    Rectangle {
        id: progressBar1
        anchors.centerIn: parent
        anchors.top: openSms.bottom
        color: "blue"
        border.width: 1
        border.color: "black"
        radius: 20
        height: 60
        width: parent.width - 100
        Rectangle {
            id: progressBar
            color: "white"
            anchors.verticalCenter: parent.verticalCenter
            height: parent.height-2
            radius: 20
            anchors.right: parent.right
            width:  {
//                mapper.infoBattary()*(parent.width/100)
                parent.width-mapper.infoBattary()*(parent.width/100)
            }
        }
        Rectangle {
            color: "white"
            anchors.verticalCenter: progressBar.verticalCenter
            height: progressBar.height
            anchors.left: progressBar.left
            width: progressBar.width/2
        }




//        ProgressBar {
//            height: parent.height
//            width: parent.width
//            maximumValue: 100
//            minimumValue: 0
//            value: {
//                mapper.infoBattary()
//            }
//        }

    }
    Rectangle {
        anchors.topMargin : progressBar.bottom
        height: 25
        width: parent.width - 300
        color: "white"
        border.color: "black"
        border.width: 1
        anchors.horizontalCenter: parent.horizontalCenter
        radius: 20
        TextEdit {
            id: phoneNumber
            height: parent.height
            width: parent.width
            anchors.centerIn: parent
        }
    }



    Rectangle {
        id: sphere
        visible: true
        color: "black"
        width: 100
        height: 100
        radius: 50

    }

    MouseArea {
        anchors.fill: panel
        hoverEnabled: true
        onEntered: startSphere.start()
        onExited: endSphere.start()
    }

    NumberAnimation {
        id: startSphere
        target: sphere
        property: "y"
        to: 365
        duration: 75
        running: true
//        easing.type: Easing.InOutQuad
    }

    NumberAnimation {
        id: endSphere
        target: sphere
        property: "y"
        to: 400
        duration: 75
//        easing.type: Easing.InOutQuad
    }

    Rectangle {
        //anchors.left: openSms.right
        id: panel
        width: parent.width
        anchors.bottom: parent.bottom
        height: 80

        //color: "red"
        LinearGradient {
            anchors.fill: parent
            start: Qt.point(0, 0) // Стартовая точка градиента
            end: Qt.point(0, 110) // конечная точка градиента
            gradient: Gradient {
                GradientStop { position: 1.0; color: "#00000000" }
                GradientStop { position: 0.0; color: "#FF000000" }
            }
        }
//-------------------Иконка СМС-------------------
        Button {
            visible: true
            id: openSms
            opacity: 0
//            anchors.left: parent.horizontalCenter
//            width: anchors.fill.parent
            width: 100
            height: parent.height
//            anchors.verticalCenter: parent.verticalCenter
//            anchors.horizontalCenter: parent.horizontalCenter
//            onClicked: {
//                smsTable.show()
//            }
        }
        Rectangle {
            id: subSphere
            width: 70
            height: 70
            color: "white"
            radius: 50
            opacity: 0
            anchors.centerIn: imageSms
        }
        Image {
            id: imageSms
//            anchors.left: openSms.left
            source: "qrc:/image/icons/message.png"
            fillMode: Image.Tile
            y: 15
            x: 25
//            anchors.verticalCenter: parent.verticalCenter
//            anchors.horizontalCenter: parent.horizontalCenter

        }

        MouseArea {
            id: mouse
            anchors.fill: openSms
            hoverEnabled: true
            onClicked: smsTable.show()
            onEntered: smsAnim.start()
            onExited: smsAnimStop.start()
        }

        SequentialAnimation {
            id: smsAnimStop
            NumberAnimation {
              target: imageSms     // Идентификатор объекта
              properties: "y" // Изменяемые свойства объекта
              from: 0
              to: 15
              duration: 75
    //          running: true // Обязательно устанавливать, иначе анимация не запустится
            }
            NumberAnimation {
              target: sphere     // Идентификатор объекта
              properties: "y" // Изменяемые свойства объекта
    //          from: 10
              to: 400
              duration: 100
    //          running: true // Обязательно устанавливать, иначе анимация не запустится
            }
            PropertyAnimation {
                target: subSphere
                property: "opacity"
                to: 0
                duration: 300
            }
        }

        SequentialAnimation {
            id: smsAnim

            PropertyAnimation {
                target: subSphere
                property: "opacity"
                to: 0.8
                duration: 300
            }

            NumberAnimation {

              target: sphere     // Идентификатор объекта
              properties: "x" // Изменяемые свойства объекта
    //          from: 10
              to: 0
              duration: 75
    //          running: true // Обязательно устанавливать, иначе анимация не запустится
            }

            NumberAnimation {

              target: sphere     // Идентификатор объекта
              properties: "y" // Изменяемые свойства объекта
    //          from: 10
              to: 365
              duration: 100
    //          running: true // Обязательно устанавливать, иначе анимация не запустится
            }

            NumberAnimation {
              target: imageSms     // Идентификатор объекта
              properties: "y" // Изменяемые свойства объекта
    //          from: 10
              to: -10
              duration: 75
    //          running: true // Обязательно устанавливать, иначе анимация не запустится
            }

//            PropertyAnimation {
//                targets: sphere
//                properties: "scale"
//                from: 1.0
//                to: 1.2
//                duration: 100
//            }


//            PropertyAnimation {
////                id: mouseExitAnim
//                targets: sphere
//                properties: "scale"
//                from: 1.2
//                to: 1.0
//                duration: 100
//            }
        }

//-------------------Иконка контакты-------------------
        Button {
            id: openContacts
            opacity: 0
            anchors.left: openSms.right
            width: 100
            height: parent.height
        }
        Rectangle {
            id: subSphere1
            width: 70
            height: 70
            color: "white"
            radius: 50
            opacity: 0
            anchors.centerIn: imageContacts
        }

        Image {
            id: imageContacts
//            anchors.left: openContacts.left
//            anchors.centerIn: openContacts
            x: openSms.width + 25
            y: 15
            source: "qrc:/image/icons/contacts.png"
            fillMode: Image.Tile
        }

        MouseArea {
            id: mouse1
            anchors.fill: openContacts
            hoverEnabled: true
            onEntered: contactAnim.start()
            onExited: contactAnimStop.start()
        }

        SequentialAnimation {
            id: contactAnimStop

            NumberAnimation {
                target: imageContacts
                property: "y"
                from: 0
                to: 15
                duration: 75
            }
            NumberAnimation {
              target: sphere
              properties: "y"
              to: 400
              duration: 75
            }
            PropertyAnimation {
                target: subSphere1
                property: "opacity"
                to: 0
                duration: 300
            }
        }

        SequentialAnimation {
            id: contactAnim
            PropertyAnimation {
                target: subSphere1
                property: "opacity"
                to: 0.8
                duration: 300
            }
            NumberAnimation {

              target: sphere
              properties: "x"
              to: openContacts.width
              duration: 75
            }

            NumberAnimation {
              target: sphere
              properties: "y"
              to: 365
              duration: 100
            }

            NumberAnimation {
                target: imageContacts
                property: "y"
                to: -10
                duration: 75
            }
        }
//-------------------Иконка трубка-------------------

        Button {
            id: callPhone
            opacity: 0
            anchors.left: openContacts.right
            width: 100
            height: parent.height
        }
        Rectangle {
            id: subSphere2
            width: 70
            height: 70
            color: "white"
            radius: 50
            opacity: 0
            anchors.centerIn: imageCall
        }
        Image {
            id: imageCall
            x: openContacts.width*2 + 25
            y: 15
            source: "qrc:/image/icons/phone.png"
            fillMode: Image.Tile
        }
        MouseArea {
            id: mouse2
            anchors.fill: callPhone
            hoverEnabled: true
            onEntered: callAnim.start()
            onExited: callAnimStop.start()
        }

        SequentialAnimation {
            id: callAnimStop
            NumberAnimation {
                target: imageCall
                property: "y"
                from: 0
                to: 15
                duration: 75
            }
            NumberAnimation {
              target: sphere
              properties: "y"
              to: 400
              duration: 75
            }
            PropertyAnimation {
                target: subSphere2
                property: "opacity"
                to: 0
                duration: 300
            }
        }

        SequentialAnimation {
            id: callAnim
            PropertyAnimation {
                target: subSphere2
                property: "opacity"
                to: 0.8
                duration: 300
            }
            NumberAnimation {
              target: sphere
              properties: "x"
              to: openContacts.width*2
              duration: 75
            }

            NumberAnimation {
              target: sphere
              properties: "y"
              to: 365
              duration: 75
            }
            NumberAnimation {
                target: imageCall
                property: "y"
                to: -10
                duration: 75
            }
        }

//-------------------Иконка exit-------------------

        Button {
            id: exit
            opacity: 0
            anchors.left: callPhone.right
            width: 100
            height: parent.height
        }
        Rectangle {
            id: subSphere3
            width: 70
            height: 70
            color: "white"
            radius: 50
            opacity: 0
            anchors.centerIn: imageExit
        }
        Image {
            id: imageExit
//            anchors.centerIn: exit
//            anchors.left: exit.left
            x: callPhone.width*3 + 25
            y: 15
            source: "qrc:/image/icons/exit.png"
            fillMode: Image.Tile
        }
        MouseArea {
            id: mouse3
            anchors.fill: exit
            hoverEnabled: true
            onClicked: Qt.quit()
            onEntered: exitAnim.start()
            onExited: exitAnimStop.start()
        }

        SequentialAnimation {
            id: exitAnimStop

            NumberAnimation {
                target: imageExit
                property: "y"
                to: 15
                duration: 75
            }
            NumberAnimation {
              target: sphere
              properties: "y"
              to: 400
              duration: 75
            }
            PropertyAnimation {
                target: subSphere3
                property: "opacity"
                to: 0
                duration: 300
            }
        }

        SequentialAnimation {
            id: exitAnim
            PropertyAnimation {
                target: subSphere3
                property: "opacity"
                to: 0.8
                duration: 300
            }
            NumberAnimation {
              target: sphere
              properties: "x"
              to: openContacts.width*3
              duration: 75
            }

            NumberAnimation {
              target: sphere
              properties: "y"
              to: 365
              duration: 75
            }

            NumberAnimation {
                target: imageExit
                property: "y"
//                from: 0
                to: -10
                duration: 75
            }
        }
//-------------------Exit-------------------
    }

    SmsTable {
        id: smsTable
    }
}

