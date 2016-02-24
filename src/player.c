#include <SDL/SDL_image.h>
#include <assert.h>

#include <player.h>
#include <sprite.h>
#include <window.h>
#include <misc.h>
#include <constant.h>
#include <player.h>

struct player {
	int x, y;
	enum direction current_direction;
	int nb_bomb;
	int nb_life;
	int bomb_range;
	int victory;
	int nb_key;
};




struct player* player_init(int bomb_number, int bomb_range, int life_number) {
	struct player* player = malloc(sizeof(*player));
	if (!player)
		error("Memory error");

	player->current_direction = SOUTH;
	player->nb_bomb = bomb_number;
	player->bomb_range = bomb_range;
	player->nb_life = life_number;
	player->victory=0;
	player->nb_key= 0;

	return player;
}

void player_free(struct player* player) {
	assert(player);
	free(player);
}

int player_get_x(struct player* player) {
	assert(player != NULL);
	return player->x;
}

int player_get_y(struct player* player) {
	assert(player != NULL);
	return player->y;
}




void player_set_current_way(struct player* player, enum direction way) {
	assert(player);
	player->current_direction = way;
}

int player_get_nb_bomb(struct player* player) {
	assert(player);
	return player->nb_bomb;
}


void player_inc_nb_bomb(struct player* player) {
	assert(player);
	if(player->nb_bomb<9){
	player->nb_bomb += 1;
	}
	if(player->nb_bomb>9){
		player->nb_bomb=8;

	}
}

void player_dec_nb_bomb(struct player* player) {
	assert(player);
	player->nb_bomb -= 1;
	if (player->nb_bomb <=0){
		player->nb_bomb=0;
	}
}

int player_get_bomb_range(struct player* player){
	assert(player);
	return player->bomb_range;
}

void player_inc_bomb_range(struct player* player){
	assert(player);
	if(player->bomb_range<4)
		player->bomb_range +=1;
}

void player_dec_bomb_range(struct player* player){
	assert(player);
	player->bomb_range -= 1;
}

int player_get_nb_life(struct player* player) {
	assert(player);
	return player->nb_life;
}

void player_inc_nb_life(struct player* player) {
	assert(player);
	player->nb_life += 1;
}

void player_dec_nb_life(struct player* player) {
	assert(player);
	player->nb_life -= 1;
}

int player_get_victory(struct player* player){
	assert(player);
	return player->victory;
}

void player_set_victory(struct player* player){
	assert(player);
	player->victory=1;
}

int player_get_nb_key(struct player* player){

	assert(player);
	return player->nb_key;
}

void player_set_nb_key(struct player* player){
	assert(player);
	player->nb_key=1;
}

void player_dec_nb_key(struct player* player) {
	assert(player);
	player->nb_key = 0;
}


void player_teleport(struct player* player){
	assert(player);

	player->x=9;
	player->y=7;

}



void player_from_map(struct player* player, struct map* map) {
	assert(player);
	assert(map);

	int i, j;
	for (i = 0; i < map_get_width(map); i++) {
		for (j = 0; j < map_get_height(map); j++) {
			if (map_get_cell_type(map, i, j) == CELL_PLAYER) {
				player->x = i;
				player->y = j;
			}
		}
	}
}



static int player_move_aux(struct player* player, struct map* map, int x, int y) {

	if (!map_is_inside(map, x, y))
		return 0;

	switch (map_get_cell_type(map, x, y)) {
	case CELL_SCENERY:
		return 0;
		break;

	case CELL_CASE:
		switch (player->current_direction){
		    case NORTH:
		        if (!map_is_inside(map,x,y-1)||map_get_cell_type(map,x,y-1)!= CELL_EMPTY){
		            return 0;
		        }

		        else


		        	if(map_get_bonus_type(map,x,y)==CELL_CASE_RANGEINC){
		            map_set_cell_type(map,x,y-1,CELL_CASE_RANGEINC);
		            map_set_cell_type(map,x,y,CELL_EMPTY);
		        	}
		        	else if(map_get_bonus_type(map,x,y)==CELL_CASE_RANGEDEC){
		        	            map_set_cell_type(map,x,y-1,CELL_CASE_RANGEDEC);
		        	            map_set_cell_type(map,x,y,CELL_EMPTY);
		        	        	}
		        	else if(map_get_bonus_type(map,x,y)==CELL_CASE_BOMBINC){
		        	            map_set_cell_type(map,x,y-1,CELL_CASE_BOMBINC);
		        	            map_set_cell_type(map,x,y,CELL_EMPTY);
		        	        	}
		        	else if(map_get_bonus_type(map,x,y)==CELL_CASE_BOMBDEC){
		        	            map_set_cell_type(map,x,y-1,CELL_CASE_BOMBDEC);
		        	            map_set_cell_type(map,x,y,CELL_EMPTY);
		        	        	}
		        	else if(map_get_bonus_type(map,x,y)==CELL_CASE_LIFE){
		        	            map_set_cell_type(map,x,y-1,CELL_CASE_LIFE);
		        	            map_set_cell_type(map,x,y,CELL_EMPTY);
		        	        	}
		        	else if(map_get_bonus_type(map,x,y)==CELL_CASE_MONSTER){
		        			    map_set_cell_type(map, x+1,y,CELL_CASE_MONSTER);
		        			    map_set_cell_type(map,x,y,CELL_EMPTY);
		        			    }
		        	else if(map_get_bonus_type(map,x,y)==CELL_CASE_TELEPORT){
		        			        			    map_set_cell_type(map, x+1,y,CELL_CASE_TELEPORT);
		        			        			    map_set_cell_type(map,x,y,CELL_EMPTY);
		        			        			    }
		        	else {
		        		map_set_cell_type(map,x,y-1, CELL_CASE);

		        	}



		        break;

		    case SOUTH:
		    	 if (!map_is_inside(map,x,y+1) || map_get_cell_type(map,x,y+1)!= CELL_EMPTY){
		    	            return 0;
		    	        }

		    	 else


		    	        	if(map_get_bonus_type(map,x,y)==CELL_CASE_RANGEINC){
		    	            map_set_cell_type(map,x,y+1,CELL_CASE_RANGEINC);
		    	            map_set_cell_type(map,x,y,CELL_EMPTY);
		    	        	}
		    	        	else if(map_get_bonus_type(map,x,y)==CELL_CASE_RANGEDEC){
		    	        	            map_set_cell_type(map,x,y+1,CELL_CASE_RANGEDEC);
		    	        	            map_set_cell_type(map,x,y,CELL_EMPTY);
		    	        	        	}
		    	        	else if(map_get_bonus_type(map,x,y)==CELL_CASE_BOMBINC){
		    	        	            map_set_cell_type(map,x,y+1,CELL_CASE_BOMBINC);
		    	        	            map_set_cell_type(map,x,y,CELL_EMPTY);
		    	        	        	}
		    	        	else if(map_get_bonus_type(map,x,y)==CELL_CASE_BOMBDEC){
		    	        	            map_set_cell_type(map,x,y+1,CELL_CASE_BOMBDEC);
		    	        	            map_set_cell_type(map,x,y,CELL_EMPTY);
		    	        	        	}
		    	        	else if(map_get_bonus_type(map,x,y)==CELL_CASE_LIFE){
		    	        	            map_set_cell_type(map,x,y+1,CELL_CASE_LIFE);
		    	        	            map_set_cell_type(map,x,y,CELL_EMPTY);
		    	        	        	}
		    	        	else if(map_get_bonus_type(map,x,y)==CELL_CASE_MONSTER){
		    	        			    map_set_cell_type(map, x+1,y,CELL_CASE_MONSTER);
		    	        			    map_set_cell_type(map,x,y,CELL_EMPTY);
		    	        			    	        	}
		    	        	else if(map_get_bonus_type(map,x,y)==CELL_CASE_TELEPORT){
		    	        			        			        			    map_set_cell_type(map, x+1,y,CELL_CASE_TELEPORT);
		    	        			        			        			    map_set_cell_type(map,x,y,CELL_EMPTY);
		    	        			        			        			    }

		    	        	else {
		    	        	        		map_set_cell_type(map,x,y-1, CELL_CASE);

		    	        	        	}


		    	        break;

		    case WEST:
		    	 if (!map_is_inside(map,x-1,y)||map_get_cell_type(map,x-1,y)!= CELL_EMPTY){
		    	            return 0;
		    	        }

		    	 else


		    	        	if(map_get_bonus_type(map,x,y)==CELL_CASE_RANGEINC){
		    	            map_set_cell_type(map,x-1,y,CELL_CASE_RANGEINC);
		    	            map_set_cell_type(map,x,y,CELL_EMPTY);
		    	        	}
		    	        	else if(map_get_bonus_type(map,x,y)==CELL_CASE_RANGEDEC){
		    	        	            map_set_cell_type(map,x-1,y,CELL_CASE_RANGEDEC);
		    	        	            map_set_cell_type(map,x,y,CELL_EMPTY);
		    	        	        	}
		    	        	else if(map_get_bonus_type(map,x,y)==CELL_CASE_BOMBINC){
		    	        	            map_set_cell_type(map,x-1,y,CELL_CASE_BOMBINC);
		    	        	            map_set_cell_type(map,x,y,CELL_EMPTY);
		    	        	        	}
		    	        	else if(map_get_bonus_type(map,x,y)==CELL_CASE_BOMBDEC){
		    	        	            map_set_cell_type(map,x-1,y,CELL_CASE_BOMBDEC);
		    	        	            map_set_cell_type(map,x,y,CELL_EMPTY);
		    	        	        	}
		    	        	else if(map_get_bonus_type(map,x,y)==CELL_CASE_LIFE){
		    	        	            map_set_cell_type(map,x-1,y,CELL_CASE_LIFE);
		    	        	            map_set_cell_type(map,x,y,CELL_EMPTY);
		    	        	        	}
		    	        	else if(map_get_bonus_type(map,x,y)==CELL_CASE_MONSTER){
		    	        			    map_set_cell_type(map, x+1,y,CELL_CASE_MONSTER);
		    	        			    map_set_cell_type(map,x,y,CELL_EMPTY);
		    	        			    	        	}
		    	        	else if(map_get_bonus_type(map,x,y)==CELL_CASE_TELEPORT){
		    	        			        			        			    map_set_cell_type(map, x+1,y,CELL_CASE_TELEPORT);
		    	        			        			        			    map_set_cell_type(map,x,y,CELL_EMPTY);
		    	        			        			        			    }

		    	        	else {
		    	        	        		map_set_cell_type(map,x,y-1, CELL_CASE);

		    	        	        	}


		    	        break;


		    case EAST:
		    	 if (!map_is_inside(map,x+1,y)||map_get_cell_type(map,x+1,y)!= CELL_EMPTY){
		    	            return 0;
		    	        }

		    	 else


		    	        	if(map_get_bonus_type(map,x,y)==CELL_CASE_RANGEINC){
		    	            map_set_cell_type(map,x+1,y,CELL_CASE_RANGEINC);
		    	            map_set_cell_type(map,x,y,CELL_EMPTY);
		    	        	}
		    	        	else if(map_get_bonus_type(map,x,y)==CELL_CASE_RANGEDEC){
		    	        	            map_set_cell_type(map,x+1,y,CELL_CASE_RANGEDEC);
		    	        	            map_set_cell_type(map,x,y,CELL_EMPTY);
		    	        	        	}
		    	        	else if(map_get_bonus_type(map,x,y)==CELL_CASE_BOMBINC){
		    	        	            map_set_cell_type(map,x+1,y,CELL_CASE_BOMBINC);
		    	        	            map_set_cell_type(map,x,y,CELL_EMPTY);
		    	        	        	}
		    	        	else if(map_get_bonus_type(map,x,y)==CELL_CASE_BOMBDEC){
		    	        	            map_set_cell_type(map,x+1,y,CELL_CASE_BOMBDEC);
		    	        	            map_set_cell_type(map,x,y,CELL_EMPTY);
		    	        	        	}
		    	        	else if(map_get_bonus_type(map,x,y)==CELL_CASE_LIFE){
		    	        	            map_set_cell_type(map,x+1,y,CELL_CASE_LIFE);
		    	        	            map_set_cell_type(map,x,y,CELL_EMPTY);
		    	        	        	}
		    	        	else if(map_get_bonus_type(map,x,y)==CELL_CASE_MONSTER){
		    	        		        map_set_cell_type(map, x+1,y,CELL_CASE_MONSTER);
		    	        		        map_set_cell_type(map,x,y,CELL_EMPTY);
		    	        	}
		    	        	else if(map_get_bonus_type(map,x,y)==CELL_CASE_TELEPORT){
		    	        			        			        			    map_set_cell_type(map, x+1,y,CELL_CASE_TELEPORT);
		    	        			        			        			    map_set_cell_type(map,x,y,CELL_EMPTY);
		    	        			        			        			    }


		    	        	else {
		    	        	        		map_set_cell_type(map,x,y-1, CELL_CASE);

		    	        	        	}

		    	        break;


		}
		break;



	case CELL_BONUS:
if(map_get_bonus_type(map,x,y)==CELL_BONUS_LIFE){
			 if(player_get_nb_life(player)<=8){
				player_inc_nb_life(player);
				map_set_cell_type(map,x,y,CELL_EMPTY);
			 }

		}

else if(map_get_bonus_type(map,x,y)==CELL_BONUS_BOMB_INC){
	         if(player_get_nb_bomb(player)<=8){
	        	 player_inc_nb_bomb(player);
	        	 map_set_cell_type(map,x,y,CELL_EMPTY);
	         }
}

else if(map_get_bonus_type(map,x,y)==CELL_BONUS_BOMB_DEC){
	         if(player_get_nb_bomb(player)!=0){
	        	 player_dec_nb_bomb(player);
	        	 map_set_cell_type(map,x,y,CELL_EMPTY);
	         }
}

else if(map_get_bonus_type(map,x,y)==CELL_BONUS_RANGE_INC){
	         if(player_get_bomb_range(player)<9){
	        	 player_inc_bomb_range(player);
	        	 map_set_cell_type(map,x,y,CELL_EMPTY);
	         }
}

else if(map_get_bonus_type(map,x,y)==CELL_BONUS_RANGE_DEC){
	        if(player_get_bomb_range(player)>=1){
	        	player_dec_bomb_range(player);
	        	map_set_cell_type(map,x,y,CELL_EMPTY);
	        }
}
else if(map_get_bonus_type(map,x,y)==CELL_BONUS_MONSTER){
	        player_dec_nb_life(player);
}
else if(map_get_bonus_type(map,x,y)==CELL_BONUS_TELEPORT){
	 player_teleport(player);
}
		return 1;

		break;

	case CELL_GOAL:
		 player_set_victory(player);

		break;

	case CELL_MONSTER:
		player_dec_nb_life(player);
		return 0;

		break;

	case CELL_PLAYER:
		break;

	case CELL_BOMB:
		player_dec_nb_life(player);
		break;
	case CELL_CLOSED_DOOR:
		if(player_get_nb_key(player)==0){
			return 0;
		}
		if(player_get_nb_key(player)!=0){
		player_dec_nb_key(player);
		map_set_cell_type(map,x,y,CELL_EMPTY);
		}
		break;
	case CELL_KEY:
		player_set_nb_key(player);
		break;

	default:
		break;
	}

	// Player has moved
	return 1;
}

int player_move(struct player* player, struct map* map) {
	int x = player->x;
	int y = player->y;
	int move = 0;

	switch (player->current_direction) {
	case NORTH:
		if (player_move_aux(player, map, x, y - 1)) {
			player->y--;
			move = 1;
		}
		break;

	case SOUTH:
		if (player_move_aux(player, map, x, y + 1)) {
			player->y++;
			move = 1;
		}
		break;

	case WEST:
		if (player_move_aux(player, map, x - 1, y)) {
			player->x--;
			move = 1;
		}
		break;

	case EAST:
		if (player_move_aux(player, map, x + 1, y)) {
			player->x++;
			move = 1;
		}
		break;
	}

	if (move) {
		map_set_cell_type(map, x, y, CELL_EMPTY);
		map_set_cell_type(map, player->x, player->y, CELL_PLAYER);
	}
	return move;
}



void player_display(struct player* player) {
	assert(player);
	window_display_image(sprite_get_player(player->current_direction),
			player->x * SIZE_BLOC, player->y * SIZE_BLOC);
}




