#include <SoftwareSerial.h>

int pressureAnalogPinC1 = 0;// pin du capteur 1 (gauche)
int pressureAnalogPinC2 = 1;// pin du capteur 2 (haut)
int pressureAnalogPinC3 = 2;// pin du capteur 3 (droite)
int pressureAnalogPinC4 = 3;// pin du capteur 4 (bas)
int pressureReadingC1; // valeur reçue du capteur 1
int pressureReadingC2;// valeur reçue du capteur 2
int pressureReadingC3;// valeur reçue du capteur 3
int pressureReadingC4;// valeur reçue du capteur 4
double barycentreX;// coordonnée x du centre de gravité
double barycentreY;// coordonnée y du centre de gravité
SoftwareSerial BTSerial(3,2);//Rx puis Tx
String message;

void setup(void) {
Serial.begin(9600);
Serial.println("Test Begin");
BTSerial.begin(9600);
BTSerial.println("Initialisation");
}

void loop(void) {
/* Lecture des valeurs des 4 capteurs Flexiforce */
pressureReadingC1 = analogRead(pressureAnalogPinC1);// lecture de la valeur
pressureReadingC2 = analogRead(pressureAnalogPinC2);
pressureReadingC3 = analogRead(pressureAnalogPinC3);
pressureReadingC4 = analogRead(pressureAnalogPinC4);
Serial.println(pressureReadingC1);
Serial.println(pressureReadingC2);
Serial.println(pressureReadingC3);
Serial.println(pressureReadingC4);

/* Limite les erreurs lors des essais à vide / Différence de serrage /A supprimer par la suite ? */
if (pressureReadingC1 < 30 && pressureReadingC2 <30 && pressureReadingC3<30 && pressureReadingC4 <30){
  pressureReadingC1 = 0;
  pressureReadingC2 = 0;
  pressureReadingC3 = 0;
  pressureReadingC4 = 0;
}


/* Calcul et affichage du barycentre */
float voltageC1 = pressureReadingC1 * (5.0 / 1023.0);// Conversion de la valeur reçue en Volts
float voltageC2 = pressureReadingC2 * (5.0 / 1023.0);
float voltageC3 = pressureReadingC3 * (5.0 / 1023.0);
float voltageC4 = pressureReadingC4 * (5.0 / 1023.0); 

barycentreX = (2*voltageC3 + voltageC2+voltageC4)/(voltageC1+voltageC2+voltageC3+voltageC4);
barycentreY = (2*voltageC2 + voltageC1+voltageC3)/(voltageC1+voltageC2+voltageC3+voltageC4);

if (isnan(barycentreX) == 1){barycentreX = 1;}// Si pas de valeur lue, mise du centre à 1
if (isnan(barycentreY) == 1){barycentreY = 1;}

Serial.print("coordonnees X = ");
Serial.println(barycentreX);
Serial.print("coordonnees Y = ");
Serial.println(barycentreY);
Serial.println();
char c;
if (Serial.available()){
c = Serial.read();
//BTSerial.print(c);
}

message = "[BX]" + String(barycentreX) + "[BY]" + String(barycentreY) + "\n";

BTSerial.print(message);

delay(500);// pour pouvoir voir les valeurs, à diminuer pour l'appli
}
