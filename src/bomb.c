#include <SDL/SDL_image.h>
#include <assert.h>

#include <map.h>
#include <player.h>
#include <sprite.h>
#include <window.h>
#include <misc.h>
#include <constant.h>
#include <game.h>
#include <list_bomb.h>
#include <stdlib.h>

struct bomb{
	int x;
	int y;
	int timer;
	int fuse;
};

int bomb_clock_fixed(struct bomb* bomb){
	return bomb->timer;
}


struct list_bomb* bomb_create(struct list_bomb *bomb_list,int x, int y) {

	struct bomb* bomb = malloc(sizeof(*bomb));

	if (!bomb)
		error("Memory error");

	bomb->x = x;
	bomb->y = y;
	bomb->fuse=4;
	bomb->timer = SDL_GetTicks();
	bomb_list = add_bomb_to_the_list_bomb(bomb_list, bomb);

	return bomb_list;
}

void bomb_delete(struct list_bomb *bomb_list,int x,int y) {
	struct bomb* bomb = malloc(sizeof(*bomb));

	if (!bomb)
		error("Memory error");

	bomb_list = list_bomb_delete(bomb_list);
}



void bomb_decrease_fuse(struct bomb *bomb){


	int timer_bomb=(SDL_GetTicks()-bomb_clock_fixed(bomb))/800;



	switch (timer_bomb) {
	case 0:
		bomb->fuse=4;
		break;
	case 1:
		bomb->fuse=3;
		break;
	case 2:
		bomb->fuse=2;
		break;
	case 3:
		bomb->fuse=1;
		break;
	case 4:
		bomb->fuse=0;
		break;
	case 5:
		bomb->fuse=5;
		break;
	default:
		bomb->fuse=5;
	}
}

int bomb_get_x(struct bomb* bomb){
	return bomb->x;
}

int bomb_get_y(struct bomb* bomb){
	return bomb->y;
}

int bomb_get_fuse(struct bomb *bomb){
	return bomb->fuse;
}

void bomb_display(struct bomb* bomb) {
	if(bomb->fuse<=4)
		window_display_image(sprite_get_bomb(bomb->fuse),bomb->x*SIZE_BLOC,bomb->y*SIZE_BLOC);
}

void bomb_explode_up(struct bomb* bomb,int range){
	int i=0;
	while(i<=range){
		window_display_image(sprite_get_bomb(bomb->fuse),bomb->x*SIZE_BLOC,((bomb->y)-i)*SIZE_BLOC);
		i++;
	}
}

void bomb_explode_down(struct bomb* bomb,int range){
	int i=0;
	while(i<=range){
		window_display_image(sprite_get_bomb(bomb->fuse),bomb->x*SIZE_BLOC,((bomb->y)+i)*SIZE_BLOC);
		i++;
	}
}

void bomb_explode_right(struct bomb* bomb,int range){
	int i=0;
	while(i<=range){
		window_display_image(sprite_get_bomb(bomb->fuse),((bomb->x)+i)*SIZE_BLOC,bomb->y*SIZE_BLOC);
		i++;
	}
}

void bomb_explode_left(struct bomb* bomb,int range){
	int i=0;
	while(i<=range){
		window_display_image(sprite_get_bomb(bomb->fuse),((bomb->x)-i)*SIZE_BLOC,bomb->y*SIZE_BLOC);
		i++;
	}
}


