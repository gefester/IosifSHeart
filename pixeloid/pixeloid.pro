TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++11
CONFIG -= qt

SOURCES += \
    pixelscreen.cpp

HEADERS += \
    pixelscreen.h


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../SFML-2.5.0_Win32/lib/ -lsfml-system -lsfml-graphics -lsfml-window
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../SFML-2.5.0_Win32/lib/ -lsfml-system-d -lsfml-graphics-d -lsfml-window-d

INCLUDEPATH += $$PWD/../../SFML-2.5.0_Win32/include
DEPENDPATH += $$PWD/../../SFML-2.5.0_Win32/include
