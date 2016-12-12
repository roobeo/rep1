#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>


typedef struct vypozicka {
   char signatura[10];
   char ISBN[14];
   char nazov[100];
   char autori[100];
   int  datum;
   int  preukaz;
   struct vypozicka *dalsi; 
} KNIZNICA;


void vytvor_vypozicku (KNIZNICA **lib) 
{
    *lib = (KNIZNICA *) malloc(sizeof(KNIZNICA));
    if (lib = NULL) 
        printf("Malo pamate.\n");   
                   
}


void uvolni (KNIZNICA **lib)
{ 
	KNIZNICA *llib,*llib_akt;
	llib=*lib;
	while (llib!=NULL){	
	llib_akt=llib;
	llib=llib->dalsi;
	free(llib_akt);
	}
	printf("pamat bola uvolnena\n");
	
};


void nacitanie_suboru (KNIZNICA **lib,int *pocet)
{
	FILE * fp;
	int CoCitam=0,lpocet=0;
	char oddelovac[3];
	KNIZNICA llib,*akt_lib,*pakt_lib;
	char *riadok = NULL;
	char *datum = NULL;
	char *preukaz = NULL;
	size_t bufsize = 255;
	size_t characters;
	riadok = (char *)malloc(bufsize * sizeof(char));	
	fp = fopen("kniznica.TXT", "r");
	if (fp != NULL)
  	{
  		
    	while (fgets(oddelovac,101 , fp)!=NULL)
    	{	
    		if (CoCitam ==1 ) { 
								if (lpocet==0) {
				
									if (*pocet>0) //uvolni(lib);									
									uvolni(lib);
									vytvor_vypozicku(lib); akt_lib=*lib;}
									
								else{
									vytvor_vypozicku(&akt_lib->dalsi);
									akt_lib=akt_lib->dalsi;
									akt_lib->dalsi=NULL;
									};
								fgets(akt_lib->signatura, 50 , fp);
								lpocet++;	
								}; 
			if (CoCitam ==2 ) {fgets(akt_lib->ISBN, 50 , fp) ;}														
			if (CoCitam ==3 ) {fgets(akt_lib->nazov, 200 , fp) ;}
			if (CoCitam ==4 ) {fgets(akt_lib->autori, 200 , fp);}
			if (CoCitam ==5 ) {fgets(datum, 50, fp);
								akt_lib->datum= atoi(datum);}
			if (CoCitam ==6 ) {
				fgets(preukaz, 50, fp);
				akt_lib->preukaz=atoi(preukaz); 
				CoCitam=0; 
				}
			else { CoCitam++;
			}
			
    }

    fclose(fp);
    free(riadok);
    if (lpocet >0) printf ("Nacitalo sa  %d zaznamov   \n",lpocet);
    *pocet=lpocet;
  }
  else  printf ("Zaznamy neboli nacitane    \n",lpocet); 
  

};

void vypis_vypozicku (KNIZNICA *lib,int i)
{
	printf("%d.\n",i);	
	printf("signatura :%s\n",lib->signatura);	 
	printf("ISBN :%s\n",lib->ISBN);	 
	printf("Nazov  :%s\n",lib->nazov);	 
	printf("Autori :%s\n",lib->autori);	 
	printf("Datum :%s\n",lib->datum);	 
	printf("Preukaz :%s\n",lib->preukaz);	 
}


void vypis (KNIZNICA *lib)
{ 
	KNIZNICA *llib;
	int i=0;
	llib=lib;
	while (llib!=NULL){
		vypis_vypozicku(llib,++i);	
		llib=llib->dalsi;
	}
	
	
};

void vypis_preukaz (KNIZNICA *lib)
{ 
	KNIZNICA *llib;
	int i=0;
	int preukaz;
	scanf("%d",&preukaz);
	llib=lib;
	while (llib!=NULL){
		if (preukaz==llib->preukaz)
			vypis_vypozicku(llib,++i);	
		llib=llib->dalsi;
	}	
	if (i==0) printf("Pre dane cislo preukazu %d neevidujeme vypozicky \n",preukaz);
};

void aktualizuj (KNIZNICA *lib)
{ 
	KNIZNICA *llib;
	int i=0;
	int datum;
	scanf("%d",&datum);
	llib=lib;
	while (llib!=NULL){
		if (datum>=llib->datum){
			llib->datum=llib->datum+10000;
			++i;	
		}			
		llib=llib->dalsi;
	}	
	printf("Aktualizovalo sa %d zaznamov \n",i);
};

void inicializuj (KNIZNICA *lib)
{ 
	char signatura[10];
   	char ISBN[14];
   	char nazov[100];
   	char autori[100];
   	char c;
   	int  datum;
   	int  preukaz;
   	
	printf("Sigantura :");
	scanf("%s",&signatura);
	strcpy(lib->signatura,signatura);
	printf("ISBN :");
	scanf("%s",&ISBN);
	strcpy(lib->ISBN,ISBN);
	printf("Nazov :");
	scanf("%s",&nazov);
	strcpy(lib->nazov,nazov);
	printf("Autori :");
	scanf("%s",&autori);
	strcpy(lib->autori,autori);
	printf("Datum :");
	scanf("%i",&datum);
	lib->datum=datum;
	printf("Preukaz :");
	scanf("%i",&preukaz);
	lib->preukaz=preukaz;
	scanf("%c",&c);			
};

void pridaj (KNIZNICA **lib)
{ 
	KNIZNICA *llib,*new_lib, *pred_lib;
	int i=0;
	int p=1;
	int poc=0;
	llib=*lib;
	scanf("%i",&i);
		
	if (i==1){
			vytvor_vypozicku(&new_lib);
			new_lib->dalsi=llib;
			printf("Vytvoril som 1 zaznam \n",i);
			*lib=new_lib;
			poc++;
			inicializuj(new_lib);
	}
	else{
	
	while (llib!=NULL && i>1 ){	
	if (p==i){	vytvor_vypozicku(&new_lib);
				new_lib->dalsi=llib;
				pred_lib->dalsi=new_lib;				
				printf("Vytvoril som zaznam  %d \n",p);
				poc++;
	}		
	pred_lib=llib;
	llib=llib->dalsi;
	p++;
	};
	if (poc==0)
	{vytvor_vypozicku(&new_lib);
	 pred_lib->dalsi=new_lib;	
	}
	inicializuj(new_lib);			 
	}
};

void zmaz (KNIZNICA **lib)
{ 
	KNIZNICA *llib, *pred_lib;
	char autori[100];
	char autori_p[100];
	
	int i=1;
	int poz=1;
	int poc=0;
	
	llib=*lib;
	pred_lib=llib;
	scanf("%s",&autori);
	 
	while (llib!=NULL ){
			i=0;
			while (autori[i])  {  autori[i]=tolower (autori[i]); i++; }	;
			strcpy(autori_p, llib->autori);
			i=0;
			while (autori_p[i])  {  autori_p[i]=tolower (autori_p[i]); i++; }	
		if 	(strstr (autori_p,autori)!=NULL)
		{ 	
			printf("Mazem autora %s \n",llib->autori);	
			if (poz==1){*lib=llib->dalsi; }
			else pred_lib->dalsi=llib->dalsi;
			free(llib);
			poc++;
		}
		pred_lib=llib;	
		llib=llib->dalsi;	
		poz++;
	}	
		printf("Zmazal som zaznam  %d \n",poc);
}


int main ()
{	
	KNIZNICA *lib;
	int pocet =0;
	char pismeno;
	do {
		scanf("%c",&pismeno);
		switch(pismeno){
					case 'n': {	nacitanie_suboru(&lib,&pocet); } ;break;
					case 'v': {	vypis(lib); } ;break;
					case 'p': {	pridaj(&lib); } ;break;
					case 'z': {	zmaz(&lib); } ;break;
					case 'h': {	vypis_preukaz(lib); } ;break;
					case 'a': {	aktualizuj(lib); } ;break;
					case 'k': pismeno='k';break;
					}
		}
		while (pismeno!='k');
	return 0;
}


