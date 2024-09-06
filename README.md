

Projemizde mikrodenetleyici dersi kapsamında ele giyilebilir bir mouse tasarlayıp gerçekleştirdik. Projemizde ESP32CAM, MPU6050, USB-TTL programlayıcı, 2 adet buton, mini breadboard ve jumper kablolar kullandık. ESP32CAM ile Bluetooth üzerinden bir bilgisayara bağlanarak, MPU6050 sensöründen gelen hareket verilerini kullanarak fare hareketlerini taklit ettik. Bu raporda projemizin detayları, kullanılan malzemeler, yazılım geliştirme süreci ve karşılaşılan zorlukları aşağıda anlatacağız.

Kullanılan Malzemeler
ESP32CAM: Bu modül hem Wi-Fi hem de Bluetooth özelliklerine sahip bir mikrodenetleyicidir.
MPU6050: İvmeölçer ve jiroskop sensörleri içeren, hareket ve ivme verilerini ölçmek için kullanılan bir modüldür.
USB-TTL Programlayıcı: ESP32CAM'i programlamak için kullanılan bir ara birimdir.
Butonlar: Sol ve sağ tıklama işlevleri için iki adet buton kullandık.
Mini Breadboard: Devre bağlantılarını düzenlemek için kullanıldı.
Jumper Kablolar: Modüller arasındaki bağlantıları sağlamak için kullanıldı.
Devre Şeması

![image](https://github.com/user-attachments/assets/7e56f8f5-3690-4c95-86fe-1b2481db654e)

Devreyi oluşturma sürecimiz:

MPU6050:
VCC - 5.0V (ESP32CAM)
GND - GND (ESP32CAM)
SCL - GPIO 13 (ESP32CAM)
SDA - GPIO 12 (ESP32CAM)
Buton 1:
Bir ucu GPIO 15'e, diğer ucu GND'ye bağlandı.
Buton 2:
Bir ucu GPIO 14'e, diğer ucu GND'ye bağlandı.
USB-TTL Programlayıcı:
RX - TX0 (ESP32CAM)
TX - RX0 (ESP32CAM)
GND - GND (ESP32CAM)
5V - 5V (ESP32CAM)

Yazılım Geliştirme Süreci
Projemizde Arduino IDE'yi kullanarak ESP32CAM için kod yazdık. Kodumuzda öncelikle gerekli kütüphaneleri dahil ettik:

#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <BleMouse.h>
MPU6050 sensörünü ve BLE Mouse (Bluetooth Low Energy Mouse) nesnelerini tanımladık

Adafruit_MPU6050 mpu;
BleMouse bleMouse("ESP32 Mouse");
Buton pinlerini ve son durum değişkenlerini tanımladık:

const int button1Pin = 15;
const int button2Pin = 14;

int lastButton1State = HIGH;
int lastButton2State = HIGH;


void setup() {
    Serial.begin(115200);
    Serial.println("Starting BLE work!");
    Wire.begin(13, 12);
    
    pinMode(button1Pin, INPUT_PULLUP);
    pinMode(button2Pin, INPUT_PULLUP);
    
    if (!mpu.begin()) {
        Serial.println("Failed to find MPU6050 chip");
        while (1) {
            delay(10);
        }
    }
    Serial.println("MPU6050 Found!");
    
    mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
    mpu.setGyroRange(MPU6050_RANGE_250_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
    
    bleMouse.begin();
    Serial.println("Bluetooth cihazı başladı: ESP32 Mouse");
}
loop() // fonksiyonu içerisinde, sensörden okunan verileri işleyerek mouse hareketlerini ve tıklama işlemlerini gerçekleştirdik:

void loop() {
    static unsigned long lastUpdate = 0;
    unsigned long currentMillis = millis();
    
    if (bleMouse.isConnected()) {
        if (currentMillis - lastUpdate >= 20) { 
            lastUpdate = currentMillis;
            
            sensors_event_t a, g, temp;
            mpu.getEvent(&a, &g, &temp);
            
            int deltaX = a.acceleration.y * 10;
            int deltaY = a.acceleration.x * 10;
            
            int button1State = digitalRead(button1Pin);
            int button2State = digitalRead(button2Pin);
            
            if (button1State != lastButton1State) {
                if (button1State == LOW) {
                    bleMouse.press(MOUSE_LEFT);
                } else {
                    bleMouse.release(MOUSE_LEFT);
                }
                lastButton1State = button1State;
            }
            
            if (button2State != lastButton2State) {
                if (button2State == LOW) {
                    bleMouse.press(MOUSE_RIGHT);
                } else {
                    bleMouse.release(MOUSE_RIGHT);
                }
                lastButton2State = button2State;
            }
            
            bleMouse.move(deltaX, deltaY);
            
            Serial.print("X: ");
            Serial.print(deltaX);
            Serial.print(" Y: ");
            Serial.println(deltaY);
        }
    } else {
        Serial.println("Mouse not connected!");
    }
}
Sonuçlar ve Değerlendirme
Projemiz başarılı bir şekilde tamamlandı ve ESP32CAM ile MPU6050 kullanarak bir ele giyilebilir mouse oluşturduk. Bu proje sayesinde Bluetooth teknolojisi ve sensör verilerini kullanarak cihazlar arası etkileşimin nasıl gerçekleştirileceğini öğrendik. Ayrıca, butonların tıklama işlevlerini programlayarak interaktif bir kullanıcı deneyimi sağladık.
