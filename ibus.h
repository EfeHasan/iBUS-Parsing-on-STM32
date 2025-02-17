#ifndef IBUS_H
#define IBUS_H

#include <stdint.h> // Sabit boyutlu veri tipleri için
#include "stm32f4xx_hal.h"    // UART_HandleTypeDef ve HAL fonksiyonları için

#define IBUS_FRAME_LENGTH 32  // iBUS veri çerçevesi uzunluğu
#define IBUS_CHANNEL_COUNT 10 // iBUS kanal sayısı

extern uint16_t ibus_channels[IBUS_CHANNEL_COUNT]; // Kanal verileri
extern uint8_t ibus_data_ready;                   // Yeni veri işareti
extern uint8_t ibus_buffer[IBUS_FRAME_LENGTH]; // iBUS veri çerçevesi

// iBUS kütüphanesi fonksiyonları
void IBUS_Parse(void);                    // iBUS verilerini çözümleme
uint16_t IBUS_GetChannel(uint8_t channel); // Belirli bir kanalı alma
uint16_t IBUS_CRC(uint8_t *data, uint8_t length); // CRC kontrol fonksiyonu
long map(long x, long in_min, long in_max, long out_min, long out_max); // veriyi mapleme fonksiyonu

#endif // IBUS_H
