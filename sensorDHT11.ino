#include "DHT.h"
 
// กำหนดค่าคงที่สำหรับเซ็นเซอร์และ LED
#define DHTPIN 5       // ขา GPIO สำหรับเซ็นเซอร์ DHT11
#define DHTTYPE DHT11  // ประเภทของเซ็นเซอร์ DHT11
#define LED_PIN 4      // ขา GPIO สำหรับควบคุม LED
 
// สร้างออบเจ็กต์สำหรับเซ็นเซอร์ DHT11
DHT dht(DHTPIN, DHTTYPE);
 
void setup() {
    // เริ่มต้นการสื่อสารผ่าน Serial Monitor
    Serial.begin(115200);
    
    // เริ่มต้นการทำงานของเซ็นเซอร์ DHT11
    dht.begin();
    
    // กำหนดขา LED เป็นขา OUTPUT
    pinMode(LED_PIN, OUTPUT);
}
 
void loop() {
    // อ่านค่าความชื้นและอุณหภูมิจากเซ็นเซอร์
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature(); // อุณหภูมิหน่วย °C
 
    // ตรวจสอบว่าการอ่านค่าล้มเหลวหรือไม่
    if (isnan(humidity) || isnan(temperature)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }
 
    // แสดงค่าความชื้นและอุณหภูมิบน Serial Monitor
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print("% Temperature: ");
    Serial.print(temperature);
    Serial.println("°C");
 
    // ควบคุม LED ตามค่าความชื้น
    if (humidity > 20) {
        digitalWrite(LED_PIN, HIGH); // เปิด LED
    } else {
        digitalWrite(LED_PIN, LOW);  // ปิด LED
    }
 
    // หน่วงเวลา 1 วินาที ก่อนอ่านค่าใหม่
    delay(1000);
}