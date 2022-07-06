#ifndef _MESSAGE_TYPE_H_
#define _MESSAGE_TYPE_H_

#include <Arduino.h>
enum MessageType : uint8_t {


    // ServiceCommunicator -> All
    // Publish and remove at next tick
    NOTIFY_AUTO_STATUS,
    NOTIFY_ALARM_STATUS,
    NOTIFY_MANUAL_STATUS,

    // ServiceCommunicator -> IrrigationManager
    OPEN_IRRIGATOR,
    CLOSE_IRRIGATOR,

    // IrrigationManager -> ServiceCommunicator
    NOTIFY_IRRIGATOR_OPENED,
    NOTIFY_IRRIGATOR_CLOSED,





};

#endif