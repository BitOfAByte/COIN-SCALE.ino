#include <SoftwareSerial.h> 
const byte HC12RxdPin = 10;                  // Recieve Pin on HC12 
const byte HC12TxdPin = 11;                  // Transmit Pin on HC12 
SoftwareSerial HC12(HC12TxdPin, HC12RxdPin);

void setup() {
	Serial.begin(9600);
	HC12.begin(9600);
	Serial.print("\nFUCKING WORK\n");
}

// the loop function runs over and over again until power down or reset
void loop() {
	if (HC12.available()) {
		Serial.write(HC12.read());
  }
	if (Serial.available()) {
		HC12.write(Serial.read());
	}
}
