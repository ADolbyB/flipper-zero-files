#include "flipperLED.h"

void flipperLED::RunSetup() {
#ifdef DISABLE_RGB_LED
  return;
#endif

  pinMode(B_PIN, OUTPUT);
  pinMode(G_PIN, OUTPUT);
  pinMode(R_PIN, OUTPUT);

  if (!settings_obj.loadSetting<bool>("EnableLED")) {
    digitalWrite(B_PIN, HIGH);
    digitalWrite(G_PIN, HIGH);
    digitalWrite(R_PIN, HIGH);
    return;
  }
    
  delay(50);

  digitalWrite(B_PIN, LOW);
  delay(500);
  digitalWrite(B_PIN, HIGH);
  digitalWrite(G_PIN, LOW);
  delay(500);
  digitalWrite(G_PIN, HIGH);
  digitalWrite(R_PIN, LOW);
  delay(500);
  digitalWrite(R_PIN, HIGH);
}

void flipperLED::attackLED() {
#ifdef DISABLE_RGB_LED
  return;
#endif
  if (!settings_obj.loadSetting<bool>("EnableLED"))
    return;
    
  digitalWrite(B_PIN, HIGH);
  digitalWrite(G_PIN, HIGH);
  digitalWrite(R_PIN, HIGH); 
  delay(10);
  digitalWrite(R_PIN, LOW);
}

void flipperLED::sniffLED() {
#ifdef DISABLE_RGB_LED
  return;
#endif
  if (!settings_obj.loadSetting<bool>("EnableLED"))
    return;
    
  digitalWrite(B_PIN, HIGH);
  digitalWrite(G_PIN, HIGH);
  digitalWrite(R_PIN, HIGH);
  delay(10);
  digitalWrite(B_PIN, LOW);
}

void flipperLED::offLED() {
#ifdef DISABLE_RGB_LED
  return;
#endif
  if (!settings_obj.loadSetting<bool>("EnableLED"))
    return;
    
  digitalWrite(B_PIN, HIGH);
  digitalWrite(G_PIN, HIGH);
  digitalWrite(R_PIN, HIGH);
}
void flipperLED::main() {
  // do nothing
}