/***************************************************
****************************************************
**                                                **
**                                                **
**            ent�te classe "Ligne3D1"            **
**                                                **
**                  Thomas John                   **
**           thomas.john@open-design.be           **
**                                                **
**                                                **
****************************************************
***************************************************/

// ceci sert � ce qu'on ne charge pas deux fois le m�me header
#ifndef C_LIGNE3D1_H

#define C_LIGNE3D1_H

#include "structures.h"
//#include <math.h>
//#include <windows.h>

#include "effet_particule.h"

class Ligne3D1
{
	// les donn�es "priv�es" (variables, fonctions...)
private:

	struct Lettre3D1 {
		// position de la lettre
		double pos_x;
		double pos_y;
		double pos_z;

		// �tat de la lettre
		int	etat;

		// timer 1
		int	temps;
		int	temps_tot;

		// timer 2 (temps_tot_2 = temps � attendre avant de changer de caract�re, si la lettre peut changer dans le temps)
		int	temps_2;
		int	temps_tot_2;

		// caract�re � afficher (56 caract�res diff�rents)
		// cet int repr�sente une position dans le tableau regroupant toutes les coordonn�es de texture
		int caractere;

		// opacit� de la lettre
		double opacite;

		// distance de la lettre par rapport � l'oeuil de la cam�ra
		double dist_tmp;

		// sp�cifie si la lettre peut changer dans le temps
		int change_sz;
	};

	// la structure qui va contenir les infos sur chaque lettre de cette ligne
	Lettre3D1* lettre_1;

	// le nombre courant de lettres actives
	int	m_nbr_actif;

	// le temps qu'il faut attendre pour cr�er une nouvelle lettre
	int	m_temps_tot;
	int	m_temps;

	// pointeur vers la structure contenant les infos de toutes sortes
	infos_gen* infos_gen_tmp;

	// index de cette clase
	int index_tmp;

	// nombre max de lettres pour cette ligne
	int nbr_max_lettres;

	// nombre de lettres affich�es (sert pour le d�compte)
	int decpt_nbr_lettres;

	// dur�e du fondu entre la lettre blanche et la lettre verte (ceci pour garder un m�me dur�e pour toutes les lettres de la ligne)
	int m_temps_fondu;

	// sp�cifie si cette ligne utilise la classe "effet_particule"
	bool m_effet_particule;

	// l'effet de particule n'est activ� que si la vitesse de cette ligne (m_temps_tot) est rapide (m_temps_tot<30)
	// lorsque toutes les lettres ont fini leur "vie", la ligne est r�initialis�e
	// il est important de ne pas charger plusieurs fois une instance de la classe "effet_particule"

	// sp�cifie si une instance de la classe "effet_particule" a �t� charg�e
	bool m_charge_part;

	// on d�clare d�j� un pointeur qui pointera vers une instance de la classe "effet_particule"
	effet_particule* particules_1;

	// la distance de la ligne par rapport � la cam�ra aurait pu �tre utilis�e pour gagner en rapidit�
	// � la place, cette distance est calcul�e pour chaque lettre de chaque ligne
	// cela augmente le temps de calcul, mais ce sera utile pour plus tard (certains effets)

	// distance de la ligne par rapport � la cam�ra (l'oeuil)
	double dist_tmp;

	// opacit� de la ligne
	//double opacite_gen;

	// initialisation d'une lettre
	void init_lettre(int index_sz);

	//les donn�es publiques
public:

	// �tat de la classe
	int m_etat;

	// les coordonn�es de la ligne
	double m_x;
	double m_y;
	double m_z;

	// le constructeur par d�faut
	Ligne3D1(double x, double y, double z, struct infos_gen*, int index);

	// le destructeur
	~Ligne3D1();

	// calcul de la position et de l'�tat des particules
	void calculer();

	// affichage des �l�ments
	void afficher();
};

#endif