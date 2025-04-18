import QtQuick 2.15
import QtQuick.Controls 2.15

Window {
    id: root
    width: 1920
    height: Screen.desktopAvailableHeight
    visible: true
    color: Qt.rgba(33 / 255, 42 / 255, 85 / 255, 1)
    screen: Qt.application.screens[0]
    title: pname

    // enum ExpectedFunction {
    //     RefreshMainPage,  // 1 刷新主页面数据
    // }

}
