/*
Dado el archivo VENTAS.DAT, ordenado por número de factura, con la siguiente
estructura de registro:
	Número de factura (int)
	Código de vendedor (int)
	Importe (float)
a) Imprima un listado ordenado por código de vendedor, con código de vendedor
	y el detalle de cada venta, ordenadas de mayor a menor por importe.
b) Genere el archivo “VentasVendedor.dat” ordenado por código de vendedor,
	con código de vendedor y el importe total de ventas.
*/

/*
SOL: Los datos del archivo los paso a una lista de vendedores ordenados por cod. 
de vendedor,con sublista de ventas ordenadas por importe de mayor a menor
Luego en simultaneo imprimo las ventas y armo el nuevo archivo para asi
no recorrer 2 veces la lista.
*/

#include <iostream>
using namespace std;

struct Venta
{
	int nroF;
	float imp;
};
struct NodoSub
{
	Venta info;
	NodoSub* sig;
};
struct Vendedor
{
	int codV;
	//float impTot;
	NodoSub* sublista;
};
struct Nodo
{
	Vendedor info;
	Nodo* sig;
};
struct VentaArch
{
	int codV;
	int nroF;
	float imp;
};
struct VendedorArch
{
	int codV;
	float impTot;
};

void generarlista(Nodo*&lista);
Nodo* buscarInsertar(Nodo*&lista,Vendedor vendedorX);
void insertar(NodoSub*&lista,Venta ventaX);
void listarGenerarArchivo(Nodo*lista);
void mostrarArchivo();

int main(){
	Nodo* listaVendedores=NULL;
	generarlista(listaVendedores);
	listarGenerarArchivo(listaVendedores);
	mostrarArchivo();
	return 0;
}

void generarlista(Nodo*&lista)
{
	FILE* archVentas = fopen("VENTAS.dat","rb");
	fseek(archVentas,0,SEEK_END);
	if (ftell(archVentas)==0)
		cout<<"El archivo fuente esta vacio"<<endl<<endl;
	else
	{
		fseek(archVentas,0,SEEK_SET);
		Nodo*p;
		VentaArch ventaXarch;
		Venta ventaX;
		Vendedor vendedorX;
		fread(&ventaXarch,sizeof(VentaArch),1,archVentas);
		while(!feof(archVentas))
		{
			vendedorX.codV = ventaXarch.codV;
			//vendedorX.impTot += ventaXarch.imp;
			vendedorX.sublista = NULL;
			ventaX.nroF = ventaXarch.nroF;
			ventaX.imp = ventaXarch.imp;
			p = buscarInsertar(lista,vendedorX);
			insertar(p->info.sublista,ventaX);
			fread(&ventaXarch,sizeof(VentaArch),1,archVentas);
		}
	}

	fclose(archVentas);
}

Nodo* buscarInsertar(Nodo*&lista,Vendedor vendedorX)
{
	Nodo*ant,*p=lista;
	while(p!=NULL && p->info.codV<vendedorX.codV)
	{
		ant=p;
		p=p->sig;
	}
	if(p!=NULL && vendedorX.codV==p->info.codV)
        return p;
	else
	{
		Nodo*n=new Nodo;
		n->info=vendedorX;
        n->sig=p;
        if(p!=lista)
			ant->sig=n;
        else
            lista=n;
        return n;
	}
}

void insertar(NodoSub*&lista,Venta ventaX)
{
    NodoSub*n,*p,*ant;
    n=new NodoSub;
    n->info=ventaX;
    p=lista;
    while(p!=NULL && p->info.imp > ventaX.imp) // mayor a menor imp
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

void listarGenerarArchivo(Nodo*lista)
{
	Nodo*p=lista;
	NodoSub*s;
	VendedorArch vendedorXarch;
	FILE*archVendedores = fopen("VentasVendedor.dat","wb");
    while(p!=NULL)
    {
    	float impTotal=0;
    	s = p->info.sublista;
        //cout<<p->info.leg<<p->info.nom<<p->info.nota<<endl;
        while(s!=NULL)
        {
        	cout<<"codV: "<<p->info.codV<<endl;
        	cout<<"nroF: "<<s->info.nroF<<endl;
        	cout<<"imp: "<<s->info.imp<<endl<<endl;
        	impTotal += s->info.imp;
        	s=s->sig;
		}
		vendedorXarch.codV = p->info.codV;
		vendedorXarch.impTot = impTotal;
		fwrite(&vendedorXarch,sizeof(VendedorArch),1,archVendedores);
        p=p->sig;
    }
    fclose(archVendedores);
	cout<<"archivo VentasVendedor.dat generado"<<endl<<endl;
}

void mostrarArchivo()
{
	FILE*archVendedores = fopen("VentasVendedor.dat","rb");
	VendedorArch vendedorXarch;
	if(archVendedores==NULL)
		cout<<"Archivo no encontrado"<<endl;
	else 
	{
		fseek(archVendedores,0,SEEK_END);
		if (ftell(archVendedores)==0)
			cout<<"El archivo destino esta vacio"<<endl;
		else {
			cout<<"Datos en el archivo:"<<endl<<endl;
			fseek(archVendedores,0,SEEK_SET);
			fread(&vendedorXarch,sizeof(VendedorArch),1,archVendedores);
			while(!feof(archVendedores)){
				cout<<"codV: "<<vendedorXarch.codV<<endl;
				cout<<"impTot: "<<vendedorXarch.impTot<<endl<<endl;
				fread(&vendedorXarch,sizeof(VendedorArch),1,archVendedores);
			}
		}
	}
	fclose(archVendedores);
}
