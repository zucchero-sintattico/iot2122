#ifndef _APP_DATA_H_
#define _APP_DATA_H_

#define BEVERAGE_COUNT 3
enum Beverage {
    COFFEE,
    TEA,
    CHOCOLATE
};

class AppData {

private:

    static const int MAX_ITEM_COUNT = 3;

    int availableItemCount[BEVERAGE_COUNT] = { MAX_ITEM_COUNT, MAX_ITEM_COUNT, MAX_ITEM_COUNT };
    Beverage selectedBeverage = COFFEE;
    int sugarLevel = 0; // 0 - 10

public:

    void setSugarLevel(int sugarLevel);
    int getSugarLevel();

    int getAvailableItemCount(Beverage beverage);
    bool consumeItem(Beverage beverage);

    bool selectNextBeverage();
    bool selectPreviousBeverage();

    bool isRefillNeeded();
    void refill();

};

#endif