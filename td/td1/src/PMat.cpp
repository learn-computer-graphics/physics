/*=============================================================*/
/*= E.Incerti (incerti@univ-eiffel.fr)                        =*/
/*= M2/IMAC3 - ANIMATION / MOTEUR PHYSIQUE                    =*/
/*= Système Masses/Ressort en dimension 1 : module matériel   =*/
/*=============================================================*/

#include <PMat.h>

/*! Création d'une masse libre !*/
/*  Création d'une particule libre : attribution des param�tres de position et masse (vitesse nulle)  */
/*  avec l'intégrateur LeapFrog */
extern void massLF(PMat *M, double pos, double x, double m)
{
  M->type = _PARTICULE;
  /* paramètres pour le moteur physique */
  M->pos = pos;
  M->vit = 0.;
  M->frc = 0.;
  M->m = m;
  /* paramètres graphiques */
  M->x = x;
  M->col = G2Xb;
}

/* variante, avec l'intégrateur Euler Explicite */
extern void massEE(PMat *M, double pos, double x, double m)
{
  M->type = _PARTICULE;
  /* paramètres pour le moteur physique */
  M->pos = pos;
  M->vit = 0.;
  M->frc = 0.;
  M->m = m;
  /* paramètres graphiques */
  M->x = x;
  M->col = G2Xg;
}

/*! Création d'une masse fixe !*/
extern void fixe(PMat *M, double pos, double x)
{
  M->type = _POINTFIXE;
  /* paramètres pour le moteur physique */
  M->pos = pos;
  M->vit = 0.;
  M->frc = 0.;
  M->m = 1.; /* juste pour le dessin */
  /* paramètres graphiques */
  M->x = x;
  M->col = G2Xr;
}
