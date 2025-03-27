/// @file CSon.cpp
/// @brief Définition de la classe CSon pour l'acquisition et le traitement du son.
/// @author AUGER
/// @date [Date]
#include "arduinoFFT.h"
#include <driver/i2s.h>
#include "CSon.h"


CSon::CSon()
    {
    this->FFT = ArduinoFFT<double>(this->vReal, this->vImag, SAMPLES, SAMPLING_FREQUENCY); 
    this->pinCconfig = {
    .bck_io_num = 14,  // Broche BCLK
    .ws_io_num = 13,   // Broche Word Select (LRCLK)
    .data_out_num = I2S_PIN_NO_CHANGE, // Pas de sortie
    .data_in_num = 12  // Entrée Data In
    };

    this->i2sConfig = {
    .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX), // Mode maître en réception
    .sample_rate = SAMPLING_FREQUENCY, // 44100 Hz
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT, // 32 bits par échantillon
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT, // Canal gauche et droit
    .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_STAND_I2S), // Format standardz
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1, // Niveau d'interruption 1
    .dma_buf_count = 8, // Nombre de tampons DMA
    .dma_buf_len = DMA_BUF_LEN, // Taille du tampon
    .use_apll = false, // APLL désactivé
    .tx_desc_auto_clear = false, // Pas de nettoyage automatique
    .fixed_mclk = 0 // Pas de fréquence fixe pour MCLK
    };




    };


    CSon::Setup(){
    result = i2s_driver_install(I2S_NUM_0, &this->i2sConfig, 0, NULL); 
    result = i2s_set_pin(I2S_NUM_0, &this->pinCconfig); 
    result = i2s_zero_dma_buffer(I2S_NUM_0); 
    return result; 
    }