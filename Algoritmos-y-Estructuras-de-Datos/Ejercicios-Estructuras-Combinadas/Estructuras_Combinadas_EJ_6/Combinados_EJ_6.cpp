/*
La ciudad de Buenos Aires requiere un estudio estad�stico de infracciones
realizadas por los veh�culos en sus calles. Para ello cuenta con un archivo de
infracciones �Infracciones.dat�, ordenado por fecha de la infracci�n creciente, con
el siguiente dise�o:
	Patente (7 caracteres)
	Fecha de Infracci�n (int, aammdd)
	C�digo de infracci�n (int, 1 a 100)
Se desea obtener un listado ordenado por c�digo de infracci�n decreciente con las
patentes que cometieron m�s de una vez la misma infracci�n.
*/

/*
SOLUCION: 
Vector de listas.
El vector tiene los tipos de infraccion.
Las listas tienen las patentes que cometieron cada infraccion.
Cada patente tiene asociada un contador de veces que cometio la infraccion.
Luego, muestro el vector de atras hacia delante, mostrando solo las patentes
que cometieron 2 o mas veces una infraccion.
*/

// 112 lineas

#include <iostream> // cin-cout
#include <string.h> // strcpy / strcmp / strlen 
using namespace std;

typedef char str7[8];

struct InfraccionArch
{
	str7 pat;
	int fecha; // AAMMDD
	int codI; // 1 a 100
};
struct Patente
{
	str7 pat;
	int cont;
};
struct Nodo
{
	Patente info;
	Nodo* sig;
};

void inicializarVector(Nodo* vector[]);
void generarVector(Nodo* vInfracciones[]);
Nodo* buscarInsertar(Nodo*&lista,Patente patenteX);
void mostrarVector(Nodo* vector[]);

int main(){
	Nodo* vInfracciones[100];
	inicializarVector(vInfracciones);
	generarVector(vInfracciones);
	mostrarVector(vInfracciones);
	return 0;
}

void inicializarVector(Nodo* vector[])
{
	for(int i=0;i<100;i++)
		vector[i] = NULL;
}

void generarVector(Nodo* vInfracciones[])
{
	FILE* archInfracciones = fopen("InfraccionesV2.dat","rb");
	Nodo*p;
	InfraccionArch infraccionX;
	Patente patenteX;
	patenteX.cont = 0;
	fread(&infraccionX,sizeof(InfraccionArch),1,archInfracciones);
	while(!feof(archInfracciones))
	{
		strcpy(patenteX.pat,infraccionX.pat);
		p = buscarInsertar(vInfracciones[infraccionX.codI-1],patenteX);
		p->info.cont++;
		fread(&infraccionX,sizeof(InfraccionArch),1,archInfracciones);
	}
	fclose(archInfracciones);
}

Nodo* buscarInsertar(Nodo*&lista,Patente patenteX)
{
	Nodo*ant,*p=lista;
	while(p!=NULL && strcmp(p->info.pat,patenteX.pat)<0)
	{
		ant=p;
		p=p->sig;
	}
	if(p!=NULL && strcmp(patenteX.pat,p->info.pat)==0)
        return p;
	else
	{
		Nodo*n=new Nodo;
		n->info=patenteX;
        n->sig=p;
        if(p!=lista)
			ant->sig=n;
        else
            lista=n;
        return n;
	}
}

void mostrarVector(Nodo* vector[])
{
	Nodo*p;
	for(int i=99;i>=0;i--)
	{
		if(vector[i]!=NULL)
		{
			cout<<"Patentes que cometieron mas de 1 una vez la infraccion "<<i+1<<endl<<endl;
			//deberia ir fuera del IF pero lo pongo dentro para que sea mas facil testear
			//si lo pongo fuera tendria en pantalla 100 veces el mensaje
			bool x = false;
			p = vector[i];
			while(p!=NULL)
			{
				if(p->info.cont>1)
				{
					x = true;
					cout<<p->info.pat<<endl;
				}
				p = p->sig;
			}
			if(!x)
				cout<<"ninguna"<<endl;
			cout<<endl;
		}
	}
}
