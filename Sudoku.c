/*
 ============================================================================
 Name        : Sudoku.c
 Author      : jordi
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char** tractafitxer(int* colum,int * files,char* fileentry){


	char **m;
	FILE *f;
	char linea[500];
    int ok=1;
    int columnes,i, j, k,w;

    *files=1;
    *colum=1,
    f = fopen(fileentry ,"r");
    if ( f == NULL){
    	printf("Error al obrir fitxer !\n");
    }else {
    	fgets (linea ,500, f );
    	linea[strlen(linea)-1]='\0';
    	//printf( "holafitxer\n");
    	while ( !feof(f)){
    		columnes = strlen (linea);
    		if ( *colum< columnes){
    			*colum = columnes;
    		}
    		*files= *(files)+1;
    		fgets (linea ,500, f );
    		linea[strlen(linea)-1]='\0';

    	}
    	//printf("Surt bucle 1");
    	//printf("FILES %d COLUM %d",*files,*colum);
    	m = (char**)malloc(*(files) *sizeof(char*));
    	if(m == NULL){
    		printf("Error MEM !\n");
    	}
    	else{
    		for (i=0 ;i<*(files) && ok;i++){
    			m[i] = (char*)malloc(*(colum)*sizeof(char));
    			if (m[i] == NULL){
    				printf("Error de mem!\n");
    				ok= 0;
    				for(j=i;j>=0;--j){
    					free(m[j]);
    				}
    			free (m);
    			}
    		 }
    	}
    	fclose(f);
    	i = 0;
    	j = 0;
        f = fopen(fileentry ,"r");
        if ( f == NULL){
        	printf("Error al obrir fitxer !\n");
        }else {
        	fgets (linea ,500, f );
        	linea[strlen(linea)-1]='\0';
        	//printf("linea %s\n",linea);
        	while(!feof(f)){
        			//printf("\n OMPLU\n");
        			for(w = 0;w<*colum;++w){
        				m[i][w]= ' ';
        			}
        			strcpy(m[i],linea);
        			//printf("\n\nfila matriu: %s\n\n",m[i]);
        			i++;
            		fgets (linea ,500, f );
            		linea[strlen(linea)-1]='\0';
            		//printf("linea %s\n",linea);
            		if (feof(f)){
            			//printf("\n OMPLU\n");
                		//printf("linea ultima linea %s\n",linea);

            			for( w = 0;w<*colum;++w){
            				m[i][w]= ' ';
            			}
            			strcpy(m[i],linea);
            			//printf("\n\nFila matriu: %s\n\n",m[i]);
            		}
        		}
        	fclose(f);

        	}


        	printf("\nMatriu original\n");
    		for (j=0;j<*files-1;j++){
    			for(k=0;k<*colum;k++){
    				printf("%c",m[j][k]);
    			}
    			printf("\n");
    		}

    	 }

    	return m;
 }
/*
void tractafitxer(char* fileentry,char m[9][9]){

	FILE *f;
	char linea[12];
    int ok=1;
    int i, j, k,w;

    	i = 0;
    	j = 0;
        f = fopen(fileentry ,"r");
        if ( f == NULL){
        	printf("Error al obrir fitxer !\n");
        }else {

        	while(i<9){
        			for(w = 0;12;++w){
        		        m[i][w]= ' ';
        		    }
        			printf("\n OMPLU\n");
            		fgets (linea ,12, f );
            		linea[9]='\0';
        			strcpy(m[i],linea);
        			printf("\n\nfila matriu: %s\n\n",m[i]);
        			i++;

            		//printf("linea %s\n",linea);
        		}
        	fclose(f);

        	}


        	printf("\nMatriu original\n");
    		for (j=0;j<9;j++){
    			for(k=0;k<9;k++){
    				printf("%c",m[j][k]);
    			}
    			printf("\n");
    		}

 }
*/
int comprovaquad(char m[9][9],int i,int j,int r,int s ){
	printf("Comprovo quad r: %d s:%d \n",r,s);
	int ok=1,k,w;
	for(w=r;w<(r+3) &&ok;++w){
		for(k=s;k<(s+3) &&ok;++k){
			printf("%c",m[w][k]);
			if(m[w][k]==m[i][j] && w!=i && k!=j) ok=0;
		}
		printf("\n");
	}
	return ok;
}
int bona(char m[9][9],int i, int j){

	printf("Comprovo hor\n");
	int w,k,ok=1;
	for(w=0;w<9 && ok;++w){
		printf("%c",m[i][w]);
		if (m[i][w]==m[i][j] && j!=w) ok=0;
	}
	if (ok){
		printf("Comprovo ver\n");
		for (w=0;w<9 && ok;++w){
			if(m[w][j]==m[i][j] && i!= w) ok=0;
		}
	if (ok){
		if(i<3 && j<3){
			ok = comprovaquad(m,i,j,0,0);
		}
		else if(i<3 && j<6){
			ok = comprovaquad(m,i,j,0,3);
		}
		else if(i<3 && j>5){
			ok = comprovaquad(m,i,j,0,6);
		}
		else if(i<6 && j<3){
			ok = comprovaquad(m,i,j,3,0);
		}
		else if(i<6 && j<6){
			ok = comprovaquad(m,i,j,3,3);
		}
		else if(i<6 && j>5){
			ok = comprovaquad(m,i,j,3,6);
		}
		else if(i<9 && j<3){
			ok = comprovaquad(m,i,j,6,0);
		}
		else if(i<9 && j<6){
			ok = comprovaquad(m,i,j,6,3);
		}
		else if(i<9 && j>12){
			ok = comprovaquad(m,i,j,6,6);
		}
	}
	}
	return ok;
}

void Backtracking(char mant[9][9],int i,int j,int n){

	int cont=0,segueix=1,auxi,auxj,k,w;
	char m2[9][9];
	for (w=0;w<9;w++){
		for(k=0;k<9;k++){
			m2[w][k]=mant[w][k];
		}
	}

	printf("Entro Back\n");
	while((m2[i][j] != '-' )&& segueix){
		if (j==8) {
			if(i==8) segueix =0;
			else{
			i++;
			j=0;
			}
		} else {
		j++;
		}
	}
	printf("i :%d j: %d ",i,j);
	m2[i][j]= '1';
	while((m2[i][j])<'9' && m2[i][j]>'0'){
		if(cont==9) m2[i][j]='9';
		else{
		m2[i][j] ='1'+cont;
		}
		printf("BONA? vALOR= %c\n",m2[i][j]);

		//printf("CONT %d\n",cont);
		cont++;
		if (i==9 && j==16){
			if (bona(m2,i,j)){
				printf("RESOLC 1");
				n--;
				//tracta
			}
		}
		else{
			printf("BONA? vALOR= %c\n",m2[i][j]);
			auxi=i;
			auxj=j;
			if(bona(m2,i,j)) {
				if (j==8) {
					auxi=i++;
					auxj=0;
					printf("entro else final linea!");
				}
				else {
					auxj=j++;
				}
				while((m2[auxi][auxj] != '-' )&& segueix){
					if (j==8) {
						if(i==8) segueix =0;
						else{
						auxi++;
						auxj=0;
						}
					} else {
					auxj++;
					}
				}
				Backtracking(m2,auxi,auxj,n);
				m2[i][j] ='1'+cont;
				printf("FIBACK");
				for (w=0;w<9;w++){
					for(k=0;k<9;k++){
						printf("%c",m2[w][k]);
					}
					printf("\n");
				}
			}
		}
	}
}

void escriufitxer(char **m,char *nom){

	FILE *g;
	int k,j;
	g = fopen(nom,"w");
	if (g==NULL){
		printf("Error creant fitxer sortida!\n");
	} else{
		for (j=0;j<9;j++){
			for(k=0;k<17;k++){
				fprintf(g,"%c",m[j][k]);
			}
			fprintf(g,"\n");
		}
	}
}

int main(int argc, char **argv){

	char **m;char m2[9][9];
	int colum,files,j,k,w,p=0;
	if (argc<3){
		printf("Tens que introduir <FITXER IN> <FITXER OUT> <N>");
	}
	else{
		//printf("ARGV:%s %s %s",argv[1],argv[2],argv[3]);
		m=tractafitxer(&colum,&files,argv[1]);
		for (w=0;w<9;w++){
				for(k=0;k<17;k++){
					if(m[w][k] !=' '){
						m2[w][p]=m[w][k];
						++p;
				}

			}
				p=0;
		}
				for (j=0;j<9;j++){
					for(k=0;k<9;k++){
						printf("%c",m2[j][k]);
					}
					printf("\n");
				}

		Backtracking(m2,0,0,atoi(argv[3]));
    	printf("\nMatriu final\n");
		for (j=0;j<9;j++){
			for(k=0;k<9;k++){
				printf("%c",m2[j][k]);
			}
			printf("\n");
		}
		//escriufitxer(m,argv[2]);

	}
	return 0;
}

