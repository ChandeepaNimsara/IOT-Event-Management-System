#include <ESP8266WiFi.h>

#include <Wire.h>               
#include <LiquidCrystal_I2C.h>  

#include <SPI.h>
#include <MFRC522.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

constexpr uint8_t RST_PIN = D3;     
constexpr uint8_t SS_PIN = D4;     //SDA
MFRC522 rfid(SS_PIN, RST_PIN); 
MFRC522::MIFARE_Key key;
String tag;   //card number

const char* ssid = "Dialog 4G 755";
const char* password = "9F1443D3";
const char* host = "script.google.com";
const int httpsPort = 443;  //establish a connection
unsigned long lastMsg = 0;

String id = "AKfycbw4XCrD5O4cer6YpFs4t8hGkChunSS08a-2NyaChM-f8yauygaZtBmCcfRBEcYQDks";    //deploy id

WiFiClientSecure client;

int count = 0;
int vis_count = 1;
char input[11];
int a = 0, b = 0, c = 0;

void setup() {
  
  Serial.begin(115200);
  SPI.begin();     // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
  pinMode(D8, OUTPUT);

  Wire.begin(D2, D1);  //I2C >>> D2=SDA, D1=SCL
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" WELCOME TO");
  lcd.setCursor(0, 1);
  lcd.print(" IOT Company ");
  delay(2000);
  lcd.clear();
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
  lcd.setCursor(0, 1);
  lcd.print("WiFi connected..");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Count Employees");
  delay(3000);
  lcd.clear();
  client.setInsecure(); //client connect with htpp
}

void connect() {
  
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  if (!client.connect(host, httpsPort)) {   //not connect sheet
    Serial.println("connection failed");
    return;
  }
}

void loop() {

  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  if (rfid.PICC_ReadCardSerial()) {
    for (byte i = 0; i < 4; i++) {
      tag += rfid.uid.uidByte[i];
    }
    Serial.println(tag);


    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }

  Serial.print("tag num:");
  Serial.println(tag);


  count = 0;
  while (count < 11)
  {
    input[count] = Serial.read();
    count++;

    delay(5);
  }
  if (count == 11)
  {
    if (tag == "14510411527")
    {
      lcd.clear();
      // sent message to google sheet
      connect();

      unsigned long now = millis();
      if (now - lastMsg > 2000) {
        lastMsg = now;

        String url = "https://script.google.com/macros/s/" + id + "/exec?func=addData&val=" + "Chandeepa";
        Serial.print("Sent message: ");
        Serial.println(url);

        client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                     "Host: " + host + "\r\n" +
                     "User-Agent: BuildFailureDetectorESP8266\r\n" +
                     "Connection: close\r\n\r\n");
      }
      
      lcd.setCursor(0, 0);
      lcd.print("No. of Vis:" + String(vis_count));
      lcd.setCursor(0, 1);
      lcd.print("Welcome Chandeepa");
      vis_count++;
      a = 1;
      delay(1000);
    }
    
    else if (tag == "15667217142")
    {
      lcd.clear();

      // sent message to google sheet
      connect();

      unsigned long now = millis();
      if (now - lastMsg > 2000) {
        lastMsg = now;

        String url = "https://script.google.com/macros/s/" + id + "/exec?func=addData&val=" + "Nimsara";
        Serial.print("Sent message: ");
        Serial.println(url);

        client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                     "Host: " + host + "\r\n" +
                     "User-Agent: BuildFailureDetectorESP8266\r\n" +
                     "Connection: close\r\n\r\n");
      }
      lcd.setCursor(0, 0);
      lcd.print("No. of Vis:" + String(vis_count));
      lcd.setCursor(0, 1);
      lcd.print("Welcome Nimsara");
      b = 1;
      vis_count++;
      delay(1000);
    }
    
    else if (tag == "23657203142")
    {
      lcd.clear();
      
      // sent message to google sheet
      connect();

      unsigned long now = millis();
      if (now - lastMsg > 2000) {
        lastMsg = now;

        String url = "https://script.google.com/macros/s/" + id + "/exec?func=addData&val=" + "Rodrigo";
        Serial.print("Sent message: ");
        Serial.println(url);

        client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                     "Host: " + host + "\r\n" +
                     "User-Agent: BuildFailureDetectorESP8266\r\n" +
                     "Connection: close\r\n\r\n");
      }
      
      lcd.setCursor(0, 0);
      lcd.print("No. of Vis:" + String(vis_count));
      lcd.setCursor(0, 1);
      lcd.print("Welcome Rodrigo");
      c = 1;
      vis_count++;
      delay(1000);
    }
    
    else
    {
      lcd.setCursor(0, 1);
      lcd.print("Welcome Back!!!");
      delay(3000);
    }
  }
  tag = "";
}
