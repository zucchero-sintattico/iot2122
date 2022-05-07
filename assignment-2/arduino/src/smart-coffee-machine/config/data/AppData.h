#ifndef _APP_DATA_H_
#define _APP_DATA_H_

#include <Arduino.h>
#define BEVERAGE_COUNT 3
#define MAX_ITEM_COUNT 3

enum Beverage : uint8_t {
    COFFEE,
    TEA,
    CHOCOLATE
};

enum Status : uint8_t {
    IDLE,
    WORKING,
    ASSISTANCE
};

class AppData {

private:
    uint8_t availableItemCount[BEVERAGE_COUNT] = { MAX_ITEM_COUNT, MAX_ITEM_COUNT, MAX_ITEM_COUNT };
    Beverage selectedBeverage = COFFEE;
    uint8_t sugarLevel = 0; // 0 - 100
    Status status = Status::IDLE;
    int selfCheckPerformedCount = 0;

public:

    Beverage getSelectedBeverage();
    String getSelectedBeverageToString();

    void setSugarLevel(uint8_t sugarLevel);
    uint8_t getSugarLevel();

    uint8_t getAvailableItemCount(Beverage beverage);
    bool consumeItem(Beverage beverage);

    bool selectNextBeverage();
    bool selectPreviousBeverage();

    bool isRefillNeeded();
    void refill();

    void setStatus(Status status);
    Status getStatus();

    void increaseSelfCheckPerformed();
    int getSelfCheckPerformedCount();
};

#endif