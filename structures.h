/***************************************************
****************************************************
**                                                **
**                                                **
**            ent�te classe "structures"          **
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

// structure contenant les infos sur la cam�ra
struct infos_cam
{
	// �tat de la classe
	int etat;

	// les coordonn�es du point vers lequel la cam�ra "regarde"
	double m_x_t;
	double m_y_t;
	double m_z_t;

	// les coordonn�es de la cam�ra (l'oeuil)
	double m_x_v;
	double m_y_v;
	double m_z_v;

	// la distance qui s�pare la cible de la cam�ra
	double m_distance;

	// la rotation en �
	double rot;
};

// structure contenant l'index et la coordonn�e z d'un ligne 3D
// en cr�ant un tableau de cette structure, il va �tre possible de classer chaque ligne selon leur ordre
// dans ce cas, l'ordre �quivaut � la coordonn�e "z" de chaque ligne afin d'afficher chaque ligne depuis
// la plus �loign�e jusqu'� la plus proche de la cam�ra
struct ordre_z
{
	// index de l'instance de la classe "ligne3d1"
	int index;

	// sa coordonn�e "z"
	double ordre;
};

// infos sur les coordonn�es des diff�rentes lettre de la texture comportant les caract�res "bizares"
// ces coordonn�es pr�-enregistr�es vont nous permettre de gagner du temps lors du rendu de la sc�ne
// les listes d'affichage auraient pu �tre utilis�es, mais elles nous obligent � utiliser la fonction
// de translation "glTranslate" qui, lorsque utilis�e trop souvent, r�duit la vitesse d'ex�cution du
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

// la structure qui va contenir toutes les informations g�n�rales que les classes ont besoin de se partager entre elles
struct infos_gen {
	//######	LISTES D'AFFICHAGE
	// on n'utilise plus les listes d'affichage -> perte de vitesse d'ex�cution
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
	// coordonn�es pour les textures aux caract�res bizares (d'autres viendront)
	infos_tex_vertes info_tex_vertes_sz[56];

	//######	AUTRES DONNEES
	// temps �coul� entre l'affichage de deux images (sc�nes)
	int msec;

	// sert pour le debuggage
	double dist_ttmp;

	// permet de jongler entre diff�rentes fonctions de blending
	GLenum prem;
	GLenum deux;

	//######	LISTE CONTENANT L'INDEX DE CHAQUE LIGNE ET LEUR COORDONNEE Z
	ordre_z* ordre_sz;

	//######	INFOS SUR LA CAMERA
	infos_cam infos_cam_sz;
};

#endif