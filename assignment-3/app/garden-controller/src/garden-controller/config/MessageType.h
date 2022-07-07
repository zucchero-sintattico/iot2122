#ifndef _MESSAGE_TYPE_H_
#define _MESSAGE_TYPE_H_

#include <Arduino.h>
enum MessageType : uint8_t {

    // ServiceCommunicator -> IrrigationController
    NOTIFY_OPEN_IRRIGATOR,
    NOTIFY_CLOSE_IRRIGATOR,

};

#endif