#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <fstream>
using namespace std;

typedef struct vypozicka {
   char  signatura[10];
   char  ISBN[14];
   char  nazov[100];
   char  autori[100];
   char  datum[8];
   char  preukaz[8];
   struct vypozicka *dalsi; 
} KNIZNICA;


void vytvor_vypozicku (KNIZNICA **lib) 
{
    *lib = (KNIZNICA *) malloc(sizeof(KNIZNICA));
    if (lib = NULL) 
        printf("Malo pamate.\n");   
                   
}

void uvolni_pamat (KNIZNICA *lib) 
{
	KNIZNICA *llib;
	llib=lib;
    //if ((*lib)->dalsi==NULL) {
	//free(lib);
	//printf("pamat bola uvolnena\n");
	//};
    //else uvolni_pamat (lib->dalsi);     
}

void uvolni (KNIZNICA **lib)
{ 
	KNIZNICA *llib,*llib_akt;
	llib=*lib;
	while (*lib!=NULL){	
	llib_akt=llib;
	llib=llib->dalsi;
	free(llib_akt);
	}
	printf("pamat bola uvolnena\n");
	
};


void nacitanie_suboru (KNIZNICA **lib ,int *pocet)
{
	int CoCitam=0,lpocet=0;
	KNIZNICA llib,*akt_lib,*pakt_lib;
	string riadok;
	pocet=0;
  	ifstream myfile ("kniznica.TXT");
  	if (myfile.is_open())
  	{
  		
    	while ( getline (myfile,riadok) )
    	{	
    		if (CoCitam ==1 ) { 
								if (lpocet==0) {
									//if (lib!=NULL) uvolni(lib);									
									
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
			if (CoCitam ==5 ) {strcpy(akt_lib->datum, riadok.c_str());}
			if (CoCitam ==6 ) {
				strcpy(akt_lib->preukaz, riadok.c_str()); 
				CoCitam=0; 
				}
			else { CoCitam++;
			}
			
    }

    myfile.close();
    if (lpocet >0) printf ("Nacitalo sa  %d zaznamov   \n",lpocet);
  }
  else cout << "Zaznamy neboli nacitane ";
  

};


void vypis (KNIZNICA *lib)
{ 
	KNIZNICA *llib;
	int i=0;
	llib=lib;
	while (llib!=NULL){
	printf("%d.\n",++i);	
	cout << llib->signatura <<'\n' ;
	cout << llib->ISBN << '\n';
	cout << llib->nazov << '\n';
	cout << llib->autori<< '\n';
   	cout << llib->datum<< '\n';
   	cout << llib->preukaz<< '\n';
	llib=llib->dalsi;
	}
	
	
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
	strcpy(new_lib->signatura,"Novy");
	strcpy(new_lib->ISBN,"Novy");
	strcpy(new_lib->nazov,"Novy");
	strcpy(new_lib->autori,"Novy");
	strcpy(new_lib->datum,"Novy");
	strcpy(new_lib->preukaz,"Novy");			 
	}
};

void zmaz (KNIZNICA **lib)
{ 
	KNIZNICA *llib, *pred_lib;
	char autori[100];
	int i=0;
	int poz=1;
	int poc=0;
	char * pch;
	
	llib=*lib;
	pred_lib=llib;
	scanf("%s",&autori);
	 
    
	
	while (llib!=NULL ){
		cout << llib->autori<< '\n';	
		if 	(strstr (llib->autori,autori)!=NULL)
		{
			if (poz==1){*lib=llib->dalsi;}
			else pred_lib->dalsi=llib->dalsi;
			//free(llib);
			}
		
		pred_lib=llib;	
		llib=llib->dalsi;	
	}	
}


int main ()
{	
	KNIZNICA *lib;
	int pocet;
	char pismeno;
	do {
		scanf("%c",&pismeno);
		switch(pismeno){
					case 'n': {	nacitanie_suboru(&lib,&pocet); } ;break;
					case 'v': {	vypis(lib); } ;break;
					case 'p': {	pridaj(&lib); } ;break;
					case 'z': {	zmaz(&lib); } ;break;
					case 'k': pismeno='k';break;
					}
		}
		while (pismeno!='k');
	return 0;
}


