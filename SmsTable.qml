import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0

Window {
    visible: false
    width: 640
    height: 480
    title: qsTr("Работа с смс")

    RowLayout {
        id: row

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 5
        height: 35

        Button {
            id: button
            text: qsTr("Открыть Mapper")
            width: 150

            Layout.fillHeight: true

            // Открываем диалоговое окно с индексом первой строки в TableView
            onClicked: {
                dialog.show()
            }
        }

        Button {
            id: downloadDB
            text: "Обновить данные"
            anchors.left: button.right
            width: 150
            Layout.fillHeight: true
            onClicked: {
                mapper.downloadDB()
                Qt.quit()
            }
        }

        Button {
            id: newSMS
            text: "Отправить СМС"
            anchors.left: downloadDB.right
            width: 150
            Layout.fillHeight: true
            onClicked: {
                dialog.showNewSMS()
            }
        }

    }

    TableView {
        id: tableView
        anchors.top: row.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 5

//        TableViewColumn {
//            role: "date"    // Эти роли совпадают с названиями ролей в C++ модели
//            title: "Date"
//        }

        TableViewColumn {
            role: "name"    // Эти роли совпадают с названиями ролей в C++ модели
            title: "Name"
        }

        TableViewColumn {
            role: "tel"  // Эти роли совпадают с названиями ролей в C++ модели
            title: "Telefone"
        }

        TableViewColumn {
            role: "dat" // Эти роли совпадают с названиями ролей в C++ модели
            title: "DateMessage"
        }
        TableViewColumn {
            role: "msg" // Эти роли совпадают с названиями ролей в C++ модели
            title: "Message"
        }

        // Устанавливаем модель в TableView
        model: myModel

        // Внешний вид строк настраивается для реализации реакции на даблКлик
        rowDelegate: Rectangle {
            anchors.fill: parent
            color: styleData.selected ? 'skyblue' : (styleData.alternate ? 'whitesmoke' : 'white');
            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.RightButton | Qt.LeftButton
                onClicked: {
                    tableView.selection.clear()
                    tableView.selection.select(styleData.row)
                    tableView.currentRow = styleData.row
                    tableView.focus = true
                }

                onDoubleClicked: {
                    /* при даблКлике по строке открываем диалоговое окно
                     * с информацией из соответствующей строки
                     * */
                    dialog.editEntry(styleData.row)
                }
            }
        }
    }

    DialogMapper {
        id: dialog
    }
}

