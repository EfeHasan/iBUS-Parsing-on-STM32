#include "ibus.h"

uint8_t ibus_buffer[IBUS_FRAME_LENGTH]; // iBUS veri çerçevesi

uint16_t ibus_channels[IBUS_CHANNEL_COUNT]; // 10 kanal için veri
uint8_t ibus_data_ready = 0;               // Yeni veri alındığını işaretler

// CRC kontrol fonksiyonu
uint16_t IBUS_CRC(uint8_t *data, uint8_t length) {
    uint16_t crc = 0xFFFF;
    for (uint8_t i = 0; i < length - 2; i++) {
        crc -= data[i];
    }
    return crc;
}

// iBUS verilerini çözümleme
void IBUS_Parse(void) {
    if (ibus_data_ready) {
        ibus_data_ready = 0; // Veri işlendiği için sıfırla

        // CRC doğrulama
        uint16_t received_crc = (ibus_buffer[30] | (ibus_buffer[31] << 8));
        if (IBUS_CRC(ibus_buffer, IBUS_FRAME_LENGTH) != received_crc) {
            return; // CRC hatası, veriyi işleme
        }

        // Kanalları doldur
        for (uint8_t i = 0; i < IBUS_CHANNEL_COUNT; i++) {
            ibus_channels[i] = ibus_buffer[2 + i * 2] | (ibus_buffer[3 + i * 2] << 8);
        }
    }
}

// Belirli bir kanalın değerini al
uint16_t IBUS_GetChannel(uint8_t channel) {
    if (channel < IBUS_CHANNEL_COUNT) {
        return ibus_channels[channel];
    }
    return 0; // Geçersiz kanal
}

//veriyi mapleme methodu
long map(long x, long in_min, long in_max, long out_min, long out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

