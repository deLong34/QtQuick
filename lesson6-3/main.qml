import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Gismeteo.net API")
    property string textRequest: "москва";
    function getData() {
        listview.model.clear()
        var xmlhttp = new XMLHttpRequest();
        var url = "http://api.weatherapi.com/v1/current.json?lang=RU&query=москва&key=YOURKEY";
        xmlhttp.onreadystatechange = function() {
            if (xmlhttp.readyState == XMLHttpRequest.DONE && xmlhttp.status == 200) {
                print(xmlhttp.responseText)
                parseWether(xmlhttp.responseText);
            } else {
                print("Неудачный запрос "  + "\nКод ошибки: " + xmlhttp.status + "\n" + xmlhttp.responseText)
            }
        }
        xmlhttp.open("GET", url, true);
        xmlhttp.setRequestHeader("X-Weatherapi-Token","179f17e2c67a4685a8b65311231506");
        xmlhttp.send();
    }
    //Парсинг JSON ответа от сервера и запись значений в ListView
    function parseWether(response) {
        var jsonObj = JSON.parse(JSON.parse(response));
        var jsonWether = jsonObj.temperature
        listview.model.append( {listdata: jsonWether.air +" "+ jsonWether.comfort + " " + jsonWether.water})

    }
    Item {
        anchors.fill: parent
        ListModel {
            id: model
        }
        ListView {
            id: listview
            anchors.fill: parent
            model: model
            header: Rectangle {
                height: 35
                width: parent.width
                color: "dark green"
                Text {
                    anchors.centerIn: parent
                    text: "Данные от сервера"
                    color: "white"
                }
            }
            delegate: Rectangle{
                width: parent.width
                height: 30
                Text {
                    text: listdata
                    anchors.centerIn: parent
                }
            }
        }
        Button {
            anchors.bottom: parent.bottom
            width: parent.width
            text: "Подтянуть данные"
            onClicked: getData()
        }
    }
}
