#ifndef SRC_BOMB_H_
#define SRC_BOMB_H_
#include <SDL/SDL_image.h>
#include <assert.h>
#include <map.h>
#include <game.h>
#include <list_bomb.h>
#include <player.h>
#include <sprite.h>
#include <window.h>
#include <misc.h>
#include <constant.h>


struct bomb;

// Return the bomb timer of a bomb matching to its creation
int bomb_timer(struct bomb* bomb);



// Create and add a bomb to the bomb_list
struct list_bomb* bomb_create(struct list_bomb *bomb_list,int x, int y);


// Delete a bomb
void bomb_delete(struct list_bomb *bomb_list,int x,int y);

// Decrease the fuse of a bomb by updating a timer and making the difference between this timer and the bomb timer
void bomb_decrease_fuse(struct bomb *bomb);

// Return x,y of the bomb
int bomb_get_x(struct bomb* bomb);
int bomb_get_y(struct bomb* bomb);


// Return the current fuse of a bomb
int bomb_get_fuse(struct bomb *bomb);

// Display the bomb on the screen
void bomb_display(struct bomb* bomb);


// Display the bomb explosion on the screen
void bomb_explode_up(struct bomb* bomb,int range);
void bomb_explode_down(struct bomb* bomb,int range);
void bomb_explode_right(struct bomb* bomb,int range);
void bomb_explode_left(struct bomb* bomb,int range);


#endif /* SRC_BOMB_H_ */
