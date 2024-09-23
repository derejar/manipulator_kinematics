#ifndef PARAMETERS_H
#define PARAMETERS_H

namespace params
{
    const double MIN_GAMMA_ANGLE = 0.0;
    const double MAX_GAMMA_ANGLE = 70.0;
    const double GAMMA_ANGLE_INTERVAL = MAX_GAMMA_ANGLE - MIN_GAMMA_ANGLE;

    const double MIN_ALPHA_ANGLE = 20.0;
    const double MAX_ALPHA_ANGLE = 60.0;
    const double ALPHA_ANGLE_INTERVAL = MAX_ALPHA_ANGLE - MIN_ALPHA_ANGLE;

    const double MIN_BETA_ANGLE = 55.0;
    const double MAX_BETA_ANGLE = 125.0;
    const double BETA_ANGLE_INTERVAL = MAX_BETA_ANGLE - MIN_BETA_ANGLE;

    const double GAMMA_STEPPER_MAX_STEPS = 300;
    const double ALPHA_STEPPER_MAX_STEPS = 1600;
    const double BETA_STEPPER_MAX_STEPS = 4400;

    const double GAMMA_ANGLE_PER_STEP = GAMMA_ANGLE_INTERVAL / GAMMA_STEPPER_MAX_STEPS;
    const double ALPHA_ANGLE_PER_STEP = ALPHA_ANGLE_INTERVAL / ALPHA_STEPPER_MAX_STEPS;
    const double BETA_ANGLE_PER_STEP = BETA_ANGLE_INTERVAL / BETA_STEPPER_MAX_STEPS;

    const long L1 = 370;
    const long L2 = 440;
}

#endif
