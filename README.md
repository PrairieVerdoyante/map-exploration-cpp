# CPP_FilRouge_ISCJ_Aubry_Sarah


## Description
### Objectifs
Mettre en pratique plusieurs concepts vus dans le cours en créant un projet unificateur, cohérent et concret.

### Buts à atteindre
* Créer un projet fonctionnel, codé selon les meilleures pratiques et les conventions générales.
* Pousser la solution sur le gitlab régulièrement chaque semaine
* Le fichier main.cpp doit fournir un aperçu global des fonctionnalités implémentées dans le projet.

### Livrables du projet
* Code du projet
* Diagramme de classes réalisé suivant les spécifications UML vues en cours (.jpeg, .png, .md ou .pdf)
* Un document test (.md, .docx ou pdf) décrivant le code réalisé (1-2 pages)

Le rendu final se fera sur CyberLearn.

### Scénario choisi
J'ai choisi le scénario "Exploration de carte".

Buts à atteindre: 
* Ajouter la classe World (ou Map)
* Ajouter un système de coordonnées et la possibilité de se déplacer dans le monde.
* Ajouter la possibilité pour les héros d'interagir avec des 3 types entités (ex. villages, trésors, PNJ, etc.)
* Ajouter des contraintes pour le déplacement (vitesse maximale ou notion du temps ou…)
* Utiliser des Exceptions pour gérer les erreurs
* Ajouter un fichier de log pour garder trace de tous les déplacements
* Utiliser le polymorphisme, la redéfinition et la surcharge des méthodes (y.c. des opérateurs)
* Utiliser du code C++ modern (C++11 ou suivants

## Démarrage du projet
* Il est important de cloner le projet dans un dossier qui se trouve dans le chemin <b>C:\dev\1242_2_cpp\projet_fil_rouge</b> ! Sinon les bibliothèques ne se chargeront pas correctement.
* Vérifier que dans les dossiers SDL2 , SDL2 TFF et SDL2_image, il y ait bien les dossiers <b>"lib"</b>; si ils n'apparaissent pas, télécharger et extraire le contenu du dossier compressé ´SDL_libraries.zip´, et remplacer les deux dossiers par le contenu du dossier compressé.

## Le jeu
Jeu d'aventure qui comprend de l'exploration, des interactions avec des personnages et des quêtes à accomplir.
Le joueur incarne un personnage qui se promène dans un monde. Le but est de parler avec le personnage présent sur la carte, de trouver un diamant et de lui rapporter.

### Classe Game
C'est la classe principale, qui s'occupe de la gestion du jeu.
Elle permet d'instancier des personnages, de créer la carte, de créer la fenêtre de jeu et de gérer les collisions.

#### Collisions
Les collisions qui sont opérationnelles dans le jeu sont celles entre le personnage et le joueur et entre le diamant et le joueur.
Une fois qu'on entre en contact avec le personnage, il demande d'aller chercher un diamant.
Le diamant peut être récupéré et déposé devant le personnage.

Je n'ai pas réussi à implémenter correctement la collision avec les arbres, par manque de temps : le joueur peut les traverser.

#### Fonctions principales
* La fonction init() crée la fenêtre, les personnages, la carte, les éléments de décor, etc.
* La fonction HandleCollisions() gère toutes les collisions du jeu. Les collisions avec les sapins ne sont pas gérées correctement.
* La fonction handleEvents() attend un signal d'arrêt, qui ferme le jeu. Elle appelle aussi la fonction handleEvents() du joueur, qui écoute les touches pressées et fait bouger le joueur en fonction de celles-ci.
* La fonction update() gère tout ce qui se fait en boucle, elle appelle la même fonction de Player qui met à jour le numéro de sprite à utiliser pour l'animation. Elle limite la caméra aux limites définies, et vérifie aussi que le joueur ne puisse pas dépasser l'écran à droite et en bas de l'écran.
* La fonction render() affiche la carte, les décorations et les personnages à l'écran.
* La fonction renderForest() permet de placer les arbres et les décorations à des coordonnées précises sur la carte. 

### Classe GameObject
les GameObject sont des personnages, qui ont une texture et des positions X et Y.
Dans cette classe, les actions effectuées principalement sont la définition des tailles de sprite, le chargement de la texture et le "setup" de la position donnée à leur création.
Ils possèdent également une possibilité d'animation.
### Classe Player
La classe Player hérite de GameObject. Elle implémente une fonction d'animation plus complexe (pour marcher de tous les côtés alors que le GameObject est immobile). Elle a également la possibilité de se déplacer et de vérifier si des collisions ont lieu, à l'aide d'une fonction qui teste si la position X et Y du joueur correspond à celle du GameObject passé en paramètre.
### Classe Tree
La classe Tree contient tous les éléments nécessaires pour créer une forêt. Elle hérite aussi de GameObject.
On peut placer un élément de décor au choix (entre des groupes de trois arbres, des fleurs ou des arbres seuls) à l'endroit souhaité sur la carte. La variable m_type permet de choisir quelle décoration on souhaite ajouter au jeu.
### Classe Diamond
La classe Diamond hérite de GameObject : elle permet d'ajouter un diamant selon le type de diamant choisi, à l'endroit souhaité sur la carte. (pour l'instant il y en a un seul implémenté).
### Classe Map
La classe Map permet de créer une carte pour la partie. 
### Classe GrassMap
La classe GrassMap hérite de la classe Map. Elle permet d'afficher une carte de type Herbe, ce qui veut dire qu'elle affichera uniquement des éléments de ce thème.
Un tableau à deux dimensions est utilisé pour choisir les coordonnées de chaque carré affiché. Ces carrés sont ensuite utilisés selon un std::unordered_map qui transforme les valeurs en coordonnées (par exemple, 50 correspond à 5;0).
Ce std::unordered_map est utilisé lors du parcours du tableau à deux dimensions : chaque case est traduite par les coordonnées correspondantes, puis ces coordonnées X et Y sont utilisées pour choisir les coordonnées dans le Tileset de la carte.

<img src="../game_project/game_project/Resources/CPP_coordonnees_carte.png" width="500" />


### Classe Backpack
La classe backpack implémente une pile avec des shared_pointer, qui permettent de stocker ou de retirer des éléments du sac à dos.
### Classe TextureManager
La classe TextureManager sert à centraliser les utilisations de la bibliothèque SDL pour afficher des éléments à l'écran ou pour les supprimer. Cela permet de centraliser les utilisations de SDL pour pouvoir les modifier plus facilement si on veut changer de bibliothèque.

## Fichier de logs
La console affiche si le diamant est déposé, et montre que le jeu a bien été initialisé et fermé.
