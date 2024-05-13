/*
En una empresa de construcción se quiere almacenar en un archivo los importes y
fechas de los materiales comprados para cada una de las obras que está
construcción. 
Para ello se ingresa por teclado, por cada compra de materiales realizada: 
el código de la obra, la fecha y el importe de la compra. 
Los datos son ingresados sin orden. 
Para cada obra se puede haber comprado materiales varias veces. 
Se pide generar un archivo secuencial con código de obra, fecha e importe,
ordenado por código de obra y por fecha, con los datos ingresados por teclado.
*/

#include <iostream>
//#include <stdio.h>
using namespace std;

struct tCompra
{
	int fecha; // AAAAMMDD, fecha de la compra
	int imp; // importe de la compra
};

struct tCompraArch
{
	int cod;
	int fecha;
	int imp;
};

struct NodoSub
{
	tCompra info;
	NodoSub*sig;
};
struct tObra
{
	int cod;
	NodoSub*sublista;
};
struct Nodo
{
	tObra info;
	Nodo*sig;
};

void generarLista(Nodo*&listaObras);
Nodo* buscarInsertar(Nodo*&lista,tObra obraX);
void insertar(NodoSub*&lista,tCompra compraX);
void generarArchivo(Nodo*lista);
void mostrarArchivo();

int main(){
	Nodo*listaObras=NULL;
	generarLista(listaObras);
	generarArchivo(listaObras);
	mostrarArchivo();	
	return 0;
}

void generarLista(Nodo*&listaObras)
{
	tObra obraX;
	tCompra compraX;
	Nodo*p;
	cout<<"Codigo de obra (fin = 0): ";
	cin>>obraX.cod;
	while(obraX.cod!=0)
	{
		cout<<"Fecha de compra (AAAAMMDD): ";
		cin>>compraX.fecha;
		cout<<"Importe de la compra: ";
		cin>>compraX.imp;
		
		obraX.sublista=NULL;
		
		p=buscarInsertar(listaObras,obraX);
		insertar(p->info.sublista,compraX);
		
		cout<<endl;
		cout<<"Codigo de obra (fin = 0): ";
		cin>>obraX.cod;
	}
}

Nodo* buscarInsertar(Nodo*&lista,tObra obraX) // busca/inserta por cod. de obra de menor a mayor
{
	Nodo*ant,*p=lista;
	while(p!=NULL && p->info.cod<obraX.cod)
	{
		ant=p;
		p=p->sig;
	}
	if(p!=NULL && obraX.cod==p->info.cod)
        return p;
	else
	{
		Nodo*n=new Nodo;
		n->info=obraX;
        n->sig=p;
        if(p!=lista)
			ant->sig=n;
        else
            lista=n;
        return n;
	}
}

void insertar(NodoSub*&lista,tCompra compraX)  // ordenado por fecha de menor a mayor, osea mas viejo primero
{
    NodoSub*n,*p,*ant;
    n=new NodoSub;
    n->info=compraX;
    p=lista;
    while(p!=NULL && p->info.fecha < compraX.fecha) 
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

void generarArchivo(Nodo*lista)
{
	Nodo*p=lista;
	NodoSub*s;
	tCompraArch compraX;
	FILE*archCompras;
	archCompras = fopen("Compras.dat","wb");
	if(archCompras==NULL)
		cout<<"ERROR"<<endl;
	else 
	{
		while(p!=NULL){
			s = p->info.sublista;
			compraX.cod = p->info.cod;
			while(s!=NULL){
				compraX.fecha = s->info.fecha;
				compraX.imp = s->info.imp;
				fwrite(&compraX,sizeof(tCompraArch),1,archCompras);
				s=s->sig;
			}
			p=p->sig;
		}
	}
	fclose(archCompras);
	cout<<endl;
	cout<<"archivo generado"<<endl<<endl;;
}

void mostrarArchivo()
{
	FILE*archCompras = fopen("Compras.dat","rb");
	tCompraArch compraX;
	if(archCompras==NULL)
		cout<<"Archivo no encontrado"<<endl;
	else 
	{
		fseek(archCompras,0,SEEK_END);
		if (ftell(archCompras)==0)
			cout<<"El archivo esta vacio"<<endl;
		else {
			cout<<"Datos en el archivo:"<<endl<<endl;
			fseek(archCompras,0,SEEK_SET);
			fread(&compraX,sizeof(tCompraArch),1,archCompras);
			while(!feof(archCompras)){
				cout<<"cod: "<<compraX.cod<<endl;
				cout<<"fecha: "<<compraX.fecha<<endl;
				cout<<"imp: "<<compraX.imp<<endl<<endl;
				fread(&compraX,sizeof(tCompraArch),1,archCompras);
			}
		}
	}
	fclose(archCompras);
}
