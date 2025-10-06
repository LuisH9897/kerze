#include <Arduino.h>

//Pinbelegung
const int ROT = 9;
const int GRUEN = 10;
const int BLAU = 11;
const int DRAHTFALLE = 4;

//Variablen
long zaehler = 0;
int erschuetterung_zaehler = 0;
byte betriebsart = 1;
boolean erschuetterung_status;
float helligkeit = 0.0;
float zufallsfaktor[4]; //Z0 bis Z3

// Funktionsdeklarationen
void HSV(int, double, double);
void zufallsfaktoren();
void erschuetterung ();

void setup() {
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  pinMode(DRAHTFALLE, INPUT_PULLUP);

  erschuetterung_status = digitalRead(DRAHTFALLE);

  randomSeed(analogRead(A0));
}

void loop() {
}

//Funktionsdefinitionen

//HSV-Farbenraum
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

//Erschuetterungserkennung
void erschuetterung(){
  if (digitalRead(DRAHTFALLE) != erschuetterung_status) {
    erschuetterung_status = !erschuetterung_status;
    erschuetterung_zaehler +=100;
  }

  if (erschuetterung_zaehler > 300) {
    betriebsart = (betriebsart + 1) %4;
    erschuetterung_zaehler = 0;
  }

  if (betriebsart == 0) { //Alles ist aus
    analogWrite(ROT, 0);
    analogWrite(GRUEN, 0);
    analogWrite(BLAU, 0);
  }

  if(betriebsart == 1) {  //Kerzenflackern
    helligkeit = zufallsfaktor[0] * sin(zaehler*0.02)
    + zufallsfaktor[1] * sin(zaehler*0.03)
    + zufallsfaktor[2] * sin(zaehler*0.07)
    + zufallsfaktor[3] * sin(zaehler*0.11);

    int rot = map(helligkeit * 100, -200, 200, 5, 255);
    int gruen = map(helligkeit * 100, -200, 200, 1, 255);

    analogWrite(ROT, constrain(rot, 5, 255));
    analogWrite(GRUEN, constrain (gruen, 1, 100));

    if (zaehler % 1000 ==0) {zufallsfaktoren();} //nach ca. 25 Sek.neue Zufallsfaktoren ermitteln
  }

  if (betriebsart == 2) {HSV(zaehler%360, 1, 1);} //Party-Modus bei voller Saettigung (1) und voller Helligkeit (1)

  if (betriebsart ==3) {  //dauerhaft weiss
    analogWrite(ROT, 255);
    analogWrite(GRUEN, 255);
    analogWrite(BLAU, 255);
  }

  zaehler++;
  delay(25);
}