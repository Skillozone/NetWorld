## Descriptif du Projet

Ce projet consiste en la recréation d'un jeu de type Risk en C, utilisant le moteur NetWorld fourni.

##### Règles du jeu : 

 - Chaque joueur se verra attribuer en début de partie un nombre équitable de territoires, chacun avec 1 soldat
 - Pendant leurs tours, les joueurs commencent par ajouter un certain nombre de soldats à leur territoires, et peuvent déplacer ceux qu'ils ont, en gardant 1 soldat sur chaque territoire à tout instant.
 - Ensuite, les joueurs peuvent déclarer des attaques sur des nodes ennemis adjacents aux leurs, qui se résolvent par comparaison de lancer de dés. Engager plus de soldats dans un combat signifie lancer plus de dés.
 - Si un combat se déroule entre X et Y soldats bleus et rouge, avec X > Y, alors le combat est départagé en comparant en ordre décroissant les dés des soldats rouge avec les Y meilleurs dés des soldats bleus en ordre décroissant.
 - Si une attaque réduit le nombre de soldats défendant à 0, l'attaquant gagne le node, et tous les soldats engagés au combat encore en vie se déplacent sur le nouveau node
 - Chaque joueur a une mission, lui indiquant comment gagner la partie. Si sa mission est accomplie à la fin de son tour de jeu, il gagne la partie.

## Installation


Projet conçu pour une compilation avec GCC et la librairie Raylib. De par la nature de la procédure d'installation et de linkage, Linux est le système d'exploitation à préférer.

### Installation sous Linux
---

1. **Installer gcc, CMake et git:**

Dans un terminal :


```bash
sudo apt update
sudo apt install build-essential git cmake
sudo apt install libasound2-dev mesa-common-dev libx11-dev libxrandr-dev libxi-dev xorg-dev libgl1-mesa-dev libglu1-mesa-dev
```


2. **Compiler et installer Raylib 3.0.0**

La procédure ci-dessous provient du tutoriel officiel pour linux de raylib ([cf. raylib-wiki](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux)), adapté pour les besoins du cours.

Tout d'abord, placez-vous dans le répertoire de votre choix. Une fois dans le répertoire de votre choix, il vous faut cloner la bibliothèque, et la compiler. Pour cela :

```bash
git clone https://github.com/raysan5/raylib.git raylib
cd raylib
git checkout '3.0.0'
mkdir build && cd build
cmake -DSHARED=ON -DSTATIC=ON ..
make
```
Ensuite, pour l'installer sur votre système :

```
sudo make install
cd ..
```

Une fois installé, vous pouvez, optionnellement, supprimer le dossier initial téléchargé depuis Github


```bash
rm -fr raylib
```

## Compiler Risk


Il n'y a plus qu'à cloner et compiler Risk :

```bash
git clone ssh://git@gvipers.imt-lille-douai.fr:2222/timothy.laird/networld.git Risk
cd Risk
./bin/build.sh
```

Un exécutable nommé risk sera généré et permettra d'exécuter le jeu en rentrant :

```bash
./risk
```

## Organisation du répertoire

Répertoire:


- *bin* : stocke de scripts pour automatiser des procédures utiles au projet.
- *.git* : répertoire de gestion de version propre à git.
- *src* : le code source du projet.
- *doc* : la documentation du projet.
- *resources* : ressources pour le projet.


Fichier à la racine:


- *.gitignore* : fichier de configuration git listant les ressources à ne pas versionner.
- *config* : Fichier de configuration pour le make (cf. *src/Makefile*).
- *config.default* : Fichier *config* utilisé à défaut (cf. *Makefile*).
- *Makefile* : Instruction de construction du projet pour *make*. Génère *config* et fait appel à *src/Makefile*.
- *projet-outline.md* : Un descriptif des composants logiciel réalisé et prévu.

## Documentation du Projet

La documentation du projet est générable avec Doxygen :

```bash
sudo apt install doxygen
doxygen
```

Un fichier *index.html* sera généré en *./doc/html* permettant de parcourir la documentation du projet dans un navigateur.

