#ifndef _COMMUNICATION_UTILITIES_H_
#define _COMMUNICATION_UTILITIES_H_

#include <Arduino.h>
#include "garden-controller/config/data/AppData.h"

struct UpdateMessage {
    bool digitalLed1active;
    bool digitalLed2active;
    uint8_t analogLed1value;
    uint8_t analogLed2value;
    uint8_t irrigatorValue;
};

enum Commands {
    OPEN_IRRIGATOR,
    CLOSE_IRRIGATOR,
};

struct CommandMessage {
    Commands command;
};

struct StatusMessage {
    bool digitalLed1active;
    bool digitalLed2active;
    uint8_t analogLed1value;
    uint8_t analogLed2value;
    bool irrigatorOpen;
    uint8_t irrigatorValue;
};

struct StatusUpdateMessage
{
    Status status;
};

class CommunicationUtilities {

public:
    static bool isUpdateMessage(String message) {
        return message.startsWith("UPDATE:");
    }

    static UpdateMessage getUpdateMessage(String message) {
        UpdateMessage updateMessage;
        updateMessage.digitalLed1active = message.substring(7, 8) == "1";
        updateMessage.digitalLed2active = message.substring(8, 9) == "1";
        updateMessage.analogLed1value = message.substring(9, 10).toInt();
        updateMessage.analogLed2value = message.substring(10, 11).toInt();
        updateMessage.irrigatorValue = message.substring(11, 12).toInt();
        return updateMessage;
    }

    static bool isCommandMessage(String message) {
        return message.startsWith("COMMAND:");
    }

    static CommandMessage getCommandMessage(String message) {
        CommandMessage commandMessage;
        String commandString = message.substring(8);
        if (commandString == "OPEN_IRRIGATOR") {
            commandMessage.command = OPEN_IRRIGATOR;
        }
        else if (commandString == "CLOSE_IRRIGATOR") {
            commandMessage.command = CLOSE_IRRIGATOR;
        }
        return commandMessage;
    }

    static bool isStatusUpdateMessage(String message) {
        return message.startsWith("STATUS_UPDATE:");
    }

    static StatusUpdateMessage getStatusUpdateMessage(String message) {
        StatusUpdateMessage statusUpdateMessage;
        String messageStatus = message.substring(13);
        if (messageStatus == "AUTO") {
            statusUpdateMessage.status = Status::AUTO;
        }
        else if (messageStatus == "MANUAL") {
            statusUpdateMessage.status = Status::MANUAL;
        }
        else if (messageStatus == "ALARM") {
            statusUpdateMessage.status = Status::ALARM;
        }
        return statusUpdateMessage;
    }

    static String getStatusMessageFromAppData(AppData* appData) {
        String statusMessage = "STATUS:";
        statusMessage += appData->isDigitalLed1Active() ? "1" : "0";
        statusMessage += ",";
        statusMessage += appData->isDigitalLed2Active() ? "1" : "0";
        statusMessage += ",";
        statusMessage += appData->getAnalogLed1Value();
        statusMessage += ",";
        statusMessage += appData->getAnalogLed2Value();
        statusMessage += ",";
        statusMessage += appData->isIrrigatorOpen() ? "1" : "0";
        statusMessage += ",";
        statusMessage += appData->getIrrigationSpeed();
        return statusMessage;
    }
};

#endif