/***************************************************
****************************************************
**                                                **
**                                                **
**                 classe "camera"                **
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
#include <gl\glu.h>
#include <math.h>

// on inclut le fichier header de cette classe
#include "camera.h" // on met les guillemets car ce fichier se trouve dans le même dossier

// constructeur par défaut
camera::camera(double x_t, double y_t, double z_t, double x_v, double y_v, double z_v, double distance, struct infos_gen* infos_sz)
{
	// on initialise toutes les variables globales de cette classe

	// pointeur vers la structure contenant toutes les infos générales
	infos_tex_tmp = infos_sz;

	// le point "cible" de la caméra (là où elle regarde, sa cible)
	infos_tex_tmp->infos_cam_sz.m_x_t = x_t;
	infos_tex_tmp->infos_cam_sz.m_y_t = y_t;
	infos_tex_tmp->infos_cam_sz.m_z_t = z_t;

	// la position de la caméra (l'oeuil)
	infos_tex_tmp->infos_cam_sz.m_x_v = x_v;
	infos_tex_tmp->infos_cam_sz.m_y_v = y_v;
	infos_tex_tmp->infos_cam_sz.m_z_v = z_v;

	// la distance qui sépare la cible de la caméra
	infos_tex_tmp->infos_cam_sz.m_distance = distance;

	// la rotation en °
	infos_tex_tmp->infos_cam_sz.rot = 270;

	// l'état de la caméra (1 = active)
	infos_tex_tmp->infos_cam_sz.etat = 1;
}

// destructeur
camera::~camera()
{
	//rien pour le moment
}

// on calcule la position de la caméra
void camera::calculer()
{
	infos_tex_tmp->infos_cam_sz.m_z_v += ((double)(infos_tex_tmp->msec) / 120.0);
	infos_tex_tmp->infos_cam_sz.m_z_t += ((double)(infos_tex_tmp->msec) / 120.0);

	// we increase the degree of rotation of the camera
	//infos_tex_tmp->infos_cam_sz.rot += ((double)(infos_tex_tmp->msec) / (30.0));

	//rot = 270;
	//on vérifie qu'on ne va pas trop loin
	//if(rot > 360)
	//{
	//	rot = rot - 360;
	//}

	//m_distance -= ((double)(infos_tex_tmp->msec) / 50000.0f);

	//if(m_distance > 250)
		//m_distance = -3000;

	// on calcule les coordonnées de la caméra en fonction de la position de sa cible et son oeuil et de son degré de rotation
	infos_tex_tmp->infos_cam_sz.m_x_v = (double)cos((infos_tex_tmp->infos_cam_sz.rot / 360.0) * 2.0 * 3.141) * infos_tex_tmp->infos_cam_sz.m_distance + infos_tex_tmp->infos_cam_sz.m_x_t;
	infos_tex_tmp->infos_cam_sz.m_z_v = (double)sin((infos_tex_tmp->infos_cam_sz.rot / 360.0) * 2.0 * 3.141) * infos_tex_tmp->infos_cam_sz.m_distance + infos_tex_tmp->infos_cam_sz.m_z_t;
	//m_x_v = m_distance;
	//m_z_v = m_distance;
	//m_y_v = y_v;
	//m_y_v = sin((rot / 360) * 2 * 3.141) * m_distance + m_z_t;

	// on informe opengl de la position de la caméra
	gluLookAt(infos_tex_tmp->infos_cam_sz.m_x_v, infos_tex_tmp->infos_cam_sz.m_y_v, infos_tex_tmp->infos_cam_sz.m_z_v, infos_tex_tmp->infos_cam_sz.m_x_t, infos_tex_tmp->infos_cam_sz.m_y_t, infos_tex_tmp->infos_cam_sz.m_z_t, 0, 1, 0);
}