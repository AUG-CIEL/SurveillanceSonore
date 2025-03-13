/// @file CSon.h
/// @brief Définition de la classe CSon pour l'acquisition et le traitement du son.
/// @author AUGER
/// @date [Date]

#ifndef CSON_H
#define CSON_H

#include "arduinoFFT.h"
#include <driver/i2s.h>

/// @brief Nombre d'échantillons pour l'analyse FFT.
#define SAMPLES 512                 
/// @brief Fréquence d'échantillonnage en Hz.
#define SAMPLING_FREQUENCY 44100    
/// @brief Taille du buffer DMA en nombre d'échantillons.
#define DMA_BUF_LEN 512             
/// @brief Nombre de buffers DMA utilisés.
#define DMA_BUF_COUNT 8             

/// @class CSon
/// @brief Classe permettant l'acquisition et le traitement des signaux sonores via I2S et FFT.
class CSon {
public:
    /// @brief Niveau sonore moyen calculé.
    float niveauSonoreMoyen;
    /// @brief Niveau sonore crête mesuré.
    float niveauSonoreCrete;
    /// @brief Tableau des valeurs réelles pour l'analyse FFT.
    float vReal[SAMPLES];
    /// @brief Tableau des valeurs imaginaires pour l'analyse FFT.
    float vImag[SAMPLES];
    /// @brief Tableau contenant les données acquises via I2S.
    int32_t i2sData[SAMPLES];

    /// @brief Constructeur de la classe CSon.
    CSon();
    
    /// @brief Configure l'interface I2S pour l'acquisition audio.
    /// @return Code d'erreur ESP (ESP_OK si succès, autre en cas d'erreur).
    esp_err_t Setup();
    
    /// @brief Acquiert les échantillons audio via DMA et I2S.
    /// @return Code d'erreur ESP (ESP_OK si succès, autre en cas d'erreur).
    esp_err_t SamplesDmaAcquisition();
};

#endif // CSON_H

