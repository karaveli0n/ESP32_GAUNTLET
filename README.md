

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

Sonuçlar ve Değerlendirme
Projemiz başarılı bir şekilde tamamlandı ve ESP32CAM ile MPU6050 kullanarak bir ele giyilebilir mouse oluşturduk. Bu proje sayesinde Bluetooth teknolojisi ve sensör verilerini kullanarak cihazlar arası etkileşimin nasıl gerçekleştirileceğini öğrendik. Ayrıca, butonların tıklama işlevlerini programlayarak interaktif bir kullanıcı deneyimi sağladık.
