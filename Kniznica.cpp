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
   char  ISBN[13];
   char  nazov[100];
   char  autori[100];
   char  datum[8];
   char  preukaz[8];
   int	 cislo;
   struct vypozicka *dalsi; 
} KNIZNICA;


void vytvor_vypozicku (KNIZNICA **lib) 
{
    KNIZNICA *llib;
    *lib = (KNIZNICA *) malloc(sizeof(KNIZNICA));
    if (llib = NULL) 
        printf("Malo pamate.\n");   
}

void nacitanie_suboru (KNIZNICA *lib ,int *pocet)
{
	int CoCitam=0;
	KNIZNICA llib,*akt_lib;
	string riadok;
	pocet=0;
  	ifstream myfile ("kniznica.TXT");
  	if (myfile.is_open())
  	{
  		//akt_lib=vytvor_vypozicku();
    	while ( getline (myfile,riadok) )
    	{	
    		if (CoCitam ==1 ) { 
							 
							// if ( poc++==0)	{lib =llib ;llib_akt=lib;}
							// else{
							//	llib_akt->dalsi=llib;
								strcpy(llib.signatura,riadok.c_str()); 
							}								
			if (CoCitam ==2 ) strcpy(llib.ISBN, riadok.c_str());
			if (CoCitam ==3 ) strcpy(llib.nazov, riadok.c_str());
			if (CoCitam ==4 ) strcpy(llib.autori, riadok.c_str()); 
			if (CoCitam ==5 ) strcpy(llib.datum, riadok.c_str());
			if (CoCitam ==6 ) {
				strcpy(llib.preukaz, riadok.c_str());  
				CoCitam=0; 
				akt_lib=&llib;
				pocet++;
				cout << akt_lib->signatura << '\n';
				}
			else CoCitam++;
   			//cout << llib.signatura << '\n';      	      
    }
    printf("%d",pocet );
    myfile.close();
  }
  else cout << "Zaznamy neboli nacitane ";
  
  //strcpy( lib->signatura,akt_lib->signatura); 
};

void nacitaj (KNIZNICA *lib)
{ 

	strcpy(lib->signatura,"dsdsa"); 

};

void vypis (KNIZNICA *lib)
{ 
	char *a ;
	KNIZNICA llib;
	//llib->signatura= lib->signatura;
	//cout << llib.signatura << '\n' ;
	
};

int main ()
{	
	KNIZNICA *lib;
	int pocet;
	char pismeno;
	vytvor_vypozicku (&lib);
	do {
		scanf("%c",&pismeno);
		switch(pismeno){
					case 'n': {
						nacitaj(lib); } ;break;
					case 'v': {
						vypis(lib); } ;break;
					case 'k': pismeno='k';break;
					}
		cout << lib->signatura << '\n' ;
		}
		while (pismeno!='k');
	return 0;
}


