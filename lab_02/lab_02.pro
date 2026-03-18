include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++20

HEADERS += \
        test_assignment.hpp \
        test_binary.hpp \
        test_comparison.hpp \
        test_constructor.hpp \
        test_unary.hpp \
        test_vector.hpp \
        const_iterator.hpp \
        iterator.hpp \
        vector.hpp \
        test_constructor.hpp \
        base_container.h \
        base_exception.h \
        const_iterator.h \
        exceptions.h \
        iterator.h \
        vector.h \

SOURCES += \
        main.cpp \
        base_container.cpp \
        base_exception.cpp \

INCLUDEPATH += \
        /usr/include/gtest \
