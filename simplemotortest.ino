#include "simplestepper.h"
#include "accelstepper.h"
#include "manipulator.h"
#include "parameters.h"

const double angles[3] = {params::MAX_ALPHA_ANGLE, params::MAX_BETA_ANGLE, params::MIN_GAMMA_ANGLE};
Manipulator manipulator(angles, params::L1, params::L2);
SimpleStepper stepper1(45, 33, 35, 800.0, 4);
SimpleStepper stepper2(49, 51, 53, 2000.0, 8);
const unsigned pins[4] = {37, 39, 41, 43};
AccelStepper stepper3(pins, 50.0, 200.0, 50.0);

void setupTimer4()
{
    cli();
    TCCR4A = 0;
    TCCR4B = (1 << CS42) | (1 << WGM42);
    TIMSK4 = (1 << OCIE4A);
    OCR4A = 1;
    sei();
}

ISR(TIMER4_COMPA_vect)
{
    for(int i = 0; i < 3; ++i)
        manipulator.step(i);
}

void setup() 
{
    Serial.begin(115200);
    setupTimer4();
    StepperParams stepperParams1;
    stepperParams1.minAngle = params::MIN_ALPHA_ANGLE;
    stepperParams1.maxAngle = params::MAX_ALPHA_ANGLE;
    stepperParams1.anglePerStep = params::ALPHA_ANGLE_PER_STEP;
    manipulator.attachStepper(&stepper1, stepperParams1);

    StepperParams stepperParams2;
    stepperParams2.minAngle = params::MIN_BETA_ANGLE;
    stepperParams2.maxAngle = params::MAX_BETA_ANGLE;
    stepperParams2.anglePerStep = params::BETA_ANGLE_PER_STEP;
    manipulator.attachStepper(&stepper2, stepperParams2);

    StepperParams stepperParams3;
    stepperParams3.minAngle = params::MIN_GAMMA_ANGLE;
    stepperParams3.maxAngle = params::MAX_GAMMA_ANGLE;
    stepperParams3.anglePerStep = params::GAMMA_ANGLE_PER_STEP;
    manipulator.attachStepper(&stepper3, stepperParams3);
}

void printCoords(const kinematics::Point& point)
{
    Serial.print("x=");
    Serial.print(point.x);
    Serial.print("; y=");
    Serial.print(point.y);
    Serial.print("; z=");
    Serial.println(point.z);
}

double x = 0;
double y = 0;
double z = 0;
double* choice = &x;

bool isNumber(const char c)
{
    return c >= '0' && c <= '9';
}

void loop() {
    if(Serial.available())
    {
        char input = Serial.read();
        switch(input)
        {
            case 'i': 
            {
                bool result = manipulator.moveTo({x, y, z});
                if(result)
                    Serial.println("Moving to:");
                else
                    Serial.println("Impossible to move to:");
                printCoords({x, y, z});
            } break;
            case 'f':
            {
                kinematics::Point point = manipulator.getCoordinates(); 
                Serial.println("I am here: ");
                printCoords(point);
            } break;
            case 'p': printCoords({x, y, z}); break;
            case 'x' : x = 0; choice = &x; break;
            case 'y' : y = 0; choice = &y; break;
            case 'z' : z = 0; choice = &z; break;
            case '-' : *choice *= -1; break;
            default:
            {
                if(isNumber(input))
                {
                    *choice *= 10.0;
                    *choice += (input - '0');
                }
            } break;
        }
    }
}
