#ifndef _DISPLAY_MANAGER_H_
#define _DISPLAY_MANAGER_H_
#define DEFAULT_WIDTH  16
#define DEFAULT_HEIGHT  2
#include "iot/actuator/Actuator.h"
#include <String.h>
#include <LiquidCrystal_I2C.h>
class DisplayManager : public Actuator {
private:
    int address = 0x27;
    int column = 0;
    int row = 0;
    LiquidCrystal_I2C lcd = LiquidCrystal_I2C(address, DEFAULT_WIDTH, DEFAULT_HEIGHT);

public:
    DisplayManager(int address, int width, int height);
    void setup();
    void changeCursor(int row, int column);
    void print(String message);
    void clear();

};

#endif //DISPLAYMANAGER_H