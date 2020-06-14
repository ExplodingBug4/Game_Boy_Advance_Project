#include <gb/gb.h>

// GameCharacter structure: id, position, graphics
typedef struct {
    UBYTE spritid[4];
    UINT8 x;
    UINT8 y;
    UINT8 width;
    UINT8 height;
} GameCharacterPlayer;

typedef struct {
    UBYTE spritid;
    UINT8 x;
    UINT8 y;
    UINT8 width;
    UINT8 height;
} GameCharacterEnemy;