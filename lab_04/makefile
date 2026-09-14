#############################################################################
# Makefile для сборки проекта лифта
#############################################################################

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -fPIC
MOC = moc
UIC = uic

# Пути к Qt
QT_CORE = -I/usr/include/x86_64-linux-gnu/qt5 \
          -I/usr/include/x86_64-linux-gnu/qt5/QtCore \
          -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets \
          -I/usr/include/x86_64-linux-gnu/qt5/QtGui

QT_DEFINES = -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB
QT_LIBS = -lQt5Core -lQt5Widgets -lQt5Gui -lpthread

# Исходные файлы
SOURCES = main.cpp \
          mainwindow.cpp \
          Elevator.cpp \
          ElevatorCabin.cpp \
          ElevatorController.cpp \
          ElevatorDoors.cpp

# MOC файлы (генерируем из заголовков)
MOC_FILES = moc_mainwindow.cpp \
            moc_Elevator.cpp \
            moc_ElevatorCabin.cpp \
            moc_ElevatorController.cpp \
            moc_ElevatorDoors.cpp

# Все объекты
OBJECTS = $(SOURCES:.cpp=.o) $(MOC_FILES:.cpp=.o)

TARGET = app.exe

.PHONY: all clean

all: $(TARGET)

# Генерация ui_mainwindow.h из mainwindow.ui
ui_mainwindow.h: mainwindow.ui
	$(UIC) mainwindow.ui -o ui_mainwindow.h

# Генерация MOC файлов из заголовков
moc_mainwindow.cpp: mainwindow.h
	$(MOC) mainwindow.h -o moc_mainwindow.cpp

moc_Elevator.cpp: Elevator.h
	$(MOC) Elevator.h -o moc_Elevator.cpp

moc_ElevatorCabin.cpp: ElevatorCabin.h
	$(MOC) ElevatorCabin.h -o moc_ElevatorCabin.cpp

moc_ElevatorController.cpp: ElevatorController.h
	$(MOC) ElevatorController.h -o moc_ElevatorController.cpp

moc_ElevatorDoors.cpp: ElevatorDoors.h
	$(MOC) ElevatorDoors.h -o moc_ElevatorDoors.cpp

# Компиляция обычных .cpp
%.o: %.cpp ui_mainwindow.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(QT_CORE) $(QT_DEFINES)

# Компиляция MOC файлов
moc_%.o: moc_%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(QT_CORE) $(QT_DEFINES)

# Линковка
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(QT_LIBS)

# Очистка
clean:
	rm -f $(OBJECTS) $(TARGET) ui_mainwindow.h $(MOC_FILES)