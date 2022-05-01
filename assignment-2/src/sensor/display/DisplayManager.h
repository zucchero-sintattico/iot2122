#ifndef _DISPLAY_MANAGER_H_
#define _DISPLAY_MANAGER_H_
#define DEFAULT_WIDTH  16
#define DEFAULT_HEIGHT  2
#include <Arduino.h>
#include <String.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "../Setuppable.h"

class DisplayManager : public Setuppable{
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