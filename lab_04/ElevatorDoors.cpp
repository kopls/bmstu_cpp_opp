#include "ElevatorDoors.h"

ElevatorDoors::ElevatorDoors(QObject* parent) :
    QObject(parent),
    status(CLOSED)
{
    openingTimer.setSingleShot(true);
    closingTimer.setSingleShot(true);
    waitingBeforeCloseTimer.setSingleShot(true);
    waitingBeforeCloseTimer.setInterval(WAITING_DEFORE_CLOSE_TIME);

    connect(&openingTimer, SIGNAL(timeout()), this, SLOT(opened()));
    connect(this, SIGNAL(doorsOpenedSignal()), &waitingBeforeCloseTimer, SLOT(start()));
    connect(&waitingBeforeCloseTimer, SIGNAL(timeout()), this, SLOT(closing()));
    connect(&closingTimer, SIGNAL(timeout()), this, SLOT(closed()));
}

void ElevatorDoors::opening()
{
    if (status == CLOSED)
    {
        status = OPENING;

        qDebug() << "Двери открываются...";

        openingTimer.start(OPENING_DOORS_TIME);
    }
}

void ElevatorDoors::opened()
{
    if (status == OPENING)
    {
        status = OPENED;

        qDebug() << "Двери открыты.";

        emit doorsOpenedSignal();
    }
}

void ElevatorDoors::closing()
{
    if (status == OPENED)
    {
        status = CLOSING;

        qDebug() << "Двери закрываются...";

        closingTimer.start(CLOSING_DOORS_TIME);
    }
}

void ElevatorDoors::closed()
{
    if (status == CLOSING)
    {
        status = CLOSED;

        qDebug() << "Двери закрыты.";

        emit doorsClosedSignal();
    }
}
