#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


int main(int argc,char *argv[]){
    
    int status,err;

    char nomFichier[30];
    strcpy(nomFichier,argv[1]);

    char fichierObjet[30];
    strcpy(fichierObjet,nomFichier);
    fichierObjet[strlen(nomFichier)-1]='o';

    char fichierExec[30];
    strcpy(fichierExec,nomFichier);
    fichierExec[strlen(nomFichier)-2]='\0';
   
    //Creation de le processus p1
    int p1=fork();
    
    if (p1==-1) {
        printf("Erreur dans la creation du processus p1 (Compilation)\n");
        exit(EXIT_FAILURE);
    }
    if(p1==0){  
        printf("Processus p1 a lance la compilation ...\n");
        err=execlp("cc","cc",nomFichier,"-c",NULL);
        printf("Erreur de compilation %d\n",err);     
        exit(EXIT_FAILURE);
    }
    
    waitpid(p1,&status,0);

    if(status>>8!=0){
    printf("\nLe processus p1: %d n'a pas créé le module objet\n",p1);
    exit(EXIT_FAILURE);
    }
    printf("Fin de compilation\n\n");

    //Creation de le processus p1
    int p2=fork();

    if(p2==-1){
          printf("Erreur dans la creation du processus p2 (Edition de lien)\n");
          exit(EXIT_FAILURE);
    } 
    if(p2==0){
        printf("Debut d'edition de lien...\n");
        err=execlp("cc","cc",fichierObjet,"-o",fichierExec,NULL);
        printf("Erreur dans la creation du fichier executable %d\n",err);     
        exit(EXIT_FAILURE);
    }
         
    waitpid(p2,&status,0);

    if(status>>8!=0){
    printf("\nLe processus p2: %d n'a pas créé le module objet\n",p2);
    exit(EXIT_FAILURE);
    }

    printf("fin d'edition des liens\n\n");
    printf("\n Lancement du resultat du programme executable:\n"); 

    char exec[30]="./";
    strcat(exec,fichierExec);
        
    err=execlp(exec,fichierExec, NULL);                                                                                          
    printf("Erreur d'execution %d\n",err);    

    exit(EXIT_SUCCESS);
}