#include "stepcounter.h"

StepCounter::StepCounter(QObject *parent) :
    QObject(parent)
{
    emit versionChanged();

    m_currentSteps = -1;
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
        setConnected(true);
        update();
    }
}

StepCounter::~StepCounter()
{
    if (sensor)
    {
        setConnected(false);
        sensor->stop();
        delete sensor;
    }
}

void StepCounter::update()
{
    if (sensor)
    {
        m_currentSteps = sensor->steps().x();
        emit stepsChanged();
    }
}

void StepCounter::dataChanged(const Unsigned &data)
{
    m_currentSteps = data.x();
    emit stepsChanged();
}

int StepCounter::readSteps()
{
    return m_currentSteps;
}

void StepCounter::setConnected(const bool &value)
{
    if (sensor)
    {
        if (value == m_isConnected)
            return;

        if (value)
        {
            update();
            connect(sensor, SIGNAL(StepCounterChanged(const Unsigned&)), this, SLOT(dataChanged(const Unsigned&)));
        }
        else
        {
            disconnect(sensor, SIGNAL(StepCounterChanged(const Unsigned&)), this, SLOT(dataChanged(const Unsigned&)));
        }

        m_isConnected = value;
        qDebug() << "connected" << value;
    }
}

QString StepCounter::readVersion()
{
    return APPVERSION;
}
