# iBUS-Parsing-on-STM32


English

Overview

This library provides an easy-to-use interface for communicating with iBUS-enabled devices, typically used in RC systems for receiving telemetry data and controlling servos, motors, and other actuators. The library handles receiving iBUS frames, parsing the data, verifying the integrity using CRC, and extracting the channel values for further processing. This implementation is optimized for STM32 microcontrollers and UART-based communication.

Features

Parse iBUS data frames of length 32 bytes.

Validate the integrity of the received data using CRC16.

Retrieve values from up to 10 channels.

Map raw channel values to any desired range for use with other systems, like PWM control.

How to Use

Library Setup

Include the ibus.h header file in your project.

Configure the UART peripheral on your STM32 to handle asynchronous communication (UART interrupt mode).

Call HAL_UART_Receive_IT(&huart2, ibus_buffer, IBUS_FRAME_LENGTH); to start receiving iBUS data into the ibus_buffer.

Parsing the DataAfter receiving the iBUS data, call IBUS_Parse() to:

Validate the data using the CRC function.

Parse the channel values and store them in the ibus_channels array.

HAL_UART_Receive_IT(&huart2, ibus_buffer, IBUS_FRAME_LENGTH); // Start receiving iBUS data
IBUS_Parse(); // Parse the received data and verify the integrity

Getting Channel DataTo retrieve a value for a specific channel (0-9), call IBUS_GetChannel(channel). This function returns the value of the specified channel, or 0 if the channel index is invalid.

uint16_t channel0_value = IBUS_GetChannel(0); // Get the value of channel 0

CRC ValidationThe IBUS_CRC() function performs a CRC16 check on the received iBUS frame to ensure that the data has not been corrupted during transmission.

Mapping ValuesThe map() function allows you to scale the received channel values from one range to another. This can be useful when mapping the raw data to control systems such as PWM or analog output.

long pwm_value = map(channel_value, 0, 2047, 1000, 2000); // Map the channel value to PWM range

Functions

IBUS_Parse(): This function processes the received iBUS frame, checks the CRC, and extracts the channel values.

IBUS_GetChannel(uint8_t channel): Retrieves the value of the specified channel (0-9). Returns 0 if the channel index is invalid.

IBUS_CRC(uint8_t *data, uint8_t length): Computes the CRC16 for the given iBUS data and compares it to the received CRC.

map(long x, long in_min, long in_max, long out_min, long out_max): Maps the input value (x) from one range (in_min to in_max) to another range (out_min to out_max).

Example Code

// Start receiving data from iBUS receiver
HAL_UART_Receive_IT(&huart2, ibus_buffer, IBUS_FRAME_LENGTH); 

// Parse the received data and validate its integrity
IBUS_Parse(); 

// Retrieve values for specific channels (e.g., channel 0)
uint16_t channel0_value = IBUS_GetChannel(0); 

// Map channel value (0-2047) to PWM range (1000-2000)
long pwm_value = map(channel0_value, 0, 2047, 1000, 2000);

Important Notes

UART Configuration: Ensure that the UART is correctly configured for interrupt-driven data reception. Use HAL_UART_Receive_IT() to enable interrupt-based data collection, ensuring that the MCU doesn't block while waiting for data.

Data Integrity: The CRC16 function ensures that the received iBUS data has not been corrupted during transmission. If the CRC check fails, the data will not be processed.

Channel Range: The iBUS protocol supports up to 10 channels, and the channel values are 16-bit (1000-2000).

Türkçe

Genel Bakış

Bu kütüphane, iBUS protokolüyle çalışan cihazlarla iletişim kurmak için kullanıcı dostu bir arayüz sağlar. iBUS, genellikle RC sistemlerinde kullanılan bir protokoldür ve bu kütüphane, iBUS çerçevelerini almak, veriyi çözümlemek, CRC ile bütünlüğünü doğrulamak ve kanal verilerini çıkarmak için kullanılır. Kütüphane, STM32 mikrodenetleyiciler için optimize edilmiştir ve UART tabanlı iletişimle çalışır.

Özellikler

32 bayttan oluşan iBUS veri çerçevelerini çözümleyin.

Alınan verilerin bütünlüğünü CRC16 ile doğrulayın.

10 kanala kadar veri alabilirsiniz.

Ham kanal değerlerini PWM kontrolü gibi başka sistemlerle uyumlu hale getirmek için değerleri belirli bir aralığa haritalayın.

Kullanım

Kütüphane Kurulumu

ibus.h başlık dosyasını projeye dahil edin.

STM32'nin UART periferalini asenkron iletişim (kesme tabanlı) için yapılandırın.

HAL_UART_Receive_IT(&huart2, ibus_buffer, IBUS_FRAME_LENGTH); fonksiyonunu çağırarak iBUS verilerini ibus_buffer içine almaya başlayın.

Veri ÇözümlemeiBUS verilerini aldıktan sonra, veriyi çözümlemek için IBUS_Parse() fonksiyonunu çağırın. Bu fonksiyon:

Veriyi CRC fonksiyonu ile doğrular.

Kanal değerlerini ibus_channels dizisine işler.

HAL_UART_Receive_IT(&huart2, ibus_buffer, IBUS_FRAME_LENGTH); // iBUS verisini almak için alımı başlat
IBUS_Parse(); // Alınan veriyi çözümle ve bütünlüğü doğrula

Kanal Verisini AlmaBelirli bir kanalın değerini almak için IBUS_GetChannel(channel) fonksiyonunu kullanın. Bu fonksiyon, belirtilen kanalın değerini döndürür, geçersiz bir kanal numarası verilirse 0 döndürür.

uint16_t channel0_value = IBUS_GetChannel(0); // Kanal 0'ın değerini al

CRC DoğrulamasıIBUS_CRC() fonksiyonu, alınan iBUS çerçevesinin CRC16 değerini hesaplar ve alınan CRC ile karşılaştırarak verinin bütünlüğünü kontrol eder.

Veri Maplememap() fonksiyonu, alınan kanal verilerini başka bir aralığa dönüştürmek için kullanılabilir. Örneğin, ham kanal verilerini PWM kontrol değeri gibi başka bir değere dönüştürmek için bu fonksiyon faydalıdır.

long pwm_value = map(channel_value, 0, 2047, 1000, 2000); // Kanal değerini PWM aralığına mapler

Fonksiyonlar

IBUS_Parse(): Alınan iBUS çerçevesini işler, CRC doğrulaması yapar ve kanal değerlerini çıkarır.

IBUS_GetChannel(uint8_t channel): Belirtilen kanalın (0-9) değerini alır. Geçersiz bir kanal istenirse 0 döndürür.

IBUS_CRC(uint8_t *data, uint8_t length): Verilen iBUS verisi için CRC16 hesaplar ve alınan CRC ile karşılaştırır.

map(long x, long in_min, long in_max, long out_min, long out_max): Giriş değerini bir aralıktan başka bir aralığa haritalar.

Örnek Kod

// iBUS alıcısından veri almayı başlat
HAL_UART_Receive_IT(&huart2, ibus_buffer, IBUS_FRAME_LENGTH); 

// Alınan veriyi çözümle ve bütünlüğünü doğrula
IBUS_Parse(); 

// Belirli bir kanalın değerini al (örneğin kanal 0)
uint16_t channel0_value = IBUS_GetChannel(0); 

// Kanal değerini PWM aralığına maple (0-2047 -> 1000-2000)
long pwm_value = map(channel0_value, 0, 2047, 1000, 2000);

Önemli Notlar

UART Yapılandırması: UART'ın doğru şekilde yapılandırıldığından emin olun. Kesme tabanlı veri alımı için HAL_UART_Receive_IT() fonksiyonu kullanılmalıdır, böylece MCU veri beklerken bloklanmaz.

Veri Bütünlüğü: CRC16 fonksiyonu, alınan iBUS verisinin iletim sırasında bozulmadığını kontrol eder. CRC doğrulaması başarısız olursa, veri işlenmez.

Kanal Aralığı: iBUS protokolü, 10 kanala kadar veri alabilir ve kanal değerleri 16-bit (1000-2000) aralığındadır.
