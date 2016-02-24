#include <assert.h>
#include <time.h>
#include <map.h>
#include <game.h>
#include <misc.h>
#include <window.h>
#include <sprite.h>
#include <player.h>
#include <monster.h>
#include <list_bomb.h>
#include <list_monster.h>
#include <bomb.h>

struct game {
	struct level* curr_level; // current level
	struct player* player;
	struct list_monster* monster;
	struct list_bomb* bomb;
	int PAUSE;

};

struct game* game_new(void){
	sprite_load(); // load sprites into process memory

	struct game* game = malloc(sizeof(*game));
	game->curr_level = level_get_level(0); // get maps of the first level
    game->bomb=NULL;
	game->player = player_init(5,1,2);
	player_from_map(game->player, level_get_map(game->curr_level, 0)); // get x,y of the player on the first map

	game->monster=NULL;
	game->monster = monster_create(game->monster,level_get_map(game->curr_level,0));

	game->PAUSE=0;

	return game;
}


void game_free(struct game* game) {
	assert(game);

	player_free(game->player);
	level_free(game->curr_level);

}


struct player* game_get_player(struct game* game) {
	assert(game);
	return game->player;
}

struct list_bomb* game_get_bomb_list(struct game* game){
	assert(game);
	return game->bomb;
}

struct list_monster* game_get_monster_list(struct game* game) {
	assert(game);
	return game->monster;
}

struct level* game_get_curr_level(struct game* game) {
	return game->curr_level;
}

void game_banner_display(struct game* game) {
	assert(game);
    struct player* player = game_get_player(game);
	struct map* map = level_get_curr_map(game_get_curr_level(game));

	int y = (map_get_height(map)) * SIZE_BLOC;
	for (int i = 0; i < map_get_width(map); i++)
		window_display_image(sprite_get_banner_line(), i * SIZE_BLOC, y);

	int white_bloc = ((map_get_width(map) * SIZE_BLOC) - 6 * SIZE_BLOC) / 4;
	int x = white_bloc;
	y = (map_get_height(map) * SIZE_BLOC) + LINE_HEIGHT;
	window_display_image(sprite_get_banner_life(), x, y);

	x = white_bloc + SIZE_BLOC;
	window_display_image(sprite_get_number(player_get_nb_life(player)), x, y);

	x = 2 * white_bloc + 2 * SIZE_BLOC;
	window_display_image(sprite_get_banner_bomb(), x, y);

	x = 2 * white_bloc + 3 * SIZE_BLOC;
	window_display_image(
			sprite_get_number(player_get_nb_bomb(game_get_player(game))), x, y);

	x = 3 * white_bloc + 4 * SIZE_BLOC;
	window_display_image(sprite_get_banner_range(), x, y);

	x = 3 * white_bloc + 5 * SIZE_BLOC;
	window_display_image(sprite_get_number(player_get_bomb_range(game_get_player(game))), x, y);

	if(player_get_nb_key(player)!=0){
			x = 3 * white_bloc + 5.9 * SIZE_BLOC;
			window_display_image(sprite_get_key(), x, y);
		}
}


void bomb_explode_and_bomb_range(struct list_bomb* bomb_list,struct map *map,struct game* game,struct bomb* bomb){ /* Handle the setting cell type of bomb and bonus, handle the display of bombs and their explosion and the explosion of bombs according to their direction, and eventually handle the disappearance of the bombs's sprites and explosions's sprites after the explosion of the bomb */


	if(bomb_get_fuse(bomb)==0){
		map_set_cell_type(map,bomb_get_x(bomb),bomb_get_y(bomb),CELL_BOMB);


		if(bomb_get_fuse(bomb)!=5){


            int range_inc=1;
			for(range_inc=1 ; range_inc<=player_get_bomb_range(game_get_player(game)) ; range_inc++){


				if(map_is_inside(map,bomb_get_x(bomb),bomb_get_y(bomb)+range_inc)){


					if(map_get_cell_type(map,bomb_get_x(bomb),bomb_get_y(bomb)+range_inc) == CELL_CASE){
						bomb_explode_down(bomb,range_inc);
						map_set_cell_type(map,bomb_get_x(bomb),bomb_get_y(bomb)+range_inc,map_get_bonus_type(map,bomb_get_x(bomb),bomb_get_y(bomb)+range_inc)+1);
					}
					else if(map_get_cell_type(map,bomb_get_x(bomb),bomb_get_y(bomb)+range_inc) == CELL_SCENERY){
						break;
					}
					else if(map_get_cell_type(map,bomb_get_x(bomb),bomb_get_y(bomb)+range_inc) != CELL_CASE && map_get_cell_type(map,bomb_get_x(bomb),bomb_get_y(bomb)+range_inc) != CELL_BONUS && map_get_cell_type(map,bomb_get_x(bomb),bomb_get_y(bomb)+range_inc) != CELL_CLOSED_DOOR && map_get_cell_type(map,bomb_get_x(bomb),bomb_get_y(bomb)+range_inc) != CELL_GOAL){
						bomb_explode_down(bomb,range_inc);
						map_set_cell_type(map,bomb_get_x(bomb),bomb_get_y(bomb)+range_inc,CELL_BOMB);
					}
					else if(map_get_cell_type(map,bomb_get_x(bomb),bomb_get_y(bomb)+range_inc) == CELL_PLAYER){
                        player_dec_nb_life(game->player);
					}
				}

			}

			for(range_inc=1 ; range_inc<=player_get_bomb_range(game_get_player(game)) ; range_inc++){


			 if(map_is_inside(map,bomb_get_x(bomb),bomb_get_y(bomb)-range_inc)){


				if(map_get_cell_type(map,bomb_get_x(bomb),bomb_get_y(bomb)-range_inc) == CELL_CASE){
					bomb_explode_up(bomb,range_inc);
					map_set_cell_type(map,bomb_get_x(bomb),bomb_get_y(bomb)-range_inc,map_get_bonus_type(map,bomb_get_x(bomb),bomb_get_y(bomb)-range_inc)+1);
				}


				else if(map_get_cell_type(map,bomb_get_x(bomb),bomb_get_y(bomb)-range_inc) == CELL_SCENERY){
					break;
				}


				else if(map_get_cell_type(map,bomb_get_x(bomb),bomb_get_y(bomb)-range_inc) != CELL_CASE && map_get_cell_type(map,bomb_get_x(bomb),bomb_get_y(bomb)-range_inc) != CELL_BONUS && map_get_cell_type(map,bomb_get_x(bomb),bomb_get_y(bomb)-range_inc) != CELL_CLOSED_DOOR && map_get_cell_type(map,bomb_get_x(bomb),bomb_get_y(bomb)-range_inc) != CELL_GOAL){
					bomb_explode_up(bomb,range_inc);
					map_set_cell_type(map,bomb_get_x(bomb),bomb_get_y(bomb)-range_inc,CELL_BOMB);
				}
				else if(map_get_cell_type(map,bomb_get_x(bomb),bomb_get_y(bomb)-range_inc) == CELL_PLAYER){
				                        player_dec_nb_life(game->player);
									}
			 }

			}

			for(range_inc=1 ; range_inc<=player_get_bomb_range(game_get_player(game)) ; range_inc++){


				if(map_is_inside(map,bomb_get_x(bomb)+range_inc,bomb_get_y(bomb))){


					if(map_get_cell_type(map,bomb_get_x(bomb)+range_inc,bomb_get_y(bomb)) == CELL_CASE){
						bomb_explode_right(bomb,range_inc);
						map_set_cell_type(map,bomb_get_x(bomb)+range_inc,bomb_get_y(bomb),map_get_bonus_type(map,bomb_get_x(bomb)+range_inc,bomb_get_y(bomb))+1);
					}


					else if(map_get_cell_type(map,bomb_get_x(bomb)+range_inc,bomb_get_y(bomb)) == CELL_SCENERY){
						break;
					}


					else if(map_get_cell_type(map,bomb_get_x(bomb)+range_inc,bomb_get_y(bomb)) != CELL_CASE && map_get_cell_type(map,bomb_get_x(bomb)+range_inc,bomb_get_y(bomb)) != CELL_BONUS && map_get_cell_type(map,bomb_get_x(bomb)+range_inc,bomb_get_y(bomb)) != CELL_CLOSED_DOOR && map_get_cell_type(map,bomb_get_x(bomb)+range_inc,bomb_get_y(bomb)) != CELL_GOAL){
						bomb_explode_right(bomb,range_inc);
						map_set_cell_type(map,bomb_get_x(bomb)+range_inc,bomb_get_y(bomb),CELL_BOMB);
					}
					else if(map_get_cell_type(map,bomb_get_x(bomb)+range_inc,bomb_get_y(bomb)) == CELL_PLAYER){
					                        player_dec_nb_life(game->player);
										}

				}

			}

			for(range_inc=1 ; range_inc<=player_get_bomb_range(game_get_player(game)) ; range_inc++){


				if(map_is_inside(map,bomb_get_x(bomb)-range_inc,bomb_get_y(bomb))){


					if(map_get_cell_type(map,bomb_get_x(bomb)-range_inc,bomb_get_y(bomb)) == CELL_CASE){
						bomb_explode_left(bomb,range_inc);
						map_set_cell_type(map,bomb_get_x(bomb)-range_inc,bomb_get_y(bomb),map_get_bonus_type(map,bomb_get_x(bomb)-range_inc,bomb_get_y(bomb))+1);
					}


					else if(map_get_cell_type(map,bomb_get_x(bomb)-range_inc,bomb_get_y(bomb)) == CELL_SCENERY){
						break;
					}


					else if(map_get_cell_type(map,bomb_get_x(bomb)-range_inc,bomb_get_y(bomb)) != CELL_CASE && map_get_cell_type(map,bomb_get_x(bomb)-range_inc,bomb_get_y(bomb)) != CELL_BONUS && map_get_cell_type(map,bomb_get_x(bomb)-range_inc,bomb_get_y(bomb)) != CELL_CLOSED_DOOR && map_get_cell_type(map,bomb_get_x(bomb)-range_inc,bomb_get_y(bomb)) != CELL_GOAL){
						bomb_explode_left(bomb,range_inc);
						map_set_cell_type(map,bomb_get_x(bomb)-range_inc,bomb_get_y(bomb),CELL_BOMB);
					}
					else if(map_get_cell_type(map,bomb_get_x(bomb)-range_inc,bomb_get_y(bomb)) == CELL_PLAYER){
					                        player_dec_nb_life(game->player);
										}

				}

			}
		}
	}
	if(bomb_get_fuse(bomb)==5 && map_get_cell_type(map,bomb_get_x(bomb),bomb_get_y(bomb))!=CELL_EMPTY){

		int range_inc=1;
		map_set_cell_type(map,bomb_get_x(bomb),bomb_get_y(bomb),CELL_EMPTY);


		for(range_inc=1 ; range_inc<=player_get_bomb_range(game_get_player(game)) ; range_inc++){


			if(map_get_cell_type(map,bomb_get_x(bomb),bomb_get_y(bomb)+range_inc) == CELL_SCENERY){
				break;
			}


			if(map_get_cell_type(map,bomb_get_x(bomb),bomb_get_y(bomb)+range_inc)!=CELL_BONUS) {
				if(map_get_cell_type(map,bomb_get_x(bomb),bomb_get_y(bomb)+range_inc)!=CELL_KEY && map_get_cell_type(map,bomb_get_x(bomb),bomb_get_y(bomb)+range_inc)!=CELL_CLOSED_DOOR && map_get_cell_type(map,bomb_get_x(bomb),bomb_get_y(bomb)+range_inc)!=CELL_GOAL){
					if(map_is_inside(map,bomb_get_x(bomb),bomb_get_y(bomb)+range_inc)){
						map_set_cell_type(map,bomb_get_x(bomb),bomb_get_y(bomb)+range_inc,CELL_EMPTY);
						bomb_delete(bomb_list,bomb_get_x(bomb),bomb_get_y(bomb)+range_inc);
					}
				}
			}

		}

		for(range_inc=1 ; range_inc<=player_get_bomb_range(game_get_player(game)) ; range_inc++){


			if(map_get_cell_type(map,bomb_get_x(bomb),bomb_get_y(bomb)-range_inc) == CELL_SCENERY){
				break;
			}


			if(map_get_cell_type(map,bomb_get_x(bomb),bomb_get_y(bomb)-range_inc)!=CELL_BONUS) {
				if(map_get_cell_type(map,bomb_get_x(bomb),bomb_get_y(bomb)-range_inc)!=CELL_KEY && map_get_cell_type(map,bomb_get_x(bomb),bomb_get_y(bomb)-range_inc)!=CELL_CLOSED_DOOR && map_get_cell_type(map,bomb_get_x(bomb),bomb_get_y(bomb)-range_inc)!=CELL_GOAL) {
					if(map_is_inside(map,bomb_get_x(bomb),bomb_get_y(bomb)-range_inc)){
						map_set_cell_type(map,bomb_get_x(bomb),bomb_get_y(bomb)-range_inc,CELL_EMPTY);
						bomb_delete(bomb_list,bomb_get_x(bomb),bomb_get_y(bomb)-range_inc);
					}
				}
			}

		}

		for(range_inc=1 ; range_inc<=player_get_bomb_range(game_get_player(game)) ; range_inc++){


			if(map_get_cell_type(map,bomb_get_x(bomb)+range_inc,bomb_get_y(bomb)) == CELL_SCENERY){
				break;
			}


			if(map_get_cell_type(map,bomb_get_x(bomb)+range_inc,bomb_get_y(bomb))!=CELL_KEY && map_get_cell_type(map,bomb_get_x(bomb)+range_inc,bomb_get_y(bomb))!=CELL_CLOSED_DOOR && map_get_cell_type(map,bomb_get_x(bomb)+range_inc,bomb_get_y(bomb))!=CELL_GOAL) {
				if(map_get_cell_type(map,bomb_get_x(bomb)+range_inc,bomb_get_y(bomb))!=CELL_BONUS) {
					if(map_is_inside(map,bomb_get_x(bomb)+range_inc,bomb_get_y(bomb))){
						map_set_cell_type(map,bomb_get_x(bomb)+range_inc,bomb_get_y(bomb),CELL_EMPTY);
						bomb_delete(bomb_list,bomb_get_x(bomb)+range_inc,bomb_get_y(bomb));
					}
				}
			}

		}

		for(range_inc=1 ; range_inc<=player_get_bomb_range(game_get_player(game)) ; range_inc++){


			if(map_get_cell_type(map,bomb_get_x(bomb)-range_inc,bomb_get_y(bomb)) == CELL_SCENERY){
				break;
			}


			if(map_get_cell_type(map,bomb_get_x(bomb)-range_inc,bomb_get_y(bomb))!=CELL_KEY && map_get_cell_type(map,bomb_get_x(bomb)-range_inc,bomb_get_y(bomb))!=CELL_CLOSED_DOOR && map_get_cell_type(map,bomb_get_x(bomb)-range_inc,bomb_get_y(bomb))!=CELL_GOAL) {
				if(map_get_cell_type(map,bomb_get_x(bomb)-range_inc,bomb_get_y(bomb))!=CELL_BONUS) {
					if(map_is_inside(map,bomb_get_x(bomb)-range_inc,bomb_get_y(bomb))){
						map_set_cell_type(map,bomb_get_x(bomb)-range_inc,bomb_get_y(bomb),CELL_EMPTY);
						bomb_delete(bomb_list,bomb_get_x(bomb)-range_inc,bomb_get_y(bomb));
					}
				}
			}

		}
	}


}

void game_display(struct game* game) {


	assert(game);


	struct list_monster *monster_list = game->monster;
	struct list_bomb *bomb_list = game->bomb;
	struct map* map = level_get_curr_map(game_get_curr_level(game));

	window_clear();

	game_banner_display(game);
	level_display(game_get_curr_level(game));
	player_display(game->player);


	// As long as the monsters's list isn't empty, display a monster and change to the next position in the list.
		while (monster_list!= NULL){
			struct monster* monster_object =(struct monster*) list_monster_current(monster_list);
			monster_display(monster_object);
			monster_list = list_monster_next(monster_list);

		}


// As long as the bombs's list isn't empty, display a bomb and the explosion according to the bomb's range and change to the next position in the list.


    while(bomb_list != NULL && game->PAUSE==0){
    	struct bomb* bomb_object = (struct bomb*) list_bomb_current(bomb_list);
    	bomb_display(bomb_object);
    	bomb_explode_and_bomb_range(bomb_list,map,game,bomb_object);
    	bomb_list = list_bomb_next(bomb_list);
    }

    // If the number of lives of the player reaches 0, display a game over screen.

    if(player_get_nb_life(game_get_player(game))==0) {
    		window_display_image(sprite_get_game_over(),0,0);
    		game->PAUSE=2;

    }

    // If the player hit the princess bomberwoman, he win
    if(player_get_victory(game_get_player(game))==1){
    	window_display_image(sprite_get_game_win(),0,0);
    	game->PAUSE=2;


    }
    // If the PAUSE are on, display a game pause screen
    if(game->PAUSE==1){
window_display_image(sprite_get_pause(),50,90);

    }

	window_refresh();
}




short input_keyboard(struct game* game) {
	SDL_Event event;
	struct player* player = game_get_player(game);

	struct map* map = level_get_curr_map(game_get_curr_level(game));

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			return 1;
		case SDL_KEYDOWN:

			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				return 1;
			case SDLK_UP:
				if(game->PAUSE==0){
				player_set_current_way(player, NORTH);
				player_move(player, map);
				}
				break;
			case SDLK_DOWN:
				if(game->PAUSE==0){
				player_set_current_way(player, SOUTH);
				player_move(player, map);
				}
				break;
			case SDLK_RIGHT:
				if(game->PAUSE==0){
				player_set_current_way(player, EAST);
				player_move(player, map);
				}
				break;
			case SDLK_LEFT:
				if(game->PAUSE==0){
				player_set_current_way(player, WEST);
				player_move(player, map);
				}
				break;
			case SDLK_SPACE:
				if(game->PAUSE==0){
				if(player_get_nb_bomb(player) == 0)
					break;
				else
					player_dec_nb_bomb(player);
				game->bomb = bomb_create(game_get_bomb_list(game),player_get_x(player),player_get_y(player));
				}
				break;
			case SDLK_p:
				if(game->PAUSE==0){
					window_display_image(sprite_get_pause(),0,0);
					game->PAUSE=1;
				}
				else {
					game->PAUSE=0;
				}
				break;

			default:
				break;
			}

			break;
		}
	}
	return 0;

}

int game_update(struct game* game) {


	struct map *map = level_get_curr_map(game_get_curr_level(game));
	struct list_bomb *bomb_list = game->bomb;

	// As long as the bombs's list isn't empty, refresh the bomb's state and change to the next position in the list
	while(bomb_list != NULL && game->PAUSE==0){
		struct bomb* bomb=(struct bomb*) list_bomb_current(bomb_list);
		bomb_decrease_fuse(bomb);
		bomb_list=list_bomb_next(bomb_list);

	}
    /* As long as the monsters's list isn't empty, refresh the monsters's timer in order to make them move randomly
	and change to the next postion in the list. The monsters doesn't move during the pause. */

	struct list_monster* monster_list = game->monster;
		while (monster_list !=NULL && game->PAUSE==0){
			struct monster* monster =(struct monster*) list_monster_current(monster_list);
			monster_update(monster,map);
			monster_list = list_monster_next(monster_list);
		}


	if (input_keyboard(game))
		return 1;// exit game

	    window_refresh();


	return 0;


}

