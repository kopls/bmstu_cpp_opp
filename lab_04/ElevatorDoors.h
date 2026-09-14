#pragma once

#include <QObject>
#include <QTimer>
#include <QDebug>

#define OPENING_DOORS_TIME 1000
#define CLOSING_DOORS_TIME 1000
#define WAITING_DEFORE_CLOSE_TIME 1000

class ElevatorDoors final : public QObject
{
    Q_OBJECT

    enum DoorsStatus {
        OPENING,
        CLOSING,
        OPENED,
        CLOSED
    };

signals:
    void doorsClosedSignal();
    void doorsOpenedSignal();

public:
    explicit ElevatorDoors(QObject* parent = nullptr);
    ~ElevatorDoors() = default;

public slots:
    void opening();

private slots:
    void closing();
    void opened();
    void closed();

private:
    DoorsStatus status;
    QTimer openingTimer;
    QTimer closingTimer;
    QTimer waitingBeforeCloseTimer;
};