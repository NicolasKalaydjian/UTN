/*
En un club deportivo barrial se quiere hacer un programa para obtener datos
estadísticos de los atletas que compitieron en el año 2019 en las 15 actividades
deportivas que se practican en el mismo.
Se tiene el archivo “Competidores.dat”, con cada una de las participaciones de los
atletas en competencias, sin orden, donde cada registro tiene el siguiente formato:
Código de actividad (1..15)
Número de socio del atleta
Fecha de la competencia (struct dia, mes, anio)
Resultado (int)
Se pide:
a) Informar por cada actividad, por cada mes, cada uno de los atletas que
compitieron y el resultado obtenido, ordenado por código de actividad, por
mes y por número de socio.
b) Informar por cada mes del año el total de atletas que compitieron en cada
actividad.
c) Informar en qué actividad deportiva hubo más de un primer puesto.
*/
/*
SOLUCION: los datos del archivo los cargo en una matriz de listas (actividad X mes),
cada lista tiene nodos de participaciones con info: nro. socio y rdo. 
las listas van a estar ordenadas por nro de socio.
Doy por hecho que cada atleta no compite mas de 1 vez en la misma actividad y mes.
Osea, hay 1 sola competencia por mes y por actividad.
*/

// 159 lineas

#include <iostream>
using namespace std;

struct Fecha
{
	int dia;
	int mes;
	int anio;
};
struct PartArch // part = participacion
{
	int codA; // codA = codigo de actividad
	int nroS; // nroS = nro de socio
	Fecha fechaC; //  fechaC = fecha de la competencia
	int rdo; 
};
struct Part
{
	int nroS;
	int rdo;
};
struct NodoSub
{
	Part info;
	NodoSub* sig;
};

void inicializarMatriz(NodoSub* matriz[15][12]);
void cargarMatriz(NodoSub* matriz[15][12]);
void insertar(NodoSub*&lista,Part partX);
void listar(NodoSub* matriz[15][12],int matriz2[15][12],bool vector[]);
void puntoB(int matriz[15][12]);
void puntoC(bool vector[15]);

int main()
{
	NodoSub* mPart[15][12];
	int mDatos[15][12]; // para punto B
	bool vector[15]; // para punto C
	inicializarMatriz(mPart);
	cargarMatriz(mPart);
	listar(mPart,mDatos,vector);
	puntoB(mDatos);
	puntoC(vector);
	
}

void inicializarMatriz(NodoSub* matriz[15][12])
{
	for(int i=0;i<15;i++)
		for(int j=0;j<12;j++){
			matriz[i][j] = NULL;
		}
		 	
}

void cargarMatriz(NodoSub* matriz[15][12])
{
	FILE* archPart = fopen("Competidores.dat","rb");
	PartArch partXarch;
	Part partX;
	fread(&partXarch,sizeof(PartArch),1,archPart);
	while(!feof(archPart))
	{
		partX.nroS = partXarch.nroS;
		partX.rdo = partXarch.rdo;
		insertar(matriz[partXarch.codA-1][partXarch.fechaC.mes-1],partX);
		fread(&partXarch,sizeof(PartArch),1,archPart);
	}
	fclose(archPart);
}

void insertar(NodoSub*&lista,Part partX)
{
    NodoSub*n,*p,*ant;
    n=new NodoSub;
    n->info=partX;
    p=lista;
    while(p!=NULL && p->info.nroS < partX.nroS) //inserto por nro de socio de menor a mayor
    {
        ant=p;
        p=p->sig;
    }
    n->sig=p;
    if(p!=lista)
        ant->sig=n;
    else
        lista=n;
}

void listar(NodoSub* matriz[15][12],int matriz2[15][12],bool vector[]) // puntoA
{
	NodoSub*s;
	bool pri;
	for(int i=0;i<15;i++)
	{
		pri = true;
		vector[i] = false;
		for(int j=0;j<12;j++)
		{
			matriz2[i][j] = 0;
			if(matriz[i][j]!=NULL)
			{
				
				s = matriz[i][j];
				while(s!=NULL)
				{
					cout<<"Actividad "<<i+1<<endl;
					cout<<"Mes "<<j+1<<endl;
					cout<<"Nro Socio: "<<s->info.nroS<<endl;
					cout<<"Resultado: "<<s->info.rdo<<endl<<endl;
					if(s->info.rdo==1&&pri==true)
						pri=false;
					else if (s->info.rdo==1)
						vector[i] = true;
					matriz2[i][j]++;
					s=s->sig;
				}
			}
		}
	}
}

void puntoB(int matriz[15][12])
{
	cout<<"cantidad de atletas que compitieron por mes y por actividad: "<<endl<<endl;
	int x = 0;
	for(int j=0;j<12;j++)
	{
		for(int i=0;i<15;i++)
		{
			if(matriz[i][j]>0)
			{
				x++;
				cout<<"Mes "<<j+1<<". ";
				cout<<"Actividad "<<i+1<<": "<<matriz[i][j]<<endl<<endl;
			}
		}
	}
	if(x<12*15)
		cout<<"en el resto no participaron atletas"<<endl<<endl;
}

void puntoC(bool vector[15])
{
	cout<<"Actividades en las que hubo mas de un 1er puesto: ";
	bool x = false;
	for(int i=0;i<15;i++)
	{
		if(vector[i])
		{
			x = true;
			cout<<i+1<<", ";
		}
	}
	if(!x)
		cout<<"ninguna";
	cout<<endl<<endl;
}
