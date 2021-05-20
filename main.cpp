/***************************************************
****************************************************
**                                                **
**                                                **
**              MATRIX FALL main.cpp              **
**                  Version 9.0                   **
**                  Thomas John                   **
**           thomas.john@open-design.be           **
**                                                **
**                                                **
****************************************************
***************************************************/

// r�alis� avec l'aide des tutoriaux de Jeff Molofee disponibles � l'adresse suivante :
// nehe.gamedev.net

// ainsi que sur d'autres bas�s sur ces premiers que vous pouvez consulter � cette adresse :
// glinfrench.apinc.org

#include "main.h"

//****************************************************************************************
//              **************************************************************************
//  proc�dures
//              **************************************************************************
//****************************************************************************************

//permet de s'amuser avec les options de blending
GLenum blend_sz(int varsz)
{
	switch (varsz)
	{
	case 1:
		return GL_ZERO;
		break;

	case 2:
		return GL_ONE;
		break;

	case 3:
		return GL_SRC_COLOR;
		break;

	case 4:
		return GL_ONE_MINUS_SRC_COLOR;
		break;

	case 5:
		return GL_DST_COLOR;
		break;

	case 6:
		return GL_ONE_MINUS_DST_COLOR;
		break;

	case 7:
		return GL_SRC_ALPHA;
		break;

	case 8:
		return GL_ONE_MINUS_SRC_ALPHA;
		break;

	case 9:
		return GL_DST_ALPHA;
		break;

	case 10:
		return GL_ONE_MINUS_DST_ALPHA;
		break;

	case 11:
		return GL_SRC_ALPHA_SATURATE;
		break;

	default:
		return GL_ZERO;
	}
}

// dessine la sc�ne
int RePaint()
{
	// on initialise notre premier compteur qui va nous permettre de conna�tre le temps �coul� entre chaque sc�ne
	temps_1 = GetTickCount();

	// ceci est la diff�rence entre le moment o� la derni�re sc�ne a �t� rendue et "maintenant"
	s_infos_gen.msec = temps_1 - temps_2;

	// on efface notre �cran
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// on remet � z�ro les entit�s
	glLoadIdentity();

	// on calcule le nombre d'images par seconde affich�es
	if (GetTickCount() - fps_2 >= 1000)
	{
		fps_2 = GetTickCount();

		fps_img_2 = fps_img_1;

		fps_img_1 = 0;
	}

	// on augmente le nombre d'images qui ont �t� affich�es
	fps_img_1++;

	// on affiche les infos dans la barre des titres
	sprintf(images_sec, "%s - fps = %d - dist = %f - msec = %i", NOM_APP_FENETRE, fps_img_2, s_infos_gen.dist_ttmp, s_infos_gen.msec);
	SetWindowText(hWnd, images_sec);

	// on calcule la position de la cam�ra
	camera_1->calculer();

	// ces variables vont servir � ordonner toutes les lignes du tableau contenant leurs index et coordonn�es z
	int i = 0, i2 = 0;
	double ordre_cour;

	// on calcule chaque ligne
	for (i = 0; i < NBR_LIGNES_MAX; i++)
	{
		ligne_1[i]->calculer();
	}

	// on trie la liste selon leur coordonn�e z (m�thode dite "bubble sort")
	for (int i4 = 0; i4 < NBR_LIGNES_MAX - 1; i4++)
	{
		for (int j4 = i4 + 1; j4 < NBR_LIGNES_MAX; j4++)
		{
			if (s_infos_gen.ordre_sz[i4].ordre > s_infos_gen.ordre_sz[j4].ordre)
			{
				// on interverti les donn�es
				ordre_cour = s_infos_gen.ordre_sz[i4].ordre;
				i2 = s_infos_gen.ordre_sz[i4].index,
					s_infos_gen.ordre_sz[i4].ordre = s_infos_gen.ordre_sz[j4].ordre;
				s_infos_gen.ordre_sz[i4].index = s_infos_gen.ordre_sz[j4].index;
				s_infos_gen.ordre_sz[j4].ordre = ordre_cour;
				s_infos_gen.ordre_sz[j4].index = i2;
			}
		}
	}

	// et on les affiche en fonction de la position de la cam�ra et de sa direction
	if ((s_infos_gen.infos_cam_sz.m_z_v - s_infos_gen.infos_cam_sz.m_z_t) < 0)
	{
		for (i = NBR_LIGNES_MAX - 1; i >= 0; i--)
		{
			//i2 = s_infos_gen.ordre_sz[i].index;
			//ordre_cour = s_infos_gen.ordre_sz[i].ordre;
			ligne_1[s_infos_gen.ordre_sz[i].index]->afficher();
		}
	}
	else {
		for (i = 0; i < NBR_LIGNES_MAX; i++)
		{
			//i2 = s_infos_gen.ordre_sz[i].index;
			//ordre_cour = s_infos_gen.ordre_sz[i].ordre;
			ligne_1[s_infos_gen.ordre_sz[i].index]->afficher();
		}
	}

	// on v�rifie si la touche escape a �t� enfonc�e
	if (touche[27] == TRUE)
	{
		// on stoppe la boucle
		b_actif = FALSE;
	}

	// permet de s'amuser avec les options de blending
	// pour ce faire, il faut d�-commenter une ligne � la fin du fichier "Ligne3D1.cpp" (c'est expliqu�)
	for (i = 48; i < 58; i++)
	{
		if (touche[i] == TRUE)
			s_infos_gen.prem = blend_sz(i - 47);
	}

	for (i = 96; i < 106; i++)
	{
		if (touche[i] == TRUE)
			s_infos_gen.deux = blend_sz(i - 95);
	}

	// on interverti nos buffers
	// il faut savoir qu'avant d'�tre affich�s � l'�cran, tous les �l�ments d'une sc�ne sont dessin�s un � un dans un buffer
	// ensuite l'adresse de ce buffer est interverti avec celle du buffer qui est visible � l'�cran
	// cela permet d'�viter quelques effets visuels d�rangeant (il serait alors possible de voir � quel moment chaque �l�ment
	// est affich�)
	SwapBuffers(DC);

	//on r�initialise notre compteur (temps entre deux affichages)
	temps_2 = temps_1;

	return TRUE;
}

// comme son nom l'indique, elle permet de fermer correctement le programme en vidant de la m�moire les diff�rents
// �l�ments qu'il a fallu cr�er
void Shutdown()
{
	if (fullscreen)
	{
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(TRUE);
	}

	wglMakeCurrent(NULL, NULL);

	wglDeleteContext(RC);
	RC = NULL;

	ReleaseDC(hWnd, DC);
	DC = NULL;

	DestroyWindow(hWnd);
	hWnd = NULL;

	UnregisterClass(NOM_APP, hInstance);
	hInstance = NULL;
}

// charge une texture de type PNG dans la variable indiqu�e dans le param�tre "texturesz"
// utilise une partie du code de la lib "glpng" (--> glpng.c)
int LoadTexture(unsigned& texture_sz, char* fichier_sz)
{
	pngInfo info;

	glGenTextures(1, &texture_sz);
	glBindTexture(GL_TEXTURE_2D, texture_sz);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if (pngLoad(fichier_sz, PNG_BUILDMIPMAPS, PNG_ALPHA, &info)) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

// charge une texture de type BMP dans la variable indiqu�e dans le param�tre "texturesz"
int LoadTextureBMP(unsigned& texture_sz, char* fichier_sz)
{
	// partie du code provient de : http://www.cppfrance.com/code.aspx?ID=11002

	FILE* fichier;
	PropPicture pStruct;

	// on ouvre le fichier
	fichier = fopen(fichier_sz, "rb");

	// on v�rifie qu'il est bien ouvert
	if (!fichier)
		return FALSE;

	// et que les informations contenues dans l'ent�te sont correctes
	if (fread(pStruct.Header, 1, 0x36, fichier) != 0x36)
		return FALSE;

	if (pStruct.Header[0] != 'B' || pStruct.Header[1] != 'M')
		return FALSE;

	if (CTOI(pStruct.Header[0x1E]) != 0)
		return FALSE;

	if (CTOI(pStruct.Header[0x1C]) != 24)
		return FALSE;

	// R�cup�re les infos du fichier
	pStruct.DataPos = CTOI(pStruct.Header[0x0A]);
	pStruct.DataSize = CTOI(pStruct.Header[0x22]);

	// R�cup�re les infos de l'image
	pStruct.Width = CTOI(pStruct.Header[0x12]);
	pStruct.Height = CTOI(pStruct.Header[0x16]);
	pStruct.Type = GL_UNSIGNED_BYTE;
	pStruct.Format = GL_RGB;
	pStruct.Components = 3;

	// !!!!
	if (pStruct.DataSize == 0)
		pStruct.DataSize = pStruct.Width * pStruct.Height * pStruct.Components;

	if (pStruct.DataPos == 0)
		pStruct.DataPos = 0x36;

	// charge l'image
	fseek(fichier, pStruct.DataPos, 0);

	pStruct.Data = new unsigned char[pStruct.DataSize];

	if (!pStruct.Data)
		return FALSE;

	if (fread(pStruct.Data, 1, pStruct.DataSize, fichier) != pStruct.DataSize)
	{
		delete pStruct.Data;
		fclose(fichier);
		return FALSE;
	}

	fclose(fichier);

	// inverse R et B
	// dans un fichier bmp, les couleurs sont enregistr�e dans cet ordre : bgr
	// pour qu'opengl puisse les lire correctement, il faut les remettre dans cet ordre : rgb
	unsigned char t;
	for (int x = 0; x < (pStruct.Width * pStruct.Height); x++)
	{
		t = pStruct.Data[x * 3];
		pStruct.Data[x * 3] = pStruct.Data[x * 3 + 2];
		pStruct.Data[x * 3 + 2] = t;
	}

	// on g�n�re une texture opengl
	glGenTextures(1, &texture_sz);

	glBindTexture(GL_TEXTURE_2D, texture_sz);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, pStruct.Components, pStruct.Width, pStruct.Height, 0,
		pStruct.Format, pStruct.Type, pStruct.Data);

	// on retourne TRUE si tout s'est bien pass�
	return TRUE;
}

// intialisation des textures
int InitTextures()
{
	int i = 0, i2 = 1, i3 = 0;

	// on charge les textures

	if (!LoadTexture(s_infos_gen.tex_lettres_vertes, "fontes_vertes_alpha.png"))
		return FALSE;

	if (!LoadTexture(s_infos_gen.tex_lettres_blanches, "fontes_blanches_alpha.png"))
		return FALSE;

	if (!LoadTextureBMP(s_infos_gen.tex_part_1, "nuage1.bmp"))
		return FALSE;

	// on cr�e une liste d'affichage pour chaque case (0 -> 55)
	// l'id�e de la liste d'affichage a �t� abandonn�e pour plusieurs raisons
	// n�anmoins, je laisse le code pour ceux que �a int�resse
	// une liste d'affichage permet de pr�-compiler une s�rie d'instruction pour ensuite
	// les appeler d'une simple fonction (gain de temps et de vitesse)
	// mais ces listes ne permettent plus un contr�le absolu sur les �l�ments qu'elle affiche

	// � la place, cette boucle va se charger de g�n�rer les coordonn�es de texture qui vont servir � afficher
	// les diff�rents caract�res des lettres
	for (i = 0; i < 56; i++)
	{
		/*
		s_infos_gen.lst_lettres_vertes[i] = glGenLists(1);

		// on commence notre nouvelle liste
		glNewList(s_infos_gen.lst_lettres_vertes[i],GL_COMPILE);

			// on sp�cifie la texture
			glBindTexture(GL_TEXTURE_2D, s_infos_gen.tex_lettres_vertes);

			// les coordonn�es de cette texture ainsi que le polygone sur lequel elle sera plac�e
			glBegin(GL_QUADS);

				glTexCoord2f(double(0.0976 * i3), double(0.113 * i2));
				glVertex3d( 0.0, 0.0, 0.0);

				glTexCoord2f(double(0.0976 * i3), double(0.113 * (i2-1)));
				glVertex3d( 0.0, 1.0, 0.0);

				glTexCoord2f(double(0.0976 * (i3+1)), double(0.113 * (i2-1)));
				glVertex3d( 1.0, 1.0, 0.0);

				glTexCoord2f(double(0.0976 * (i3+1)), double(0.113 * i2));
				glVertex3d( 1.0, 0.0, 0.0);

			glEnd();

		// la liste ce termine ici
		glEndList();
		*/

		// on enregister les coordonn�es
		s_infos_gen.info_tex_vertes_sz[i].x1 = float(0.0976 * i3);
		s_infos_gen.info_tex_vertes_sz[i].y1 = float(0.113 * i2);

		s_infos_gen.info_tex_vertes_sz[i].x2 = float(0.0976 * i3);
		s_infos_gen.info_tex_vertes_sz[i].y2 = float(0.113 * (i2 - 1));

		s_infos_gen.info_tex_vertes_sz[i].x3 = float(0.0976 * (i3 + 1));
		s_infos_gen.info_tex_vertes_sz[i].y3 = float(0.113 * (i2 - 1));

		s_infos_gen.info_tex_vertes_sz[i].x4 = float(0.0976 * (i3 + 1));
		s_infos_gen.info_tex_vertes_sz[i].y4 = float(0.113 * i2);

		// on incr�mente i3 (sp�cifie la colonne dans laquelle on se trouve)
		i3++;

		// on v�rifie que i3 ne d�passe pas 3
		if (i3 > 9)
		{
			// on remet i3 � z�ro (colonne)
			i3 = 0;

			// on passe � la ligne suivante
			i2++;
		}
	}

	return TRUE;
}

// on initialise le programme (chargement des textures, on d�termine certains param�tres,...)
int InitGL()
{
	// on sp�cifie le type de texture qu'on utilise
	glEnable(GL_TEXTURE_2D);

	// on initialise les textures
	if (!InitTextures())
		return FALSE;

	// la couleur par laquelle la sc�ne sera effac�e avant chaque rendu
	// (peut �tre per�u comme le fond)
	// ici, noir
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// on active le "blending"
	glEnable(GL_BLEND);

	// et on sp�cifie son mode
	glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);

	//glDisable(GL_DEPTH_TEST);
	//glClearDepth(1.0);
	//glDepthFunc(GL_LESS);
	//glEnable(GL_DEPTH_TEST);

	glShadeModel(GL_SMOOTH);

	// calcul de la perspective (la meilleure)
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// si on arrive jusqu'ici, on retourne TRUE (tout s'est bien pass�)
	return TRUE;
}

// ReSize : permet de redimensionner la taille de l'affichage
void ReSize(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45, (double)width / (double)height, 1, 100000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Cette fonction est appel�e par Windows (c'est via celle-ci que tous les messages sont envoy�s � l'application)
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM	lParam)
{
	switch (uMsg)
	{
	case WM_SYSCOMMAND:
	{
		switch (wParam)
		{
		case SC_SCREENSAVE:
		case SC_MONITORPOWER:
			return 0;
		}
		break;
	}

	case WM_CLOSE:
	{
		b_actif = FALSE;
		return 0;
	}

	case WM_KEYDOWN:
	{
		touche[wParam] = TRUE;
		return 0;
	}

	case WM_KEYUP:
	{
		touche[wParam] = FALSE;
		return 0;
	}

	case WM_SIZE:
	{
		ReSize(LOWORD(lParam), HIWORD(lParam));
		return 0;
	}
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

// CreateGLWindow : cr�e la fen�tre sur laquelle on va pouvoir dessiner
BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	WNDCLASS	wc;
	DWORD		dwExStyle;
	DWORD		dwStyle;
	RECT		WindowRect;
	WindowRect.left = (long)0;
	WindowRect.right = (long)width;
	WindowRect.top = (long)0;
	WindowRect.bottom = (long)height;
	fullscreen = fullscreenflag;

	hInstance = GetModuleHandle(NULL);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = NOM_APP;

	RegisterClass(&wc);

	if (fullscreen)
	{
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = width;
		dmScreenSettings.dmPelsHeight = height;
		dmScreenSettings.dmBitsPerPel = bits;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
	}

	if (fullscreen)
	{
		dwExStyle = WS_EX_APPWINDOW;
		dwStyle = WS_POPUP;
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle = WS_OVERLAPPEDWINDOW;
	}

	ShowCursor(TRUE);

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);

	hWnd = CreateWindowEx(dwExStyle, NOM_APP, title, dwStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		0, 0, WindowRect.right - WindowRect.left, WindowRect.bottom - WindowRect.top,
		NULL, NULL, hInstance, NULL);

	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		bits,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		16,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	DC = GetDC(hWnd);

	SetPixelFormat(DC, ChoosePixelFormat(DC, &pfd), &pfd);

	RC = wglCreateContext(DC);

	wglMakeCurrent(DC, RC);

	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);

	return TRUE;
}

// WinMain : c'est la fonction appel�e lors du lancement du programme
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// contient les messages provenant de Windows
	MSG	msg;

	// we create the window
	if (!CreateGLWindow(NOM_APP_FENETRE, 1024, 768, 32, fullscreen))
	{
		// there was a problem creating the window
		MessageBox(HWND_DESKTOP, "Unable to create main window", "Error", MB_OK | MB_ICONEXCLAMATION);

		// on quitte le programme
		return -1;
	}

	// the window is created, on continue

	// we initialize the program
	if (!InitGL())
	{
		// there was a problem initializing
		MessageBox(HWND_DESKTOP, "Impossible d'initialiser le programme", "Erreur", MB_OK | MB_ICONEXCLAMATION);

		// we quit the program
		return -1;
	}

	// on cr�e notre tableau qui va contenir l'index et la coo z de chaque ligne
	s_infos_gen.ordre_sz = new ordre_z[NBR_LIGNES_MAX];

	// on charge les lignes
	for (int i = 0; i < NBR_LIGNES_MAX; i++)
	{
		ligne_1[i] = new Ligne3D1(double((rand() % 200) - 100), double((rand() % 200) - 100), double((rand() % 200) - 100), &s_infos_gen, i);
	}

	// on redimensionne l'affichage (en fait ici on l'initialise, cette fonction va permettre de redimensionner
	// l'affichage pendant que le programme tourne)
	ReSize(1024, 768);

	// tout s'est bien pass�, on active la boucle
	b_actif = TRUE;

	// on commence la boucle
	while (b_actif)
	{
		// on intercepte les messages envoy�s au programme
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// on v�rifie si ce n'est pas une demande de fermeture
			if (msg.message == WM_QUIT)
			{
				// oui, on stoppe la boucle
				b_actif = FALSE;
			}
			else
			{
				// non, on passe le message
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			// on dessine la sc�ne
			RePaint();
		}
	}

	// on d�charge tout ce qu'il faut d�charger
	Shutdown();

	// on quitte le programme
	return (msg.wParam);
}