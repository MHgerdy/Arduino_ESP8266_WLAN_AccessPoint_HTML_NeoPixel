/*--------------------------------------------------
HTTP 1.1 Webserver as AccessPoint for ESP8266 
for ESP8266 adapted Arduino IDE

by Stefan Thesen 08/2015 - free for anyone

Does HTTP 1.1 with defined connection closing.
Handles empty requests in a defined manner.
Handle requests for non-exisiting pages correctly.

This demo allows to switch two functions:
Function 1 creates serial output and toggels GPIO2
Function 2 just creates serial output.

Serial output can e.g. be used to steer an attached
Arduino, Raspberry etc.
--------------------------------------------------*/
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN D4 // Hier wird angegeben, an welchem digitalen Pin die WS2812 LEDs bzw. NeoPixel angeschlossen sind
#define NUMPIXELS 20 // Hier wird die Anzahl der angeschlossenen WS2812 LEDs bzw. NeoPixel angegeben
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int pause=125; // 100 Millisekunden Pause bis zur Ansteuerung der nächsten LED.


#include <ESP8266WiFi.h>

const char* ssid = "OLIVER-AP";
const char* password = "12345678";  // set to "" for open access point w/o passwortd

unsigned long ulReqcount;

WiFiClient client;
int HTTPAuswahl_NEOPixel;
int HTTPAuswahl_OnboardLED;

// Create an instance of the server on Port 80
WiFiServer server(80);

void setup() 
{
  // setup globals
  ulReqcount=0; 
  
  // prepare GPIO2
  pinMode(2, OUTPUT);
  digitalWrite(2, 0);
  
  // start serial
  Serial.begin(9600);
  delay(1);
  
  // AP mode
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  server.begin();
  
  pixels.begin(); // Initialisierung der NeoPixel
  pixels.setPixelColor(0, pixels.Color(0,0,0));
  pixels.show();
}



void NeopixelBlinkRING(){
  pixels.setPixelColor(0, pixels.Color(0,20,0)); // Pixel1 leuchtet in der Farbe Grün
  pixels.show(); // Durchführen der Pixel-Ansteuerung
  delayWifi (pause); // Pause, in dieser Zeit wird nichts verändert.
  pixels.setPixelColor(1, pixels.Color(0,0,20)); // Pixel1 leuchtet in der Farbe Grün
  pixels.show(); // Durchführen der Pixel-Ansteuerung
  delayWifi (pause); // Pause, in dieser Zeit wird nichts verändert.
  pixels.setPixelColor(2, pixels.Color(0,20,0)); // Pixel2 leuchtet in der Farbe Grün
  pixels.show(); // Durchführen der Pixel-Ansteuerung
  delayWifi (pause); // Pause, in dieser Zeit wird nichts verändert.
  pixels.setPixelColor(3, pixels.Color(0,0,20)); // Pixel3 leuchtet in der Farbe Grün
  pixels.show(); // Durchführen der Pixel-Ansteuerung
  delayWifi (pause); // Pause, in dieser Zeit wird nichts verändert.
  pixels.setPixelColor(4, pixels.Color(0,20,0)); // Pixel4 leuchtet in der Farbe Grün
  pixels.show(); // Durchführen der Pixel-Ansteuerung
  delayWifi (pause); // Pause, in dieser Zeit wird nichts verändert.
  pixels.setPixelColor(5, pixels.Color(0,0,20)); // Pixel5 leuchtet in der Farbe Grün
  pixels.show(); // Durchführen der Pixel-Ansteuerung
  delayWifi (pause); // Pause, in dieser Zeit wird nichts verändert.
  pixels.setPixelColor(6, pixels.Color(0,20,0)); // Pixel5 leuchtet in der Farbe Grün
  pixels.show(); // Durchführen der Pixel-Ansteuerung
  delayWifi (pause); // Pause, in dieser Zeit wird nichts verändert.
  pixels.setPixelColor(7, pixels.Color(0,0,20)); // Pixel5 leuchtet in der Farbe Grün
  pixels.show(); // Durchführen der Pixel-Ansteuerung
  delayWifi (pause); // Pause, in dieser Zeit wird nichts verändert.
  pixels.setPixelColor(8, pixels.Color(0,20,0)); // Pixel5 leuchtet in der Farbe Grün
  pixels.show(); // Durchführen der Pixel-Ansteuerung
  delayWifi (pause); // Pause, in dieser Zeit wird nichts verändert.
  pixels.setPixelColor(9, pixels.Color(0,0,20)); // Pixel5 leuchtet in der Farbe Grün
  pixels.show(); // Durchführen der Pixel-Ansteuerung
  delayWifi (pause); // Pause, in dieser Zeit wird nichts verändert.
  pixels.setPixelColor(10, pixels.Color(0,20,0)); // Pixel5 leuchtet in der Farbe Grün
  pixels.show(); // Durchführen der Pixel-Ansteuerung
  delayWifi (pause); // Pause, in dieser Zeit wird nichts verändert.
  pixels.setPixelColor(11, pixels.Color(0,0,20)); // Pixel5 leuchtet in der Farbe Grün
  pixels.show(); // Durchführen der Pixel-Ansteuerung
  delayWifi (pause); // Pause, in dieser Zeit wird nichts verändert.
  pixels.setPixelColor(12, pixels.Color(0,20,0)); // Pixel5 leuchtet in der Farbe Grün
  pixels.show(); // Durchführen der Pixel-Ansteuerung
  delayWifi (pause); // Pause, in dieser Zeit wird nichts verändert.
  pixels.setPixelColor(13, pixels.Color(0,0,20)); // Pixel5 leuchtet in der Farbe Grün
  pixels.show(); // Durchführen der Pixel-Ansteuerung
  delayWifi (pause); // Pause, in dieser Zeit wird nichts verändert.
  pixels.setPixelColor(14, pixels.Color(0,20,0)); // Pixel5 leuchtet in der Farbe Grün
  pixels.show(); // Durchführen der Pixel-Ansteuerung
  delayWifi (pause); // Pause, in dieser Zeit wird nichts verändert.
  pixels.setPixelColor(15, pixels.Color(0,0,20)); // Pixel5 leuchtet in der Farbe Grün
  pixels.show(); // Durchführen der Pixel-Ansteuerung
  delayWifi (500); // Pause, in dieser Zeit wird nichts verändert.
  
  // Zurücksetzen aller Pixelfarben auf Stufe "0" (aus)
  pixels.setPixelColor(0, pixels.Color(0,0,0));
  pixels.setPixelColor(1, pixels.Color(0,0,0));
  pixels.setPixelColor(2, pixels.Color(0,0,0));
  pixels.setPixelColor(3, pixels.Color(0,0,0));
  pixels.setPixelColor(4, pixels.Color(0,0,0));
  pixels.setPixelColor(5, pixels.Color(0,0,0));
  pixels.setPixelColor(6, pixels.Color(0,0,0));
  pixels.setPixelColor(7, pixels.Color(0,0,0));
  pixels.setPixelColor(8, pixels.Color(0,0,0));
  pixels.setPixelColor(9, pixels.Color(0,0,0));
  pixels.setPixelColor(10, pixels.Color(0,0,0));
  pixels.setPixelColor(11, pixels.Color(0,0,0));
  pixels.setPixelColor(12, pixels.Color(0,0,0));
  pixels.setPixelColor(13, pixels.Color(0,0,0));
  pixels.setPixelColor(14, pixels.Color(0,0,0));
  pixels.setPixelColor(15, pixels.Color(0,0,0));
  pixels.show(); // Durchführen der Pixel-Ansteuerung
  delayWifi (pause); // Pause, die LEDs bleiben in dieser Zeit aus
}



void Neopixel_partikel01()
{
   /* NeopixelBlinkRING();
  */
  for (int i=0; i<5; i++){
  pixels.setPixelColor(0, pixels.Color(0,0,20)); // Pixel1 leuchtet in der Farbe Grün
  pixels.setPixelColor(4, pixels.Color(0,0,20)); // Pixel1 leuchtet in der Farbe Grün
  pixels.setPixelColor(8, pixels.Color(0,0,20)); // Pixel1 leuchtet in der Farbe Grün
  pixels.setPixelColor(12, pixels.Color(0,0,20)); // Pixel1 leuchtet in der Farbe Grün
 
  pixels.show(); // Durchführen der Pixel-Ansteuerung
 
  delayWifi(333);
 
  pixels.setPixelColor(1, pixels.Color(0,20,0)); // Pixel1 leuchtet in der Farbe Grün
  pixels.setPixelColor(5, pixels.Color(0,20,0)); // Pixel1 leuchtet in der Farbe Grün
  pixels.setPixelColor(9, pixels.Color(0,20,0)); // Pixel1 leuchtet in der Farbe Grün
  pixels.setPixelColor(13, pixels.Color(0,20,0)); // Pixel1 leuchtet in der Farbe Grün
 
  pixels.show(); // Durchführen der Pixel-Ansteuerung
 
  delayWifi(333);
 
  pixels.setPixelColor(2, pixels.Color(20,0,0)); // Pixel1 leuchtet in der Farbe Grün
  pixels.setPixelColor(6, pixels.Color(20,0,0)); // Pixel1 leuchtet in der Farbe Grün
  pixels.setPixelColor(10, pixels.Color(20,0,0)); // Pixel1 leuchtet in der Farbe Grün
  pixels.setPixelColor(14, pixels.Color(20,0,0)); // Pixel1 leuchtet in der Farbe Grün
 
  pixels.show(); // Durchführen der Pixel-Ansteuerung
 
  delayWifi(333);
 
  pixels.setPixelColor(3, pixels.Color(20,20,20)); // Pixel1 leuchtet in der Farbe Grün
  pixels.setPixelColor(7, pixels.Color(20,20,20)); // Pixel1 leuchtet in der Farbe Grün
  pixels.setPixelColor(11, pixels.Color(20,20,20)); // Pixel1 leuchtet in der Farbe Grün
  pixels.setPixelColor(15, pixels.Color(20,20,20)); // Pixel1 leuchtet in der Farbe Grün
 
  pixels.show(); // Durchführen der Pixel-Ansteuerung
 
  delayWifi(1000);
 
  pixels.setPixelColor(0, pixels.Color(0,0,0));
  pixels.setPixelColor(1, pixels.Color(0,0,0));
  pixels.setPixelColor(2, pixels.Color(0,0,0));
  pixels.setPixelColor(3, pixels.Color(0,0,0));
  pixels.setPixelColor(4, pixels.Color(0,0,0));
  pixels.setPixelColor(5, pixels.Color(0,0,0));
  pixels.setPixelColor(6, pixels.Color(0,0,0));
  pixels.setPixelColor(7, pixels.Color(0,0,0));
  pixels.setPixelColor(8, pixels.Color(0,0,0));
  pixels.setPixelColor(9, pixels.Color(0,0,0));
  pixels.setPixelColor(10, pixels.Color(0,0,0));
  pixels.setPixelColor(11, pixels.Color(0,0,0));
  pixels.setPixelColor(12, pixels.Color(0,0,0));
  pixels.setPixelColor(13, pixels.Color(0,0,0));
  pixels.setPixelColor(14, pixels.Color(0,0,0));
  pixels.setPixelColor(15, pixels.Color(0,0,0));
  pixels.show(); // Durchführen der Pixel-Ansteuerung
  }
}


void OnboardLED(int pSpeed)
{
   Serial.println("OnboardLED-begin");
        pinMode(LED_BUILTIN, OUTPUT);
        for (int i=0; i<10 ; i++){
          digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
          delayWifi(pSpeed);                       // wait for a second
          digitalWrite(LED_BUILTIN, HIGH);    // turn the LED off by making the voltage LOW
          delayWifi(pSpeed); 
        }
   Serial.println("OnboardLED-end");      
}

void delayWifi(int pPause){
  unsigned long ultimeout = millis()+pPause;
  while(!client && (millis()<ultimeout) )
  {
    client = server.available();
  }
} 


void loop() 
{
    
  // Check if a client has connected
  client = server.available();
  
   
    if (HTTPAuswahl_OnboardLED==1) {
        OnboardLED(500);
    }   
    if (HTTPAuswahl_OnboardLED==2) {
        OnboardLED(250);
    }        
    if (HTTPAuswahl_NEOPixel==1) {
        NeopixelBlinkRING();
    } 
    if (HTTPAuswahl_NEOPixel==2) {
        Neopixel_partikel01();
    } 
    
  if (!client) 
  {
    return;
  }
  
  
  // Wait until the client sends some data
  Serial.println("new client");
  unsigned long ultimeout = millis()+250;
  while(!client.available() && (millis()<ultimeout) )
  {
    delay(1);
  }
  if(millis()>ultimeout) 
  { 
    Serial.println("client connection time-out!");
    return; 
  }
  
  // Read the first line of the request
  String sRequest = client.readStringUntil('\r');
  //Serial.println(sRequest);
  client.flush();
  
  // stop client, if request is empty
  if(sRequest=="")
  {
    Serial.println("empty request! - stopping client");
    client.stop();
    return;
  }
  
  // get path; end of path is either space or ?
  // Syntax is e.g. GET /?pin=MOTOR1STOP HTTP/1.1
  String sPath="",sParam="", sCmd="";
  String sGetstart="GET ";
  int iStart,iEndSpace,iEndQuest;
  iStart = sRequest.indexOf(sGetstart);
  if (iStart>=0)
  {
    iStart+=+sGetstart.length();
    iEndSpace = sRequest.indexOf(" ",iStart);
    iEndQuest = sRequest.indexOf("?",iStart);
    
    // are there parameters?
    if(iEndSpace>0)
    {
      if(iEndQuest>0)
      {
        // there are parameters
        sPath  = sRequest.substring(iStart,iEndQuest);
        sParam = sRequest.substring(iEndQuest,iEndSpace);
      }
      else
      {
        // NO parameters
        sPath  = sRequest.substring(iStart,iEndSpace);
      }
    }
  }
  
  ///////////////////////////////////////////////////////////////////////////////
  // output parameters to serial, you may connect e.g. an Arduino and react on it
  ///////////////////////////////////////////////////////////////////////////////
  if(sParam.length()>0)
  {
    int iEqu=sParam.indexOf("=");
    if(iEqu>=0)
    {
      sCmd = sParam.substring(iEqu+1,sParam.length());
      Serial.println(sCmd);
    }
  }
  
  
  ///////////////////////////
  // format the html response
  ///////////////////////////
  String sResponse,sHeader;
  
  ////////////////////////////
  // 404 for non-matching path
  ////////////////////////////
  if(sPath!="/")
  {
    sResponse="<html><head><title>404 Not Found</title></head><body><h1>Not Found</h1><p>The requested URL was not found on this server.</p></body></html>";
    
    sHeader  = "HTTP/1.1 404 Not found\r\n";
    sHeader += "Content-Length: ";
    sHeader += sResponse.length();
    sHeader += "\r\n";
    sHeader += "Content-Type: text/html\r\n";
    sHeader += "Connection: close\r\n";
    sHeader += "\r\n";
  }
  ///////////////////////
  // format the html page
  ///////////////////////
  else
  {
    ulReqcount++;
    sResponse  = "<html><head><title>Demo f&uumlr ESP8266 Steuerung</title></head><body>";
    sResponse += "<font color=\"#000000\"><body bgcolor=\"#d0d0f0\">";
    sResponse += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=yes\">";
    sResponse += "<h1>Olis Access Point</h1>";
   /* 
    sResponse += "Funktion 1 schaltet GPIO2 und erzeugt eine serielle Ausgabe.<BR>";
    sResponse += "Funktion 2 erzeugt nur eine serielle Ausgabe.<BR>";
    */
    sResponse += "<FONT SIZE=+1>";
  /*  sResponse += "<p>Funktion 1 <a href=\"?pin=FUNCTION1ON\"><button>einschalten</button></a>&nbsp;<a href=\"?pin=FUNCTION1OFF\"><button>ausschalten</button></a></p>";
    sResponse += "<p>Funktion 2 <a href=\"?pin=FUNCTION2ON\"><button>einschalten</button></a>&nbsp;<a href=\"?pin=FUNCTION2OFF\"><button>ausschalten</button></a></p>";
  */
    sResponse += "<p>Funktion 1 <a href=\"?pin=BLINK1\"><button>Blink Test 1</button></a>&nbsp;</p>";
    sResponse += "<p>Funktion 2 <a href=\"?pin=BLINK2\"><button>Blink Test 2</button></a>&nbsp;</p>";  
    sResponse += "<p>Funktion 3 <a href=\"?pin=NEOPIXEL1\"><button>NeopixelBlinkRING</button></a>&nbsp;</p>";  
    sResponse += "<p>Funktion 4 <a href=\"?pin=NEOPIXEL2\"><button>Neopixel_partikel01</button></a>&nbsp;</p>";  
    //////////////////////
    // react on parameters
    //////////////////////
    if (sCmd.length()>0)
    {
      // write received command to html page
      sResponse += "Kommando:" + sCmd + "<BR>";
      
      // switch GPIO
      if(sCmd.indexOf("FUNCTION1ON")>=0)
      {
        digitalWrite(2, 1);
      }
      else if(sCmd.indexOf("FUNCTION1OFF")>=0)
      {
        digitalWrite(2, 0);
      }

      else if(sCmd.indexOf("BLINK1")>=0)
      {
          if (HTTPAuswahl_OnboardLED==1) {
            HTTPAuswahl_OnboardLED=0;
          } else {
            HTTPAuswahl_OnboardLED=1;
          }
      }

      else if(sCmd.indexOf("BLINK2")>=0)
      {
          if (HTTPAuswahl_OnboardLED==2) {
            HTTPAuswahl_OnboardLED=0;
          } else {
            HTTPAuswahl_OnboardLED=2;
          }
      }
      else if(sCmd.indexOf("NEOPIXEL1")>=0)
      {
          if (HTTPAuswahl_NEOPixel==1) {
            HTTPAuswahl_NEOPixel=0;
          } else {
            HTTPAuswahl_NEOPixel=1;
          }
      }
      else if(sCmd.indexOf("NEOPIXEL2")>=0)
      {
          if (HTTPAuswahl_NEOPixel==2) {
            HTTPAuswahl_NEOPixel=0;
          } else {
            HTTPAuswahl_NEOPixel=2;
          }
      }
    }
    sResponse += "<FONT SIZE=-2>";
    sResponse += "<BR>Aufrufz&auml;hler="; 
    sResponse += ulReqcount;
    sResponse += "<BR>";
  /*  
    sResponse += "Stefan Thesen 08/2015<BR>";
    */
    sResponse += "</body></html>";
    
    sHeader  = "HTTP/1.1 200 OK\r\n";
    sHeader += "Content-Length: ";
    sHeader += sResponse.length();
    sHeader += "\r\n";
    sHeader += "Content-Type: text/html\r\n";
    sHeader += "Connection: close\r\n";
    sHeader += "\r\n";
  }
  
  // Send the response to the client
  client.print(sHeader);
  client.print(sResponse);
  
  // and stop the client
  client.stop();
  Serial.println("Client disonnected");
}
