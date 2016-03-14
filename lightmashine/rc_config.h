#include "Arduino.h"

/*
* Empfaengerkonfiguration.
*/

// Der Pin, an dem der Schalkanal des Empfaengers angeschlossen ist.
// (Das is meisst der 3. oder 4. Kanal)
#define SIG_PIN A0

// Der Pin an dem der Gaskanal angeschlossen wird( 2. Kanal).
#define THROTTLE_PIN A1

/*
* Zeitraum in Millisekunden.
* Dies ist die Zeit, welcher der Gaskanal mindestens in Neutralstellung verharren muss,
* bevor Standby aktiviert wird.
*/
#define STANDBY_WAIT_TIME 5000

// Die Signalwerte, die der Empfaenger fuer mindest und maximal Wert uebermittelt.
#define RECIEVER_MIN 1078
#define RECIEVER_MAX 1885

// Zeitraum in Millisekunden. Dieser wird verwendet um festzulegen ab welcher Dauer und wie Lightmashine
// den ueber Funke uebertragenen Befehl interpretiert.
// Bei Hebel-Steuerung: Hebel muss laenger als dieser Wert in Position gehalten werden, damit
//                      Lightmashine das als Befehl erkennt.
// Bei Knopf-Steuerung: Knopf laenger als dieser Wert gedrueckt: Licht an/aus. Knopf kuerzer als der Wert
//                      gedrueckt: naechstes Lichtprogramm.
#define ACTIVATE_PERIOD 500

// Verwendeter Funke-Umschalter.
// 1 - fuer Umschalten per Hebel
// 2 - fuer Umschalten per Knopf
#define SWITCH_TYPE 2

/*
* Gaswert ab dem Backfire beginnt.
* In Prozent, 0-100%
*/
#define BACKFIRE_START 70

/*
* Intensitaet vom Backfire.
* Je groesser desto laenger der maximale Abstand zwischen 2x "blitzen".
* Werte am besten zwischen 15 und 70 sind brauchbar.
* Je spaeter Backfire beginnt( groesseres BACKFIRE_START), desto kleiner kann dieser Wert sein.
*/
#define BACKFIRE_INTENSITY 40


/*
* VORSICHT: Diese Einstellung koenne ggf. zu einer Fehlfunktion führen.
*/

// Dies ist die Empfindlichkeit fuer den Gaskanal.
// neutral + - this value is still considered neutral e.g. in isBraking-method
#define THROTTLE_NEUTRAL_RANGE 15
