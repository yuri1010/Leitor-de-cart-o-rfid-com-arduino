#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define endereco 0x27
#define colunas  16
#define linhas   2

bool som;
String chave = "Desligado";

Servo servo;

LiquidCrystal_I2C lcd(endereco, colunas, linhas);

void setup() {

  servo.attach(8);
  
  Serial.begin(9600);
  pinMode(3, INPUT);
  
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("Captando sons...");
  delay(1000);
  lcd.clear();

}

void loop() {

  int lino = analogRead(A1);
  byte angulo = map(lino, 0, 1023, 0, 179);
  servo.write(angulo);
  Serial.print("A1: ");
  Serial.print(lino);
  Serial.print("Angulo: ");
  Serial.println(angulo);
  int audio = analogRead(A0);
  
  //lcd.clear();
  if(audio > 900){
  
      lcd.setCursor(0,0);
      lcd.print("     -   -");
      lcd.setCursor(0,1);
      lcd.print("       _");
  }else{

      lcd.setCursor(0,0);
      lcd.print("     0   0");
      lcd.setCursor(0,1);
      lcd.print("       _ ");
  }
  //lcd.print(chave);
  Serial.println(audio);
  //delay(200);

}
