/***************************************************
****************************************************
**                                                **
**                                                **
**         entête classe "effet_particule"        **
**                                                **
**                  Thomas John                   **
**           thomas.john@open-design.be           **
**                                                **
**                                                **
****************************************************
***************************************************/

// ceci sert à ce qu'on ne charge pas deux fois le même header
#ifndef C_EFFET_PARTICULE_H

#define C_EFFET_PARTICULE_H

#include "structures.h"

class effet_particule

{
	// les données "privées" (variables, fonctions...)
private:

	// structure qui va contenir les informations sur chaque particules
	struct particules {
		// coordonnées
		double x;
		double y;
		double z;
		// vitesse
		double vitesse;
		// direction
		double d_x;
		double d_y;
		double d_z;
		// vie
		double vie;
		//taille
		double taille;
		// couleur
		double r;
		double g;
		double b;
	};

	// on déclare la variable qui va contenir notre tableau de particules
	particules* t_particules;

	// fonction d'initialisation d'une particule
	void init_particule(int particulesz);

	// structure qui contient toutes les infos générales
	infos_gen* infos_tex_tmp;

	// les données publiques
public:

	// état de la classe
	int etat;

	// les coordonnées (x, y, z)
	double m_x;
	double m_y;
	double m_z;

	// la vitesse des particules
	double m_vitesse;

	// le nombre max de particules à afficher en même temps
	int m_nombre_tot;

	// le nombre de particules couramment affichées
	int m_nombre_actifs;

	// le temps qu'il faut (en unité) pour créer une(de) nouvelle(s) particule(s)
	int	m_temps_tot;
	int	m_temps;

	// nombre de particules émises en même temps
	int m_nbr_emission;

	// le constructeur par défaut
	effet_particule(double x, double y, double z, double vitesse, int nombre_tot, struct infos_gen*, int vitesse_emission, int nbr_emission);

	// le destructeur
	~effet_particule();

	// calcul de la position des particules
	void calculer();

	// affichage des particules
	void afficher();
};

#endif