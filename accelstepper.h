#ifndef ACCELSTEPPER_H
#define ACCELSTEPPER_H

#include "stepper.h"

class AccelStepper : public Stepper
{
public:
    AccelStepper(const unsigned pins[4], const double speed, const double maxSpeed = 0.0, const double acceleration = 0.0);
    void setSteps(const int count) override;
    unsigned int getSteps() const override;
    void setSpeed(const double speed) override;
    double getSpeed() const override;
    bool step() override;
    bool getDirection() const;
private:
    const unsigned m_pins[4];
    const bool m_currents[4][4] = {
        {true, false, false, true},
        {false, true, false, true},
        {false, true, true, false},
        {true, false, true, false}
    };
    unsigned m_index;
    double m_speed;
    double m_currentSpeed;
    double m_maxSpeed;
    double m_acceleration;
    bool m_direction;
    volatile unsigned int m_stepsCount;
    int m_stepsBeforeDecelerate;
    int m_coefficient;
};

#endif
