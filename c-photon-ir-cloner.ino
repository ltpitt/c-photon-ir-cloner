/*
 * IRCloner - Implementation of a IR cloner using IRTransmitter and IRremote
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * An IR LED must be connected to input IR_PIN
 * A LED must be connected to input LED_PIN
 * Version 0.1 June, 2016
 * Davide Nastri - http://www.davidenastri.it
 * http://github.com/ltpitt
 */

// IR Transmitter Library
#include <IRTransmitter.h>
// IR Receiver Library
#include <IRremote.h>

// Here we specify the infrared led pin
#define IR_PIN D4
// Here we specify the visual feedback led pin
#define LED_PIN D7

// Here we specify the infrared receiver pin
int RECV_PIN = D2;

// Initializing IRReceiver
IRrecv irrecv(RECV_PIN);
decode_results results;

// Initializing IRTransmitter
IRTransmitter transmitter(IR_PIN, LED_PIN);

// Raw data example
unsigned int data[67] = {9000, 4450, 550, 550, 600, 500, 600, 550, 550, 1650, 600, 550, 550, 550, 600, 500, 600, 550,
                            600, 1600, 600, 1650, 600, 1650, 600, 500, 600, 1650, 600, 1600, 600, 1650, 600, 1650, 600,
                            500, 600, 1650, 600, 1650, 550, 550, 600, 1650, 550, 550, 600, 500, 600, 550, 550, 1650,
                            600, 550, 550, 550, 600, 1650, 550, 550, 600, 1650, 550, 1650, 650, 1600,
                            600};  // NEC 10EF6897

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  
  // Sending via IR data    
  transmitter.Transmit(data, sizeof(data) / sizeof(data[0]));

  // Receiving IR signal and printing it using serial port
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
  
}
