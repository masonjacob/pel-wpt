#include <Arduino.h>

// Generating Two 180° Out of Phase 50 kHz Square 
// Waves with dead time on Timer1 of an 
// Arduino UNO (Pins 9 and 10)
// Written January 23rd, 2023 by John Wasser

// frequency =  16MHz / (2 * prescaleFactor *  (TOP + 1))
// Correction, because Phase Correct PWM is used: 
// frequency =  16MHz / (2 * prescaleFactor *  TOP)
const unsigned TOP = 80;
const unsigned deadTime = 2; // deadtime in 120ns intervals
// frequency =  16MHz / (2 * 1 *  160)
// frequency =  16MHz / 320
// frequency = 50,000

void setup()
{
  Serial.begin(115200);
  delay(200);

  digitalWrite(9, LOW);
  pinMode(9, OUTPUT);
  digitalWrite(10, LOW);
  pinMode(10, OUTPUT);

  // Stop Timer/Counter1
  TCCR1A = 0;  // Timer/Counter1 Control Register A
  TCCR1B = 0;  // Timer/Counter1 Control Register B
  TIMSK1 = 0;  // Timer/Counter1 Interrupt Mask Register

  // Set Timer/Counter1 to Waveform Generation Mode 8:
  // Phase and Frequency correct PWM with TOP set by ICR1
  TCCR1B |= _BV(WGM13);  // WGM=8
  TCCR1A |= _BV(COM1A1);  // Normal PWM on Pin 9
  TCCR1A |= _BV(COM1B1) | _BV(COM1B0); // Inverted PWM on Pin 10

  ICR1 = TOP;
  // Difference between OCR1A and OCR1B is Dead Time
  OCR1A = (TOP / 2) - deadTime;
  OCR1B = (TOP / 2) + deadTime;

  // Start timer by setting the clock-select bits to non-zero
  TCCR1B |= _BV(CS10); // prescale = 1
}

void loop() {}

// #define G_H1 3
// #define G_L1 5
// #define G_H2 6
// #define G_L2 9 


// // void setup() {
// //     pinMode (9, OUTPUT);
// //     // set up Timer 1
// //     TCCR1A = bit (COM1A0);  // toggle OC1A on Compare Match
// //     TCCR1B = bit (WGM12) | bit (CS10);   // CTC, no prescaling
// //     OCR1A =  80;       // output every cycle

// //     // pinMode(3, OUTPUT);    
// //     // pinMode (11, OUTPUT);
// //     // // set up Timer 1
// //     // TCCR2A = bit (COM2A1);  // toggle OC1A on Compare Match
// //     // TCCR2B = bit (WGM22) | bit (CS20);   // CTC, no prescaling
// //     // OCR2A =  0;       // output every cycle
// // }

// void setup() {
//     pinMode(9, OUTPUT); // PWM pin for Timer 1 (OC1A)
//     pinMode(10, OUTPUT); // PWM pin for Timer 1 (OC1B)
//     pinMode(3, OUTPUT); // PWM pin for Timer 2 (OC2B)
//     pinMode(11, OUTPUT); // PWM pin for Timer 2 (OC2A)

//     noInterrupts(); // Disable interrupts to configure timers

//     // Configure Timer 2 for PWM @ 100 kHz on OC2B.
//     TCCR2A = 
//         1 << COM2B1 | // Clear OC2B on compare match, set OC2B at BOTTOM (non-inverting mode)
//         1 << WGM20  | // Fast PWM mode, top at 0xFF
//         1 << WGM21;   // ...
//     TCCR2B = 
//         1 << WGM22  | // ...
//         1 << CS21;    // No prescaling
//     OCR2A = 19; // 50% duty cycle for Timer 2
//     OCR2B = 8; // 50% duty cycle for Timer 2

//     // Configure Timer 1 for PWM @ 100 kHz on OC1A and OC1B.
//     TCCR1A = 
//         1 << COM1A1 | // Clear OC1A on compare match, set OC1A at BOTTOM (non-inverting mode)
//         1 << COM1B1 | // Clear OC1B on compare match, set OC1B at BOTTOM (non-inverting mode)
//         1 << WGM11;   // Fast PWM mode, top at ICR1
//     TCCR1B = 
//         1 << WGM13 |  // Fast PWM mode, top at ICR1
//         1 << WGM12 |  // ...
//         1 << CS10;    // No prescaling
//     OCR1A = 58; // 31.25% duty cycle for Timer 1 (48% duty cycle is approximately 79 out of 255)
//     OCR1B = 58; // 31.25% duty cycle for Timer 1
//     ICR1 = 159; // Setting TOP value for Timer 1, gives 100 kHz frequency

//     interrupts(); // Enable interrupts after timer configuration
// }


// // void setup() {
// //     // The output will be on digital 3 = PD3 = OC2B.
// //     pinMode(3, OUTPUT);
// //     pinMode(9, OUTPUT);
// //     pinMode(10, OUTPUT);
// //     pinMode(11, OUTPUT);

// //     noInterrupts();

// //     // Configure timer 2 for PWM @ 10 kHz on OC2B.
// //     TCCR2A = 
// //         // 1 << COM2A1 | // Inverting mode for OC2A
// //         // 1 << COM2A0 | // ...
// //         1 << COM2B1 | // Inverting mode for OC2B
// //         // 1 << COM2B0 | // ...
// //         1 << WGM20  | // Fast PWM mode
// //         1 << WGM21;   // ...
// //     TCCR2B = 
// //         1 << WGM22  | // ...
// //         1 << CS21;    // No prescaling
// //     // DDRB = 
// //     //     1 << DDB1 |   // Sets Ports as Outputs, unnessesary *I think*
// //     //     1 << DDB2;
// //     OCR2A = 19; // Sets the duty cycle to 50% (Timer 2 is 16bit vs 8bit for Timer 1, so multply by 2^8 = 256)
// //     OCR2B = 8;

// //     TCCR1A = 
// //         1 << COM1A1 |
// //         1 << COM1A0 |
// //         1 << COM1B1 |
// //         1 << WGM11;
// //     TCCR1B = 
// //         1 << WGM13 |
// //         1 << WGM12 |
// //         1 << CS10;
// //     // DDRB = 
// //     //     1 << DDB1 |
// //     //     1 << DDB2;
// //     OCR1A = 100;
// //     OCR1B = 100;
// //     ICR1 = 159;

// //     interrupts();

// //     // digitalWrite(3, LOW);
// //     // digitalWrite(9, HIGH);
// //     // digitalWrite(10, LOW);
// //     // // digitalWrite(11, LOW);

// //     // TCCR1A = bit(COM1A0)  // toggle OC1A on Compare Match
// //     //        | bit (COM1B0);  // toggle OC1A on Compare Match
// //     // TCCR1B = bit(WGM12) 
// //     //        | bit(CS11);   // CTC, no prescaling
// //     // OCR1A =  9;       // output every cycle
// //     // OCR1B = 9;

// // // Configure timer 2 for PWM @ 10 kHz on OC2B.
// //     // TCCR2A = _BV(COM2B1)  // non-inverting PWM on OC2B
// //     //        | _BV(WGM20)   // mode 7: fast PWM, TOP = OCR2A
// //     //        | _BV(WGM21);  // ditto
// //     // TCCR2B = _BV(WGM22)   // ditto
// //     //        | _BV(CS21);   // clock @ F_CPU / 8
// //     // OCR2A  = 19;          // period = (19 + 1) * 8 CPU cycles
// //     // OCR2B  = 9;           // HIGH for (9 + 1) * 8 CPU cycles
    
// //     // Configure timer 2 for PWM @ 10 kHz on OC2B.
// //     // TCCR2A = bit(COM2A0)
// //     //        | bit(COM2B0);  // non-inverting PWM on OC2B
// //     // TCCR2B = bit(WGM22)   // ditto
// //     //        | bit(CS20);   // clock @ F_CPU
// //     // OCR2A  = 1;

// //     // TCCR1A = bit(COM1A0)  // toggle OC1A on Compare Match
// //     //        | bit (COM1B0);  // toggle OC1A on Compare Match
// //     // TCCR1B = bit(WGM12) 
// //     //        | bit(CS11);   // CTC, no prescaling
// //     // OCR1A =  9;       // output every cycle
// // }

//  void loop() {
//  }

// // Basic example with PWM:

// // void setup() {
// //     // The output will be on digital 3 = PD3 = OC2B.
// //     pinMode(3, OUTPUT);

// //     // Configure timer 2 for PWM @ 10 kHz on OC2B.
// //     TCCR2A = _BV(COM2B1)  // non-inverting PWM on OC2B
// //            | _BV(WGM20)   // mode 7: fast PWM, TOP = OCR2A
// //            | _BV(WGM21);  // ditto
// //     TCCR2B = _BV(WGM22)   // ditto
// //            | _BV(CS20);   // clock @ F_CPU
// //     OCR2A  = 15;
// //     OCR2B  = 7;
// // }

// // void loop() {
// //     // Nothing to do here, the signal is generated in hardware.
// // }


// // basic example with no PWM:
// // 
// //   // set up 8 MHz timer on pin 9
// //   pinMode (9, OUTPUT);
// //   // set up Timer 1
// //   TCCR1A = bit (COM1A0);  // toggle OC1A on Compare Match
// //   TCCR1B = bit (WGM12) | bit (CS10);   // CTC, no prescaling
// //   OCR1A =  0;       // output every cycle






// // /**
// //  * @brief 
// //  * 
// //  * @param frequency The frequency, in Hz, of the square wave to be generated
// //  * @param duration the duration, in seconds, of the square wave to be generated
// //  */
// // void generateSquareWave(int frequency, int duration);

// // void setup() {
// //   // put your setup code here, to run once:
// //   // Serial.begin(9600);
// //   pinMode(G_H1, OUTPUT);
// //   pinMode(G_L1, OUTPUT);
// //   pinMode(G_H2, OUTPUT);
// //   pinMode(G_L2, OUTPUT);
// // }

// // void loop() {
// //     digitalWrite(G_H1, HIGH);
// //     digitalWrite(G_L2, HIGH);
// //     digitalWrite(G_H2, LOW);
// //     digitalWrite(G_L1, LOW);
// //     delayMicroseconds(5);
// //     digitalWrite(G_H1, LOW);
// //     digitalWrite(G_L2, LOW);
// //     digitalWrite(G_H2, HIGH);
// //     digitalWrite(G_L1, HIGH);
// //     delayMicroseconds(5);

// //   // generateSquareWave(100000, 5);
// //   // delay(10000);
// // }

// // void generateSquareWave(int frequency, int duration) {
// //   int delay = 1000000 / frequency / 2;
// //   int loopEnd = (1000000 * duration) / (delay * 2);
// //   Serial.println(loopEnd);
// //   for (int i = 0; i < loopEnd; i++) {
// //     digitalWrite(G_H1, HIGH);
// //     digitalWrite(G_L2, HIGH);
// //     digitalWrite(G_H2, LOW);
// //     digitalWrite(G_L1, LOW);
// //     delayMicroseconds(delay);
// //     digitalWrite(G_H1, LOW);
// //     digitalWrite(G_L2, LOW);
// //     digitalWrite(G_H2, HIGH);
// //     digitalWrite(G_L1, HIGH);
// //     delayMicroseconds(delay);
// //   }
// // }
// // const uint16_t TOGGLE_TIME = 5;  // toggle pin every 5 us

// // void setup() {
// //     pinMode(13, OUTPUT);
// // }

// // void loop() {
// //     static uint16_t last_toggle;
// //     static uint8_t pin_state = LOW;

// //     if ((uint16_t) micros() - last_toggle >= TOGGLE_TIME) {
// //         pin_state = !pin_state;       // invert pin state
// //         digitalWrite(13, pin_state);
// //         last_toggle += TOGGLE_TIME;
// //     }
// // }
