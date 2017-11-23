#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

const int MAX_X=20;
const int MAX_Y=20;

struct grille_cell
{
    int tx,ty;
    int nb_viv;
    int nb_mort;
    int etat[MAX_X][MAX_Y];
};

void init_grille(struct grille_cell &jeu)
{
    int i,j;
    cout<<"Entrez les dimensions du jeu."<<endl<<"Nombre de lignes";
    cin>>jeu.tx;
    cout<<"Nombre de colonnes";
    cin>>jeu.ty;
    cout<<"Entrez le nombre de cellules vivantes.";
    cin>>jeu.nb_viv;
    jeu.nb_mort=(jeu.tx*jeu.ty)-jeu.nb_viv;
    for(i=0;i<=jeu.tx+1;i++)
    {
       for(j=0;j<=jeu.ty+1;j++)
       {
           jeu.etat[i][j]=0;
       }
    }
}

void place_cell_vivantes (struct grille_cell &jeu)
{
    int i,c,l;
    for (i=0;i<jeu.nb_viv;i++)
    {
        do
        {
            l=rand()%jeu.tx+1;
            c=rand()%jeu.ty+1;
        }
        while(jeu.etat[l][c]!=0);
        jeu.etat[l][c]=1;
    }
}

void affiche_grille (struct grille_cell jeu)
{
    int i,j;
    for(i=1;i<=jeu.tx;i++)
    {
       for(j=1;j<=jeu.ty;j++)
       {
           if(jeu.etat[i][j])
           {
               cout << "■";
           }
           else
           {
               cout <<"□";
           }

       }cout<<endl;
    }
    cout<<endl;
}

void etat_suivant (struct grille_cell &t)
{
    int i,j,c,l;
    struct grille_cell t1;
    int voisin[MAX_X][MAX_Y];
    for(i=0;i<t.tx+2;i++)
    {
        for(j=0;j<t.ty+2;j++)
        {
        voisin[i][j]=0;
        }
    }
    for(i=1;i<=t.tx;i++)
    {
       for(j=1;j<=t.ty;j++)
       {
            for(l=i-1;l<=i+1;l++)
            {
                for(c=j-1;c<=j+1;c++)
                {
                    if(t.etat[l][c]==1)
                    {
                        voisin[i][j]=voisin[i][j]+1;
                        if((l==i)&&(c==j))
                        {
                            voisin[i][j]=voisin[i][j]-1;
                        }
                    }
                }
            }

       }

    }
    for(i=1;i<=t.tx;i++)
    {
       for(j=1;j<=t.ty;j++)
       {
          if (t.etat[i][j]==1)
          {
              if((voisin[i][j]==0)||(voisin[i][j]==1)||(voisin[i][j]>=4))
                {
                    t1.etat[i][j]=0;
                }
              else if ((voisin[i][j]==2)||(voisin[i][j]==3))
              {
                t1.etat[i][j]=1;
              }
              else{t1.etat[i][j]=0;}
          }
          else
          {
              if(voisin[i][j]==3)
              {
                  t1.etat[i][j]=1;
              }
              else{t1.etat[i][j]=0;}
          }
    }
    }

     for(i=1;i<=t.tx;i++)
    {
       for(j=1;j<=t.ty;j++)
       {
           t.etat[i][j]=t1.etat[i][j];

       }

    }
}

int main()
{
    int c;
    srand(time(NULL));
    int i,j;
    struct grille_cell jeu;
    init_grille(jeu);
    place_cell_vivantes(jeu);
    affiche_grille(jeu);

    do
    {
        etat_suivant(jeu);
        affiche_grille(jeu);

            cout<<"Voulez vous voir la suite ? Entrez 1 si oui et 0 si non."<<endl;
            cin>>c;


    }
    while((jeu.nb_viv>1)&&(c==1));

    return 0;


}
