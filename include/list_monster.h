
#ifndef INCLUDE_LIST_MONSTER_H_
#define INCLUDE_LIST_MONSTER_H_



#include <map.h>
#include <player.h>
#include <sprite.h>
#include <window.h>
#include <misc.h>
#include <constant.h>
#include <game.h>

struct list_monster;




struct list_monster* add_monster_to_the_list_monster(struct list_monster * list_monster, void * new_monster);

struct list_monster* list_monster_current(struct list_monster * item );


struct list_monster * list_monster_next(struct list_monster * item);



#endif /* INCLUDE_LIST_MONSTER_H_ */
