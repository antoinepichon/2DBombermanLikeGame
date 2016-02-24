# PG110-2D-Bomberman-like-video-game-C-SDL-Eclipse-
Realisation of a 2D bomberman-like video game using SDL library

Gestion des collisions : 


La limitation des mouvements du joueur par le cadre de la carte, les éléments de décors, les caisses et les montres fonctionne.
Le déplacement d'une caisse par le joueur si rien ne gêne dans le sens de la poussée et la limitation de déplacement d'une seule caisse à la fois fonctionne.
La perte d'une vie lors d'une collision avec un monstre fonctionne.
L'invulnérabilité temporaire après la collision avec un monstre ne fonctionne pas.



Bonus, Malus : 


L’apparition des bonus fonctionne lors de l’explosion d’une caisse.
Lorsque le joueur marche sur un bonus, son effet fonctionne et les nombres dans la bannière du bas sont modifiés pour les 5 bonus de base.

Il y’a les 5 bonus inclus de base dans le jeu : portée+/portée-, bomb-/bomb+, vie+.

Un sixième bonus a été rajouté : teleport : téléporte le joueur à un endroit donné sur la carte.



Bombes : 


La pose d’une bombe par le joueur sur la case sur laquelle il se trouve lorsque le joueur presse la touche [ESPACE] fonctionne.
La diminution de la mèche de la bombe à chaque seconde et son explosion au bout de 4 secondes fonctionne.
La portée de la bombe fonctionne et l’interruption de la propagation de l’explosion par les éléments de décor fonctionne.
L’explosion d’une caisse et l’affichage de son contenu  fonctionne mais si une caisse se trouve derrière, elle explose et affiche son contenu également et ne reste pas intacte.
La disparition d’un monstre, bonus ou malus sur le chemin de l’explosion fonctionne.
La perte d’une vie au cas où le joueur se trouve sur une cellule touchée par une explosion fonctionne.
Les explosions n’ont aucun effet sur les portes, les clefs ou la princesse.
Lorsqu’une bombe explose, il n’y a pas de nouvelle bombe ajoutée à l’inventaire du joueur, le jeu n’en devient que plus amusant car le joueur doit gérer son nombre de bombes et il peut s’aider de bonus pour augmenter ce nombre.



Gestion des vies : 


L’initialisation du joueur avec 2 vies au démarrage du jeu fonctionne.
La perte d’une vie en cas de collision avec un monstre ou s’il se trouve sur une cellule touchée par l’explosion d’une bombe fonctionne.
La fin de la partie au cas où le nombre de vie du joueur atteint 0 fonctionne. (Stoppe le jeu et affiche un écran de game over).



Panneau d’informations :
 

Le panneau d’information affiche le nombre de vies, le nombre de bombes et leur portée, et la présence d’une clef dans l’inventaire.
Mais il n’affiche pas  le numéro de niveau. (Pas de nouvelle carte, donc pas de numéro de niveau).



Monstres : 


Les monstres sont présents dès le chargement de la carte mais ne peuvent pas apparaitre à l’explosion d’une caisse.
(Pas de bonus monstre).

Les déplacements aléatoires des monstres sont fonctionnels



Fichiers carte et chargement : 

Partie non traitée.



Pause : 


La touche  [P] mettant le jeu en pause et permettant de reprendre la partie fonctionne.(Affiche une image de pause et stoppe le jeu).
Cette pause stoppe les déplacements et actions du joueur, les déplacements des monstres et la fonction permettant la diminution de la mèche de la bombe mais ne stoppe pas le timer se mettant à jour dans la fonction game_update servant de référence pour la diminution de la mèche de la bombe.



Sauvegarde / Chargement Partie : 


Partie non traitée.
