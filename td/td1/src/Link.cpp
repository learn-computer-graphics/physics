/*=============================================================*/
/*= E.Incerti (incerti@univ-eiffel.fr)                        =*/
/*= M2/IMAC3 - ANIMATION / MOTEUR PHYSIQUE                    =*/
/*= Système Masses/Ressort en dimension 1 : module liaison    =*/
/*=============================================================*/

#include <g2x.h>

#include <PMat.h>
#include <Link.h>

/*================================================*/
/*= FONCTIONS DE CREATION DES MODULES DE LIAISON =*/
/*================================================*/

/*! Création d'un module Force Constante (exp. Gravité) !*/
extern void frcConst(Link* L, double force_const)
{
  /* param�tres pour le moteur physique */
  L->type   = _FRC_CONST;
  L->frc    = force_const;
  L->k      = 0.;
  L->z      = 0.;
  L->s      = 0.;
  L->l      = 0.;
  L->on_off = true;
}

/*! Création d'un ressort linéaire (de Hook) !*/
extern void ressort(Link* L, double k)
{
  L->type   = _RESSORT;
  /* paramètres pour le moteur physique */
  L->k      = k ;
  L->z      = 0.;
  L->s      = 0.;
  L->l      = 0.;
  L->on_off = true;
}
  
/*! Création d'un frein cinétique linéaire !*/
extern void frein(Link* L, double z)
{
  L->type = _FREIN;
  /* paramères pour le moteur physique */
  L->k      = 0.;
  L->z      = z ;
  L->s      = 0.;
  L->on_off = true;
}

/*! Création d'un ressort+frein !*/
extern void ressortFrein(Link* L, double k, double z)
{
  L->type = _RESSORT_FREIN;
  /* paramètres pour le moteur physique */
  L->k      = k ;
  L->z      = z ;
  L->s      = 0.;
  L->l      = 0.;
  L->on_off = true;
}

/*! Création d'une butée visco-élastique seuillée !*/
extern void rfButee(Link *L, double k, double z, double s)
{
  L->type = _RF_BUTEE;
  /* paramètres pour le moteur physique */
  L->k      = k ;
  L->z      = z ;
  L->s      = s ; /* seuil de distance pour détachement   */
  L->l      = 0.;
  L->on_off = true;
}


/*! Création d'une liaison de rupture avec condition sur l'élongation !*/
extern void rfCondPos(Link *L, double k, double z, double s)
{
  L->type = _CONDIT_RF;
  /* paramètres pour le moteur physique */
  L->k      = k ;
  L->z      = z ;
  L->s      = s ; /* seuil d'elongation pour rupture      */
  L->l      = 0.;
  L->on_off = true;
}


/*! Connexion d'une Liaison entre 2 points Mat !*/
/* pas utilisé dans sytèmes de particules       */
/* ça sert surtout pour les topologies fixes    */
extern void connect(PMat *M1, Link *L, PMat *M2)
{
  L->M1=M1;
  L->M2=M2;
  if (M1==NULL || M2==NULL) return;
  L->l = (M2->pos-M1->pos);
}
