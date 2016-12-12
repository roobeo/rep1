#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <fstream>
using namespace std;

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

void uvolni_pamat (KNIZNICA **lib) 
{
	KNIZNICA *llib;
	llib=*lib;
    if (llib->dalsi==NULL) {
	free(*lib);
	printf("pamat bola uvolnena\n");
	}
    else uvolni_pamat(&llib->dalsi);     
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
	int CoCitam=0,lpocet=0;
	KNIZNICA llib,*akt_lib,*pakt_lib;
	string riadok;
  	ifstream myfile ("kniznica.TXT");
  	if (myfile.is_open())
  	{
  		
    	while ( getline (myfile,riadok) )
    	{	
    		if (CoCitam ==1 ) { 
								if (lpocet==0) {
				n
									if (*pocet>0) uvolni(lib);									
									vytvor_vypozicku(lib); akt_lib=*lib;}
									
								else{
									vytvor_vypozicku(&akt_lib->dalsi);
									akt_lib=akt_lib->dalsi;
									akt_lib->dalsi=NULL;
									}						
								strcpy(akt_lib->signatura,riadok.c_str()); 
								lpocet++;	
								}; 
			if (CoCitam ==2 ) {strcpy(akt_lib->ISBN, riadok.c_str()) ;}														
			if (CoCitam ==3 ) {strcpy(akt_lib->nazov, riadok.c_str()) ;}
			if (CoCitam ==4 ) {strcpy(akt_lib->autori, riadok.c_str());}
			if (CoCitam ==5 ) {akt_lib->datum= atoi(riadok.c_str());}
			if (CoCitam ==6 ) {
				akt_lib->preukaz=atoi(riadok.c_str()); 
				CoCitam=0; 
				}
			else { CoCitam++;
			}
			
    }

    myfile.close();
    if (lpocet >0) printf ("Nacitalo sa  %d zaznamov   \n",lpocet);
    *pocet=lpocet;
  }
  else cout << "Zaznamy neboli nacitane ";
  

};

void vypis_vypozicku (KNIZNICA *lib,int i)
{
	printf("%d.\n",i);	
	cout << "signatura :" << lib->signatura <<'\n' ;
	cout << "ISBN :" << lib->ISBN << '\n';
	cout << "Nazov :" << lib->nazov << '\n';
	cout << "Autori :" << lib->autori<< '\n';
   	cout << "Datum :" << lib->datum<< '\n';
   	cout << "Preukaz :" << lib->preukaz<< '\n';	
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
	strcpy(lib->signatura,"");
	strcpy(lib->ISBN,"");
	strcpy(lib->nazov,"");
	strcpy(lib->autori,"");
	lib->datum=20161010;
	lib->preukaz=10000000;			
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


