#ifndef KINEMATICS_H
#define KINEMATICS_H

namespace kinematics
{
    struct Point
    {
        double x;
        double y;
        double z;
    };

    struct Angles
    {
        double alpha;
        double beta;
        double gamma;
    };

    Point calculateForwardKinematics(const Angles& angles, const long L1, const long L2);
    Angles calculateInverseKinematics(const Point& point, const long L1, const long L2);
}

#endif
