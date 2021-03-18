#include <ESP8266WiFi.h>   
#include "SinricPro.h"
#include "SinricProSwitch.h"
 
#define WIFI_SSID         "nomeDoSeuWifi" //PARÂMETRO    
#define WIFI_PASS         "suaSenha" //PARÂMETRO
#define APP_KEY           "1acd2513-2293-4915-bc59-2386a0f56584"      // O seu App Key é algo como "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET        "51eb253a-6629-4790-9458-0116e9f626cc-caab7408-9989-4dcd-a6ec-fdff09f85ecb"   // O seu App Secret é algo como "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"
 
#define Abajour_ID        "Coloque seu id aqui"    // Algo como "5dc1564130xxxxxxxxxxxxxx"
#define Lampada_ID        "6015cf17b8cb375513d9fce2"    // Algo como "5dc1564130xxxxxxxxxxxxxx"
#define Regua_ID          "60171b9e63a508543acdbda2"    // Algo como "5dc1564130xxxxxxxxxxxxxx"
#define Ventilador_ID     "Coloque seu id aqui"    // Algo como "5dc1564130xxxxxxxxxxxxxx"
 
 
#define Abajour_Pin 0  // O pino fisico onde está ligado
#define Lampada_Pin 1  // O pino fisico onde está ligado
#define Regua_Pin 2  // O pino fisico onde está ligado
#define Ventilador_Pin 3  // O pino fisico onde está ligado
 
#define BAUD_RATE         9600                // Se precisar, pode trocar o baud rate
 
 
void setupWiFi();
void setupSinricPro();
bool AbajourState(const String &deviceId, bool &state);
bool LampadaState(const String &deviceId, bool &state);
bool ReguaState(const String &deviceId, bool &state);
bool VentiladorState(const String &deviceId, bool &state);
 
 
// main setup function
void setup() {
  setupWiFi();
  setupSinricPro(); 
  pinMode(Abajour_Pin, OUTPUT);
  pinMode(Lampada_Pin, OUTPUT);
  pinMode(Regua_Pin, OUTPUT);
  pinMode(Ventilador_Pin, OUTPUT);
  
  digitalWrite(Abajour_Pin, HIGH);
  digitalWrite(Lampada_Pin, HIGH);
  digitalWrite(Regua_Pin, HIGH);
  digitalWrite(Ventilador_Pin, HIGH);
}
 
void loop() {
  SinricPro.handle();
}
 
 
bool AbajourState(const String &deviceId, bool &state) {
  digitalWrite(Abajour_Pin, !state);
  return true; // request handled properly
}
 
bool LampadaState(const String &deviceId, bool &state) {
  digitalWrite(Lampada_Pin, !state);
  return true; // request handled properly
}
 
bool ReguaState(const String &deviceId, bool &state) {
  digitalWrite(Regua_Pin, !state);
  return true; // request handled properly
}
 
bool VentiladorState(const String &deviceId, bool &state) {
  digitalWrite(Ventilador_Pin, !state);
  return true; // request handled properly
}
 
// setup das conexões Wifi
void setupWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASS);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(250); 
  }
}
 
// setup das funções para o SinricPro
void setupSinricPro() {
  // add devices and callbacks to SinricPro
  SinricProSwitch &mySwitch1 = SinricPro[Abajour_ID];
  mySwitch1.onPowerState(AbajourState);
 
  SinricProSwitch &mySwitch2 = SinricPro[Lampada_ID];
  mySwitch2.onPowerState(LampadaState);
 
  SinricProSwitch &mySwitch3 = SinricPro[Regua_ID];
  mySwitch3.onPowerState(ReguaState);
 
  SinricProSwitch &mySwitch4 = SinricPro[Ventilador_ID];
  mySwitch4.onPowerState(VentiladorState);
 
  // setup SinricPro
  SinricPro.onConnected([](){  }); 
  SinricPro.onDisconnected([](){  });
  SinricPro.begin(APP_KEY, APP_SECRET);
}
