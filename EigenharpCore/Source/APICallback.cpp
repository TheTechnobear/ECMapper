#include "APICallback.h"

APICallback::APICallback(EigenApi::Eigenharp& eh, OSC::OSCMessageFifo *sendQueue) : eh_(eh) {
    this->sendQueue = sendQueue;
}

void APICallback::device(const char* dev, DeviceType dt, int rows, int cols, int ribbons, int pedals) {
    deviceId = dev;
    switch(cols) {
        case 2:
            currentDevice = Pico;
            break;
        case 4:
            currentDevice = Tau;
            break;
        case 5:
            currentDevice = Alpha;
            break;
        default:
            currentDevice = None;
            break;
    }
    
    OSC::Message msg {
        .type = OSC::MessageType::Device,
        .key = 0,
        .course = 0,
        .active = 0,
        .pressure = 0,
        .roll = 0,
        .yaw = 0,
        .value = 0,
        .pedal = 0,
        .strip = 0,
        .device = currentDevice
    };
    sendQueue->add(&msg);

    
    
//    
//    std::cout << "device " << dev << " (" << dt << ") " << rows << " x " << cols << " strips " << ribbons << " pedals " << pedals << std::endl;
}

void APICallback::key(const char* dev, unsigned long long t, unsigned course, unsigned key, bool a, unsigned p, int r, int y) {
    static int counter = 0;
    counter++;
    if (counter%1024 == 0)
        std::cout  << "key " << dev << " @ " << t << " - " << course << ":" << key << ' ' << a << ' ' << p << ' ' << r << ' ' << y << std::endl;
    
    OSC::Message msg {
        .type = OSC::MessageType::Key,
        .key = key,
        .course = course,
        .active = a,
        .pressure = p,
        .roll = r,
        .yaw = y,
        .value = 0,
        .pedal = 0,
        .strip = 0,
        .device = currentDevice
    };
    sendQueue->add(&msg);
}
void APICallback::breath(const char* dev, unsigned long long t, unsigned val) {
//    std::cout  << "breath " << dev << " @ " << t << " - "  << val << std::endl;
    OSC::Message msg {
        .type = OSC::MessageType::Breath,
        .key = 0,
        .course = 0,
        .active = 0,
        .pressure = 0,
        .roll = 0,
        .yaw = 0,
        .value = val,
        .pedal = 0,
        .strip = 0,
        .device = currentDevice
    };
    sendQueue->add(&msg);
}

void APICallback::strip(const char* dev, unsigned long long t, unsigned strip, unsigned val) {
//    std::cout  << "strip " << dev << " @ " << t << " - " << strip << " = " << val << std::endl;
    
    OSC::Message msg {
        .type = OSC::MessageType::Strip,
        .key = 0,
        .course = 0,
        .active = 0,
        .pressure = 0,
        .roll = 0,
        .yaw = 0,
        .value = val,
        .pedal = 0,
        .strip = strip,
        .device = currentDevice
    };
    sendQueue->add(&msg);
}

void APICallback::pedal(const char* dev, unsigned long long t, unsigned pedal, unsigned val) {
//    std::cout  << "pedal " << dev << " @ " << t << " - " << pedal << " = " << val << std::endl;
    OSC::Message msg {
        .type = OSC::MessageType::Pedal,
        .key = 0,
        .course = 0,
        .active = 0,
        .pressure = 0,
        .roll = 0,
        .yaw = 0,
        .value = val,
        .pedal = pedal,
        .strip = 0,
        .device = currentDevice
    };
    sendQueue->add(&msg);
}
