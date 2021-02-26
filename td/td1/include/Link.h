/*=============================================================*/
/*= E.Incerti (incerti@univ-eiffel.fr)                        =*/
/*= M2/IMAC3 - ANIMATION / MOTEUR PHYSIQUE                    =*/
/*= Système Masses/Ressort en dimension 1 : module liaison    =*/
/*=============================================================*/

#ifndef _LINK_
#define _LINK_

#include <PMat.h>

/* Module produisant une force constante -- 'équivalent' du point fixe */
#define _FRC_CONST 0
/* Ressort linéaire (de Hook) - force proportionnelle à l'élongation */
#define _RESSORT 1
/* Frein linéaire - force proportionnelle à la vitesse relative des points */
#define _FREIN 2
/* Ressort+Frein intégrés */
#define _RESSORT_FREIN 3
/* Liaison condtionnelle de rupture -- condition sur l'élong. ou la force  */
#define _CONDIT_RF 4
/* Butée conditionelle : ressort frein inactif au-delà d'un seuil de dist. */
#define _RF_BUTEE 5

struct Link
{
  int type; /* type pour usages divers */

  double k;                      /* raideur pour les ressorts          */
  double l;                      /* longueur à vide pour les ressorts  */
  double z;                      /* viscosité pour les freins          */
  double s;                      /* seuil pour les liens conditionnels */
  PMat *M1, *M2;                 /* les 2 PMat de branchement          */
  double frc;                   /* force à distribuer sur M1 et M2    */
  bool on_off;                  /* flag d'activité     */

  /*! Algorithme Force Constante             !*/
  /*  1 seul point mat. M1 ou M2, au choix... */
  void algoFrcConst()
  {
    PMat* M=(M1?M1:M2);
    M->frc += frc;
  }

  /*! Algo. ressort de Hook (linéaire)                            !*/
  /* produit une force : F=k*(d-l0).AB                             */
  /* où (d-l0) est l'allongement et AB le vecteur inter particules */
  void algoRessort()
  {
    double d = M2->pos-M1->pos;
    double f = k*(d-l);
    M1->frc += f;
    M2->frc -= f;
  }
    
  /*! Algo. frein cinétique                           !*/
  /* produit une force : F=z*(V2-V1)                   */
  /* où (V2-V1) est la vitesse relative des particules */
  void algoFrein()
  {
    double f = z*(M2->vit-M1->vit);
    M1->frc += f;
    M2->frc -= f;
  }

  /*! Algo. ressort+frein         !*/
  /*combine les 2 algos précédents */
  void algoRessortFrein()
  { 
    double d = M2->pos-M1->pos;
    double f = k*(d-l) + z*(M2->vit-M1->vit);
    M1->frc += f;
    M2->frc -= f;
  }  

  /*! Algo. butée visco-élastique                    !*/
  /*! active uniquement si dist. < seuil             !*/
  /* comme précédemment mais avec un seuil d'activit� */
  void algoRF_Butee()
  { 
    double d = M2->pos-M1->pos;
    if (d>s) return;

    double f = k*(d-l)+z*(M2->vit-M1->vit);
    M1->frc += f;
    M2->frc -= f;
  }  


  /*! Algo. lien visco-élastique "cassable"          !*/
  /*! si d>seuil, la liaison devient inactive        !*/
  void algoRF_CondPos()
  { /* si la liaison est déjà cassée : rien */
    if (!on_off) return;

    double d = M2->pos-M1->pos;
    /* si l'allongement est trop fort : la liaison casse */
    if (d>s) { on_off=0; return; }

    double f = k*(d-l)+z*(M2->vit-M1->vit);
    M1->frc += f;
    M2->frc -= f;
  }

  /* quelques couleurs (cf. <g2x_Colors.h>) */
  G2Xcolor Lcols[8]={G2Xr,G2Xo,G2Xy,G2Xg,G2Xb,G2Xc,G2Xm,G2Xk};

  void drawM1M2()
  {
    g2x_Line(M1->x,M1->pos,M2->x,M2->pos,Lcols[type],1);
  }


  void drawFrc()
  {
    PMat* M=(M1!=NULL?M1:M2);
    g2x_Line(M->x,M->pos,M->x,M->pos+0.001*frc,Lcols[type],1);
  }

};

/* les  constructeurs */
/*! Création d'un module Force Constante (exp. Gravité)*/
void frcConst(Link *L, double frc);

/*! Création d'un ressort linéaire (de Hook) */
void ressort(Link *L, double k);

/*! Création d'un frein cinétique linéaire */
void frein(Link *L, double z);

/*! Création d'un ressort+frein : les 2 précédents combinés */
void ressortFrein(Link *L, double k, double z);

/*! Création d'une butée visco-élastique seuillée, non linéaire */
void rfButee(Link *L, double k, double z, double s);

/*! Création d'une liaison de rupture avec condition sur l'élongation */
void rfCondPos(Link *L, double k, double z, double s);

/*! Connexion d'une Liaison entre 2 points Mat */
void connect(PMat *M1, Link *L, PMat *M2);

#endif
