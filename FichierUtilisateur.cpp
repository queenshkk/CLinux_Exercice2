#include "FichierUtilisateur.h"
#include <sys/types.h>
#include <unistd.h> // read, write, lseek, close
#include <stdio.h> // perror
#include <fcntl.h> // open
#include <string.h>     // strlen, strncpy, strncmp

int estPresent(const char* nom)
{
  UTILISATEUR u;
  int fd, rc, pos=1;

  if((fd = open(FICHIER_UTILISATEURS,O_RDONLY))== -1)
  {
      perror("Erreur de open()");
      return -1;
  }
  
  while ((rc = read(fd,&u, sizeof(UTILISATEUR))) == sizeof(UTILISATEUR))
  {  
    if(strcmp(nom, u.nom)==0)
    {
      close(fd);
      return pos;
    }
   
    pos++;

  }

  if (rc == -1)
  {
    perror("Erreur de read");
    close(fd);
    return -1;
  }
  
  close(fd);
  return 0;

}

////////////////////////////////////////////////////////////////////////////////////
int hash(const char* motDePasse)
{
  int somme=0, i=0;

   while (i<strlen(motDePasse))
    {
        somme =somme+(int)motDePasse[i];
        i++;
    }

    somme=somme%97;
    return somme;
}

////////////////////////////////////////////////////////////////////////////////////
void ajouteUtilisateur(const char* nom, const char* motDePasse)
{
  int fd, wr,i=0;

  UTILISATEUR u;

  if((fd = open(FICHIER_UTILISATEURS,O_WRONLY | O_APPEND | O_CREAT, 0644)) == -1)
  {
      perror("Erreur de open()");
      return;
  }

  while (i < 19 && nom[i] != '\0') {
    u.nom[i] = nom[i];
    i++;
  }
  u.nom[i] = '\0';

  u.hash=hash(motDePasse);

  
  if ((wr = write(fd, &u, sizeof(UTILISATEUR)))!= sizeof(UTILISATEUR)) {
    perror("Erreur write");
  }

  close(fd);

}

////////////////////////////////////////////////////////////////////////////////////
int verifieMotDePasse(int pos, const char* motDePasse)
{
  int fd, ha, off, rc;
  UTILISATEUR u;

  if((fd = open(FICHIER_UTILISATEURS,O_RDONLY))== -1)
  {
      perror("Erreur de open()");
      return -1;
  }  

  off = (pos - 1) * sizeof(UTILISATEUR);

  if (lseek(fd, off, SEEK_SET) == -1) {
    perror("Erreur lseek");
    close(fd);
    return -1;
  }

  if ((rc = read(fd, &u, sizeof(UTILISATEUR))) != sizeof(UTILISATEUR)) {
    perror("Erreur read");
    close(fd);
    return -1; 
  }

  ha=hash(motDePasse);

  close(fd);

  if(ha== u.hash){
    return 1;
  }

  return 0;
}

////////////////////////////////////////////////////////////////////////////////////
int listeUtilisateurs(UTILISATEUR *vecteur) // le vecteur doit etre suffisamment grand
{
  int fd, rc, cnt=0;
  UTILISATEUR u;

  if((fd = open(FICHIER_UTILISATEURS,O_RDONLY))== -1)
  {
      perror("Erreur de open()");
      return -1;
  }  

  while((rc=read(fd, &u, sizeof(UTILISATEUR)))==sizeof(UTILISATEUR)){
    vecteur[cnt] = u;
    cnt++;
  }

  if (rc == -1) {
    perror("Erreur read");
    close(fd);
    return -1; 
  }

  close(fd);
  return cnt;

  
}
