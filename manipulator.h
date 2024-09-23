#ifndef MANIPULATOR_H
#define MANIPULATOR_H

#include "kinematics.h"
#include "stepper.h"

struct StepperParams
{
    double minAngle;
    double maxAngle;
    double anglePerStep;
    double interval;
    double invokeCount = 0;
};

class Manipulator
{
public:
    Manipulator(const double angles[3], const long L1, const long L2);
    void attachStepper(Stepper* stepper, const StepperParams& stepperParams);
    void step(const unsigned index);
    bool moveTo(const kinematics::Point& point);
    kinematics::Point getCoordinates() const;
private:
    unsigned calculateInterval(Stepper* stepper) const;
private:
    volatile double m_angles[3];
    double m_L1;
    double m_L2;
    Stepper* m_steppers[3];
    StepperParams m_stepperParams[3];
    unsigned m_steppersAdded = 0;
};

#endif
