#define PERIODE_RELEVE 10000  // période relevé et envoi en ms

#include <Arduino.h>
#include <Wire.h>
#include <SSD1306.h>

// put function declarations here:
int myFunction(int, int);

void setup() {
  
  // Initialiser la communication série (facultatif pour le débogage)
  Serial.begin(115200);
  SSD1306 ecranOled(0x3c, 5, 4);

  // Initialiser l'écran OLED
  ecranOled.init();
  ecranOled.clear();

  ecranOled.setFont(ArialMT_Plain_16);

  // Dessiner le texte (nom de l'application et version)
  ecranOled.drawString(10, 10, "NomApp: MonApp");
  ecranOled.drawString(10, 30, "Version: 1.0");

  // Afficher sur l'écran
  ecranOled.display();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Vitesse de transmission :");
  Serial.println(115200);
  Serial.println();
  delay(3000);

 float niveauSonoreMoy = 0; 
      int periodeReleve = PERIODE_RELEVE / son.tempsEchantillon; 


 }

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}
