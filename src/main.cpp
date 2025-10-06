#include <Arduino.h>

//Pinbelegung
#define ROT = 9
#define GRUEN = 10
#define BLAU = 11
#define DRAHTFALLE = 4

//Variablen
long zaehler = 0;
int erschuetterung_zaehler = 0;
byte betriebsart = 1;
boolean erschuetterung_status;
float helligkeit = 0.0;
float zufallsfaktor[4]; //Z0 bis Z3

// Funktionsdeklarationen
void HSV(int, double, double);

void setup() {
}

void loop() {
}

//Funktionsdefinitionen
void HSV(int H, double S, double V) {
  //Hier machen wir uns den HSV-Farbraum zunutze. Der entsprechende Algorithmus ist im Internet zu finden.

  double R = 0, G = 0, B = 0;

  //Dominierende Farbe bestimmen und Hilfswerte bestimmen
  int h_i = (int) floor(H/60.0);

  double f = H/60.0 - h_i;
  double p = V * (1-S);
  double q = V * (1-S*f);
  double t = V * (1-S*(1-f));

  switch(h_i){  //Hilfswerte werden aufgeteilt. Dominierende Farbe als Kriterium

    case 0: //rot dominiert, Tendenz zu gruen
      R = V;
      G = t;
      B = p;
      break;
    case 1: //gruen dominiert ,Tendenz zu rot
      R = q;
      G = V;
      B = p;
      break;
      case 2: //gruen dominiert, Tendenz zu blau
      R = p;
      G = V;
      B = t;
      break;
    case 3: //blau dominiert ,Tendenz zu gruen
      R = p;
      G = q;
      B = V;
      break;
      case 4: //blau dominiert, Tendenz zu rot
      R = t;
      G = p;
      B = V;
      break;
    case 5: //rot dominiert ,Tendenz zu blau
      R = V;
      G = p;
      B = q;
      break;
  }

  //Wertebereich eingrenzen
  int rot = constrain ((int)255*R,0,255);
  int gruen = constrain ((int)255*G,0,255);
  int blau = constrain ((int)255*B,0,255);

  analogWrite(ROT, rot);
  analogWrite(GRUEN, gruen);
  analogWrite(BLAU, blau);
}