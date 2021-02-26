/*=============================================================*/
/*= E.Incerti (incerti@univ-eiffel.fr)                        =*/
/*= M2/IMAC3 - ANIMATION / MOTEUR PHYSIQUE                    =*/
/*= Système Masses/Ressort en dimension 1 : module matériel   =*/
/*=============================================================*/

#ifndef _PMAT_2
#define _PMAT_2

#include <g2x.h>

#define _POINTFIXE 0
#define _PARTICULE 1

struct PMat
{
  int type; /* type pour usages divers */

  double m;   /* paramètre de masse */
  double pos; /* position courante */
  double vit; /* vitesse  courante */
  double frc; /* buffer de force */

  /*! Algorithme de la masse libre 2D (2� loi de Newton)    !*/
  /*! intégration : leapfrog                                !*/
  void leapfrog(double h)
  {
    vit += h * frc / m; /* 1ere intégration : vitesse   V(n+1)=V(n)+h*F(n)/m - EXplicite */
    pos += h * vit;        /* 2e intgration : position  X(n+1)=X(n)+h*V(n+1) - IMplicite */
    frc = 0.;                 /* on vide le buffer de force */
  }


  /*! intégration : Euler Explicite                         !*/
  void eulerexp(double h)
  {
    pos += h * vit;        /* 1ere intégration : position  X(n+1)=X(n)+h*V(n)   - EXplicite */
    vit += h * frc / m; /* 2e intégration : vitesse   V(n+1)=V(n)+h*F(n)/m - EXplicite */
    frc = 0.;                 /* on vide le buffer de force */
  }

  /*! Algorithme du point fixe (position constante)         !*/
  void pointfixe(double h)
  { /* ne fait rien, à part vider le buffer de force       */
    frc = 0.; 
    /* ne sert que si on veut "figer" une particule mobile */
    vit = 0.; 
  }

  void drawcirc()
  { /* rayon indexé sur la masse */
    g2x_Circle(x,pos,0.2*m,col,2);
  }

  void drawdot()
  { /* rayon indexé sur la masse */
    g2x_FillCircle(x,pos,0.2,col);
  }

  G2Xcolor col; /* couleur RGBA (4 float) */
  double x;     /* 2ème coord. pour positionnement 2D */
};

/*! Création d'une particule mobile !*/
/* avec l'intégrateur LeapFrog */
void massLF(PMat *M, double pos, double x, double m);
/* variante, avec l'intégrateur Euler Explicite */
void massEE(PMat *M, double pos, double x, double m);

/*! Création d'une masse fixe !*/
void fixe(PMat *M, double pos, double x);

#endif
