import QtQuick
import QtQuick.Controls 2.12
import service.TodoModel 1.0
import service.EmployeeModel 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    /*TodoModel{
            id: myModel
            inputFile: "/Users/ngomy2001/Desktop/STUDY/QT/untitled/saveFile.txt"
        }
        */

    EmployeeModel{
        id: employeeModel
        inputFile: "/Users/ngomy2001/Desktop/STUDY/QT/untitled/employeeFile.txt"
    }

        /* ListView{
            id: myTodoList
            anchors.fill: parent
            model: myModel
            header: Row{
                Button{
                    text: "append/add"
                    onClicked: {
                        myModel.addItem()
                    }
                }
                Button{
                    text: "save"
                    onClicked: {
                        myModel.saveTodoListModelToFile()
                    }
                }
            }
            spacing: 20

            delegate: Row{
                width: parent.width
                anchors.left: parent.left
                anchors.leftMargin: 20
                TextField{
                    text: noidung
                    color: "red"
                    width: parent.width -200
                    onTextEdited: {
                        noidung = text
                    }
                }
                CheckBox{
                    checked: trangthai
                    onCheckedChanged: {
                        trangthai = checked
                    }
                }
                Button{
                    text: "Remove"
                    onClicked: {
                        myModel.removeItem(index)
                    }
                }
            }
        } */

        //START
        ListView{
            id: myEmployeeList
            anchors.fill: parent
            model: employeeModel
            header: Row{
                Button{
                    text: "UPDATE"
                    onClicked: {
                        employeeModel.saveEmployeeListModelToFile()
                    }
                }
            }
            spacing: 20

            delegate: Row{
                width: parent.width
                anchors.left: parent.left
                anchors.leftMargin: 20
                TextField{
                    text: name
                    color: "red"
                    width: parent.width -200
                    onTextEdited: {
                        name = text
                    }
                }
                TextField{
                    text: cppVal
                    color: "red"
                    width: parent.width -200
                    onTextEdited: {
                        cppVal = text
                    }
                }
                TextField{
                    text: qmlVal
                    color: "red"
                    width: parent.width -200
                    onTextEdited: {
                        qmlVal = text
                    }
                }
                TextField{
                    text: openGlVal
                    color: "red"
                    width: parent.width -200
                    onTextEdited: {
                        openGlVal = text
                    }
                }
                TextField{
                    text: jsVal
                    color: "red"
                    width: parent.width -200
                    onTextEdited: {
                        jsVal = text
                    }
                }
                TextField{
                    text: avgVal
                    color: "red"
                    width: parent.width -200
                    onTextEdited: {
                        avgVal = text
                    }
                }
            }
        }

}
