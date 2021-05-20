/***************************************************
****************************************************
**                                                **
**                                                **
**         ent�te classe "effet_particule"        **
**                                                **
**                  Thomas John                   **
**           thomas.john@open-design.be           **
**                                                **
**                                                **
****************************************************
***************************************************/

// ceci sert � ce qu'on ne charge pas deux fois le m�me header
#ifndef C_EFFET_PARTICULE_H

#define C_EFFET_PARTICULE_H

#include "structures.h"

class effet_particule

{
	// les donn�es "priv�es" (variables, fonctions...)
private:

	// structure qui va contenir les informations sur chaque particules
	struct particules {
		// coordonn�es
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

	// on d�clare la variable qui va contenir notre tableau de particules
	particules* t_particules;

	// fonction d'initialisation d'une particule
	void init_particule(int particulesz);

	// structure qui contient toutes les infos g�n�rales
	infos_gen* infos_tex_tmp;

	// les donn�es publiques
public:

	// �tat de la classe
	int etat;

	// les coordonn�es (x, y, z)
	double m_x;
	double m_y;
	double m_z;

	// la vitesse des particules
	double m_vitesse;

	// le nombre max de particules � afficher en m�me temps
	int m_nombre_tot;

	// le nombre de particules couramment affich�es
	int m_nombre_actifs;

	// le temps qu'il faut (en unit�) pour cr�er une(de) nouvelle(s) particule(s)
	int	m_temps_tot;
	int	m_temps;

	// nombre de particules �mises en m�me temps
	int m_nbr_emission;

	// le constructeur par d�faut
	effet_particule(double x, double y, double z, double vitesse, int nombre_tot, struct infos_gen*, int vitesse_emission, int nbr_emission);

	// le destructeur
	~effet_particule();

	// calcul de la position des particules
	void calculer();

	// affichage des particules
	void afficher();
};

#endif