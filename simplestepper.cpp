#include <arduino.h>
#include "simplestepper.h"

SimpleStepper::SimpleStepper(const unsigned stepPin, const unsigned directionPin, const unsigned enablePin,
                                                                const double speed, const unsigned multiplier)
    : m_stepPin(stepPin),
        m_directionPin(directionPin),
        m_enablePin(enablePin),
        m_speed(speed*multiplier),
        m_multiplier(multiplier),
        m_stepsCount(0),
        m_direction(Stepper::CW)
{
    pinMode(stepPin, OUTPUT);
    pinMode(directionPin, OUTPUT);
    pinMode(enablePin, OUTPUT);
}

void SimpleStepper::setSteps(const int count)
{
    m_direction = (count > 0) ? Stepper::CW : Stepper::CCW;
    m_stepsCount = abs(count)*m_multiplier;
}

unsigned int SimpleStepper::getSteps() const
{
    return m_stepsCount;
}

void SimpleStepper::setSpeed(const double speed)
{
    m_speed = speed ? (speed*m_multiplier) : m_multiplier;
}

double SimpleStepper::getSpeed() const
{
    return m_speed;
}

bool SimpleStepper::step()
{
    if(!m_stepsCount)
        return false;
    digitalWrite(m_enablePin, LOW);
    digitalWrite(m_directionPin, m_direction);
    digitalWrite(m_stepPin, !digitalRead(m_stepPin));
    --m_stepsCount;
    return (m_stepsCount + 1) % m_multiplier == 0;
}

bool SimpleStepper::getDirection() const
{
    return m_direction;
}
