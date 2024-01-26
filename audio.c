#include <adlmidi.h>
#include <raylib.h>
#include <stdio.h>
#include "audio.h"

#define MAX_SAMPLES_PER_UPDATE 4096

struct ADL_MIDIPlayer *midi_player;
struct ADLMIDI_AudioFormat adl_audio_format = {
    ADLMIDI_SampleType_S16,
    sizeof(ADL_SInt16),
    sizeof(ADL_SInt16) * 2,
};
AudioStream midi_stream;

void callback(void *buffer, unsigned int frames) {
    adl_playFormat(midi_player, frames * 2, (ADL_UInt8 *)buffer,
        (ADL_UInt8 *)buffer + adl_audio_format.containerSize,
        &adl_audio_format);
}

int audio_init(void) {
    midi_player = adl_init(44100);

    if (!midi_player) {
        fprintf(stderr, "Couldn't initialize ADLMIDI: %s\n", adl_errorString());
        return 1;
    }

    adl_switchEmulator(midi_player, ADLMIDI_EMU_NUKED);
    adl_setNumChips(midi_player, 2);
    adl_setBank(midi_player, 74);
    adl_setVolumeRangeModel(midi_player, ADLMIDI_VolumeModel_AUTO);

    InitAudioDevice();
    SetAudioStreamBufferSizeDefault(MAX_SAMPLES_PER_UPDATE);

    midi_stream = LoadAudioStream(44100, 16, 2);
    SetAudioStreamCallback(midi_stream, callback);

    return 0;
}

int audio_shutdown(void) {
    UnloadAudioStream(midi_stream);
    adl_close(midi_player);
    CloseAudioDevice();

    return 0;
}

int play_midi_from_file(const char *path, bool loop) {
    adl_setLoopEnabled(midi_player, loop);

    if (adl_openFile(midi_player, path) < 0) {
        fprintf(stderr, "Couldn't open music file: %s\n", adl_errorInfo(midi_player));
        return 1;
    }

    PlayAudioStream(midi_stream);

    return 0;
}
