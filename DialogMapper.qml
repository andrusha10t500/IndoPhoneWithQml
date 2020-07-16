import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

Dialog {
    title: qsTr("Dialog Mapper")
    height: 420
    width: 480

    // функция, которая открывает диалоговое окно с данными из первой строки
    function show() {
        open()
        mapper.updateData(0)
    }
    function showNewSMS() {
        open()
    }

    /* Функция, которая открывает диалоговое окно с данными из строки,
     * по которой был произведён даблКлик
     * */
    function editEntry(row) {
        open()
        mapper.updateData(row)
    }

    contentItem: Rectangle {
        implicitHeight: 420
        implicitWidth: 480

        GridLayout {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 5
            rowSpacing: 10
            columnSpacing: 10
            rows: 4
            columns: 2


//            Text {
//                text: qsTr("Дата")
//                Layout.fillWidth: true
//            }

//            TextField {
//                id: dateField  // По данному id передаём объект в Data Mapper
//                Layout.preferredWidth: 200
//            }

            Text {
                text: qsTr("Имя")
                Layout.fillWidth: true
            }

            TextField {
                id: timeField   // По данному id передаём объект в Data Mapper
                Layout.preferredWidth: 200
            }

            Text {
                text: qsTr("Номер телефона")
                Layout.fillWidth: true
            }

            TextField {
                id: randomField  // По данному id передаём объект в Data Mapper
                Layout.preferredWidth: 200
            }

            Text {
                text: qsTr("Дата сообщения")
                Layout.fillWidth: true
            }

            TextField {
                id: messageDateField  // По данному id передаём объект в Data Mapper
                Layout.preferredWidth: 200
            }
            Text {
                text: qsTr("Сообщение")
                Layout.fillWidth: true
            }

            TextArea {
                id: messageField  // По данному id передаём объект в Data Mapper
                Layout.preferredWidth: 200
                Layout.preferredHeight: 200
            }
        }

        Rectangle {
            color: "#eeeeee"
            height: 50
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right

            RowLayout {
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 5
                spacing: 10

                // Кнопка пролистывает строки от последней к первой
                Button {
                    id: buttonPrevious
                    text: qsTr("Предыдущий")
                    Layout.preferredWidth: 80

                    onClicked: {
                        mapper.toPrevious()
                    }
                }

                // Кнопка пролистывает строки от первой к последней
                Button {
                    id: buttonNext
                    text: qsTr("Следующий")
                    Layout.preferredWidth: 80

                    onClicked: {
                        mapper.toNext()
                    }
                }

                Rectangle {
                    Layout.fillWidth: true
                    color: "#eeeeee"
                }

                Button {
                    id: buttonOk
                    text: qsTr("Ok")
                    Layout.preferredWidth: 80
                    onClicked: close()
                }

                Button {
                    id: buttonCancel
                    text: qsTr("Cancel")
                    Layout.preferredWidth: 80
                    onClicked: close()
                }
            }
        }
    }

    /* По результату создания диалогового окна добавляем
     * в Data Mapper объекты QML по их id, с указанием номера роли в модели данных
     * и свойством объекта, в которое будут подставляться данные.
     *
     * То есть: dateField  - это id объекта TextField
     *          0x0100 + 1 - это DateRole модели, которая равна Qt::UserRole + 1
     *          "text"     - это свойство объекта TextField, куда будут подставляться данные
     * */
    Component.onCompleted: {
//        mapper.addMapping(dateField, (0x0100 + 1), "text")
        mapper.addMapping(timeField, (0x0100 + 1), "text")
        mapper.addMapping(randomField, (0x0100 + 2), "text")
        mapper.addMapping(messageDateField, (0x0100 + 3), "text")
        mapper.addMapping(messageField, (0x0100 + 4), "text")

    }
}

