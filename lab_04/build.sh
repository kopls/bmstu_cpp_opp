#!/bin/bash

# Очистка
rm -f *.o *.moc.cpp ui_mainwindow.h app.exe

# Генерация ui
uic mainwindow.ui -o ui_mainwindow.h

# Генерация MOC файлов
moc Elevator.h -o moc_Elevator.cpp
moc ElevatorController.h -o moc_ElevatorController.cpp
moc ElevatorCabin.h -o moc_ElevatorCabin.cpp
moc ElevatorDoors.h -o moc_ElevatorDoors.cpp
moc mainwindow.h -o moc_mainwindow.cpp

# Компиляция основных файлов
g++ -std=c++17 -fPIC -c main.cpp -o main.o -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB

g++ -std=c++17 -fPIC -c mainwindow.cpp -o mainwindow.o -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB

g++ -std=c++17 -fPIC -c Elevator.cpp -o Elevator.o -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB

g++ -std=c++17 -fPIC -c ElevatorCabin.cpp -o ElevatorCabin.o -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB

g++ -std=c++17 -fPIC -c ElevatorController.cpp -o ElevatorController.o -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB

g++ -std=c++17 -fPIC -c ElevatorDoors.cpp -o ElevatorDoors.o -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB

# Компиляция MOC файлов
g++ -std=c++17 -fPIC -c moc_Elevator.cpp -o moc_Elevator.o -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB

g++ -std=c++17 -fPIC -c moc_ElevatorController.cpp -o moc_ElevatorController.o -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB

g++ -std=c++17 -fPIC -c moc_ElevatorCabin.cpp -o moc_ElevatorCabin.o -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB

g++ -std=c++17 -fPIC -c moc_ElevatorDoors.cpp -o moc_ElevatorDoors.o -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB

g++ -std=c++17 -fPIC -c moc_mainwindow.cpp -o moc_mainwindow.o -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB

# Линковка
g++ -fPIC -o app.exe main.o mainwindow.o Elevator.o ElevatorCabin.o ElevatorController.o ElevatorDoors.o moc_Elevator.o moc_ElevatorController.o moc_ElevatorCabin.o moc_ElevatorDoors.o moc_mainwindow.o -lQt5Core -lQt5Widgets -lQt5Gui -lpthread

echo "Build complete! Run ./app.exe"
