/***************************************************
****************************************************
**                                                **
**                                                **
**              entête classe "main"              **
**                                                **
**                  Thomas John                   **
**           thomas.john@open-design.be           **
**                                                **
**                                                **
****************************************************
***************************************************/

#ifndef C_MAIN_H

#define C_MAIN_H

//##### LIBRAIRIES

	//on inclut les librairies
#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "glu32.lib" )

//##### ENTETES

	//la librairie windows est à inclure avant celle d'opengl
#include	<windows.h>

//permet de lire les fichiers .png
#include	"glpng.h"

//entêtes opengl
#include	<gl\gl.h>
#include	<gl\glu.h>

//entrée/sortie
//#include	<stdio.h>

//permet d'effectuer certaines opérations mathématiques
#include	<math.h>

//entête de la classe "camera"
#include	"camera.h"

//entête de la classe "Ligne3D1"
#include	"Ligne3D1.h"

//contient les structures regroupant toutes sortes d'informations (textures, temps, liste d'affichage...)
#include	"structures.h"
//on crée une structure qui va contenir les infos sur les textures et les liste d'affichage
infos_gen	s_infos_gen;

//##### DEFINITIONS

	//définit le nombre de lignes à afficher
#define		NBR_LIGNES_MAX_DEF 1000
int			NBR_LIGNES_MAX = NBR_LIGNES_MAX_DEF;

//nom de l'application
#define		NOM_APP "Matrix Fall X 0.1"
#define		NOM_APP_FENETRE "Matrix Fall X alpha 0.1"

//##### VARIABLES (de tout ici)

	//tableau représentant les différentes touches du clavier
bool		touche[256];

//contient l'hwnd de la fenêtre
HWND		hWnd;

//contient l'hdc
HDC			DC;
HGLRC		RC;

HINSTANCE	hInstance;

//spécifie si on est en mode Fullscreen ou en mode fenêtre (par défaut -> fenêtre)
bool		fullscreen = TRUE;

//spécifie si le programme est actif (la boucle d'affichage se termine quand b_actif est à false)
bool		b_actif = FALSE;

//permet de calculer le nombre de millisecondes écoulées entre chaque rendu de scène
char images_sec[256];
int temps_1;
int temps_2;
int temps_x;

//allows to calculate the number of images displayed per second
int fps_1;
int fps_2;
int fps_img_1;
int fps_img_2;

//##### INSTANCES DE CLASSES

	//classe ligne3d (on les initialisera plus tard)
Ligne3D1* ligne_1[NBR_LIGNES_MAX_DEF];

//classe "camera"
camera* camera_1 = new camera(0, 0, 0, 0, 0, 0, 175, &s_infos_gen);

//##### CHARGEMENT DES BMP
	//ce bout de code a été repris d'une source : http://www.cppfrance.com/code.aspx?ID=11002
struct PropPicture {
	unsigned char   Header[0x36];
	GLuint          DataPos, DataSize;
	GLint           Components;
	GLsizei         Width, Height;
	GLenum          Format, Type;
	GLuint          Name[1];
	unsigned char* Data;
};

#define EXIT {fclose(fichier);return -1;}
#define CTOI(C) (*(int*)&C)

#endif
