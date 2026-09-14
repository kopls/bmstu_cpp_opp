#include "ElevatorController.h"

ElevatorController::ElevatorController(QObject* parent) :
    QObject(parent),
    status(NO_FLOORS),
    direction(STAND),
    currentFloor(1),
    targetFloor(1)
{
    QObject::connect(this, SIGNAL(reachActFloorSignal(bool)), this, SLOT(reachActFloorSlot(bool)));
    QObject::connect(this, SIGNAL(reachFloorSignal(bool, int)), this, SLOT(reachFloorSlot(bool, int)));
    QObject::connect(this, SIGNAL(noFloorsSignal()), this, SLOT(noFloorsSlot()));
}

void ElevatorController::getNewFloorSlot(int newFloor)
{
    if (status == NO_FLOORS || status == REACH_FLOOR || status == REACH_ACT_FLOOR)
    {
        int prevStatus = status;
        status = GETTING_NEW_FLOOR;
        addToQueue(newFloor);
        
        if (newFloor == currentFloor && prevStatus == NO_FLOORS)
        {
            targetFloor = currentFloor;
            direction = STAND;
        }
        else
        {
            qDebug() << "Добавили в очередь этажей" << newFloor;

            int priorityTarget = getPriorityTarget();
            if (priorityTarget != -1)
            {
                targetFloor = priorityTarget;
                updateDirection();
            }
        }
        
        emit reachFloorSignal(prevStatus == REACH_FLOOR || prevStatus == REACH_ACT_FLOOR, currentFloor);
    }
}

void ElevatorController::reachFloorSlot(bool wasInterrupted, int curFloor)
{
    if (status == GETTING_NEW_FLOOR || status == REACH_FLOOR
        || status == REACH_ACT_FLOOR || status == REACHED_FLOOR)
    {
        int prevStatus = status;
        status = REACH_FLOOR;

        if (!wasInterrupted)
            emit reachActFloorSignal(prevStatus == REACH_FLOOR || prevStatus == REACH_ACT_FLOOR);
    }
}

void ElevatorController::reachActFloorSlot(bool floorJustPassed)
{
    if (status == REACH_FLOOR)
    {
        status = REACH_ACT_FLOOR;

        if (floorJustPassed)
        {
            currentFloor += direction;
        }

        if (currentFloor == targetFloor)
        {
            emit stopCabineSignal();
        }
        else
        {
            //qDebug() << "Очередь:" << QList<int>(queue.begin(), queue.end());
            //qDebug() << "Текущий этаж " << currentFloorl;
            emit moveCabineSignal(currentFloor + direction);
        }
    }
}

void ElevatorController::reachedFloorSlot()
{
    if (status == REACH_FLOOR || status == REACH_ACT_FLOOR)
    {
        status = REACHED_FLOOR;
        
        if (!queue.empty())
            queue.remove(currentFloor);

        if (!queue.empty())
        {
            targetFloor = queue.front();
            updateDirection();
            emit reachFloorSignal(false, currentFloor);
        }
        else
        {
            emit noFloorsSignal();
        }
    }
}

void ElevatorController::noFloorsSlot()
{
    if (status == REACHED_FLOOR)
    {
        status = NO_FLOORS;
        direction = STAND;
        targetFloor = currentFloor;

        qDebug() << "Встали...";
    }
}

void ElevatorController::addToQueue(int floor)
{
    for (int f : queue)
        if (f == floor) return;

    if (direction == UP)
    {
        if (floor > currentFloor)
        {
            auto it = queue.begin();
            while (it != queue.end() && *it > currentFloor && *it < floor)
                ++it;

            queue.insert(it, floor);
        }
        else
        {
            auto it = queue.begin();
            while (it != queue.end() && *it > currentFloor)
                ++it;
            
            while (it != queue.end() && *it > floor && *it < currentFloor)
                ++it;
            
            queue.insert(it, floor);
        }
    }
    else if (direction == DOWN)
    {
        if (floor < currentFloor)
        {
            auto it = queue.begin();
            while (it != queue.end() && *it < currentFloor && *it > floor)
                ++it;

            queue.insert(it, floor);
        }
        else
        {
            auto it = queue.begin();
            while (it != queue.end() && *it < currentFloor)
                ++it;
            
            while (it != queue.end() && *it < floor && *it > currentFloor)
                ++it;
            
            queue.insert(it, floor);
        }
    }
    else
    {
        queue.push_back(floor);
    }
}

int ElevatorController::getPriorityTarget()
{
    if (queue.empty())
        return -1;
    
    return queue.front();
}

void ElevatorController::updateDirection()
{
    if (targetFloor > currentFloor)
        direction = UP;
    else if (targetFloor < currentFloor)
        direction = DOWN;
    else
        direction = STAND;
}
