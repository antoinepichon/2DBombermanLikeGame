#include <SDL/SDL_image.h>
#include <assert.h>
#include <stdlib.h>
#include <monster.h>
#include <sprite.h>
#include <window.h>
#include <misc.h>
#include <constant.h>
#include <monster.h>
#include <list_monster.h>
#include <map.h>
#include <game.h>
#include <time.h>

struct monster {
	int x, y;
	enum direction current_direction;
	int timer;
};


struct list_monster* monster_create(struct list_monster *monster_list,struct map* map) {
	assert(map);

	int i, j;
	for (i = 0; i < map_get_width(map); i++) {
		for (j = 0; j < map_get_height(map); j++) {
			if (map_get_cell_type(map, i, j) == CELL_MONSTER) {
				struct monster* monster = malloc(sizeof(*monster));
				monster->x = i;
				monster->y = j;
				monster->current_direction=SOUTH;
				monster->timer = SDL_GetTicks();
				monster_list = add_monster_to_the_list_monster(monster_list, monster);
			}
		}
	}
	return monster_list;
}


int monster_clock_fixed(struct monster *monster){
	assert(monster);
	return monster->timer;
}


int monster_get_x(struct monster* monster) {
	assert(monster != NULL);
	return monster->x;
}

int monster_get_y(struct monster* monster) {
	assert(monster != NULL);
	return monster->y;
}


void monster_set_current_way(struct monster* monster, enum direction way) {
	assert(monster);
	monster->current_direction = way;
}



static int monster_move_aux(struct monster* monster, struct map* map, int x, int y) {

	if (!map_is_inside(map, x, y)){
		return 0;
	}

	switch (map_get_cell_type(map, x, y)) {

	case CELL_SCENERY:
			return 0;
			break;

		case CELL_CASE:
			return 0;
			break;

		case CELL_BONUS:
			break;

		case CELL_GOAL:
			return 0;
			break;

		case CELL_MONSTER:
			return 0;
			break;

		case CELL_PLAYER:
			return 0;
			break;

		case CELL_BOMB:

			monster_die(monster);
			map_set_cell_type(map,x,y,CELL_EMPTY);
			return 0;
			break;


		default:
			break;
	}

	// Monster has moved
	return 1;
}

int monster_move(struct monster* monster, struct map* map) {
	int x = monster->x;
	int y = monster->y;

	int move = 0;

	if (!map_is_inside(map, x, y))
			return 0;

	switch (monster->current_direction) {
	case NORTH:
		if (monster_move_aux(monster, map, x, y - 1)) {
			map_set_cell_type(map,x,y,CELL_EMPTY);
			monster->y--;
			map_set_cell_type(map,monster_get_x(monster),monster_get_y(monster),CELL_MONSTER);

			move = 1;
		}
		break;

	case SOUTH:
		if (monster_move_aux(monster, map, x, y + 1)) {
			map_set_cell_type(map,x,y,CELL_EMPTY);
			monster->y++;
			map_set_cell_type(map,monster_get_x(monster),monster_get_y(monster),CELL_MONSTER);

			move = 1;
		}
		break;

	case WEST:
		if (monster_move_aux(monster, map, x - 1, y)) {
			map_set_cell_type(map,x,y,CELL_EMPTY);
			monster->x--;
			map_set_cell_type(map,monster_get_x(monster),monster_get_y(monster),CELL_MONSTER);

			move = 1;
		}
		break;

	case EAST:
		if (monster_move_aux(monster, map, x + 1, y)) {
			map_set_cell_type(map,x,y,CELL_EMPTY);
			monster->x++;
			map_set_cell_type(map,monster_get_x(monster),monster_get_y(monster),CELL_MONSTER);

			move = 1;
		}
		break;
	}
	return move;
}

void monster_update(struct monster *monster, struct map *map){

		if((SDL_GetTicks()-monster_clock_fixed(monster))%10==9){

			int randmonster = rand()%4;
			switch(randmonster){
			case NORTH:
				monster_set_current_way(monster,NORTH);
				monster_move(monster,map);
				break;
			case SOUTH:
				monster_set_current_way(monster,SOUTH);
				monster_move(monster,map);
				break;
			case EAST:
				monster_set_current_way(monster,EAST);
				monster_move(monster,map);
				break;
			case WEST:
				monster_set_current_way(monster,WEST);
				monster_move(monster,map);
				break;
			}
		}


}

void monster_die(struct monster* monster){
	assert(monster);

	monster->x=25;
	monster->y=25;

}
void monster_display(struct monster* monster) {
	assert(monster);
	window_display_image(sprite_get_monster(monster->current_direction),
			monster->x * SIZE_BLOC, monster->y * SIZE_BLOC);
}

