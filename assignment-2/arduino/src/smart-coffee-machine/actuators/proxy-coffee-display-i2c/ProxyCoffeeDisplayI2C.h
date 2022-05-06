#ifndef _PROXY_COFFEE_DISPLAY_I2C_H_
#define _PROXY_COFFEE_DISPLAY_I2C_H_

#include "../coffee-display-i2c/CoffeeDisplayI2C.h"

class ProxyCoffeeDisplayI2C : public CoffeeDisplayI2C {

public:
    ProxyCoffeeDisplayI2C() : CoffeeDisplayI2C() {};
    ProxyCoffeeDisplayI2C(int width, int height) : CoffeeDisplayI2C(width, height) {};
    ProxyCoffeeDisplayI2C(int address, int width, int height) : CoffeeDisplayI2C(address, width, height) {};

};
#endif