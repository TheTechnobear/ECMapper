#include "OSCCommunication.h"

OSCCommunication::OSCCommunication() {
    receiver.addListener(this);
    receiver.registerFormatErrorHandler([this](const char *data, int dataSize) {
        std::cout << "invalid OSC data";
    });
    
    startTimer(1000);
}

OSCCommunication::~OSCCommunication() {
    stopTimer();
    sender.disconnect();
    receiver.disconnect();
}

bool OSCCommunication::connectSender(juce::String ip, int port)  {
    this->senderIP = ip;
    this->senderPort = port;
    return sender.connect(senderIP, senderPort);
}

void OSCCommunication::disconnectSender() {
    sender.disconnect();
    senderPort = -1;
}

bool OSCCommunication::connectReceiver(int port)  {
    this->receiverPort = port;
    return receiver.connect(receiverPort);
}

void OSCCommunication::disconnectReceiver() {
    receiver.disconnect();
    receiverPort = -1;
}

void OSCCommunication::oscMessageReceived(const juce::OSCMessage &message) {
    if (message.getAddressPattern() == "/EigenharpMapper/led" && message.size() == 3) {
        std::cout << "message received: " << message[0].getInt32() << " " << message[1].getInt32() << " " << message[2].getInt32();
        sendkeyLEDEventMessage(message[0].getInt32(), message[1].getInt32(), message[2].getInt32());
    }
}

void OSCCommunication::sendDeviceName(const juce::String &name) {
    sender.send("/EigenharpCore/device", name);
}

void OSCCommunication::sendKey(unsigned course, unsigned key, bool a, unsigned p, int r, int y) {
         sender.send("/EigenharpCore/key", (int)course, (int)key, (int)a, (int)p, (int)r, (int)y);
}

void OSCCommunication::sendBreath(unsigned val) {
    sender.send("/EigenharpCore/breath", (int)val);
}

void OSCCommunication::sendStrip(unsigned strip, unsigned val) {
    sender.send("/EigenharpCore/strip", (int)strip, (int)val);
}

void OSCCommunication::sendPedal(unsigned pedal, unsigned val) {
    sender.send("/EigenharpCore/pedal", (int)pedal, (int)val);
}

void OSCCommunication::timerCallback() {
    sender.send("/EigenharpCore/ping");
}

void OSCCommunication::addListener(Listener* listenerToAdd) {
    listeners.add(listenerToAdd);
}

void OSCCommunication::removeListener(Listener* listenerToRemove) {
    jassert(listeners.contains(listenerToRemove));
    listeners.remove(listenerToRemove);
}

void OSCCommunication::sendkeyLEDEventMessage(int course, int key, int colour) {
    listeners.call([this, course, key, colour](Listener& l) { l.keyLEDChanged(this, course, key, colour); });
}
