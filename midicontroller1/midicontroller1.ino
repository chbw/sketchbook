#include <Encoder.h> // Include the Encoder library.
// This must be done before the Control Surface library.
#include <Control_Surface.h> // Include the Control Surface library


USBMIDI_Interface midi;




// Instantiate a CCButton object
CCButton button = {
  // Push button on pin 5:
  5,
  // General Purpose Controller #1 on MIDI channel 1:
  {MIDI_CC::General_Purpose_Controller_5, CHANNEL_1},
};




// Instantiate a CCRotaryEncoder object
CCRotaryEncoder enc = {
  {2, 3},       // pins
  MCU::V_POT_4, // MIDI address (CC number + optional channel)
  1,            // optional multiplier if the control isn't fast enough
};



// Instantiate a CCPotentiometer object
CCPotentiometer potentiometer0 = {
  A0,                                   // Analog pin connected to potentiometer
  {MIDI_CC::Channel_Volume, CHANNEL_1}, // Channel volume of channel 1
};
CCPotentiometer potentiometer1 = {
  A1,                                   // Analog pin connected to potentiometer
  {MIDI_CC::General_Purpose_Controller_1, CHANNEL_1}, // General_Purpose_Controller_1 of channel 1
};
CCPotentiometer potentiometer2 = {
  A2,                                   // Analog pin connected to potentiometer
  {MIDI_CC::General_Purpose_Controller_2, CHANNEL_1}, // General_Purpose_Controller_2 of channel 1
};
CCPotentiometer potentiometer3 = {
  A3,                                   // Analog pin connected to potentiometer
  {MIDI_CC::General_Purpose_Controller_3, CHANNEL_1}, // General_Purpose_Controller_3 of channel 1
};



// The note numbers corresponding to the buttons in the matrix
const int noteOffset = 36;
const AddressMatrix<4, 3> addresses = {{
  {72-noteOffset, 73-noteOffset, 74-noteOffset},
  {75-noteOffset, 76-noteOffset, 77-noteOffset},
  {78-noteOffset, 79-noteOffset, 80-noteOffset},
  {81-noteOffset, 82-noteOffset, 83-noteOffset},
}};

NoteButtonMatrix<4, 3> buttonmatrix = {
  {10, 16, 14, 15}, // row pins
  {9, 8, 7},    // column pins
  addresses,    // address matrix
  CHANNEL_1,    // channel and cable number
};


analog_t reversePot(analog_t raw) {
    // map the value from [minimumValue, maximumValue] to [0, 16383]
    return map(raw, 0, 16383, 16383, 0);
}

void setup() {
  potentiometer0.map(reversePot);
  potentiometer1.map(reversePot);
  potentiometer2.map(reversePot);
  potentiometer3.map(reversePot);

  // Select the correct relative MIDI CC mode.
  // Options:
  //   - TWOS_COMPLEMENT (default)
  //   - BINARY_OFFSET
  //   - SIGN_MAGNITUDE
  // Aliases:
  //   - REAPER_RELATIVE_1
  //   - REAPER_RELATIVE_2
  //   - REAPER_RELATIVE_3
  //   - TRACKTION_RELATIVE
  //   - MACKIE_CONTROL_RELATIVE
  RelativeCCSender::setMode(relativeCCmode::MACKIE_CONTROL_RELATIVE);
  Control_Surface.begin();
}

void loop() {
  Control_Surface.loop();
}
