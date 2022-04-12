#ifndef BUTTONS_MANAGER_H
#define BUTTONS_MANAGER_H

#include <stdint.h>

/**
 * The manager for the buttons that handle the interrupts and manage the buttons states.
 */
class ButtonsManager {

    private:

    /// The current ButtonsManager instance.
    static ButtonsManager* currentManager;

    /**
     * the interrupt handler for the buttons
     */
    static void handleInterrupt();

    /**
     * Set the current manager.
     */
    static void attachCurrentManager(ButtonsManager* manager);

    /**
     * Check if an interrupt is caused by the bouncing of a button.
     */
    static bool isBouncingInterrupt();

    private:

    /// The buttons' pins.
    uint8_t buttonPins[4];

    /// The states of the buttons.
    volatile bool buttonStates[4];

    public:
    /**
     * Create a new ButtonsManager.
     * @param buttonPins the pins of the buttons.
     */
    ButtonsManager(uint8_t buttonPins[4]);

    /**
     * Setup the buttons manager.
     * ! This method must be called in arduino setup() !
     */
    void setup();

    /**
     * Enable the interrupts for the buttons.
     */
    void start();

    /**
     * Disable the interrupts for the buttons.
     */
    void stop();

    /**
     * Check if a button has been pressed.
     * @return true if a button has been pressed, false otherwise.
     */
    bool hasAnyButtonBeenPressed();

    /**
     * Get the index of the pressed button.
     * @return the index of the pressed button.
     */
    uint8_t getPressedButtonIndex();

    /**
     * Release the pressed buttons.
     */
    void releasePressedButton();

    private:
    /**
     * Set the pressed state of a button.
     * @param index the index of the button.
     */
    void setButtonPressed(uint8_t index);

};

#endif