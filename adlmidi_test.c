#include <adlmidi.h>
#include <raylib.h>
#include <stdio.h>
#include "audio.h"

#define MAX_SAMPLES_PER_UPDATE 4096

static struct ADL_MIDIPlayer *midi_player;
static struct ADLMIDI_AudioFormat adl_audio_format = {
    ADLMIDI_SampleType_S16,
    sizeof(ADL_SInt16),
    sizeof(ADL_SInt16) * 2,
};

void AudioInputCallback(void *buffer, unsigned int frames)
{
    adl_playFormat(midi_player, frames * 2, (ADL_UInt8 *)buffer, (ADL_UInt8 *)buffer + adl_audio_format.containerSize, &adl_audio_format);
}


int main(void)
{
    int err = 0;

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [audio] example - raw audio streaming");

    err = audio_init();

    if (err) {
        goto close_window;
    }

    err = play_midi_from_file("music.mid", true);

    if (err) {
        goto close_window;
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
        EndDrawing();
    }

    audio_shutdown();
close_window:
    CloseWindow();

    return err;
}
