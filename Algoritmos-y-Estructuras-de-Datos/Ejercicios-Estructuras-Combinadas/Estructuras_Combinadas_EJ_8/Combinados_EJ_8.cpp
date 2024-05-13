/*
8) Una biblioteca necesita un programa que efectúe las altas en el archivo maestro de
libros. Para ello cuenta con:
	a) LIBROS.dat, archivo maestro de libros ordenado por código de libro,
	con un registro por cada libro, con el siguiente diseño:
		Código de libro (int)
		Título del libro (30 caracteres)
		Apellido del autor (15 caracteres)
		Nacionalidad (int)
		Cantidad de ejemplares
	b) NOVEDADES.dat, archivo con los libros a dar de alta sin ningún
	orden, con el mismo diseño del archivo maestro.
Se pide realizar la metodología necesaria para que el programa:
1) Genere un nuevo archivo LIBROSACT.dat, con el mismo diseño y orden que el
maestro y con las altas incorporadas.
2) Emitir el siguiente listado, agrupado por nacionalidad y ordenado ascendente
por cantidad total de autores:
	Nacionalidad................................... Cantidad Total de autores: 999
			Apellido del Autor 						Cantidad total de títulos
			……...................... 					99
*/

/*
SOLUCION: novedades lo meto es una lista y hago apareo entre esa lista y el archivo 
maestrio de libros, y los voy metiendo en el archivo LibrosAct.dat.
Cuando tengo dos codigos de libro iguales tengo que cargar uno solo pero
sumando la cantidad de ejemplares.
Al mismo tiempo cargo todo en un vector (nacionalidades) con sublista (autores).
El vector tiene strcuts con puntero a la sublista y la cantidad de autores.
La sublista tiene struct de Autor, con apellido de autor y cantidad de titulos.
*/

#include <iostream>
#include <string.h>
using namespace std;

struct Libro
{
	int cod;
	char tit[31];
	char ape[16];
	int nac;
	int cant;
};
struct NodoNov
{
	Libro info;
	NodoNov* sig;
};
struct Autor
{
	char ape[16];
	int cantT;
};
struct NodoSub
{
	Autor info;
	NodoSub* sig;
};
struct datoVec
{
	int cantA;
	NodoSub* sublista;
};

void inicializarVector(datoVec vec[]);
void extraerNovedades(NodoNov*&lista);
void insertar(NodoNov*&lista,Libro libroX);
void generarArchivoVector(NodoNov* lista,datoVec vec[]);
void cargarVector(datoVec vec[],Libro libroX);
NodoSub* buscarInsertar(NodoSub*&lista,Autor autorX,bool &x);
void mostrarVector(datoVec vec[]);
void mostrarArchivo();

int main(){
	NodoNov* listaNovedades = NULL;
	datoVec vNacionalidades[220];
	inicializarVector(vNacionalidades);
	extraerNovedades(listaNovedades);
	generarArchivoVector(listaNovedades,vNacionalidades);
	mostrarVector(vNacionalidades);
	mostrarArchivo();
	return 0;
}

void inicializarVector(datoVec vec[])
{
	for(int i=0;i<220;i++)
	{
		vec[i].cantA = 0;
		vec[i].sublista = NULL;	
	}
}

void extraerNovedades(NodoNov*&lista)
{
	FILE*archNovedades=fopen("Novedades.dat","rb");
	Libro libroX;
	fread(&libroX,sizeof(Libro),1,archNovedades);
	while(!feof(archNovedades))
	{
		insertar(lista,libroX);
		fread(&libroX,sizeof(Libro),1,archNovedades);
	}
	fclose(archNovedades);
}

void insertar(NodoNov*&lista,Libro libroX)
{
    NodoNov*n,*p,*ant;
    n=new NodoNov;
    n->info=libroX;
    p=lista;
    while(p!=NULL && p->info.cod < libroX.cod) // inserto por codLibro de menor a mayor
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

void generarArchivoVector(NodoNov* lista,datoVec vec[])
{
	FILE*archLibros = fopen("Libros.dat","rb");
	FILE*archLibrosAct = fopen("LibrosAct.dat","wb");
	NodoNov*p = lista;
	Libro libroA;
	Libro libroB;
	fread(&libroA,sizeof(Libro),1,archLibros);
	while(p!=NULL && !feof(archLibros))
	{
		libroB = p->info;
		if(libroA.cod == libroB.cod)
		{
			libroA.cant += libroB.cant;
			fwrite(&libroA,sizeof(Libro),1,archLibrosAct);
			cargarVector(vec,libroA);
			fread(&libroA,sizeof(Libro),1,archLibros);
			p = p->sig;
		}
		else if(libroA.cod > libroB.cod)
		{
			fwrite(&libroB,sizeof(Libro),1,archLibrosAct);
			cargarVector(vec,libroB);
			p = p->sig;
		}
		else
		{
			fwrite(&libroA,sizeof(Libro),1,archLibrosAct);
			cargarVector(vec,libroA);
			fread(&libroA,sizeof(Libro),1,archLibros);
		}
	}
	if(p!=NULL)
	{
		do
		{
			libroB = p->info;
			fwrite(&libroB,sizeof(Libro),1,archLibrosAct);
			cargarVector(vec,libroB);
			p = p->sig;
		} while(p!=NULL);
	}
	if(!feof(archLibros))
	{
		do 
		{
			fwrite(&libroA,sizeof(Libro),1,archLibrosAct);
			cargarVector(vec,libroA);
			fread(&libroA,sizeof(Libro),1,archLibros);
		} while(!feof(archLibros));
	}
	fclose(archLibros);
	fclose(archLibrosAct);
}

void cargarVector(datoVec vec[],Libro libroX)
{
	Autor autorX;
	autorX.cantT = 0;
	NodoSub*p;
	bool x = false;
	strcpy(autorX.ape,libroX.ape);
	p = buscarInsertar(vec[libroX.nac-1].sublista,autorX,x);
	p->info.cantT++;
	if(x)
	{
		vec[libroX.nac-1].cantA++;
	}
}

NodoSub* buscarInsertar(NodoSub*&lista,Autor autorX,bool &x)
{
	NodoSub*ant,*p=lista;
	while(p!=NULL && strcmp(p->info.ape,autorX.ape)<0)
	{
		ant=p;
		p=p->sig;
	}
	if(p!=NULL && strcmp(p->info.ape,autorX.ape)==0)
        return p;
	else
	{
		x = true;
		NodoSub*n=new NodoSub;
		n->info=autorX;
        n->sig=p;
        if(p!=lista)
			ant->sig=n;
        else
            lista=n;
        return n;
	}
}

void mostrarVector(datoVec vec[])
{
	NodoSub*p;
	for(int i=0;i<220;i++)
	{
		if(vec[i].sublista!=NULL)
		{
			cout<<"-- Nacionalidad "<<i+1<<". Cantidad total de autores: "<<vec[i].cantA<<endl<<endl;
			p = vec[i].sublista;
			while(p!=NULL)
			{
				cout<<"Autor: "<<p->info.ape<<". Cantidad total de titulos: "<<p->info.cantT<<endl;
				p = p->sig;
			}
			cout<<endl;
		}
	}
}

void mostrarArchivo()
{
	FILE*archLibrosAct=fopen("LibrosAct.dat","rb");
	Libro libroX;
	fread(&libroX,sizeof(Libro),1,archLibrosAct);
	while(!feof(archLibrosAct)){
		cout<<"Cod. Libro: "<<libroX.cod<<endl;
		cout<<"Titulo: "<<libroX.tit<<endl;;
		cout<<"Apellido del Autor: "<<libroX.ape<<endl;
		cout<<"Nacionalidad: "<<libroX.nac<<endl;
		cout<<"Cant. de ejemplares: "<<libroX.cant<<endl<<endl;
		fread(&libroX,sizeof(Libro),1,archLibrosAct);
	}
	fclose(archLibrosAct);
}
