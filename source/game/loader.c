#include "game.h"

#include "common.h"
#include "../system/libgv/libgv.h"
#include "../system/libfs/libfs.h"

typedef struct {
    GV_ACT  actor;
    void    *info;
    int     type;
    int     reading;
    int     time;
} Work;
