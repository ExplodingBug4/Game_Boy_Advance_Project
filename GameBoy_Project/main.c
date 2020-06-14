#include <gb/gb.h>
#include <gb/font.h>
#include <stdio.h>
#include "Main_Screen_data.c"
#include "Main_Screen_map.c"
#include "Sprites.c"
#include "BackgroundTiles.c"
#include "Background.c"
#include "WindowMap.c"
#include "GameCharacter.c"

#define numOfEnemies 5

// Global Variables.
GameCharacterPlayer player;
GameCharacterEnemy enemy[numOfEnemies];
UBYTE spriteSize = 8; 

// Function Prototypes.
void welcomeScreen();
void setupPlayer();
void setupEnemies();
void updateScore();
void updatePlayer();
void updateEnemy();
void movePlayer(GameCharacterPlayer* character, UINT8 x, UINT8 y);
void moveEnemy(GameCharacterEnemy* character, UINT8 x, UINT8 y);
void performantdelay(UINT8 numloops);
UBYTE checkCollision(GameCharacterPlayer* player, GameCharacterEnemy* enemy);

int main()
{
    // Set the font. Must be done first.
    font_t min_font;
    font_init();

    // Display the welcome screen. Afterward, reset memory.
    welcomeScreen();

    // Load the font into the background memory.
    min_font = font_load(font_min);

    // Set the font for the HUD window.
    font_set(min_font);

    // Set the tiles for the HUD window.
    set_win_tiles(0, 0, 5, 1, WindowMap);

    // Move the window.
    move_win(123, 5);

    // This loads all 6 sprite tiles into the sprite memory.
    set_sprite_data(0, 6, Sprites);

    // Setup player after loading sprites.
    setupPlayer();

    // Setup all enemies.
    setupEnemies();

    // Load the BackgroundTiles data.
    set_bkg_data(37, 7, BackgroundTiles);

    // Set the background.
    set_bkg_tiles(0, 0, 40, 18, BackgroundMap);

    // Display all data onto the screen.
    SHOW_BKG; 
    SHOW_WIN;       
    SHOW_SPRITES;
    DISPLAY_ON;

    // Create an infinite game loop. 
    while(1)
    {
        // Change player position from joystick the input.
        updatePlayer();

        // Update the enemy's position.
        updateEnemy();

        // Sets a delay.
        performantdelay(2);

        // Updates the score on the display every tick.
        updateScore();

        // Check for any collisions. If there is, the game ends. Jump to the end label.
        if ((checkCollision(&player, &enemy[0]) || checkCollision(&player, &enemy[1]) || checkCollision(&player, &enemy[2]) ||
             checkCollision(&player, &enemy[3]) || checkCollision(&player, &enemy[4])))
        {
            goto end;
        }
    }

    // Label for when the game ends.
    end:

    // Game is now over. Print a message.
    printf("\n\n\n\n\n\n\n === Game Over ===");

    return 0;
}

// Load the main menu.
void welcomeScreen()
{
    // Load the data and map into memory.
    set_bkg_data(0, 243, Main_Screen_data);
    set_bkg_tiles(0, 0, 20, 18, Main_Screen_map);

    // Wait until the "START" key is pressed.
    waitpad(J_START);

    // Reset the background data memory.
    set_bkg_data(0, 243, Main_Screen_data_reset);
    set_bkg_tiles(0, 0, 20, 18, Main_Screen_map_reset);
}

// Constructs the player.
void setupPlayer()
{
    // Initialize the starting position, width, and height.
    player.x = 69;
    player.y = 69;
    player.width = 16;
    player.height = 16;

    // Load sprites from the tiles for the player.
    set_sprite_tile(0, 0); 
    player.spritid[0] = 0;
    set_sprite_tile(1, 0); 
    player.spritid[1] = 1;
    set_sprite_tile(2, 0); 
    player.spritid[2] = 2;
    set_sprite_tile(3, 0); 
    player.spritid[3] = 3;

    // Move the player to its specified starting position.
    movePlayer(&player, player.x, player.y);
}

// Constructs the all enemies.
void setupEnemies() 
{
    // for-loop counter.
    int i;

    // Set the width and height of all enemies to 8.
    for (i = 0; i < numOfEnemies; ++i)
    {
        enemy[i].width = 8;
        enemy[i].height = 8;
    }

    // Set the starting position for all enemies.
    enemy[0].x = 40;       
    enemy[0].y = 100;
    enemy[1].x = 90;      
    enemy[1].y = 50;
    enemy[2].x = 20;       
    enemy[2].y = 80;
    enemy[3].x = 90;    
    enemy[3].y = 90;                               
    enemy[4].x = 20;      
    enemy[4].y = 20;

    // Load sprite for the enemies. Right is the tile from memory.
    set_sprite_tile(4, 1);  
    enemy[0].spritid = 4;
    set_sprite_tile(5, 2); 
    enemy[1].spritid = 5;
    set_sprite_tile(6, 3); 
    enemy[2].spritid = 6;
    set_sprite_tile(7, 4); 
    enemy[3].spritid = 7;
    set_sprite_tile(8, 5); 
    enemy[4].spritid = 8;

    // Move all enemies to their starting positions.
    for (i = 0; i < numOfEnemies; ++i)
    {
        moveEnemy(&enemy[i], enemy[i].x, enemy[i].y);
    }
}

// Update the player's position from the joystick input.
void updatePlayer()
{
    // Switch statement depending on button pressed.
    switch(joypad())
    {
        case J_LEFT:
            // Subtract player's x-position by 5. 
            player.x -= 5;

            // Check if the position is out of bounds.
            if (player.x < 15)
            {
                player.x = 15;
            }
            
            // Move the player.
            movePlayer(&player, player.x, player.y);
            break;

        case J_RIGHT:
            // Add player's x-position by 5.
            player.x += 5;

            // Check if the position is out of bounds.
            if (player.x > 96)
            {
                player.x = 96;
            }

            // Move the player.
            movePlayer(&player, player.x, player.y);
            break;

        case J_UP:
            // Subtract player's y-position by 5.
            player.y -= 5;

            // Check if the position is out of bounds.
            if (player.y < 23)
            {
                player.y = 23;
            }

            // Move the player.
            movePlayer(&player, player.x, player.y);
            break;

        case J_DOWN:
            // Add player's y-position by 5.
            player.y += 5;

            // Check if the position is out of bounds.
            if (player.y > 136)
            {
                player.y = 136;
            }

            // Move the player.
            movePlayer(&player, player.x, player.y);
            break;
    }
}

// Move the player by the coordinates specified.
void movePlayer(GameCharacterPlayer* character, UINT8 x, UINT8 y)
{
    // Since the player is made of 4 sprites, it needs to move all 4 sprites.
    move_sprite(character->spritid[0], x, y); 
    move_sprite(character->spritid[1], x + spriteSize, y);
    move_sprite(character->spritid[2], x, y + spriteSize);
    move_sprite(character->spritid[3], x + spriteSize, y + spriteSize);
}

// Update the position of all enemies.
void updateEnemy()
{
    // for-loop counter.
    int i;

    // Makes all the enemies fall down.
    for (i = 0; i < numOfEnemies; i++)
    {
        // Formula for the speed of each enemy. +1 at the end because of index 0.
        enemy[i].y += 4 * (i / 3) + 1;

        // Reset if enemy goes out of bounds. The x-position tracks the player.
        if (enemy[i].y >= 144)
        {
            enemy[i].y = 23;
            enemy[i].x = player.x;
        }

        // Moves the enemy.
        moveEnemy(&enemy[i], enemy[i].x, enemy[i].y);
    }
}

// Move the enemy by the coordinates specified.
void moveEnemy(GameCharacterEnemy* character, UINT8 x, UINT8 y)
{
    move_sprite(character->spritid, x, y); 
}

// Updates the score.
void updateScore()
{
    // Adjust the windowMapTwo[] numerical values. Short circuit.
    if (WindowMapTwo[4] < 0x0C)
    {
        if (WindowMapTwo[4] == 0x0B) WindowMapTwo[4] = 0x02; 
        else ++WindowMapTwo[4];
    }
    if (WindowMapTwo[4] == 0x02 && WindowMapTwo[3] < 0x0C)   
    {
        if (WindowMapTwo[3] == 0x0B) WindowMapTwo[3] = 0x02;
        else ++WindowMapTwo[3];
    }
    if (WindowMapTwo[4] == 0x02 && WindowMapTwo[3] == 0x02 && WindowMapTwo[2] < 0x0C)
    {
        if (WindowMapTwo[2] == 0x0B) WindowMapTwo[2] = 0x02;
        else ++WindowMapTwo[2];
    }
    if (WindowMapTwo[4] == 0x02 && WindowMapTwo[3] == 0x02 && WindowMapTwo[2] == 0x02 && WindowMapTwo[1] < 0x0C)
    {
        if (WindowMapTwo[1] == 0x0B) WindowMapTwo[1] = 0x02;
        else ++WindowMapTwo[1];
    }
    if (WindowMapTwo[4] == 0x02 && WindowMapTwo[3] == 0x02 && WindowMapTwo[2] == 0x02 && WindowMapTwo[1] && WindowMapTwo[0] < 0x0C)
    {
        if (WindowMapTwo[0] == 0x0B) WindowMapTwo[0] = 0x02;
        else ++WindowMapTwo[0];
    }

    // Load the update WindowMapTwo.
    set_win_tiles(0, 2, 5, 1, WindowMapTwo);
}

// Delay function for the game.
void performantdelay(UINT8 numloops)
{
    UINT8 i;
    for(i = 0; i < numloops; i++){
        wait_vbl_done();
    }     
}

// Checks if a collision has occured between the player and the enemy.
UBYTE checkCollision(GameCharacterPlayer* player, GameCharacterEnemy* enemy)
{
    return (player->x >= enemy->x && player->x <= enemy->x + enemy->width) && (player->y >= enemy->y && player->y <= enemy->y + enemy->height) || 
           (enemy->x >= player->x && enemy->x <= player->x + player->width) && (enemy->y >= player->y && enemy->y <= player->y + player->height);
}
