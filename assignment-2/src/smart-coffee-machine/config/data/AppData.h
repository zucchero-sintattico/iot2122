#ifndef _APP_DATA_H_
#define _APP_DATA_H_


class AppData {

    private:

    static const int MAX_AVAILABLE_COFFEE = 10;
    static const int MAX_AVAILABLE_TEA = 10;
    static const int MAX_AVAILABLE_CHOCOLATE = 10;

    int availableCoffee = MAX_AVAILABLE_COFFEE;
    int availableTea = MAX_AVAILABLE_TEA;
    int availableChocolate = MAX_AVAILABLE_CHOCOLATE;

    public:

    int getAvailableCoffee();
    int getAvailableTea();
    int getAvailableChocolate();

    bool consumeCoffee();
    bool consumeTea();
    bool consumeChocolate();

    void refill();

};

#endif