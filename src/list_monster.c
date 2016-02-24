#include <SDL/SDL_image.h>
#include <assert.h>

#include <map.h>
#include <player.h>
#include <sprite.h>
#include <window.h>
#include <misc.h>
#include <constant.h>
#include <game.h>


struct list_monster{
	void * monstre;
	struct list_monster *monstre_suivant;
};


struct list_monster* add_monster_to_the_list_monster(struct list_monster * list_monster, void * new_monster){

	/* On crée un nouvel élément new */
	struct list_monster* new = malloc(sizeof(*new));

    /* On assigne la valeur new_monster au nouvel élément new */
	new->monstre=new_monster;
	/* On assigne l'adresse de l'élement suivant au nouvel élément new */
	new -> monstre_suivant=list_monster;
	list_monster=new;

	/* On retourne la nouvelle liste, i.e le pointeur sur le premier élément */

	return list_monster;

}

struct list_monster* list_monster_current(struct list_monster * item ){
	return item->monstre;

}


struct list_monster * list_monster_next(struct list_monster * item){
	return item->monstre_suivant;
}

