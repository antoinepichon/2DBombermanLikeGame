#include <SDL/SDL_image.h>
#include <assert.h>

#include <map.h>
#include <player.h>
#include <sprite.h>
#include <window.h>
#include <misc.h>
#include <constant.h>
#include <game.h>


struct list_bomb{
	void * bombe;
	struct list_bomb *bombe_suivante;
};


struct list_bomb* add_bomb_to_the_list_bomb(struct list_bomb * list_bomb, void * new_bomb){

	/* Create a new element : new */
	struct list_bomb* new = malloc(sizeof(*new));

    /* Assign the value new_bomb to the new element new */
	new->bombe=new_bomb;
	/* Assign address of the next element to the new element new */
	new -> bombe_suivante=list_bomb;
	list_bomb=new;

	/* Return the new list_bomb, the pointer on the first element */

	return list_bomb;

}

struct list_bomb* list_bomb_current(struct list_bomb * item ){
	return item->bombe;

}

struct list_bomb* list_bomb_delete(struct list_bomb * list_bomb){

	/* If the list is empty, return NULL */
	if(list_bomb == NULL){
		return NULL;
	}

	/* If the list include an only element */

	if(list_bomb->bombe_suivante == NULL){
			return NULL;
		}

    /* If the list include at least two elements */

	struct list_bomb* tmp =list_bomb;
	struct list_bomb* ptmp = list_bomb;
   /* As long as this is not the last element */
	while(tmp->bombe_suivante != NULL){
		/* ptmp store the tmp's address */
		ptmp = tmp;
		/* Move tmp (ptmp keep the former value of tmp) */
		tmp = tmp->bombe_suivante;
	}


/* So, tmp point to the last element, ptmp point to the second to last element
 * The last element are erased and the second to last element become the last element.
 */

	ptmp->bombe_suivante = NULL;
	free(tmp);
	return list_bomb;



}

struct list_bomb * list_bomb_next(struct list_bomb * item){
	return item->bombe_suivante;
}


