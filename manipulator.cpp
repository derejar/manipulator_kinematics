#include "manipulator.h"
#include <arduino.h>

Manipulator::Manipulator(const double angles[3], const long L1, const long L2)
    : m_angles{angles[0], angles[1], angles[2]},
      m_L1(L1),
      m_L2(L2)
{}

void Manipulator::attachStepper(Stepper* stepper, const StepperParams& params)
{
    if(m_steppersAdded >= 3)
        return;
    m_steppers[m_steppersAdded] = stepper;
    m_stepperParams[m_steppersAdded] = params;
    m_stepperParams[m_steppersAdded].interval = calculateInterval(stepper);
    ++m_steppersAdded;
}

void Manipulator::step(const unsigned index)
{
    if(m_steppersAdded <= index)
        return;
    ++m_stepperParams[index].invokeCount;
    if(m_stepperParams[index].invokeCount >= m_stepperParams[index].interval)
    {
        m_stepperParams[index].invokeCount = 0;
        if(!m_steppers[index]->step())
            return;
        bool direction = m_steppers[index]->getDirection();
        int coefficient = (direction == Stepper::CW) ? 1 : -1;
        m_angles[index] += coefficient*m_stepperParams[index].anglePerStep;
        m_stepperParams[index].interval = calculateInterval(m_steppers[index]);
    }
}

bool Manipulator::moveTo(const kinematics::Point& point)
{
    kinematics::Angles angles = kinematics::calculateInverseKinematics(point, m_L1, m_L2);
    double anglesArr[3] = {angles.alpha, angles.beta, angles.gamma};
    bool isAchievable = true;
    for(unsigned int i = 0; i < 3; ++i)
        isAchievable &= m_stepperParams[i].minAngle <= anglesArr[i] && anglesArr[i] <= m_stepperParams[i].maxAngle;
    if(!isAchievable)
        return false;
    for(unsigned int i = 0; i < 3; ++i)
    {
        int steps = (anglesArr[i] - m_angles[i]) / m_stepperParams[i].anglePerStep;
        if(m_steppersAdded > i)
            m_steppers[i]->setSteps(steps);
    }
   return true;
}

kinematics::Point Manipulator::getCoordinates() const
{
    return kinematics::calculateForwardKinematics({m_angles[0], m_angles[1], m_angles[2]}, m_L1, m_L2);
}

unsigned Manipulator::calculateInterval(Stepper* stepper) const
{
    return 62500 / stepper->getSpeed();
}
