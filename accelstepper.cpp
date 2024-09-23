#include <arduino.h>
#include "accelstepper.h"


AccelStepper::AccelStepper(const unsigned pins[4], const double speed, const double maxSpeed,
                                                                       const double acceleration)
    : m_pins{pins[0], pins[1], pins[2], pins[3]},
          m_index(0),
          m_speed(speed),
          m_currentSpeed(0),
          m_maxSpeed(maxSpeed),
          m_acceleration(acceleration / speed),
          m_direction(Stepper::CW),
          m_stepsCount(0),
          m_stepsBeforeDecelerate(0),
          m_coefficient(0)
{
    for(int i = 0; i < 4; ++i)
        pinMode(pins[i], OUTPUT);
    AccelStepper::setSpeed(speed);
}

void AccelStepper::setSteps(const int count)
{
    if(m_stepsCount)
        return;
    m_direction = (count > 0) ? Stepper::CW : Stepper::CCW;
    m_stepsCount = abs(count);
    m_stepsBeforeDecelerate = m_stepsCount / 2;
    m_coefficient = 1;
    m_currentSpeed = m_speed;
}

void AccelStepper::setSpeed(const double speed)
{
    if(!speed)
        m_speed = 1.0;
    if(speed > m_maxSpeed)
    {
        m_maxSpeed = m_speed;
        m_acceleration = 0;
    }
}

unsigned int AccelStepper::getSteps() const
{
    return m_stepsCount;
}

bool AccelStepper::step()
{
    if(!m_stepsCount)
        return false;
    unsigned index = (m_direction == Stepper::CCW) ? m_index : (3 - m_index);
    for(unsigned i = 0; i < 4; ++i)
        digitalWrite(m_pins[i], m_currents[index][i]);
    m_index = (m_index + 1) % 4;
    --m_stepsCount;

    if(m_acceleration)
    {
        if(m_coefficient)
        {
            m_currentSpeed += m_coefficient*m_acceleration;
        }

        if(m_coefficient && m_currentSpeed >= m_maxSpeed)
        {
            m_coefficient = 0;
            m_stepsBeforeDecelerate = (2*m_stepsBeforeDecelerate - m_stepsCount) + 2;
        }

        if(m_stepsCount == m_stepsBeforeDecelerate)
            m_coefficient = -1;
    }
    return true;
}

double AccelStepper::getSpeed() const
{
    return m_currentSpeed;
}

bool AccelStepper::getDirection() const
{
    return m_direction;
}
