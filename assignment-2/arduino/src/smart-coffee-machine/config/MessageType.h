#ifndef _MESSAGE_TYPE_H_
#define _MESSAGE_TYPE_H_

#include <Arduino.h>
enum MessageType : uint8_t {

    // PresenceTask's messages
    ACTIVATE_PRESENCE_TASK,
    DEACTIVATE_PRESENCE_TASK,

    // Beverage's messages
    ACTIVATE_BEVERAGE_SELECTOR_TASK,
    ACTIVATE_BEVERAGE_MAKER_TASK,

    // ApplicationCommunicatorTask's messages
    REFILL,
    RECOVER,

};

#endif