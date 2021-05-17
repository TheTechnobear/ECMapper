#include "Layout.h"

Layout::Layout(DeviceType::DeviceType instrumentType): valueTree("layout") {
    switch(instrumentType) {
        case DeviceType::Alpha:
            normalKeyCount = 120;
            percKeyCount = 12;
            keyRowCount = 5;
            keyRowLengths[0] = 24;
            keyRowLengths[1] = 24;
            keyRowLengths[2] = 24;
            keyRowLengths[3] = 24;
            keyRowLengths[4] = 24;
            buttonCount = 0;
            stripCount = 2;
            break;
        case DeviceType::Tau:
            normalKeyCount = 72;
            percKeyCount = 12;
            keyRowCount = 4;
            keyRowLengths[0] = 16;
            keyRowLengths[1] = 16;
            keyRowLengths[2] = 20;
            keyRowLengths[3] = 20;
            keyRowLengths[4] = 0;
            buttonCount = 8;
            stripCount = 1;
            break;
        case DeviceType::Pico:
            normalKeyCount = 18;
            percKeyCount = 0;
            keyRowCount = 2;
            keyRowLengths[0] = 9;
            keyRowLengths[1] = 9;
            keyRowLengths[2] = 0;
            keyRowLengths[3] = 0;
            keyRowLengths[4] = 0;
            buttonCount = 4;
            stripCount = 1;
            break;
        default:
            break;
    }
    

    valueTree.setProperty(id_instrumentType, instrumentType, nullptr);
    for (int i = 0; i < normalKeyCount; i++)
        addKeyConfig(EigenharpKeyType::Normal, 0, i);

    if (instrumentType == DeviceType::Pico) {
        for (int i = 0; i < buttonCount; i++)
            addKeyConfig(EigenharpKeyType::Button, 1, i);
    }
    else {
        for (int i = 0; i < percKeyCount; i++)
            addKeyConfig(EigenharpKeyType::Perc, 1, i);
        for (int i = 0; i < buttonCount; i++)
            addKeyConfig(EigenharpKeyType::Button, 2, i);
    }
}

Layout::~Layout() {
}

void Layout::addKeyConfig(EigenharpKeyType keyType, int course, int key) {
    auto keyMap = KeyConfig(keyType, valueTree);
    KeyConfig::KeyId id = { .course = course, .keyNo = key };
    keyMap.setKeyId(id);
    keyConfigs.push_back(keyMap);
}

juce::ValueTree Layout::getValueTree() const {
    return valueTree;
}

void Layout::setValueTree(juce::ValueTree valueTree) {
    this->valueTree.copyPropertiesFrom(valueTree, nullptr);
    for (int i = 0; i < valueTree.getNumChildren(); i++) {
        keyConfigs[i].setValueTree(valueTree.getChild(i));
    }
}

int Layout::getNormalkeyCount() const {
    return normalKeyCount;
}

int Layout::getPercKeyCount() const {
    return percKeyCount;
}

int Layout::getButtonCount() const {
    return buttonCount;
}

int Layout::getStripCount() const {
    return stripCount;
}

int Layout::getKeyRowCount() const {
    return keyRowCount;
}

const int* Layout::getKeyRowLengths() const {
    return keyRowLengths;
}

int Layout::getTotalKeyCount() const {
    return normalKeyCount + percKeyCount + buttonCount;
}

int Layout::getPercKeyStartIndex() const {
    return normalKeyCount;
}

int Layout::getButtonStartIndex() const {
    return normalKeyCount + percKeyCount;
}

DeviceType::DeviceType Layout::getDeviceType() const {
    return (DeviceType::DeviceType)valueTree[id_instrumentType].toString().getIntValue();
}

KeyConfig* Layout::getKeyConfigs() {
    return keyConfigs.data();
}

void Layout::addListener(juce::ValueTree::Listener *listener) {
    valueTree.addListener(listener);
}
