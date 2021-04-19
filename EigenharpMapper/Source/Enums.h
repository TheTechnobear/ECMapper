#pragma once

enum InstrumentType {
    Alpha = 1,
    Tau = 2,
    Pico = 3
};

enum KeyMappingType {
    None = 0,
    Note = 10,
    MidiCC = 20,
    Internal = 30
};

enum EigenharpKeyType {
    Normal = 1,
    Perc,
    Button
};

enum KeyColour {
    Off = 0,
    Green,
    Yellow,
    Red
};
