/***************************************************
****************************************************
**                                                **
**                                                **
**            entête classe "Ligne3D1"            **
**                                                **
**                  Thomas John                   **
**           thomas.john@open-design.be           **
**                                                **
**                                                **
****************************************************
***************************************************/

// ceci sert à ce qu'on ne charge pas deux fois le même header
#ifndef C_LIGNE3D1_H

#define C_LIGNE3D1_H

#include "structures.h"
//#include <math.h>
//#include <windows.h>

#include "effet_particule.h"

class Ligne3D1
{
	// les données "privées" (variables, fonctions...)
private:

	struct Lettre3D1 {
		// position de la lettre
		double pos_x;
		double pos_y;
		double pos_z;

		// état de la lettre
		int	etat;

		// timer 1
		int	temps;
		int	temps_tot;

		// timer 2 (temps_tot_2 = temps à attendre avant de changer de caractère, si la lettre peut changer dans le temps)
		int	temps_2;
		int	temps_tot_2;

		// caractère à afficher (56 caractères différents)
		// cet int représente une position dans le tableau regroupant toutes les coordonnées de texture
		int caractere;

		// opacité de la lettre
		double opacite;

		// distance de la lettre par rapport à l'oeuil de la caméra
		double dist_tmp;

		// spécifie si la lettre peut changer dans le temps
		int change_sz;
	};

	// la structure qui va contenir les infos sur chaque lettre de cette ligne
	Lettre3D1* lettre_1;

	// le nombre courant de lettres actives
	int	m_nbr_actif;

	// le temps qu'il faut attendre pour créer une nouvelle lettre
	int	m_temps_tot;
	int	m_temps;

	// pointeur vers la structure contenant les infos de toutes sortes
	infos_gen* infos_gen_tmp;

	// index de cette clase
	int index_tmp;

	// nombre max de lettres pour cette ligne
	int nbr_max_lettres;

	// nombre de lettres affichées (sert pour le décompte)
	int decpt_nbr_lettres;

	// durée du fondu entre la lettre blanche et la lettre verte (ceci pour garder un même durée pour toutes les lettres de la ligne)
	int m_temps_fondu;

	// spécifie si cette ligne utilise la classe "effet_particule"
	bool m_effet_particule;

	// l'effet de particule n'est activé que si la vitesse de cette ligne (m_temps_tot) est rapide (m_temps_tot<30)
	// lorsque toutes les lettres ont fini leur "vie", la ligne est réinitialisée
	// il est important de ne pas charger plusieurs fois une instance de la classe "effet_particule"

	// spécifie si une instance de la classe "effet_particule" a été chargée
	bool m_charge_part;

	// on déclare déjà un pointeur qui pointera vers une instance de la classe "effet_particule"
	effet_particule* particules_1;

	// la distance de la ligne par rapport à la caméra aurait pu être utilisée pour gagner en rapidité
	// à la place, cette distance est calculée pour chaque lettre de chaque ligne
	// cela augmente le temps de calcul, mais ce sera utile pour plus tard (certains effets)

	// distance de la ligne par rapport à la caméra (l'oeuil)
	double dist_tmp;

	// opacité de la ligne
	//double opacite_gen;

	// initialisation d'une lettre
	void init_lettre(int index_sz);

	//les données publiques
public:

	// état de la classe
	int m_etat;

	// les coordonnées de la ligne
	double m_x;
	double m_y;
	double m_z;

	// le constructeur par défaut
	Ligne3D1(double x, double y, double z, struct infos_gen*, int index);

	// le destructeur
	~Ligne3D1();

	// calcul de la position et de l'état des particules
	void calculer();

	// affichage des éléments
	void afficher();
};

#endif