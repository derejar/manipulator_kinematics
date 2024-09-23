#include "kinematics.h"
#include <arduino.h>

namespace kinematics
{
    Point calculateForwardKinematics(const Angles& angles, const long L1, const long L2)
    {
        const double A = L1;
        const double B = L2;
        double sinGamma = sin(radians(angles.gamma));
        double cosGamma = cos(radians(angles.gamma));
        double sinAlpha = sin(radians(angles.alpha));
        double cosAlpha = cos(radians(angles.alpha));
        double sinAngles = sin(radians(angles.alpha + angles.beta - 180.0));
        double cosAngles = cos(radians(angles.alpha + angles.beta - 180.0));

        Point point;
        point.x = cosGamma*(A*cosAlpha + B*cosAngles);
        point.y = A*sinAlpha + B*sinAngles;
        point.z = sinGamma*(A*cosAlpha + B*cosAngles);
        return point;
    }

    Angles calculateInverseKinematics(const Point& point, const long L1, const long L2)
    {
        const double A = L1;
        const double B = L2;
        double R = sqrt(point.x*point.x + point.z*point.z);
        double cosGamma = point.x / R;

        double L = sqrt(point.x*point.x + point.y*point.y + point.z*point.z);
        double cosBetaUpper = A*A + B*B - L*L;
        double cosBetaLower = 2*A*B;
        double cosBeta = cosBetaUpper / cosBetaLower;

        double cosEpsilonUpper = A*A + L*L - B*B;
        double cosEpsilonLower = 2*A*L;
        double cosEpsilon = cosEpsilonUpper / cosEpsilonLower;
        double cosDelta = R / L;

        Angles angles;
        if(point.y >= 0)
            angles.alpha = degrees(acos(cosEpsilon)) + degrees(acos(cosDelta));
        else
            angles.alpha = degrees(acos(cosEpsilon)) - degrees(acos(cosDelta));
        angles.beta = degrees(acos(cosBeta));
        angles.gamma = degrees(acos(cosGamma));
        return angles;
    }
}
