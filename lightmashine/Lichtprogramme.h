#include "Arduino.h"

/*
** Grundeinstellungen
*/

// gibt an ob der Arduino sofort mit dem ersten
// Lichtprogramm loslegt, oder erst auf den
// Einschaltbefehl wartet.
// true - sofort loslegen
// false - warten
#define START_WITH_LIGHT_ON true

// Anzahl der Pins, die am Arduino angesteuert werden sollen.
// Davon haengt die Anzahl Werte ab, die man bei den Lichtprogrammen
// in der horizontalen angegeben werden.
#define PIN_ANZAHL 12

// Pause zwischen der Frames in Millisekunden. Je kleiner, desto schneller.
#define FRAME_PAUSE 100

// Von links nach rechts platziert man sich sich
// die LEDs, zum bequemen LED-Programm bauen spaeter.
// an die jeweilige Position kommt die Pin-Nummer
// an der die LED angeschlossen ist.
uint8_t led_pin_mapping[PIN_ANZAHL] =
// Vorne l/r           Hinten Links    Hinten Rechts
//
// B  w     w  B       B  R  R  R      R  R   R   B
// l  e     e  l       l  o  o  o      o  o   o   l
// i  i     i  i       i  t  t  t      t  t   t   i
// n  s     s  n       n                          n
// k  s     s  k       k                          k
// e           e       e                          e
// r           r       r                          r
 { 0, 1,    2, 3,      4, 5, 6, 7,     8, 9, 10, 11};


// Licht-Programme
const uint8_t leds[][PIN_ANZAHL] PROGMEM = {

// Vorlagen zum kopieren:
//  { X, X,    X, X,      X, X, X, X,     X, X,  X,  X,},
//  { _, _,    _, _,      _, _, _, _,     _, _,  _,  _,},


/*
** Modell 1, 4 LEDs vorne, 8 hinten
*/


/* normal on */
 { _, X,    X, _,      _, X, X, _,     _, X,  X,  _,},
 {  PROGRAM_ENDE},

 /* normal on, with hazard lights */
  {  X,  X,   X,  X,      X, 70, 70,  _,    _, 70, 70,  X,},
  {  X,  X,   X,  X,      X, 70, 70,  _,    _, 70, 70,  X,},
  {  X,  X,   X,  X,      X, 70, 70,  _,    _, 70, 70,  X,},
  {  X,  X,   X,  X,      X, 70, 70,  _,    _, 70, 70,  X,},
  {  _,  X,   X,  _,      _, 70, 70,  _,    _, 70, 70,  _,},
  {  _,  X,   X,  _,      _, 70, 70,  _,    _, 70, 70,  _,},
  {  _,  X,   X,  _,      _, 70, 70,  _,    _, 70, 70,  _,},
  {  _,  X,   X,  _,      _, 70, 70,  _,    _, 70, 70,  _,},
  {  PROGRAM_ENDE},

/* waving */
 { 70, 10,  70, 10,    _, 10, 10,  _,     _, 10, 10,  _,},
 { 60, 20,  60, 20,    _, 15, 15,  _,     _, 15, 15,  _,},
 { 50, 30,  50, 30,    _, 20, 20,  _,     _, 20, 20,  _,},
 { 40, 40,  40, 40,    _, 25, 25,  _,     _, 25, 25,  _,},
 { 30, 50,  30, 50,    _, 30, 30,  _,     _, 30, 30,  _,},
 { 20, 60,  20, 60,    _, 35, 35,  _,     _, 35, 35,  _,},
 { 10, 70,  10, 70,    _, 40, 40,  _,     _, 40, 40,  _,},
 { 20, 60,  20, 60,    _, 50, 50,  _,     _, 50, 50,  _,},
 { 30, 50,  30, 50,    _, 60, 60,  _,     _, 60, 60,  _,},
 { 40, 40,  40, 40,    _, 70, 70,  _,     _, 70, 70,  _,},
 { 50, 30,  50, 30,    _, 85, 85,  _,     _, 85, 85,  _,},
 { 60, 20,  60, 20,    _,  X,  X,  _,     _,  X,  X,  _,},
 {  PROGRAM_ENDE},

/* front party, rear "arrow" */
 {  X,  _,   _,  X,       X,   _,   _,  _,    _,  _,   _,   X,},
 {  _,  X,   X,  _,      80,   X,   _,  _,    _,  _,   X,  80,},
 {  X,  _,   _,  X,       _,  50,   X,  _,    _,   X, 50,  _,},
 {  _,  X,   X,  _,       _,   _,  50,  X,    X,  50,   _,  _,},
 {  X,  _,   _,  X,       _,   _,   _, 50,   50,   _,   _,  _,},
 {  _,  X,   X,  _,       _,   _,   _,  _,    _,   _,   _,  _,},
 {  X,  _,   _,  X,       _,   _,   _,  _,    _,   _,   _,  _,},
 {  _,  X,   X,  _,       _,   _,   _,  _,    _,   _,   _,  _,},
 {  X,  _,   _,  X,       _,   _,   _,  _,    _,   _,   _,  _,},
 {  _,  X,   X,  _,       _,   _,   _,  _,    _,   _,   _,  _,},
 {  X,  _,   _,  X,       _,   _,   _,  _,    _,   _,   _,  _,},
 {  _,  X,   X,  _,       _,   _,   _,  _,    _,   _,   _,  _,},
 {  PROGRAM_ENDE},

/* moderate flashing */
 {  X,  _,   _,  X,       _,   X,   _,  X,    X,   _,   X,  _,},
 {  _,  _,   _,  _,       _,   _,   _,  _,    _,   _,   _,  _,},
 {  _,  X,   X,  _,       _,   _,   _,  _,    _,   _,   _,  _,},
 {  _,  _,   _,  _,       _,   _,   _,  _,    _,   _,   _,  _,},
 {  X,  _,   _,  X,       X,   _,   X,  _,    _,   X,   _,  X,},
 {  _,  _,   _,  _,       _,   _,   _,  _,    _,   _,   _,  _,},
 {  _,  X,   X,  _,       _,   _,   _,  _,    _,   _,   _,  _,},
 {  _,  _,   _,  _,       _,   _,   _,  _,    _,   _,   _,  _,},

 {  PROGRAM_ENDE},

  /* just US-like hazard lights */
 {  X,  _,   _,  X,       X,   _,   _,  _,    _,   _,   _,  X,},
 {  _,  _,   _,  _,       _,   _,   _,  _,    _,   _,   _,  _,},
 {  X,  _,   _,  X,       X,   _,   _,  _,    _,   _,   _,  X,},
 {  X,  _,   _,  X,       X,   _,   _,  _,    _,   _,   _,  X,},
 {  _,  _,   _,  _,       _,   _,   _,  _,    _,   _,   _,  _,},
 {  _,  _,   _,  _,       _,   _,   _,  _,    _,   _,   _,  _,},
 {  _,  _,   _,  _,       _,   _,   _,  _,    _,   _,   _,  _,},
 {  _,  _,   _,  _,       _,   _,   _,  _,    _,   _,   _,  _,},
 {  _,  _,   _,  _,       _,   _,   _,  _,    _,   _,   _,  _,},


 {  PROGRAM_ENDE},

 {FIN}

};




/*
** Erweiterte Einstellungen
*/

// Der Pin, an dem der Empfaenger angeschlossen ist.
#define SIG_PIN A0

#define THROTTLE_PIN A1

/*
* Hier werden die Pin-Nummern
* fuer die LED's, welche spaeter als Bremslicht
* geschaltet werden sollen eingetragen, jeweils durch Komma getrennt.
* Es ist darauf zu achten, dass nur Pin's, welche nicht für das Lichprogramm
* als Backfire oder für Signale vom Empfänger genutzt werden eingetragen werden.
*/
const uint8_t led_pin_brakelights[] = { A2, A3, A4 };

/*
* Hier werden die Pin-Nummern
* fuer die LED's, welche spaeter als Backfire/ Anti-Lag
* geschaltet werden sollen eingetragen, jeweils durch Komma getrennt.
* Es ist darauf zu achten, dass nur Pin's, welche nicht für das Lichprogramm,
* als Bremslicht oder für Signale vom Empfänger genutzt werden eingetragen werden.
*/
const uint8_t led_pin_backfire[] = { 12, 13 };

// Die Signalwerte, die der Empfaenger fuer mindest und maximal Wert uebermittelt.
#define RECIEVER_MIN 1378
#define RECIEVER_MAX 1885

// Zeitraum in Millisekunden. Dieser wird verwendet um festzulegen ab welcher Dauer und wie Lightmashine
// den ueber Funke uebertragenen Befehl interpretiert.
// Bei Hebel-Steuerung: Hebel muss laenger als dieser Wert in Position gehalten werden, damit 
//                      Lightmashine das als Befehl erkennt.
// Bei Knopf-Steuerung: Knopf laenger als dieser Wert gedrueckt: Licht an/aus. Knopf kuerzer als der Wert
//                      gedrueckt: naechstes Lichtprogramm.
#define ACTIVATE_PERIOD 800

// Verwendeter Funke-Umschalter.
// 1 - fuer Umschalten per Hebel
// 2 - fuer Umschalten per Knopf
#define SWITCH_TYPE 2

uint8_t modelSelectPins[] = {NICHT_DA};
uint8_t led_pin_mapping_2[PIN_ANZAHL] = {};
// {12,10,11,     6, 9, 13,    2, 3, 4,         7, 5, 8,   NICHT_DA, NICHT_DA};
// {12,10,NICHT_DA, NICHT_DA, NICHT_DA, NICHT_DA,  NICHT_DA, NICHT_DA, NICHT_DA, NICHT_DA, NICHT_DA, NICHT_DA,   NICHT_DA, NICHT_DA};

uint8_t led_pin_mapping_3[PIN_ANZAHL] = { };
 
 
uint8_t led_pin_mapping_4[PIN_ANZAHL] = { };


 
uint8_t led_pin_mapping_5[PIN_ANZAHL] = { };


