#include "SelfCheckTask.h"
#define MAX_TEMPERATURE 24
#define MIN_TEMPERATURE 17
#define MIN_ANGLE 0
#define MAX_ANGLE 180


void SelfCheckTask::init() {
    this->thermometerManager->setup();
    this->motor->setup();
}

void SelfCheckTask::computeRead() {
    if (this->getState() == SelfCheckTaskState::TEMPERATURE_CHECK) {
        this->thermometerManager->computeRead();
    }
}

void SelfCheckTask::tick() {
    switch (this->getState()) {
    case SelfCheckTaskState::IDLE:
        onIdleState();
        break;
    case SelfCheckTaskState::MECHANIC_CHECK:
        onMechanicCheckState();
        break;
    case SelfCheckTaskState::TEMPERATURE_CHECK:
        onTemperatureCheckState();
        break;
    case SelfCheckTaskState::ASSISTANCE:
        onAssistanceState();
        break;
    }
}

void SelfCheckTask::onIdleState() {
    this->tempo += this -> getPeriod();
    if(this->tempo == MAX_PERIOD){
        this->setState(SelfCheckTaskState::MECHANIC_CHECK);
    }
}

void SelfCheckTask::onMechanicCheckState() {
    this->tempo += this -> getPeriod();
    this -> motor -> returnToStart();
    for(int i = 0; i < MAX_ANGLE; i++){
        this -> motor -> rotateTo(i);
    }

    for(int i = MAX_ANGLE; i < 0; i--){
        this -> motor -> rotateTo(i);
    }

    this->setState(SelfCheckTaskState::TEMPERATURE_CHECK);
}

void SelfCheckTask::onTemperatureCheckState() {
    this->tempo += this -> getPeriod();
    if(this->thermometerManager -> getTemperature() >= MIN_TEMPERATURE && 
       this->thermometerManager -> getTemperature() <= MAX_TEMPERATURE) {
           this->setState(SelfCheckTaskState::IDLE);
           this->tempo = 0;
    }else{
           this->setState(SelfCheckTaskState::ASSISTANCE);
    }
}

void SelfCheckTask::onAssistanceState() {
    this->tempo += this -> getPeriod();
    if(this -> getMessageBus()-> isMessagePresent(MessageType::RECOVER)){
        this -> getMessageBus()->removeMessage(MessageType::RECOVER);
        this -> setState(SelfCheckTaskState::IDLE);
        this->tempo = 0;
    }
}