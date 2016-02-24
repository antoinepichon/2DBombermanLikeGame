/*
 * list_bomb.h
 *
 *  Created on: 21 mai 2015
 *      Author: apichon
 */

#ifndef INCLUDE_LIST_BOMB_H_
#define INCLUDE_LIST_BOMB_H_


#include <map.h>
#include <player.h>
#include <sprite.h>
#include <window.h>
#include <misc.h>
#include <constant.h>
#include <game.h>

struct list_bomb;




struct list_bomb* add_bomb_to_the_list_bomb(struct list_bomb * list_bomb, void * new_bomb);

struct list_bomb* list_bomb_current(struct list_bomb * item );

struct list_bomb* list_bomb_delete(struct list_bomb * list_bomb);


struct list_bomb * list_bomb_next(struct list_bomb * item);




#endif /* INCLUDE_LIST_BOMB_H_ */
