#include <Servo.h>

const int LDR_TL_PIN = A0;
const int LDR_TR_PIN = A1;
const int LDR_BL_PIN = A2;
const int LDR_BR_PIN = A3;

const int SERVO_X_PIN = 9;
const int SERVO_Y_PIN = 10;

Servo servoX;
Servo servoY;

int servoXPos = 0;
int servoYPos = 0;

unsigned long trackTimer = 0;

void setup()
{
    Serial.begin(115200);
    
    pinMode(LDR_TL_PIN, INPUT);
    pinMode(LDR_TR_PIN, INPUT);
    pinMode(LDR_BL_PIN, INPUT);
    pinMode(LDR_BR_PIN, INPUT);

    servoX.attach(SERVO_X_PIN);
    servoY.attach(SERVO_Y_PIN);
}

int diffToDirection(int diff, int threshold)
{
    if (abs(diff) < threshold) {
        return 0;
    }

    if (diff > 0)
    {
        return 1;
    }

    if (diff < 0)
    {
        return -1;
    }

    return 0;
}

void track()
{
    if ((millis() - trackTimer) >= 100)
    {
        int tl = analogRead(LDR_TL_PIN);
        int tr = analogRead(LDR_TR_PIN);
        int bl = analogRead(LDR_BL_PIN);
        int br = analogRead(LDR_BR_PIN);

        int topDiff = tl - tr;
        int bottomDiff = bl - br;

        int leftDiff = tl - bl;
        int rightDiff = tr - br;

        float xDiff = (topDiff + bottomDiff) / 2.0;
        float yDiff = (leftDiff + rightDiff) / 2.0;

        const int TRACK_THRESHOLD = 10;
        
        servoXPos += diffToDirection(xDiff, TRACK_THRESHOLD);
        servoYPos += diffToDirection(yDiff, TRACK_THRESHOLD);

        servoXPos = constrain(servoXPos, 0, 180);
        servoYPos = constrain(servoYPos, 0, 180);
    }
}

void updateServo()
{
    servoX.write(servoXPos);
    servoY.write(servoYPos);
}

void loop()
{
    track();
    updateServo();
}
