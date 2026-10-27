#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <Arduino.h>
#include <Preferences.h>
#include "pins.h"
#include "../localization/Localization.h"

// OS menu color theme palettes. NEVER reorder: the value is persisted in NVS.
enum ColorTheme : uint8_t {
    THEME_CLASSIC = 0, // Y3 Pure Yellow (255, 255, 0)
    THEME_EMERALD = 1, // G2 Emerald     (0, 180, 60)
    THEME_AZURE   = 2, // B5 Sky / Azure (0, 180, 255)
    THEME_VIOLET  = 3, // U3 Violet      (165, 30, 210)
    THEME_ROSE    = 4, // P2 Deep Rose   (230, 30, 100)
    THEME_COUNT   = 5
};

class ConfigManager {
public:
    static const int SLEEP_OPTION_COUNT = 5;
    static const int THEME_OPTION_COUNT = THEME_COUNT;

    ConfigManager();
    void begin();

    // --- Volume (0% to 100%, 0% = OFF) ---
    int getVolume() const;
    void setVolume(int vol);
    void toggleMute();
    bool isMuted() const;

    // --- Brightness (10% to 100%) ---
    int getBrightness() const;
    void setBrightness(int val);
    void applyBrightness() const;
    void applyDimmedBrightness() const;
    void setBacklightRaw(uint8_t pwm) const;
    static int calculateBrightnessPwm(int percent);

    // --- Auto-Sleep Timeout ---
    int getSleepTimeoutIndex() const;
    void setSleepTimeoutIndex(int idx);
    void toggleSleepTimeout();
    unsigned long getSleepTimeoutMs() const;

    // --- Language ---
    Language getLanguage() const;
    void setLanguage(Language lang);

    // --- Color Theme ---
    ColorTheme getColorTheme() const;
    void setColorTheme(ColorTheme theme);
    void cycleColorTheme(int direction);
    static uint16_t getThemeColor();

    // --- Highscore Management ---
    void resetAllHighscores(const char* const gameNames[], int gameCount);

private:
    int _volume;
    int _lastNonZeroVolume;
    int _brightness;
    int _sleepTimeoutIndex;
    int _lastNonZeroSleepTimeoutIndex;
    Language _language;
    ColorTheme _colorTheme;

    static ColorTheme _activeTheme;
    static const uint16_t THEME_COLORS[THEME_COUNT];
    static const unsigned long SLEEP_TIMEOUTS_MS[SLEEP_OPTION_COUNT];
};

#endif // CONFIGMANAGER_H
