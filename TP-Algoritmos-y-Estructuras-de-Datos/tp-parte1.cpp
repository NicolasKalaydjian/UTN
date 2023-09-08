#include <iostream>
#include <string.h>
using namespace std;

typedef char str30[31];

struct tDocente {
	str30 nombre;
	int dni;
};

struct tCurso {
	int codigo;
	int cupo;
	tDocente docente;
	int nivel;
	str30 idioma;
};

void inicializarMatriz(tCurso m[][8]);
void incializarVector(tCurso v[],int cant);
int buscarFila(str30 v[],str30 x);
void ingresarCursos(tCurso m[][8],str30 v[],int &cant);
void generarArchivos(str30 vI[],tCurso vC[],int cant);
void copiarDatos(tCurso m[][8], tCurso v[]);
void ordenarVector(tCurso v[],int t);
void mostrarArchivos(str30 v[]);
void punto2(tCurso m[][8], str30 v[]);
void punto3(tCurso m[][8], str30 v[]);
void punto4(tCurso m[][8]);

int main() {
	str30 vIdiomas[] = {"Ingles","Frances","Portugues","Italiano","Aleman","Chino"};
	tCurso mCursos[6][8];
	inicializarMatriz(mCursos);
	int cant=0;
	ingresarCursos(mCursos,vIdiomas,cant);
	tCurso vCursos[cant];
	incializarVector(vCursos,cant);
	copiarDatos(mCursos,vCursos);
	ordenarVector(vCursos,cant);
	generarArchivos(vIdiomas,vCursos,cant);
	//punto2(mCursos,vIdiomas);
	//punto3(mCursos,vIdiomas);
	//punto4(mCursos);
	mostrarArchivos(vIdiomas);
	return 0;
};

void inicializarMatriz(tCurso m[][8]) {
	for(int i=0; i<6; i++) {
		for(int j=0; j<8; j++) {
			m[i][j].codigo=0;
			m[i][j].cupo=0;
			strcpy(m[i][j].docente.nombre,"");
			m[i][j].docente.dni=0;
			m[i][j].nivel=0;
			strcpy(m[i][j].idioma,"");
		}
	}
};

void incializarVector(tCurso v[],int cant) {
	for(int i=0; i<cant; i++) {
		v[i].codigo=0;
		v[i].cupo=0;
		strcpy(v[i].docente.nombre,"");

		v[i].docente.dni=0;
		v[i].nivel=0;
		strcpy(v[i].idioma,"");
	}
};

int buscarFila(str30 v[],str30 x) { 
	int i=0;
	while(i<6 && strcmpi(v[i],x)!=0)
		i++;
	if(i==6)
		return -1;
	else
		return i;
};

void ingresarCursos(tCurso m[][8],str30 v[],int &cant) {
	str30 idioma;
	int nivel, fila;
	cout<<"Ingresar cursos (nivel '0' para finalizar)"<<endl<<endl;
	do {
		cout<<"Ingresar nivel (1 al 8): ";
		cin>>nivel;
		if(nivel<0||nivel>8)
			cout<<"nivel incorrecto"<<endl;
	} while (nivel<0||nivel>8);
	while(nivel!=0) {
		cout<<"Ingresar idioma: ";
		cin>>idioma;
		fila = buscarFila(v,idioma);
		if ((m[fila][nivel-1].codigo==0) && (fila>-1)) {
			cant++;
			m[fila][nivel-1].nivel = nivel; 
			strcpy(m[fila][nivel-1].idioma, idioma);
			cout<<"Ingresar codigo: ";
			cin>>m[fila][nivel-1].codigo;
			cout<<"Ingresar cupo: ";
			cin>>m[fila][nivel-1].cupo;
			cout<<"Ingresar nombre del docente: ";
			fflush(stdin);
			cin.getline(m[fila][nivel-1].docente.nombre,31);
			cout<<"Ingresar dni del docente: ";
			cin>>m[fila][nivel-1].docente.dni;
			cout<<endl;
		} else cout<<"Curso ya existente o idioma incorrecto"<<endl<<endl;
		do {
			cout<<"Ingresar nivel (1 al 8): ";
			cin>>nivel;
			if(nivel<0||nivel>8)
				cout<<"nivel fuera de los valores posibles"<<endl;
		} while (nivel<0||nivel>8);
	}
	cout<<endl;
};

void copiarDatos(tCurso m[][8], tCurso v[]) {
	int cant=0;
	for(int i=0; i<6; i++) {
		for(int j=0; j<8; j++) {
			if(m[i][j].codigo!=0) {
				v[cant] = m[i][j];
				cant++;
			}
		}
	}
};

void ordenarVector(tCurso v[],int t) {
	unsigned int i=1,j;
	tCurso aux;
	bool cambio;
	do {
		cambio=false;
		for(j=0; j<t-i; j++) {
			if(v[j].codigo>v[j+1].codigo) {
				aux=v[j];
				v[j]=v[j+1];
				v[j+1]=aux;
				cambio=true;
			}
		}
		i++;
	} while(i<t && cambio);
};

void generarArchivos(str30 vI[],tCurso vC[],int cant) {
	cout<<"PUNTO 1"<<endl<<endl;
	FILE*archIdioma;
	str30 nomArch;
	for(int i=0; i<6; i++) {
		strcpy(nomArch,vI[i]);
		strcat(nomArch,".dat");
		cout<<nomArch<<" creado"<<endl;
		archIdioma = fopen(nomArch,"wb");
		if(archIdioma==NULL) {
			cout<<"ERROR"<<endl;
		} else {
			for(int j=0; j<cant; j++) {
				if(strcmpi(vC[j].idioma,vI[i])==0) {
					fwrite(&vC[j],sizeof(tCurso),1,archIdioma);
				}
			}
		}
		fclose(archIdioma);
	}
	cout<<endl;
};

void mostrarArchivos(str30 v[]) {
	cout<<"CHEQUEO DEL PUNTO 1"<<endl<<endl;
	tCurso cursoX;
	FILE*archIdioma;
	str30 nomArch;
	for(int i=0; i<6; i++) {
		int cant=0;
		strcpy(nomArch,v[i]);
		strcat(nomArch,".dat");
		archIdioma = fopen(nomArch,"rb");
		cout<<"Archivo "<<nomArch<<" abierto. Sus cursos son:"<<endl<<endl;
		if(archIdioma==NULL) {
			cout<<"ERROR. Archivo no existe."<<endl;
		} else {
			fread(&cursoX,sizeof(tCurso),1,archIdioma);
			while(!feof(archIdioma)) {
				cout<<"Codigo: "<<cursoX.codigo<<endl;
				cout<<"Nivel: "<<cursoX.nivel<<endl;
				cout<<"Cupo: "<<cursoX.cupo<<endl;
				cout<<"Nombre del docente: "<<cursoX.docente.nombre<<endl;
				cout<<"DNI del docente: "<<cursoX.docente.dni<<endl<<endl;;
				cant++;
				fread(&cursoX,sizeof(tCurso),1,archIdioma);	
			}
			fclose(archIdioma);
			if(cant==0)
				cout<<"no tiene cursos cargados"<<endl<<endl;
		}
	}
	cout<<endl;
}

void punto2(tCurso m[][8], str30 v[]) {
	cout<<"PUNTO 2"<<endl<<endl;
	for(int i=0; i<6; i++) {
		int cantC = 0;
		for(int j=0; j<8; j++) {
			if(m[i][j].codigo!=0)
				cantC++;
		}
		cout<<"cant. de cursos de "<<v[i]<<": "<<cantC<<endl;
	}
	cout<<endl;
}

void punto3(tCurso m[][8], str30 v[]) {
	cout<<"PUNTO 3"<<endl<<endl;
	cout<<"Idiomas que tienen cursos en los 8 niveles: ";
	bool siHay = false;
	for(int i=0; i<6; i++) {
		int cantC = 0;
		for(int j=0; j<8; j++) {
			if(m[i][j].codigo!=0)
				cantC++;
		}
		if(cantC == 8) {
			siHay = true;
			cout<<v[i]<<", ";
		}
	}
	if(!siHay)
		cout<<"no hay";
	cout<<endl<<endl;
};

void punto4(tCurso m[][8]) {
	cout<<"PUNTO 4"<<endl<<endl;
	cout<<"Niveles en los que no se dictara ningun idioma: ";
	bool siHay = false;
	for(int j=0; j<8; j++) {
		int cantC = 0;
		for(int i=0; i<6; i++) {
			if(m[i][j].codigo!=0)
				cantC++;
		}
		if(cantC == 0) {
			siHay = true;
			cout<<j+1<<", ";
		}
	}
	if(!siHay)
		cout<<"no hay";
	cout<<endl<<endl;
};