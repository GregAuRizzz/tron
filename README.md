# Tron 

Jeu de Tron réalisé par **Grégory DUPORGE** et **Julien Biout** dans le cadre d'une SAé en C.

Ce projet est basé sur l'architecture MVC et propose deux interfaces : une interface graphique avec **SDL2** et une interface en mode texte avec **ncurses**.

---

## Compilation

Pour compiler le projet, exécutez simplement :

```bash
make
```
Nettoyage : 
```bash
make clean
``` 

Pour executer sdl (argument -sdl) :
```bash
 ./main -sdl
``` 

Vous pouvez y ajuster la taille (argument -taille <hauteur> <largeur>) : 
```bash
./main -sdl -taille 700 700
```

Pour executer ncurse (argument -ncurse) : 
```bash
./main -ncurse
``` 


Assurez vous d'avoir bien installé SDL2, SDL2_image, ncurse
Ubuntu & debian :
```bash
sudo apt update
sudo apt install build-essential libsdl2-dev libsdl2-image-dev libncurses5-dev
```