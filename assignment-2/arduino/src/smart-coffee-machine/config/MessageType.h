#ifndef _MESSAGE_TYPE_H_
#define _MESSAGE_TYPE_H_

enum MessageType {

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