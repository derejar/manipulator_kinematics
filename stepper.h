#ifndef STEPPER_H
#define STEPPER_H

class Stepper
{
public:
    static const bool CW = false;
    static const bool CCW = true;
public:
    virtual void setSteps(const int count) = 0;
    virtual unsigned int getSteps() const = 0;
    virtual void setSpeed(const double speed) = 0;
    virtual double getSpeed() const = 0;
    virtual bool step() = 0;
    virtual bool getDirection() const = 0;
    virtual ~Stepper() = default;
};

#endif
