#include "Elevator.h"

Elevator::Elevator(QObject* parent) : QObject(parent)
{
    QObject::connect(&controller, SIGNAL(moveCabineSignal(int)),
                     &cabine, SLOT(moveBetweenFloorsSlot(int)));

    QObject::connect(&controller, SIGNAL(stopCabineSignal()),
                     &cabine, SLOT(stopOnFloorSlot()));

    QObject::connect(&cabine, SIGNAL(cabinePassedFloorSignal(bool, int)),
                     &controller, SLOT(reachFloorSlot(bool, int)));

    QObject::connect(&cabine, SIGNAL(cabinePassedFloorSignal(bool, int)),
                     this, SLOT(throwFloorToInterfaceSlot(bool, int)));

    QObject::connect(&cabine, SIGNAL(cabineReadyToMoveSignal()),
                     &controller, SLOT(reachedFloorSlot()));

    QObject::connect(this, SIGNAL(getNewFloorSignal(int)),
                     &controller, SLOT(getNewFloorSlot(int)));
}

void Elevator::newFloorSlot(int newFloor)
{
    emit getNewFloorSignal(newFloor);
}

void Elevator::throwFloorToInterfaceSlot(bool wasInterruptedNotNeed, int curFloor)
{
    emit throwCurFloorSignal(curFloor);
}
