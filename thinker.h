#ifndef THINKER_H
#define THINKER_H

typedef struct Thinker {
    void (*tick)(void*, double);
} Thinker;

#endif /* THINKER_H */
