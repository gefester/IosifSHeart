TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        debugFunctions.cpp \
        field.cpp \
        main.cpp \
        tetromino.cpp

HEADERS += \
    field.h \
    tetromino.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-pixeloid-Desktop_Qt_5_9_8_MinGW_32bit-Debug/release/ -lpixeloid
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-pixeloid-Desktop_Qt_5_9_8_MinGW_32bit-Debug/debug/ -lpixeloid

INCLUDEPATH += $$PWD/../pixeloid
DEPENDPATH += $$PWD/../pixeloid

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-pixeloid-Desktop_Qt_5_9_8_MinGW_32bit-Debug/release/libpixeloid.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-pixeloid-Desktop_Qt_5_9_8_MinGW_32bit-Debug/debug/libpixeloid.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-pixeloid-Desktop_Qt_5_9_8_MinGW_32bit-Debug/release/pixeloid.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-pixeloid-Desktop_Qt_5_9_8_MinGW_32bit-Debug/debug/pixeloid.lib



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../SFML-2.5.0_Win32/lib/ -lsfml-system -lsfml-graphics -lsfml-window
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../SFML-2.5.0_Win32/lib/ -lsfml-system-d -lsfml-graphics-d -lsfml-window-d

INCLUDEPATH += $$PWD/../../SFML-2.5.0_Win32/include
DEPENDPATH += $$PWD/../../SFML-2.5.0_Win32/include

CONFIG(release, debug|release): DESTDIR = $$OUT_PWD/release
CONFIG(debug, debug|release): DESTDIR = $$OUT_PWD/debug

copy_to_build.path = $$DESTDIR/fonts
copy_to_build.files = fonts/*

#INSTALLS += \
#    copy_to_build
