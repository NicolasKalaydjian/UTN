/*
Dado el archivo VENTAS.DAT, ordenado por número de factura, con la siguiente
estructura de registro:
	Número de factura (int)
	Código de vendedor (int) (1 a 10)
	Importe (float)
a) Imprima un listado ordenado por código de vendedor, con código de vendedor
	y el detalle de cada venta, ordenadas de mayor a menor por importe.
b) Genere el archivo “VentasVendedor.dat” ordenado por código de vendedor,
	con código de vendedor y el importe total de ventas.
*/

/*
SOLUCION: 
1. Los datos del archivo los paso a un vector de listas.
2. Imprimo la info y genero el archivo al mismo tiempo.
*/

// 133 lineas

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

void incializarVector(NodoSub* vector[]);
void cargarVector(NodoSub* vector[]);
void insertar(NodoSub*&lista,Venta ventaX);
void listarGenerarArchivo(NodoSub* vector[]);
void mostrarArchivo();

int main()
{
	NodoSub* vVendedores[10];
	incializarVector(vVendedores);
	cargarVector(vVendedores);
	listarGenerarArchivo(vVendedores);
	mostrarArchivo();
	return 0;
}

void incializarVector(NodoSub* vector[])
{
	for(int i=0;i<10;i++){
		vector[i] = NULL;
	}
}

void cargarVector(NodoSub* vector[])
{
	FILE* archVentas = fopen("VENTAS.dat","rb");
	VentaArch ventaXarch;
	Venta ventaX;
	fread(&ventaXarch,sizeof(VentaArch),1,archVentas);
	while(!feof(archVentas))
	{
		ventaX.nroF = ventaXarch.nroF;
		ventaX.imp = ventaXarch.imp;
		insertar(vector[ventaXarch.codV-1],ventaX);
		fread(&ventaXarch,sizeof(VentaArch),1,archVentas);
	}
	fclose(archVentas);
}

void insertar(NodoSub*&lista,Venta ventaX)
{
    NodoSub*n,*p,*ant;
    n=new NodoSub;
    n->info=ventaX;
    p=lista;
    while(p!=NULL && p->info.imp > ventaX.imp)
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

void listarGenerarArchivo(NodoSub* vector[])
{
	FILE* archVendedores = fopen("VentasVendedor.dat","wb");
	VendedorArch vendedorXarch;
	NodoSub*s;
	for(int i=0;i<10;i++)
	{
		if(vector[i]!=NULL)
		{
			float impTotal=0;
			s = vector[i];
			while(s!=NULL)
			{
				cout<<"codV: "<<i+1<<endl;
				cout<<"nroF: "<<s->info.nroF<<endl;
	        	cout<<"imp: "<<s->info.imp<<endl<<endl;
				impTotal += s->info.imp;
				s=s->sig;
			}
			vendedorXarch.codV = i+1;
			vendedorXarch.impTot = impTotal;
			fwrite(&vendedorXarch,sizeof(VendedorArch),1,archVendedores);
		}
	}
	fclose(archVendedores);
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
