/* DDS
 * Example: Simple Sin
 * This is a simple example that outputs a sin 
 * wave on pin 3.
*/

#define DDS_REFCLK_DEFAULT 9600
#include <DDS.h>

#define PWM_PIN 3

#define DDS_USE_ONLY_TIMER2 false
#define TIMER2_PHASE_ADVANCE 24

DDS dds;

void setup() {
  pinMode(PWM_PIN, OUTPUT);
  digitalWrite(PWM_PIN, LOW);
  
  dds.start();
  dds.startPhaseAccumulator(DDS_USE_ONLY_TIMER2);
  dds.playWait(600, 3000);
  dds.on();
  //dds.setAmplitude(31);
}

void loop() {
  dds.setFrequency(2200);
}


#if DDS_USE_ONLY_TIMER2
ISR(TIMER2_OVF_vect) {
  static unsigned char tcnt = 0;
  if(++tcnt == TIMER2_PHASE_ADVANCE) {
    tcnt = 0;
    dds.clockTick();
  }
}
#else // Use the ADC timer instead
ISR(ADC_vect) {
  if(false){
    static unsigned char tcnt = 0;
    TIFR1 = _BV(ICF1); // Clear the timer flag
    if(++tcnt == 4) {
      tcnt = 0;
    }
    dds.clockTick();
  }
}
#endif