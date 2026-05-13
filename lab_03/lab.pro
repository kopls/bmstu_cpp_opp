QT       += widgets
TEMPLATE  = app
TARGET    = lab_03
CONFIG   += c++20 console -Wall -Werror -Wextra -Wpedantic
CONFIG   -= app_bundle

INCLUDEPATH += \
    $$PWD \
    $$PWD/camera \
    $$PWD/commands \
    $$PWD/drawer \
    $$PWD/load \
    $$PWD/load/builders \
    $$PWD/load/builders/model \
    $$PWD/load/builders/camera \
    $$PWD/load/builders/scene \
    $$PWD/load/directors \
    $$PWD/load/directors/model \
    $$PWD/load/directors/camera \
    $$PWD/load/directors/scene \
    $$PWD/load/directors/readers \
    $$PWD/load/moderators \
    $$PWD/load/moderators/model \
    $$PWD/load/moderators/camera \
    $$PWD/load/moderators/scene \
    $$PWD/load/moderators/creators \
    $$PWD/manager \
    $$PWD/objects \
    $$PWD/scene \
    $$PWD/visitor

SOURCES += $$files($$PWD/*.cpp, true)
HEADERS += $$files($$PWD/*.h, true)

SOURCES -= $$PWD/manager/base_manager_creator.cpp
