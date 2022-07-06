#include "Arduino.h"
#include "MsgService.h"

String content;

MsgServiceClass MsgService;

bool MsgServiceClass::isMsgAvailable() {
  return msgAvailable;
}

Msg* MsgServiceClass::receiveMsg() {
  if (msgAvailable) {
    Msg* msg = currentMsg;
    msgAvailable = false;
    currentMsg = NULL;
    content = "";
    return msg;
  }
  else {
    return NULL;
  }
}

void MsgServiceClass::init(int bufferSize) {
  Serial.begin(9600);
  content.reserve(bufferSize);
  content = "";
  currentMsg = NULL;
  msgAvailable = false;
}

void MsgServiceClass::sendMsg(const String& msg) {
  Serial.println(msg);
}

void serialEvent() {
  /* reading the content */
  while (Serial.available() && !MsgService.msgAvailable) {
    char ch = (char)Serial.read();
    if (ch == '\r') continue;
    if (ch == '\n') {
      MsgService.currentMsg = new Msg(content);
      MsgService.msgAvailable = true;
    }
    else {
      content += ch;
    }
  }
}

bool MsgServiceClass::isMsgAvailable(Pattern& pattern) {
  return (msgAvailable && pattern.match(*currentMsg));
}

Msg* MsgServiceClass::receiveMsg(Pattern& pattern) {
  if (msgAvailable && pattern.match(*currentMsg)) {
    Msg* msg = currentMsg;
    msgAvailable = false;
    currentMsg = NULL;
    content = "";
    return msg;
  }
  else {
    return NULL;
  }

}


