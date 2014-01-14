int main(){

	int *px;//On déclare un pointeur sur un int
	
	float a,b;//On déclare 2 float
	float *pa,*pb//On déclare 2 pointeurs sur float
	
	float a=-1.167;//On déclare un float et on l'initialise à -1.167
	float *pa=&a;//On déclare un pointeur sur a et on lui affecte l'adresse de a
	
	char c1,c2,c3;//On déclare 3 "char"
	char *pc1, *pc2, *pc3=&c1;//On déclare 3 pointeurs sur "char" et on met l'addresse de c1 dans pc3
	
	double fonc (double *a, double *b, int *c);//Prototype de fonction renvoyant un "double" et prenant en paramètre 2 pointeurs sur le type "double" et un sur le type "int"
	double *fonc (double *a, double *b, int *c);//Pointeur de fonction renvoyant un "double" et prenant en paramètre 2 pointeurs sur le type "double" et un sur le type "int" [A VERIFIER]
	
	double (*a)[12];//Déclaration d'un pointeur sur tableau de 12 "double"
	
	double *a[12];//Déclaration d'un tableau de pointeur sur "double" de 12 cases
	
	char *d[4]={"Nord","Sud","Est","Ouest"};//Déclaration d'un tableau de pointeurs sur "char" et affectations de chaînes de caractères
	
	long *p[10][20];
	
	char exemple(int (*pf)(char a,char b));//Déclaration, d'une fonction retournant un char et prenant en paramètre un pointeur sur fonction retournant un "int" et prenant en paramètre 2 "char"
	
	int (*pf)();//Déclaration, d'une fonction retournant un int et ne prenant pas de paramètre
	
	int (*pf)(char a, char b);//Déclaration, d'une fonction retournant un int et prenant 2 "char" en paramètre
	
	int (*pf)(char *a, char *b);//Déclaration, d'une fonction retournant un int et prenant 2 pointeurs sur "char" en paramètre
}
