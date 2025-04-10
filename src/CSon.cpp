/// @file CSon.cpp
/// @brief Définition de la classe CSon pour l'acquisition et le traitement du son.
/// @author AUGER
/// @date [Date]


#include "arduinoFFT.h"
#include <driver/i2s.h>
#include "CSon.h"


// Constructeur de la classe CSon
CSon::CSon()
{
    // Initialisation de l'objet FFT
    this->FFT = ArduinoFFT<double>(this->vReal, this->vImag, SAMPLES, SAMPLING_FREQUENCY);


    // Configuration des broches I2S
    this->pinCconfig = {
        .bck_io_num = 14,  // Broche BCLK
        .ws_io_num = 13,   // Broche Word Select (LRCLK)
        .data_out_num = I2S_PIN_NO_CHANGE, // Pas de sortie
        .data_in_num = 12  // Entrée Data In
    };


    // Configuration du module I2S
    this->i2sConfig = {
        .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX), // Mode maître en réception
        .sample_rate = SAMPLING_FREQUENCY, // Fréquence d'échantillonnage
        .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT, // 32 bits par échantillon
        .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT, // Canal gauche et droit
        .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_STAND_I2S), // Format standard
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1, // Niveau d'interruption
        .dma_buf_count = 8, // Nombre de tampons DMA
        .dma_buf_len = DMA_BUF_LEN, // Taille des tampons
        .use_apll = false, // APLL désactivé
        .tx_desc_auto_clear = false, // Pas de nettoyage automatique
        .fixed_mclk = 0 // Pas de fréquence fixe pour MCLK
    };
}


// Configuration du module I2S
esp_err_t CSon::Setup()
{
    esp_err_t result;


    // Installation du driver I2S
    result = i2s_driver_install(I2S_NUM_0, &this->i2sConfig, 0, NULL);
    if (result != ESP_OK) return result;


    // Configuration des broches I2S
    result = i2s_set_pin(I2S_NUM_0, &this->pinCconfig);
    if (result != ESP_OK) return result;


    // Réinitialisation du tampon DMA
    result = i2s_zero_dma_buffer(I2S_NUM_0);


    return result;
}


// Acquisition des données audio via DMA
esp_err_t CSon::SamplesDmaAcquisition()
{
    // Variable pour le nombre d'octets lus en mémoire DMA
    size_t bytesRead;


    // Capture des données audio via le module I2S
    esp_err_t result = i2s_read(I2S_NUM_0, &this->i2sData, sizeof(this->i2sData), &bytesRead, portMAX_DELAY);


    if (result == ESP_OK)
    {
        // Calcul du nombre d'échantillons lus
        int16_t samplesRead = bytesRead / sizeof(int32_t);


        if (samplesRead > 0)  
        {
            float mean = 0.0f;


            // Traitement des échantillons audio
            for (int16_t i = 0; i < samplesRead; ++i)  
            {
                i2sData[i] = i2sData[i] >> 8;
                float absoluteValue = abs(i2sData[i]);
                mean += absoluteValue;


                if (absoluteValue > niveauSonoreCrete)
                {
                    niveauSonoreCrete = absoluteValue;
                }
            }


            // Calcul du niveau sonore moyen
            this->niveauSonoreMoyen = mean / samplesRead;


            // Envoi des données formatées sur le port série pour le Serial Plotter
            Serial.print("Moyen: ");
            Serial.print(this->niveauSonoreMoyen);
            Serial.print("\t");


            Serial.print("Crete: ");
            Serial.println(this->niveauSonoreCrete);
        }    
    }


    return result;
}
