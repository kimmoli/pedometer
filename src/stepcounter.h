#ifndef STEPCOUNTER_H
#define STEPCOUNTER_H

#include <QObject>
#include <sensord-qt5/stepcountersensor_i.h>
#include <sensord-qt5/sensormanagerinterface.h>

class StepCounter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString version READ readVersion NOTIFY versionChanged())
    Q_PROPERTY(int steps READ readSteps NOTIFY stepsChanged())

public:
    explicit StepCounter(QObject *parent = 0);
    ~StepCounter();

    QString readVersion();
    int readSteps();

signals:
    void versionChanged();
    void stepsChanged();

private slots:
    void dataChanged(const Unsigned& data);

private:
    StepCounterSensorChannelInterface* sensor;
    int m_current_steps;
};

#endif // STEPCOUNTER_H
