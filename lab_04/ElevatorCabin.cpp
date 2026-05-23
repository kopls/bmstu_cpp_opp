#include "ElevatorCabin.h"

ElevatorCabin::ElevatorCabin(QObject* parent) :
    QObject(parent),
    status(READY_TO_MOVE)
{
    moveTimer.setSingleShot(true);

    QObject::connect(this, SIGNAL(openDoorsSignal()), &doors, SLOT(opening()));
    QObject::connect(&doors, SIGNAL(doorsClosedSignal()), this, SLOT(readyToMoveSlot()));
    QObject::connect(&moveTimer, SIGNAL(timeout()), this, SLOT(passFloorSlot()));
}

void ElevatorCabin::moveBetweenFloorsSlot(int newCurFloor)
{
    if (status == READY_TO_MOVE || status == PASSING_FLOOR)
    {
        curFloor = newCurFloor;
        status = MOVING_BETWEEN_FLOORS;

        qDebug() << "Едем...";

        moveTimer.start(CABINE_MOVING_BETWEEN_FLOORS_TIME);
    }
}

void ElevatorCabin::stopOnFloorSlot()
{
    if (status == PASSING_FLOOR || status == READY_TO_MOVE)
    {
        status = STOPPING_ON_FLOOR;

        qDebug() << "Приехали.";
        
        emit openDoorsSignal();
    }
}

void ElevatorCabin::passFloorSlot()
{
    if (status == MOVING_BETWEEN_FLOORS)
    {
        status = PASSING_FLOOR;
        qDebug() << "Текущий этаж " << curFloor;
        emit cabinePassedFloorSignal(false, curFloor);
    }
}

void ElevatorCabin::readyToMoveSlot()
{
    if (status == STOPPING_ON_FLOOR)
    {
        status = READY_TO_MOVE;
        emit cabineReadyToMoveSignal();
    }
}
