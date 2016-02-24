#ifndef PLAYER_H_
#define PLAYER_H_

#include <map.h>
#include <constant.h>

struct player;

// Creates a new player with a given number of available bombs and their range, and a given number of lives
struct player* player_init(int bomb_number,int bomb_range, int life_number);
void   player_free(struct player* player);

// Returns the current position of the player
int player_get_x(struct player* player);
int player_get_y(struct player* player);

// Set the direction of the next move of the player
void player_set_current_way(struct player * player, enum direction direction);

// Set, Increase, Decrease the number of bomb that player can put
int  player_get_nb_bomb(struct player * player);
void player_inc_nb_bomb(struct player * player);
void player_dec_nb_bomb(struct player * player);

// Set, Increase, Decrease the range of the bomb's explosion
int player_get_bomb_range(struct player* player);
void player_inc_bomb_range(struct player* player);
void player_dec_bomb_range(struct player* player);

// Set, Increase, Decrease the number of lives
int player_get_nb_life(struct player* player);
void player_inc_nb_life(struct player* player);
void player_dec_nb_life(struct player* player);

// Set victory
int player_get_victory(struct player* player);
void player_set_victory(struct player* player);

//Set, Increase, Decrease the number of keys
int player_get_nb_key(struct player* player);
void player_set_nb_key(struct player* player);
void player_dec_nb_key(struct player* player);

// Teleport the player
void player_teleport(struct player* player);

// Load the player position from the map
void player_from_map(struct player* player, struct map* map);

// Move the player according to the current direction
int player_move(struct player* player, struct map* map);

// Display the player on the screen
void player_display(struct player* player);



#endif /* PLAYER_H_ */
