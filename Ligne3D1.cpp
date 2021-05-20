/***************************************************
****************************************************
**                                                **
**                                                **
**               classe "Ligne3D1"                **
**                                                **
**                  Thomas John                   **
**           thomas.john@open-design.be           **
**                                                **
**                                                **
****************************************************
***************************************************/

// on inclut les entêtes
#include <windows.h>
#include <gl\gl.h>
//#include <gl\glu.h>
#include <math.h>

#include <stdio.h>

// on inclut le fichier header de cette classe
#include "Ligne3D1.h" //on met les guillemets car ce fichier se trouve dans le même dossier

// initialisation d'une lettre
void Ligne3D1::init_lettre(int index_sz)
{
	// on initialise toutes les variables de cette lettre
	// il est important d'initialiser toutes les variable d'une structure ou d'une classe lorsqu'elle est créée
	// avant de les utiliser

	// les coordonnées
	lettre_1[index_sz].pos_x = m_x;
	lettre_1[index_sz].pos_y = m_y - (0.7 * m_nbr_actif); // chaque lettre se trouve plus bas de 0.7
	lettre_1[index_sz].pos_z = m_z;

	// état de la lettre 1 = début
	lettre_1[index_sz].etat = 1;

	// timer 1
	lettre_1[index_sz].temps = 0;
	lettre_1[index_sz].temps_tot = m_temps_tot;

	// le caractère que cette lettre va afficher (parmi 56)
	lettre_1[index_sz].caractere = rand() % 55;

	// l'opacité de cette lettre
	lettre_1[index_sz].opacite = 100;

	// la distance qui la sépare de l'oeuil de la caméra
	lettre_1[index_sz].dist_tmp = 0;

	// spécifie si le caractère de la lettre peut changer dans le temps
	lettre_1[index_sz].change_sz = rand() % 3;

	// timer 2 (changement de caractère)
	lettre_1[index_sz].temps_2 = 0;
	lettre_1[index_sz].temps_tot_2 = 70 + (rand() % 500);
}

// constructeur par défaut
Ligne3D1::Ligne3D1(double x, double y, double z, struct infos_gen* infos_sz, int index)
{
	// on initialise toutes les variables globales

	// pointeur vers structure contenant les infos générales
	infos_gen_tmp = infos_sz;

	// les coordonnées
	m_y = double((rand() % 100) - 50) + infos_gen_tmp->infos_cam_sz.m_y_v;
	m_z = double((rand() % 100)) + infos_gen_tmp->infos_cam_sz.m_z_v;
	// au plus la ligne est éloignée de la caméra, au sa marge sur la coordonnée x sera grande
	m_x = double((rand() % 100) - 50) + infos_gen_tmp->infos_cam_sz.m_x_v;
	/*
		// sert pour les tests
		m_x = infos_gen_tmp->infos_cam_sz.m_x_t;
		m_y = infos_gen_tmp->infos_cam_sz.m_y_t;
		m_z = infos_gen_tmp->infos_cam_sz.m_z_t;
	*/
	// l'état de la classe (1 = active)
	m_etat = 1;

	// le nombre max de lettres à afficher
	nbr_max_lettres = 20 + int(rand() % 100);

	// sert pour le décompte
	decpt_nbr_lettres = nbr_max_lettres;

	// on crée notre tableau qui va contenir les infos concernant chaque lettre
	lettre_1 = new Lettre3D1[nbr_max_lettres + 1];

	// le nombre de lettres actives
	m_nbr_actif = 0;

	// timer 1
	m_temps = 0;
	m_temps_tot = 1 + (rand() % 300);

	// index de cette instance de classe
	index_tmp = index;

	// durée du fondu blanc->vert
	m_temps_fondu = m_temps_tot;

	// aucune instance de la classe "effet_particule" n'a encore été chargée
	m_charge_part = FALSE;

	// si la vitesse d'affichage des lettres est rapide (<30) et si on affiche plus de 60 lettres, on affiche les particules
	if (m_temps_tot < 30 && nbr_max_lettres>60)
	{
		// on met la variable à TRUE
		m_effet_particule = TRUE;

		// on crée la classe
		particules_1 = new effet_particule(0, 0, 0, 1, 200, infos_sz, 1, 1);
		particules_1->m_x = m_x;
		particules_1->m_y = m_y;
		particules_1->m_z = m_z;

		// une instance de cette classe a été chargée
		m_charge_part = TRUE;
	}
	else {
		// sinon on met la variable à FALSE
		m_effet_particule = FALSE;
	}

	// distance ligne-caméra
	dist_tmp = 0;
}

// destructeur
Ligne3D1::~Ligne3D1()
{
	// on décharge l'instance de de la classe "effet_particule" si elle a été chargée
	if (m_charge_part = TRUE)
		delete particules_1;
}

// on calcule la position et l'état de chaque élément de cette ligne
void Ligne3D1::calculer()
{
	// % calculé en fonction des données du timer de chaque lettre (temps et temps_tot)
	double prct_sz;
	//char oki[256] = "";

	// on vérifie s'il faut créer une nouvelle lettre
	if (m_nbr_actif < nbr_max_lettres)
	{
		// on incrémente notre timer
		m_temps += infos_gen_tmp->msec;

		// on vérifie si notre timer n'est pas arrivé au bout
		if (m_temps >= m_temps_tot)
		{
			// on crée une nouvelle lettre
			m_nbr_actif++;

			// on initialise la nouvelle lettre
			init_lettre(m_nbr_actif);

			// on ré-initialise notre timer
			m_temps = 0;
		}
	}

	// ces variables vont nous permettre de calculer la distance qui sépare chaque lettre de l'oeuil de la caméra
	double dist_x;
	double dist_y;
	double dist_z;

	/*

	// ce bout de code permet de calculer la distance qui sépare la ligne de l'oeuil de la caméra
	// désormais, cette distance est calculée pour chaque lettre
	// je laisse toujours le code pour ceux qui n'ont pas besoin de le calculer pour chaque lettre et
	// ainsi gagner quelques fps

	// on modifie l'opacité de la ligne en fonction de la distance qui la sépare de la caméra
	dist_x = infos_gen_tmp->infos_cam_sz.m_x_v - m_x;
	dist_y = infos_gen_tmp->infos_cam_sz.m_y_v - m_y;
	dist_z = infos_gen_tmp->infos_cam_sz.m_z_v - m_z;

	dist_tmp = sqrt( (dist_x * dist_x) + (dist_y * dist_y) + (dist_z * dist_z));

	infos_gen_tmp->dist_ttmp = dist_tmp;

	if(dist_tmp > 200)
	{
		opacite_gen = 0;
	}else if( dist_tmp < 100 ){
		opacite_gen = 1;
	}else{
		opacite_gen = 1 - ((dist_tmp-100) / 100);
	}
	*/

	int	i;

	// on calcule l'état des lettres
	for (i = 1; i <= m_nbr_actif; i++)
	{
		// on vérifie que la lettre est encore active
		if (lettre_1[i].etat > 0)
		{
			// on incrémente le timer
			lettre_1[i].temps += infos_gen_tmp->msec;

			// ok, on fait ce qu'il faut en fonction de l'état de la lettre
			switch (lettre_1[i].etat)
			{
			case 1:	// on fait apparaître la lettre blanche

				// on calcule le pourcentage
				prct_sz = (double(lettre_1[i].temps) / double(lettre_1[i].temps_tot));

				// on change l'opacité
				lettre_1[i].opacite = prct_sz;
				//lettre_1[i].opacite = prct_sz * opacite_gen; // sert uniquement si on ne calcule que la distance ligne-caméra

				break;

			case 2: // on affiche la lettre blanche

				// on change l'opacité (qui reste à 1 en fait)
				lettre_1[i].opacite = 1.0;
				//lettre_1[i].opacite = opacite_gen; // sert uniquement si on ne calcule que la distance ligne-caméra

				break;

			case 3: // transition entre la lettre blanche et verte

				// on calcule le pourcentage
				prct_sz = (double(lettre_1[i].temps) / double(lettre_1[i].temps_tot));

				// on change l'opacité
				lettre_1[i].opacite = prct_sz;
				//lettre_1[i].opacite = prct_sz * opacite_gen; // sert uniquement si on ne calcule que la distance ligne-caméra

				break;

			case 4:	// on affiche la lettre verte

				// on change l'opacité
				lettre_1[i].opacite = 1.0;
				//lettre_1[i].opacite = opacite_gen; // sert uniquement si on ne calcule que la distance ligne-caméra

				break;

			case 5: // on diminue l'opacité de la lettre

				// on calcule le pourcentage
				prct_sz = 1.0 - (double(lettre_1[i].temps) / double(lettre_1[i].temps_tot));

				// on change l'opacité
				lettre_1[i].opacite = prct_sz;
				//lettre_1[i].opacite = prct_sz * opacite_gen; // sert uniquement si on ne calcule que la distance ligne-caméra

				break;
			}

			// on vérifie si la lettre peut changer
			if (lettre_1[i].change_sz == 1)
			{
				// oui, on incrémente le timer adéquat
				lettre_1[i].temps_2 += infos_gen_tmp->msec;

				// si le timer arrive à la fin, on change le caractère
				if (lettre_1[i].temps_2 >= lettre_1[i].temps_tot_2)
				{
					// on re-initialise le timer
					lettre_1[i].temps_2 = 0;

					// et on change de caractère
					lettre_1[i].caractere = int(rand() % 55);
				}
			}

			// on modifie l'opacité de la lettre en fonction de la distance qui la sépare de la caméra
			dist_x = infos_gen_tmp->infos_cam_sz.m_x_v - m_x;
			dist_y = infos_gen_tmp->infos_cam_sz.m_y_v - m_y;
			dist_z = infos_gen_tmp->infos_cam_sz.m_z_v - m_z;

			// ici, c'est de l'oeuil de la caméra
			//dist_x = infos_gen_tmp->infos_cam_sz.m_x_t - m_x;
			//dist_y = infos_gen_tmp->infos_cam_sz.m_y_t - m_y;
			//dist_z = infos_gen_tmp->infos_cam_sz.m_z_t - m_z;

			// on calcule la distance
			lettre_1[i].dist_tmp = sqrt((dist_x * dist_x) + (dist_y * dist_y) + (dist_z * dist_z));
			//dist_tmp = sqrt( (dist_x * dist_x) + (dist_y * dist_y) + (dist_z * dist_z)); // sert pour distance ligne-caméra

			// debug
			//infos_gen_tmp->dist_ttmp = dist_tmp;

			// on vérifie si la lettre n'est pas trop loin
			if (lettre_1[i].dist_tmp > 200)
			{
				// si, alors on ne l'affiche pas
				lettre_1[i].opacite = 0;
			}
			else if (lettre_1[i].dist_tmp > 100) {
				// non, on peut encore la voir, on calcule sont opacité en fonction de sa distance (entre 100 et 200)
				lettre_1[i].opacite = (1 - ((lettre_1[i].dist_tmp - 100) / 100)) * lettre_1[i].opacite;
			}
		}
	}

	//on récupère la distance lettre-caméra de la dernière lettre
	dist_tmp = lettre_1[i - 1].dist_tmp;

	// si cette ligne utilise une classe "effet_particule", on la calcule
	if (m_effet_particule == TRUE)
	{
		// on vérifie si toutes les lettres de la ligne ont été créées
		if (m_nbr_actif >= nbr_max_lettres)
		{
			//oui, on stoppe l'émission de nouvelles particules
			particules_1->etat = 2;
		}

		// on met à jour la coordonnée y de la classe d'émission de particule
		particules_1->m_y = m_y - (0.7 * m_nbr_actif);

		// et on effectue les calculs
		particules_1->calculer();
	}

	// on spécifie la coordonnée z de cette ligne dans notre tableau qui va servir à trier toutes les lignes
	// de sorte à les afficher de la plus éloignée à la plus proche
	infos_gen_tmp->ordre_sz[index_tmp].index = index_tmp;
	infos_gen_tmp->ordre_sz[index_tmp].ordre = m_z;
}

// affichage des éléments
void Ligne3D1::afficher()
{
	int i = 0, i2 = 0, i3 = 0;
	//double db_tmp;

	// debug
	char oki[256] = "";

	// on parcoure toutes les lettres
	for (i = 1; i <= m_nbr_actif; i++)
	{
		// ## ! ##
		// on ne vérifie plus s'il faut afficher la lettre ou pas ici
		// cela posait problème avec l'état n°3 de la lettre car même si l'opacité de la lettre verte était de zéro,
		// l'opacité de la lettre blanche équivalait à (1 - opacité lettre verte) donc 1
		// comme cette vérification n'est effectuée que sur la lettre principale (en fait la structure contenant les infos sur
		// chaque lettre ne prend pas en compte le fait qu'il puisse y avoir deux lettres), la lettre blanche qui avait comme
		// opacité 1 n'était pas affichée, causant de ce fait un effet de scintillement
		// ##   ##

		// on vérifie que la lettre est encore active
		//if(lettre_1[i].etat > 0 && lettre_1[i].opacite > 0)
		//{
			// en fonction de l'état de la lettre
		switch (lettre_1[i].etat)
		{
		case 0: // on ne fait rien
			break;

		case 1: // affichage de la lettre blanche

			// on vérifie s'il faut afficher cette lettre
			if (lettre_1[i].opacite > 0)
			{
				// on spécifie la texture à utiliser
				glBindTexture(GL_TEXTURE_2D, infos_gen_tmp->tex_lettres_blanches);
			}

			// on vérifie si cette partie n'est pas terminée
			if (lettre_1[i].temps >= lettre_1[i].temps_tot)
			{
				// on change l'état de la lettre
				lettre_1[i].etat++;

				// on remet le compteur à zéro
				lettre_1[i].temps = 0;

				// on spécifie une nouvelle durée pour le timer
				lettre_1[i].temps_tot = 1;
			}

			break;

		case 2: // affichage de la lettre blanche

			if (lettre_1[i].opacite > 0)
			{
				// on spécifie la texture à utiliser
				glBindTexture(GL_TEXTURE_2D, infos_gen_tmp->tex_lettres_blanches);
			}

			// on vérifie si cette partie n'est pas terminée
			if (lettre_1[i].temps >= lettre_1[i].temps_tot)
			{
				// on change l'état de la lettre
				lettre_1[i].etat++;

				// on remet le compteur à zéro
				lettre_1[i].temps = 0;

				// on spécifie une nouvelle durée (celle de la transition blanc->vert)
				lettre_1[i].temps_tot = m_temps_fondu;

				// debug
				//sprintf(oki, "on commence...\n");
				//OutputDebugString(oki);
			}

			break;

		case 3: // fondu du blanc au vert

			// debug
			//sprintf(oki, "opacite = %f ", lettre_1[i].opacite);
			//OutputDebugString(oki);

			// on vérifie si la distance lettre-caméra est inférieure à 201 (sinon on affiche rien)
			if (lettre_1[i].dist_tmp < 201)
			{
				// on affiche la lettre blanche

				// on spécifie la texture à utiliser (caractères blancs)
				glBindTexture(GL_TEXTURE_2D, infos_gen_tmp->tex_lettres_blanches);

				// l'opacité de la lettre blanche est la différence de celle de la verte par rapport à 1
				// donc quand l'opacité de la lettre verte augmente (pour apparaître), l'opacité de la lettre
				// blanche diminue (disparait)
				// on prend aussi en compte la distance lettre-caméra
				if (lettre_1[i].dist_tmp < 200 && lettre_1[i].dist_tmp > 100)
				{
					// on cspécifie l'opacité
					glColor4d(1.0, 1.0, 1.0, (1 - ((lettre_1[i].dist_tmp - 100) / 100)) - lettre_1[i].opacite);

					// debug
					//sprintf(oki, " || entre deux : %f \n", (1 - ((lettre_1[i].dist_tmp-100) / 100)) - lettre_1[i].opacite);
					//OutputDebugString(oki);
				}
				else {
					// on spécifie l'opacité
					glColor4d(1.0, 1.0, 1.0, (1 - lettre_1[i].opacite));

					// debug
					//sprintf(oki, " || dedans : %f \n", (1 - lettre_1[i].opacite));
					//OutputDebugString(oki);
				}

				// debug
				//infos_gen_tmp->dist_ttmp = lettre_1[i].opacite;

				// on dessine la lettre blanche
				glBegin(GL_QUADS);

				glTexCoord2f(infos_gen_tmp->info_tex_vertes_sz[lettre_1[i].caractere].x1, infos_gen_tmp->info_tex_vertes_sz[lettre_1[i].caractere].y1);
				glVertex3d(lettre_1[i].pos_x, lettre_1[i].pos_y, lettre_1[i].pos_z);

				glTexCoord2f(infos_gen_tmp->info_tex_vertes_sz[lettre_1[i].caractere].x2, infos_gen_tmp->info_tex_vertes_sz[lettre_1[i].caractere].y2);
				glVertex3d(lettre_1[i].pos_x, lettre_1[i].pos_y + 1.0, lettre_1[i].pos_z);

				glTexCoord2f(infos_gen_tmp->info_tex_vertes_sz[lettre_1[i].caractere].x3, infos_gen_tmp->info_tex_vertes_sz[lettre_1[i].caractere].y3);
				glVertex3d(lettre_1[i].pos_x + 1.0, lettre_1[i].pos_y + 1.0, lettre_1[i].pos_z);

				glTexCoord2f(infos_gen_tmp->info_tex_vertes_sz[lettre_1[i].caractere].x4, infos_gen_tmp->info_tex_vertes_sz[lettre_1[i].caractere].y4);
				glVertex3d(lettre_1[i].pos_x + 1.0, lettre_1[i].pos_y, lettre_1[i].pos_z);

				glEnd();

				// on spécifie la texture à utiliser (cette fois, la texture pour les caractères verts)
				glBindTexture(GL_TEXTURE_2D, infos_gen_tmp->tex_lettres_vertes);
			}

			// on vérifie si cette partie n'est pas terminée
			if (lettre_1[i].temps >= lettre_1[i].temps_tot)
			{
				// on change l'état de la lettre
				lettre_1[i].etat++;

				// on remet le compteur à zéro
				lettre_1[i].temps = 0;

				// on spécifie une nouvelle durée
				lettre_1[i].temps_tot = 500 + (rand() % 2000);

				// debug
				//sprintf(oki, "on termine...\n\n");
				//OutputDebugString(oki);
			}

			break;

		case 4: // on affiche la lettre verte

			if (lettre_1[i].opacite > 0)
			{
				// on spécifie la texture à utiliser
				glBindTexture(GL_TEXTURE_2D, infos_gen_tmp->tex_lettres_vertes);
			}

			// on vérifie si cette partie n'est pas terminée
			if (lettre_1[i].temps >= lettre_1[i].temps_tot)
			{
				// on change l'état de la lettre
				lettre_1[i].etat++;

				// on remet le compteur à zéro
				lettre_1[i].temps = 0;
			}

			break;

		case 5: // on diminue l'opacité de la lettre verte

			if (lettre_1[i].opacite > 0)
			{
				// on spécifie la texture à utiliser
				glBindTexture(GL_TEXTURE_2D, infos_gen_tmp->tex_lettres_vertes);
			}

			// on vérifie si cette partie n'est pas terminée
			if (lettre_1[i].temps >= lettre_1[i].temps_tot)
			{
				// on change l'état de la lettre
				lettre_1[i].etat = 0;

				// on remet le compteur à zéro
				lettre_1[i].temps = 0;

				// une lettre active en moins
				decpt_nbr_lettres--;

				// debug
				//sprintf(oki, "nombre de lettres restantes : %i\n" , decpt_nbr_lettres);
				//OutputDebugString(oki);

				// on vérifie si toutes les lettres sont désactivées
				if (decpt_nbr_lettres == 0)
				{
					// on réinitialise la ligne
					m_y = double((rand() % 150) - 50) + infos_gen_tmp->infos_cam_sz.m_y_t;
					i3 = (rand() % 200) - 100;
					m_z = i3 + infos_gen_tmp->infos_cam_sz.m_z_t;
					// on définit la position x en fonction de z
					// au plus la ligne est proche de la caméra au moins sa position x pourra être grande
					m_x = double((rand() % 100) - 50) + infos_gen_tmp->infos_cam_sz.m_x_t;
					//if(i3 < 0){ i3 = 0; }
					//m_x = double((rand() % (100 + (i3*10))) - (50 + (i3*5))) + infos_gen_tmp->infos_cam_sz.m_x_t;

/*
							m_x = infos_gen_tmp->infos_cam_sz.m_x_t;
							m_y = infos_gen_tmp->infos_cam_sz.m_y_t;
							m_z = infos_gen_tmp->infos_cam_sz.m_z_t;
*/

// debug
//infos_gen_tmp->dist_ttmp = index_tmp;
					sprintf(oki, "diff : %i\n", i3);
					OutputDebugString(oki);

					// l'état de la classe (1 = active)
					m_etat = 1;

					// le nombre max de lettres
					//nbr_max_lettres = 50;

					// sert pour le décompte
					decpt_nbr_lettres = nbr_max_lettres;

					// on crée notre tableau qui va contenir les infos concernant chaque lettre
					//lettre_1 = new Lettre3D1[nbr_max_lettres];

					// le nombre de lettres actives
					m_nbr_actif = 0;

					// timer à zéro
					m_temps = 0;
					/*
												if(m_effet_particule == TRUE)
												{
													particules_1->m_x = m_x;
													particules_1->m_y = m_y;
													particules_1->m_z = m_z;
													particules_1->etat = 1;
													particules_1->m_nombre_actifs=0;
												}
					*/

					// vitesse à laquelle de nouvelles lettres sont créées
					m_temps_tot = 1 + int((rand() % 300));

					// si la vitesse d'affichage des lettres est rapide (<30) et si la ligne est suffisamment grande,
					// on affiche les particules
					if (m_temps_tot < 30 && nbr_max_lettres>60)
					{
						// on vérifie si une instance de la classe "effet_particule" a déjà été chargée
						if (m_charge_part == FALSE)
						{
							// non, on la charge
							particules_1 = new effet_particule(0, 0, 0, 1, 200, infos_gen_tmp, 1, 1);

							m_charge_part = TRUE;
						}

						// on met la variable à TRUE
						m_effet_particule = TRUE;

						// on initialise l'émetteur de particule
						particules_1->m_x = m_x;
						particules_1->m_y = m_y;
						particules_1->m_z = m_z;
						particules_1->etat = 1;
						particules_1->m_nombre_actifs = 0;
					}
					else {
						// sinon on met la variable à FALSE
						m_effet_particule = FALSE;
					}
				}
			}

			break;
		}

		// on vérifie s'il faut afficher cette lettre
		if (lettre_1[i].etat > 0 && lettre_1[i].opacite > 0)
		{
			// l'opacité
			glColor4d(1.0, 1.0, 1.0, lettre_1[i].opacite);

			// on dessine la lettre
			glBegin(GL_QUADS);

			glTexCoord2f(infos_gen_tmp->info_tex_vertes_sz[lettre_1[i].caractere].x1, infos_gen_tmp->info_tex_vertes_sz[lettre_1[i].caractere].y1);
			glVertex3d(lettre_1[i].pos_x, lettre_1[i].pos_y, lettre_1[i].pos_z);

			glTexCoord2f(infos_gen_tmp->info_tex_vertes_sz[lettre_1[i].caractere].x2, infos_gen_tmp->info_tex_vertes_sz[lettre_1[i].caractere].y2);
			glVertex3d(lettre_1[i].pos_x, lettre_1[i].pos_y + 1.0, lettre_1[i].pos_z);

			glTexCoord2f(infos_gen_tmp->info_tex_vertes_sz[lettre_1[i].caractere].x3, infos_gen_tmp->info_tex_vertes_sz[lettre_1[i].caractere].y3);
			glVertex3d(lettre_1[i].pos_x + 1.0, lettre_1[i].pos_y + 1.0, lettre_1[i].pos_z);

			glTexCoord2f(infos_gen_tmp->info_tex_vertes_sz[lettre_1[i].caractere].x4, infos_gen_tmp->info_tex_vertes_sz[lettre_1[i].caractere].y4);
			glVertex3d(lettre_1[i].pos_x + 1.0, lettre_1[i].pos_y, lettre_1[i].pos_z);

			glEnd();
		}

		//}
	}

	// si cette ligne utilise une classe "effet_particule", on l'affiche
	if (m_effet_particule == TRUE && dist_tmp < 201)
	{
		// on change le mode de blending pour l'affichage des particules
		//glBlendFunc(GL_SRC_ALPHA,GL_ONE);
		//glBlendFunc(GL_ONE,GL_ONE);
		glBlendFunc(GL_SRC_COLOR, GL_ONE);

		// sert pour les tests
		// les modes de "blending" peuvent être changé via le pavé numérique du clavier et les chiffres
		// se trouvant au-dessus des lettres (ceux accessible avec shift enfoncé)
		// tous les modes ne sont pas présents (il en manque 1 de chaque, le 11ème)
		//glBlendFunc(infos_gen_tmp->prem,infos_gen_tmp->deux);

		// on spécifie la texture à utiliser
		glBindTexture(GL_TEXTURE_2D, infos_gen_tmp->tex_part_1);

		// on affiche les particules
		particules_1->afficher();

		// on remet le mode de blending initial
		glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
	}
}