/*=================================================================*/
/*= E.Incerti - eric.incerti@univ-eiffel.fr                       =*/
/*= Université Gustave Eiffel                                     =*/
/*= Code "corde"              =*/
/*=================================================================*/

#include <g2x.h>
#include <PMat.h>
#include <Link.h>

/* tailles de la fenêtre (en pixel) */
static int WWIDTH=512, WHEIGHT=512;
/* limites de la zone reelle associee a la fenetre */
static double wxmin=-10.,wymin=-10.,wxmax=+10.,wymax=+10.;

static double h;            /* 1./Fe      */
static int Fe;           /* fréquence d'échantillonnage        */
static int Fa=1;         /* on affiche 1 echantillon sur Faff  */
static double m,k,z;        /* masse, rigidité, viscosité               */ 
static char P_ou_F = 'f'; /* type de perturbation initiale      */
static double tempo=0.02;   /* temporisation de la simul          */ 

static PMat M,S;
static Link L;

void reset()
{	
  M.pos=M.vit=M.frc=0.;
  switch (P_ou_F)
  {
    case 'P' : case 'p' : /* contrainte initiale : particule déplacée */
      M.pos=.5;
      break;
    case 'F' : case 'f' : /* Autre forme de contrainte initiale : impulsion de force */
      M.frc=1.*SQR(Fe);   /* notez le calibrage par Fe */
      break;
  }
}


/*=  Constructon du modèle  =*/
void modeleur()
{
  Fe= 100;            /* paramètre du simulateur Fe=1/h                  */ 
  h = 1./Fe;
  m = 1.;             /* la plupart du temps, toutes les masses sont � 1 */
  k = 0.100*m*SQR(Fe);/* raideurs   -> � multiplier par m*Fe�            */
  z = 0.005*m*Fe;     /* viscosir�s -> � multiplier par m*Fe             */
  /*! les objets : une masse mobile (M) reli�e � un pt. fixe (S)
   *               par un ressort-frein (L)                            !*/
  fixe(&S,0.,0.);
  massLF(&M,0.,0.,m); 
  /* MassEE(&M,0.,+2.,m); */ /* la m�me chose, mais avec Euler Explicite */
  
  ressortFrein(&L,k,z);
  /* connection du ressort entre les 2 masses */
  connect(&M,&L,&S);  
  reset();
}


/* la fonction d'initialisation */
static void init(void)
{  
	/* zone graphique reelle associee a la fenetre                 */
  /* si cette fonction n'est pas appelée, les valeurs par défaut */
  /* sont (-1.,-1)->(+1.,+1.)                                    */
	g2x_SetWindowCoord(wxmin,wymin,wxmax,wymax);
	modeleur();

	/* les paramètres règlables */
	g2x_CreateScrollv_i("Fa",&Fa,1,20,1,"Fa");
	g2x_CreateScrollv_d("tmp",&tempo,0.,.1,1.,"tempo");
	g2x_CreateScrollh_d("k",&k,k*0.01,k*5.,1,"k");
	g2x_CreateScrollh_d("z",&z,z*0.01,z*5.,1,"z");
  g2x_CreatePopUp("reset",reset,"reset");
}

/* la fonction de dessin */
static void draw()
{
	g2x_SetRefreshFreq(Fa);
  switch (M.type)
  {
    case _PARTICULE:
      M.drawdot();
      break;
    case _POINTFIXE:
      M.drawcirc();
    default:
      break;
  }
  switch (S.type)
  {
    case _PARTICULE:
      S.drawdot();
      break;
    case _POINTFIXE:
      S.drawcirc();
    default:
      break;
  }
  switch(L.type) {
    case _FRC_CONST:
      L.drawFrc();
      break;
    case _RESSORT:
    case _FREIN:
    case _RESSORT_FREIN:
    case _RF_BUTEE:
    case _CONDIT_RF:
      L.drawM1M2();
      break;
    default:
      break;
  }
	L.k=k;
  L.z=z; /* mise à jour des paramètres => scrollbar */
}


/* la fonction d'animation */
static void anim()
{
  /* d'abord les Link */
  switch(L.type) {
    case _RESSORT:
      ressort(&L,k);
      break;
    case _FRC_CONST:
      frcConst(&L,L.frc);
      break;
    case _FREIN:
      frein(&L,z);
      break;
    case _RESSORT_FREIN:
      ressortFrein(&L,k,z);
      break;
    case _RF_BUTEE:
      rfButee(&L,k,z,L.s);
      break;
    case _CONDIT_RF:
      rfCondPos(&L,k,z,L.s);
      break;
    default:
      break;
  }

  switch(M.type) {
    case _PARTICULE:
      M.leapfrog(h);
      break;

    case _POINTFIXE:
      M.pointfixe(h);
      break;
    
    default:
      break;
  }

  switch (S.type)
  {
    case _PARTICULE:
      S.leapfrog(h);
      break;

    case _POINTFIXE:
      S.pointfixe(h);
      break;
    
    default:
      break;
  }

  g2x_tempo(tempo); /* temporisation, si ça va trop vite */
}

/* la fonction de sortie */
static void quit()
{
	fprintf(stderr,"Bye !\n\n");
}

/***************************************************************************/
/* La fonction principale : NE CHANGE JAMAIS                               */
/***************************************************************************/
int main(int argc, char **argv)
{
	/* creation de la fenetre - titre et tailles (pixels) */
	g2x_InitWindow(*argv,WWIDTH,WHEIGHT);
	g2x_SetInitFunction(init); /* fonction d'initialisation */
	g2x_SetDrawFunction(draw); /* fonction de dessin        */
	g2x_SetAnimFunction(anim); /* fonction d'animation      */
	g2x_SetExitFunction(quit); /* fonction de sortie        */
	/* lancement de la boucle principale */
  return g2x_MainStart();
}
