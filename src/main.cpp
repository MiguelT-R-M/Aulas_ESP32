// Não testei na placa ainda, não tenho as peças... bibliotecas não foram analizadas 100%
// proj: https://wokwi.com/projects/479951238319217665


#include <Wire.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define PINO_DHT  12        // fio amarelo
#define TIPO_DHT  DHT22
// #define PINO_SDA  8         // I2C padrão do ESP32-S3
// #define PINO_SCL  9
#define PINO_SDA 40 // I2C padrão do ESP32-S3-N16R8
#define PINO_SCL 39

DHT dht(PINO_DHT, TIPO_DHT);
LiquidCrystal_I2C lcd(0x27, 16, 2);   // endereço, colunas, linhas

byte grau[8] = {0b01100, 0b10010, 0b10010, 0b01100};
byte smile[8] = {0b0, 0b0, 0b0, 0b01010, 0b10001, 0b01110}; // Cara ":)"


void setup() {
  
  Serial.begin(115200);
  Wire.begin(PINO_SDA, PINO_SCL);
  dht.begin();

  lcd.init();
  lcd.backlight();
  lcd.createChar(0, grau);
  lcd.createChar(1, smile);
  lcd.setCursor(0, 0);
  lcd.print("LASER ESP32-S3");
  lcd.setCursor(0, 1);
  lcd.print("Iniciando");
  delay(500);
  lcd.print(".");
  delay(500);
  lcd.print(".");
  delay(500);
  lcd.print(".");
  delay(2000);
  lcd.clear();
  // lcd.setCursor(0, 0);
  // lcd.print("Temperatura: 30");
  // lcd.write(0);
  // lcd.setCursor(0, 1);
  // lcd.write(1);
}

void loop() {
  float umi = dht.readHumidity();
  float temp = dht.readTemperature(); 

  if(isnan(umi) || isnan(temp)){
    lcd.setCursor(0, 0);
    lcd.print("Falha no sensor ");
    Serial.println("Falha na leitura do DHT22");
  } else{
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temp, 1);
    lcd.write(0);           // o caractere de grau criado acima 
    lcd.print("C   ");

    lcd.setCursor(0, 1);
    lcd.print("Umid: ");
    lcd.print(umi, 1);
    lcd.print(" % ");
    lcd.write(1);
    lcd.print("   ");

    // ... envia o mesmo texto pelo Serial ...

    delay(2000);   // 1 leitura a cada 2 s
  }


  delay(10); 
}
