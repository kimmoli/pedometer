#include "stepcounter.h"

StepCounter::StepCounter(QObject *parent) :
    QObject(parent)
{
    emit versionChanged();

    m_current_steps = -1;
    emit stepsChanged();

    SensorManagerInterface& sm = SensorManagerInterface::instance();

    sm.loadPlugin("stepcountersensor");
    sm.registerSensorInterface<StepCounterSensorChannelInterface>("stepcountersensor");

    sensor = StepCounterSensorChannelInterface::interface("stepcountersensor");

    if (sensor == NULL || !sensor->isValid())
    {
        qDebug() << "Unable to get session:" << sm.errorString();
    }
    else
    {
        sensor->start();
        sensor->setStandbyOverride(true);
        connect(sensor, SIGNAL(StepCounterChanged(const Unsigned&)), this, SLOT(dataChanged(const Unsigned&)));
        m_current_steps = sensor->steps().x();
        emit stepsChanged();
    }
}

StepCounter::~StepCounter()
{
    if (sensor)
    {
        disconnect(sensor, SIGNAL(StepCounterChanged(const Unsigned&)), this, SLOT(dataChanged(const Unsigned&)));
        sensor->stop();
        delete sensor;
    }
}

void StepCounter::dataChanged(const Unsigned &data)
{
    m_current_steps = data.x();
    emit stepsChanged();
}

int StepCounter::readSteps()
{
    return m_current_steps;
}

QString StepCounter::readVersion()
{
    return APPVERSION;
}
