/***************************************************
****************************************************
**                                                **
**                                                **
**            classe "effet_particule"            **
**                                                **
**                  Thomas John                   **
**           thomas.john@open-design.be           **
**                                                **
**                                                **
****************************************************
***************************************************/

// on inclut les ent�tes
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <math.h>
#include "vector3f.h"

// on inclut le fichier header de cette classe
#include "effet_particule.h" //on met les guillemets car ce fichier se trouve dans le m�me dossier

// initialise une particule
void effet_particule::init_particule(int particulesz)
{
	// coordonn�es de d�part
	// on laisse une marge pour que les particules n'apparaissent pas toutes au m�me point
	t_particules[particulesz].x = m_x + 0.5 + (double(rand() % 1) - 0.5) / 5;
	t_particules[particulesz].y = m_y - 1 - (double(rand() % 1) - 0.5) / 2;
	t_particules[particulesz].z = m_z + (double(rand() % 1) - 0.5) / 5;

	// direction des particules
	t_particules[particulesz].d_x = (double(rand() % 50) - 25) / 5000;
	t_particules[particulesz].d_y = -(double(rand() % 3)) / 100; //les particulent descendent un peu
	t_particules[particulesz].d_z = (double(rand() % 50) - 25) / 5000;

	// vitesse � laquelle elles meurent
	t_particules[particulesz].vitesse = 0.01 - ((double(rand() % 5)) / 1000);

	// vie (opacit�)
	t_particules[particulesz].vie = 1.0;

	// taille
	t_particules[particulesz].taille = 0.7 + (double(rand() % 7) / 10);

	//couleurs
	/* SYMPA : ROUGE/ORANGE */
	t_particules[particulesz].r = 0.92;// + ((double(rand() % 10)-5)/50);
	t_particules[particulesz].g = 0.72;// + ((double(rand() % 10)-5)/50);
	t_particules[particulesz].b = 0.58;// + ((double(rand() % 10)-5)/50);
}

// constructeur par d�faut
effet_particule::effet_particule(double x, double y, double z, double vitesse, int nombre_tot, struct infos_gen* infos_sz, int vitesse_emission, int nbr_emission)
{
	// on r�cup�re notre pointeur vers la structure contenant toutes les infos utiles
	infos_tex_tmp = infos_sz;

	// on met notre �tat � 1
	etat = 1; // signifie que la classe est active (0 = morte)

	// on initialise les variables indiquant la position de l'�metteur de particules
	m_x = x;
	m_y = y;
	m_z = z;

	// vitesse � laquelle les particules "vivent" (se d�pacent, meurent...)
	// n'est pas encore utilis�e, mais on l'initialise quand m�me
	m_vitesse = vitesse;

	// nombre max de particules � afficher en m�me temps
	m_nombre_tot = nombre_tot;

	// nombre de particules actives
	m_nombre_actifs = 0;

	// permet de sp�cifier une dur�e entre chaque �mition de particule
	m_temps = 0;
	m_temps_tot = vitesse_emission;

	// nombre de particules �mises en m�me temps
	m_nbr_emission = nbr_emission;

	// on cr�e notre tableau de particules
	t_particules = new particules[nombre_tot];
}

// destructeur
effet_particule::~effet_particule()
{
	//
}

// on calcule la position de chaque particule et on en cr�e une nouvelle s'il le faut
void effet_particule::calculer()
{
	int i = 0;

	// on v�rifie s'il faut cr�er une nouvelle particule
	if (m_nombre_actifs + m_nbr_emission <= m_nombre_tot && etat == 1)
	{
		m_temps += infos_tex_tmp->msec;

		if (m_temps >= m_temps_tot)
		{
			// on en cr�e autant qu'il le faut
			for (i = 0; i < m_nbr_emission; i++)
			{
				// on initialise la nouvelle particule
				init_particule(m_nombre_actifs);

				m_nombre_actifs++;
			}

			// on remet notre compteur � z�ro
			m_temps = 0;
		}
	}

	// on met � jour la position et l'opacit� (vie) de chaque particule en fonction de "infos_tex_tmp->msec" qui est le temps en ms pass� entre l'affichage de 2 images
	for (i = 0; i < m_nombre_actifs; i++)
	{
		// coordonn�es
		t_particules[i].x += (t_particules[i].d_x * infos_tex_tmp->msec / 10);
		t_particules[i].y += (t_particules[i].d_y * infos_tex_tmp->msec / 10);
		t_particules[i].z += (t_particules[i].d_z * infos_tex_tmp->msec / 10);

		// vie
		t_particules[i].vie -= (t_particules[i].vitesse * infos_tex_tmp->msec / 10);

		// taille
		t_particules[i].taille -= (t_particules[i].vitesse * infos_tex_tmp->msec / 25);

		// on v�rifie que la vie de cette particule n'atteint pas 0
		if (t_particules[i].vie <= 0)
		{
			// on la r�initialise s'il le faut
			if (etat == 1)
				init_particule(i);
		}
	}
}

// on affiche la particule (avec effet de type "billboarding")
// pour plus d'infos sur le billboarding (en anglais : http://www.lighthouse3d.com/opengl/billboarding/index.php3?billCheat)
// vous verrez, c'est tr�s bien expliqu� !
void effet_particule::afficher()
{
	// tableau qui va contenir la matrice "MODELVIEW"
	// cette matric inscrit toutes les tranformations g�om�triques que l'on fait
	float mat[16];

	// on r�cup�re la matrice
	glGetFloatv(GL_MODELVIEW_MATRIX, mat);

	// on d�clare les vecteurs qui vont nous permettre de calculer le billboarding
	vector3f vRight(mat[0], mat[4], mat[8]);
	vector3f vUp(mat[1], mat[5], mat[9]);
	vector3f vPoint0;
	vector3f vPoint1;
	vector3f vPoint2;
	vector3f vPoint3;
	vector3f vCenter;

	//double fAdjustedSize = 0.4 + (double(rand() % 4)/10);

	glBegin(GL_QUADS);

	// on affiche toutes les particules actives
	for (int i = 0; i < m_nombre_actifs; i++)
	{
		// on v�rifie que cette particule est toujours en vie
		if (t_particules[i].vie > 0)
		{
			// on d�finit le centre
			vCenter.x = t_particules[i].x;
			vCenter.y = t_particules[i].y;
			vCenter.z = t_particules[i].z;

			// on calcule les coordonn�es des 4 points qui vont constituer la particule
			vPoint0 = vCenter + ((-vRight - vUp) * t_particules[i].taille);
			vPoint1 = vCenter + ((vRight - vUp) * t_particules[i].taille);
			vPoint2 = vCenter + ((vRight + vUp) * t_particules[i].taille);
			vPoint3 = vCenter + ((-vRight + vUp) * t_particules[i].taille);

			// on ajuste la couleur de la particule (et son opacit� --> d�pend du mode de blending)
			//glColor3d( t_particules[i].vie / 4 , t_particules[i].vie / 1.1, t_particules[i].vie / 1.5 );
			glColor3d(t_particules[i].vie * t_particules[i].r, t_particules[i].vie * t_particules[i].g, t_particules[i].vie * t_particules[i].b);

			// on dessine notre particule
			glTexCoord2d(0.0, 0.0);
			glVertex3d(vPoint0.x, vPoint0.y, vPoint0.z);

			glTexCoord2d(1.0, 0.0);
			glVertex3d(vPoint1.x, vPoint1.y, vPoint1.z);

			glTexCoord2d(1.0, 1.0);
			glVertex3d(vPoint2.x, vPoint2.y, vPoint2.z);

			glTexCoord2d(0.0, 1.0);
			glVertex3d(vPoint3.x, vPoint3.y, vPoint3.z);
		}
	}

	glEnd();
}