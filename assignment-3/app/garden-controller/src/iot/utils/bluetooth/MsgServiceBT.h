#ifndef __MSGSERVICEBT__
#define __MSGSERVICEBT__

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "iot/utils/serial/MsgService.h"

class MsgServiceBT {

public:
  MsgServiceBT() {}
  MsgServiceBT(int rxPin, int txPin);
  void init();
  bool isMsgAvailable();
  Msg* receiveMsg();
  bool sendMsg(Msg msg);

private:
  String content;
  Msg* availableMsg;
  SoftwareSerial* channel;

};

#endif