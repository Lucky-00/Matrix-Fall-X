/***************************************************
****************************************************
**                                                **
**                                                **
**            entête classe "structures"          **
**                                                **
**                  Thomas John                   **
**           thomas.john@open-design.be           **
**                                                **
**                                                **
****************************************************
***************************************************/

#ifndef C_STRUCTURES_H

#define C_STRUCTURES_H

#include	<gl\gl.h>

// structure contenant les infos sur la caméra
struct infos_cam
{
	// état de la classe
	int etat;

	// les coordonnées du point vers lequel la caméra "regarde"
	double m_x_t;
	double m_y_t;
	double m_z_t;

	// les coordonnées de la caméra (l'oeuil)
	double m_x_v;
	double m_y_v;
	double m_z_v;

	// la distance qui sépare la cible de la caméra
	double m_distance;

	// la rotation en °
	double rot;
};

// structure contenant l'index et la coordonnée z d'un ligne 3D
// en créant un tableau de cette structure, il va être possible de classer chaque ligne selon leur ordre
// dans ce cas, l'ordre équivaut à la coordonnée "z" de chaque ligne afin d'afficher chaque ligne depuis
// la plus éloignée jusqu'à la plus proche de la caméra
struct ordre_z
{
	// index de l'instance de la classe "ligne3d1"
	int index;

	// sa coordonnée "z"
	double ordre;
};

// infos sur les coordonnées des différentes lettre de la texture comportant les caractères "bizares"
// ces coordonnées pré-enregistrées vont nous permettre de gagner du temps lors du rendu de la scène
// les listes d'affichage auraient pu être utilisées, mais elles nous obligent à utiliser la fonction
// de translation "glTranslate" qui, lorsque utilisée trop souvent, réduit la vitesse d'exécution du
// programme (ici une dizaine de fps)
struct infos_tex_vertes {
	float x1;
	float y1;

	float x2;
	float y2;

	float x3;
	float y3;

	float x4;
	float y4;
};

// la structure qui va contenir toutes les informations générales que les classes ont besoin de se partager entre elles
struct infos_gen {
	//######	LISTES D'AFFICHAGE
	// on n'utilise plus les listes d'affichage -> perte de vitesse d'exécution
	// lettres vertes
	//GLuint lst_lettres_vertes[56];

	//######	TEXTURES
	// lettres blanches
	GLuint tex_lettres_blanches;

	// lettres vertes
	GLuint tex_lettres_vertes;

	// particule 1
	GLuint tex_part_1;

	//######	COORDONNEES DE TEXTURES
	// coordonnées pour les textures aux caractères bizares (d'autres viendront)
	infos_tex_vertes info_tex_vertes_sz[56];

	//######	AUTRES DONNEES
	// temps écoulé entre l'affichage de deux images (scènes)
	int msec;

	// sert pour le debuggage
	double dist_ttmp;

	// permet de jongler entre différentes fonctions de blending
	GLenum prem;
	GLenum deux;

	//######	LISTE CONTENANT L'INDEX DE CHAQUE LIGNE ET LEUR COORDONNEE Z
	ordre_z* ordre_sz;

	//######	INFOS SUR LA CAMERA
	infos_cam infos_cam_sz;
};

#endif