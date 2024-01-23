#ifndef AUDIO_H
#define AUDIO_H

#include <stdbool.h>

int audio_init(void);
int audio_shutdown(void);
int play_midi_from_file(const char *path, bool loop);

#endif /* AUDIO_H */
