
/*
   Toerenteller met Arduino Uno / Nano / Mini Pro door Frits Sijbel en Toin van Daal
   Het circuit:
   Arduino:
   Sensor aan Gnd, 5V+ en D3 gebruiken voor de digitale uitgang van de Hall of IR sensor 
   4 posities LED display met TM1637 driver chip aan Gnd, 5V+ en D6 voor de dio en D7 voor de clk
*/

#include "TM1637.h"                                             // nodig voor het 4 digit display
int Led4DP = 6 ;                                                // Data Puls aansluiting
int Led4CP = 7 ;                                                // Clock Puls aansluiting
TM1637 Led4Display(Led4CP,Led4DP);

                                                                // initialisatie en declaratie van globale constanten en variabelen:
   const int SpeedSensorPin = 3;                                // Digital input pin that the sensor is attached to
   int Seconde = 250;                                           // Aantal clocktikken hoelang een meting duurt.
   int Secondefactor = 4;
   volatile int SpeedSensorValue = 0;                           // value read from the speedsensor
   int VerstrekenTijd = 0;                                      // Meet de tijd tussen millis() en BewaarSec om te vergelijken met Seconde
   unsigned long BewaarSec = millis();                          // Bewaart nieuwe millis() nadat de secondecyclus verstreken en uitgevoerd is
   volatile int RpmTellerHoog = 0;                              // De teller die bijhoudt hoeveel omwentelingen per seconde er zijn geweest
   unsigned long BewaarSec1 = millis();
   unsigned long BewaarSec2 = millis();
   unsigned long Pulstijd = 0;
   unsigned long PulstijdOud = 0;
   int Hysteresis = 5;
   int Rpm;
   
void setup()
{  
  //start 4 digit display
   Led4Display.init();
   Led4Display.set(BRIGHT_TYPICAL);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;

  //setup voor de sensor
   pinMode(SpeedSensorPin, INPUT);
   attachInterrupt (1, HallSensor, RISING );                     // definieert een interrupt handler welke een functie aanroept bij de actie rising

  //setup serial communication
   Serial.begin(9600);                                           // initialize serial communications at 9600 bps nodig voor printen naar scherm
}

void loop()     {  
  if (Pulstijd > 50-Hysteresis) {                                // voor toerental onder de 1200
         Hysteresis = 5 ;                                        // om heen en weer springen tussen de twee meethodes te voorkomen
         PulstijdOud=(3*PulstijdOud + Pulstijd)/4 ;              // Om de uitlezing wat stabieler te maken
         Rpm = 60000/PulstijdOud;
         if (BewaarSec - BewaarSec1 > 15000) { Rpm = 0 ; }       // toerental beneden 5 Rpm dus weergave naar 0
         weergeven();                                            // weergevne via serieel 
         Led4weergeven(Rpm);                                     // weergeven op 4 digit LED display
         BewaarSec = millis();                                   // Bewaart nieuwe millis() nadat de secondecyclus verstreken en uitge
  }
  
  VerstrekenTijd = millis() - BewaarSec;                         // rekent de verstreken tijd tussen huidige en laatst vastgelegde tijd uit.
   if (VerstrekenTijd >= Seconde) {  
        Hysteresis = 0;
        Rpm = RpmTellerHoog*240/Secondefactor ;
        weergeven();                                             // weergevne via serieel 
        Led4weergeven(Rpm);                                      // weergeven op 4 digit LED display
        if ( RpmTellerHoog < 20 ) {
          Secondefactor = Secondefactor*2; 
        }
        if ( RpmTellerHoog > 50 ) {
           Secondefactor = Secondefactor/2; 
        }
        if (Secondefactor < 1 ){Secondefactor = 1;}
        if (Secondefactor > 8 ){Secondefactor = 8;}
        Seconde = 250*Secondefactor ;
        RpmTellerHoog=0;                                          // zet de teller weer op nul om opnieuw te tellen
        BewaarSec = millis();                                     // Bewaart nieuwe millis() nadat de secondecyclus verstreken en uitgevoerd is
   }
}

void HallSensor()    {                                             // Functie om sensor te detecteren.
       RpmTellerHoog++;                                            // Teller hoe vaak gedetecteerd
       BewaarSec2 = BewaarSec1;
       BewaarSec1 = millis();
       Pulstijd = BewaarSec1-BewaarSec2;
}

void weergeven()     {                                             // Subroutine voor weergeven naar serial en naar LCD I2C
        Serial.print("RpmTeller = ");                              // print the results to the serial monitor:
        Serial.print(Rpm);
        Serial.println();
 
}

void Led4weergeven(int v)     {                                     // Subroutine voor weergeven naar 4 posities Led display
        int ones = v%10;v=v/10;
        int tens = v%10;v=v/10;
        int hundreds = v%10;v=v/10;
        int thousands = v%10;v=v/10;
        int tenthousands = v%10;
        
        if (tenthousands == 0) {                                    //Now print the number digit by digit
        Led4Display.display(3,(byte)ones);
        Led4Display.display(2,(byte)tens);
        Led4Display.display(1,(byte)hundreds);
        Led4Display.display(0,(byte)thousands); 
        Led4Display.point(POINT_OFF);
        }
        else {                                                      //Now print the number digit by digit shifted one position
        Led4Display.display(3,(byte)tens);                          //and switch on the points
        Led4Display.display(2,(byte)hundreds);
        Led4Display.display(1,(byte)thousands); 
        Led4Display.display(0,(byte)tenthousands); 
        Led4Display.point(POINT_ON);  
        }  
}
