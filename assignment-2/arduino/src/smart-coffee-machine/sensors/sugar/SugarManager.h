#ifndef _SUGAR_MANAGER_H_
#define _SUGAR_MANAGER_H_

#include "../potentiometer/PotentiometerManager.h"

class SugarManager : public PotentiometerManager {

    public:
    SugarManager(int pin);
    int getPercentage();

};
#endif