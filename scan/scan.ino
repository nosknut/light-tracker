#include <Servo.h>

const int LDR_TL_PIN = A0;
const int LDR_TR_PIN = A1;
const int LDR_BL_PIN = A2;
const int LDR_BR_PIN = A3;

const int SERVO_X_PIN = 9;
const int SERVO_Y_PIN = 10;

Servo servoX;
Servo servoY;

int scanMax = 0;
int scanMaxX = 0;
int scanMaxY = 0;

int[181][181] scanMap;
int[181][181] scanMapTl;
int[181][181] scanMapTr;
int[181][181] scanMapBl;
int[181][181] scanMapBr;

void setup()
{
    pinMode(LDR_TL_PIN, INPUT);
    pinMode(LDR_TR_PIN, INPUT);
    pinMode(LDR_BL_PIN, INPUT);
    pinMode(LDR_BR_PIN, INPUT);

    servoX.attach(SERVO_X_PIN);
    servoY.attach(SERVO_Y_PIN);
}

void scan()
{
    for (int x = 0; x <= 180; x++)
    {
        for (int y = 0; y <= 180; y++)
        {
            servoX.write(x);
            servoY.write(y);
            delay(10);

            int tl = analogRead(LDR_TL_PIN);
            int tr = analogRead(LDR_TR_PIN);
            int bl = analogRead(LDR_BL_PIN);
            int br = analogRead(LDR_BR_PIN);

            scanMap[x][y] = (tl + tr + bl + br) / 4.0;
            scanMapTl[x][y] = tl;
            scanMapTr[x][y] = tr;
            scanMapBl[x][y] = bl;
            scanMapBr[x][y] = br;
        }
    }
}

void findMax() {
    scanMax = 0;
    scanMaxX = 0;
    scanMaxY = 0;

    for (int x = 0; x <= 180; x++)
    {
        for (int y = 0; y <= 180; y++)
        {
            if (scanMap[x][y] > scanMax)
            {
                scanMax = scanMap[x][y];
                scanMaxX = x;
                scanMaxY = y;
            }
        }
    }
}

void printMax() {

    Serial.print("Max: ");
    Serial.print(scanMax);
    Serial.print(" at [");
    Serial.print(maxX);
    Serial.print(", ");
    Serial.print(maxY);
    Serial.println("]");
}

void lookAtMax() {
    servoX.write(scanMaxX);
    servoY.write(scanMaxY);
}

void loop()
{
    scan();
    printMax();
    lookAtMax();
    delay(5000);
}
