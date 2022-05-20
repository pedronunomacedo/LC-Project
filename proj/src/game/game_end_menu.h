#pragma once

#include <lcom/lcf.h>
#include "lib/devices/graphics.h"
#include "lib/sprite/sprite.h"
#include "lib/utils/utils.h"
#include "game/game.h"

#define GAME_END_BTN_X 376
#define GAME_END_BTN_Y 700

/**
 * @brief Initialize game end menu sprites
 * 
 * @return int Return 0 upon success and non-zero otherwise
 */
int (initialize_game_end_menu)(void);

/**
 * @brief Destroy game end menu sprites
 * 
 */
void (destroy_game_end_menu)(void);

/**
 * @brief Draw game end menu in the screen
 * 
 * @return int Return 0 upon success and non-zero otherwise
 */
int (draw_game_end_menu)(void);

/**
 * @brief Set the result of the game 
 * 
 * @param res Integer corresponding to the final result of the game
 */
void (set_result_game_end_menu)(int res);
