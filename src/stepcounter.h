#ifndef STEPCOUNTER_H
#define STEPCOUNTER_H

#include <QObject>
#include <sensord-qt5/stepcountersensor_i.h>
#include <sensord-qt5/sensormanagerinterface.h>
#include <QDBusConnection>

class StepCounter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString version READ readVersion NOTIFY versionChanged())
    Q_PROPERTY(int steps READ readSteps NOTIFY stepsChanged())
    Q_PROPERTY(bool autoUpdate READ readAutoUpdate WRITE setAutoUpdate)

public:
    explicit StepCounter(QObject *parent = 0);
    ~StepCounter();

    QString readVersion();
    int readSteps();
    bool readAutoUpdate() { return m_isConnected; }
    void setAutoUpdate(const bool& value) { setConnected(value); }

signals:
    void versionChanged();
    void stepsChanged();

private slots:
    void dataChanged(const Unsigned& data);

private:
    void setConnected(const bool& value);
    void update();

    StepCounterSensorChannelInterface* sensor;
    int m_currentSteps;
    bool m_isConnected;
};

#endif // STEPCOUNTER_H
