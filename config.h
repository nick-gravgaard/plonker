#pragma once

#ifdef AUDIO_ENABLE
#define STARTUP_SONG SONG(PLANCK_SOUND)

#define MIDI_BASIC

#define ENCODER_RESOLUTION 4
#endif

/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/
#define ORYX_CONFIGURATOR
#define PLANCK_EZ_LED_LOWER 3
#define PLANCK_EZ_LED_RAISE 4
#define PLANCK_EZ_LED_ADJUST 8

#define TAPPING_TERM 200
