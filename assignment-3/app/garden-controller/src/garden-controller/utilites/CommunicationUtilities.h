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
        updateMessage.digitalLed1active = message.charAt(7) == '1';
        updateMessage.digitalLed2active = message.charAt(9) == '1';
        updateMessage.analogLed1value = message.charAt(11) - '0';
        updateMessage.analogLed2value = message.charAt(13) - '0';
        updateMessage.irrigatorValue = message.charAt(15) - '0';
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
        return message.startsWith("STATUS_CHANGE:");
    }

    static StatusUpdateMessage getStatusUpdateMessage(String message) {
        StatusUpdateMessage statusUpdateMessage;
        String messageStatus = message.substring(14);
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
        statusMessage += String(appData->getAnalogLed1Value());
        statusMessage += ",";
        statusMessage += String(appData->getAnalogLed2Value());
        statusMessage += ",";
        statusMessage += appData->isIrrigatorOpen() ? "1" : "0";
        statusMessage += ",";
        statusMessage += String(appData->getIrrigationSpeed());
        return statusMessage;
    }
};

#endif