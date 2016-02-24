/*
 * monster.h
 *
 *  Created on: 20 mars 2014
 *      Author: Maxime
 */

#ifndef MONSTER_H_
#define MONSTER_H_

#include <map.h>
#include <constant.h>
#include <list_monster.h>
#include <monster.h>

struct monster;


// Creates a new monster
struct list_monster* monster_create(struct list_monster *monster_list,struct map* map);

// Return the timer of monster
int monster_clock_fixed(struct monster *monster);

// Returns the current position of the monster
int monster_get_x(struct monster* monster);
int monster_get_y(struct monster* monster);

// Set the direction of the next move of the monster
void monster_set_current_way(struct monster* monster, enum direction way);

// Move the monster according to the current direction
int monster_move(struct monster* monster, struct map* map);

/* Switch the current direction of monsters each time that the condition is verified */
void monster_update(struct monster *monster, struct map *map);

//Kill a monster when he is on a CELL_BOMB by making him leave the map
void monster_die(struct monster* monster);

// Display the monster on the screen
void monster_display(struct monster* monster);

#endif /* MONSTER_H_ */
