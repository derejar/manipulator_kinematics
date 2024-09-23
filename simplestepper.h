#ifndef SIMPLESTEPPER_H
#define SIMPLESTEPPER_H

#include "stepper.h"

class SimpleStepper : public Stepper
{
public:
    SimpleStepper(const unsigned stepPin, const unsigned directionPin, const unsigned enablePin,
                                                        const double speed, unsigned multiplier = 8);
    void setSteps(const int count) override;
    unsigned int getSteps() const override;
    void setSpeed(const double speed) override;
    double getSpeed() const override;
    bool step() override;
    bool getDirection() const;
private:
    const unsigned m_stepPin;
    const unsigned m_directionPin;
    const unsigned m_enablePin;
    double m_speed;
    unsigned m_multiplier;
    volatile unsigned int m_stepsCount;
    bool m_direction;
};

#endif
