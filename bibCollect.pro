QT += qml quick quickcontrols2 testlib sql

CONFIG += c++14



RESOURCES += \
    qml/qml.qrc \
    img/img.qrc

win32 {
    gcc:QMAKE_CXXFLAGS +=  -std=c++14 -Wall -Wextra -pedantic
}

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



INCLUDEPATH += ./include

HEADERS += \
    include/CUHFReader.h \
    include/CReaderModel.h \
    include/CAbstractReader.h \
    include/CReaderParser.h \
    include/testcreaderparser.h \
    resultsqlmodel.h

SOURCES += \ # main.cpp #\
    resultsqlmodel.cpp \
    source/main.cpp \
    source/CUHFReader.cpp \
    source/CAbstractReader.cpp \
    source/CReaderModel.cpp \
    include/CReaderParser.cpp \
    include/testcreaderparser.cpp


DISTFILES += \
    qml/ResultTab.qml \
    qml/qtquickcontrols2.conf \
    qml/ClockWidget.qml \
    qml/HardwareTab.qml \
    qml/main.qml \
    qml/MainTabView.qml \
    qml/Page1.qml \
    img/delete20.png
