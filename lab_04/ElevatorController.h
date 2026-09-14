#pragma once

#include <QObject>
#include <list>
#include <QDebug>

class ElevatorController final : public QObject
{
    Q_OBJECT

    enum ControllerStatus {
        NO_FLOORS,
        GETTING_NEW_FLOOR,
        REACH_FLOOR,
        REACH_ACT_FLOOR,
        REACHED_FLOOR
    };

    enum Direction {
        DOWN = -1,
        STAND = 0,
        UP = 1
    };

signals:
    void moveCabineSignal(int curFloor);
    void stopCabineSignal();

    void reachFloorSignal(bool wasInterrupted, int curFloor);
    void reachActFloorSignal(bool floorJustPassed);
    void noFloorsSignal();

public:
    explicit ElevatorController(QObject* parent = nullptr);
    ~ElevatorController() = default;

public slots:
    void getNewFloorSlot(int newFloor);
    void reachFloorSlot(bool wasInterrupted, int curFlor);
    void reachedFloorSlot();

private slots:
    void noFloorsSlot();
    void reachActFloorSlot(bool floorJustPassed);

private:
    void addToQueue(int floor);
    void updateDirection();
    int getPriorityTarget();

    ControllerStatus status;
    Direction direction;
    int currentFloor;
    int targetFloor;
    std::list<int> queue;
};
