//Random Music Player

// Written By: pekasus
// Based on code written by Limor Fried (see below)

/*************************************************** 
  This is an example for the Adafruit VS1053 Codec Breakout

  Designed specifically to work with the Adafruit VS1053 Codec Breakout 
  ----> https://www.adafruit.com/products/1381

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

// include SPI, MP3 and SD libraries
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>
#include <EEPROM.h>

// define the pins used
//#define CLK 13       // SPI Clock, shared with SD card
//#define MISO 12      // Input data, from VS1053/SD card
//#define MOSI 11      // Output data, to VS1053/SD card
// Connect CLK, MISO and MOSI to hardware SPI pins. 
// See http://arduino.cc/en/Reference/SPI "Connections"

// These are the pins used for the breakout example
#define BREAKOUT_RESET  9      // VS1053 reset pin (output)
#define BREAKOUT_CS     10     // VS1053 chip select pin (output)
#define BREAKOUT_DCS    8      // VS1053 Data/command select pin (output)
// These are the pins used for the music maker shield
#define SHIELD_RESET  -1      // VS1053 reset pin (unused!)
#define SHIELD_CS     7      // VS1053 chip select pin (output)
#define SHIELD_DCS    6      // VS1053 Data/command select pin (output)

// These are common pins between breakout and shield
#define CARDCS 4     // Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ 3       // VS1053 Data request, ideally an Interrupt pin

Adafruit_VS1053_FilePlayer musicPlayer = 
  // create breakout-example object!
  Adafruit_VS1053_FilePlayer(BREAKOUT_RESET, BREAKOUT_CS, BREAKOUT_DCS, DREQ, CARDCS);
  // create shield-example object!
  //Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);
  
byte volume;
int volume_addr = 29;
const byte volumeupbutton = 7;
const byte volumedownbutton = 6;
const byte skip = 5;

String list = "list.txt";
File listFile;

void setup() {
  Serial.begin(9600);
  Serial.println("Adafruit VS1053 Simple Test");

  if (! musicPlayer.begin()) { // initialise the music player
     Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
     while (1);
  }
  Serial.println(F("VS1053 found"));
  
  SD.begin(CARDCS);    // initialise the SD card
  volume = EEPROM.read(volume_addr);
  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(volume, volume);

  // Timer interrupts are not suggested, better to use DREQ interrupt!
  //musicPlayer.useInterrupt(VS1053_FILEPLAYER_TIMER0_INT); // timer int

  // If DREQ is on an interrupt pin (on uno, #2 or #3) we can do background
  // audio playing
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int
  pinMode(volumeupbutton, INPUT_PULLUP);
  pinMode(volumedownbutton, INPUT_PULLUP);
  pinMode(skip, INPUT_PULLUP);
/*  if (SD.exists(list)) {
    Serial.println(list + " exists.");
    SD.remove(list);
    Serial.println(list + " removed.");
  }
  listFile = SD.open(list, FILE_WRITE);
  */
  randomSeed(analogRead(A0));
}

void loop() {
  // File is playing in the background so other actions can be 
  // carried out during playback (such as skip and volume)
  int songnumber = random(138);
  char sc[4];
  dtostrf(songnumber, 3, 0, sc);

  String first = "/";
  String last = ".mp3";
  String total = first + sc + last;
  const char *song = total.c_str();
  Serial.println(song);

  Serial.println("Playing 1");
  musicPlayer.startPlayingFile(song);
      whilePlaying();

delay(1000);
}

void whilePlaying() {
  while (musicPlayer.playingMusic) {
    if(digitalRead (volumeupbutton) == 0) {
      volumeup();
      delay(100);
    }
    if(digitalRead (volumedownbutton) == 0) {
      volumedown();
      delay(100);
    }
    if(digitalRead(skip) == 0) {
      musicPlayer.stopPlaying();
    }
  }
}

void volumeup() {
  if (volume >  4) {
    volume -=5;
    musicPlayer.setVolume(volume, volume);
    EEPROM.write(volume_addr, volume);
  }
}

void volumedown() {
  if (volume < 100) {
    volume +=5;
    musicPlayer.setVolume(volume, volume);
    EEPROM.write(volume_addr, volume);
  }
}
