/***************************************************
****************************************************
**                                                **
**                                                **
**             class header "camera"             **
**                                                **
**                  Thomas John                   **
**           thomas.john@open-design.be           **
**                                                **
**                                                **
****************************************************
***************************************************/

// this is to prevent the same header from being loaded twice
#ifndef C_CAMERA_H

#define C_CAMERA_H

#include "structures.h"

class camera

{
	// "private" data (variables, functions, etc.)
private:

	// structure qui contient les infos g�n�rales et notamment celles de la cam�ra
	infos_gen* infos_tex_tmp;

	// les donn�es publiques
public:

	// le constructeur par d�faut
	camera(double x_t, double y_t, double z_t, double x_v, double y_v, double z_v, double distance, struct infos_gen*);

	// le destructeur
	~camera();

	// calcul de la position de la cam�ra
	void calculer();
};

#endif