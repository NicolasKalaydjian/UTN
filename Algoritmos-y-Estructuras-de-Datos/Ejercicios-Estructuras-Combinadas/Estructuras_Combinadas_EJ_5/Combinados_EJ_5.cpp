/*
Una compañía que ofrece préstamos a sus clientes a pagar en 12 meses, desea
obtener un listado con los códigos de clientes y los números de las cuotas
adeudadas de aquellos clientes que adeuden cuotas, ordenado por código de
cliente. Para ello cuenta con un archivo de cobranzas, sin ningún orden, con el
siguiente diseño:
	Código de cliente (int)
	Número de cuota (1 a 12)
*/

/*
SOLUCION: 
Lista de vectores.
Cada nodo de la lista en info tiene el vector y el codigo de cliente.
El vector es de 12 elementos y de tipo bool.

*/

// 104 lineas

#include <iostream>
using namespace std;

struct cobroArch
{
	int codC; 
	int nroC; // 1 a 12
};
struct Cliente
{
	int codC;
	bool pagos[12];
	int contP;
};
struct Nodo
{
	Cliente info;
	Nodo* sig;
};

void generarLista(Nodo*&lista);
void inicializarVector(bool vec[]);
Nodo* buscarInsertar(Nodo*&lista,Cliente clienteX);
void listar(Nodo*lista);

int main()
{
	Nodo* listaClientes = NULL;
	generarLista(listaClientes);
	listar(listaClientes);
	return 0;
}

void generarLista(Nodo*&lista)
{
	FILE* archCobros = fopen("Cobranzas.dat","rb");
	Nodo*p;
	cobroArch cobroXarch;
	Cliente clienteX;
	inicializarVector(clienteX.pagos);
	clienteX.contP=0;
	fread(&cobroXarch,sizeof(cobroArch),1,archCobros);
	while(!feof(archCobros))
	{
		clienteX.codC = cobroXarch.codC;
		p = buscarInsertar(lista,clienteX);
		p->info.pagos[cobroXarch.nroC-1] = true;
		p->info.contP++;
		fread(&cobroXarch,sizeof(cobroArch),1,archCobros);
	}
	fclose(archCobros);
}

void inicializarVector(bool vec[])
{
	for(int i=0;i<12;i++)
		vec[i] = false;
}

Nodo* buscarInsertar(Nodo*&lista,Cliente clienteX)
{
	Nodo*ant,*p=lista;
	while(p!=NULL && p->info.codC<clienteX.codC)
	{
		ant=p;
		p=p->sig;
	}
	if(p!=NULL && clienteX.codC==p->info.codC)
        return p;
	else
	{
		Nodo*n=new Nodo;
		n->info=clienteX;
        n->sig=p;
        if(p!=lista)
			ant->sig=n;
        else
            lista=n;
        return n;
	}
}

void listar(Nodo*lista)
{
	Nodo*p=lista;
	bool x = false;
	while(p!=NULL)
	{	
		if(p->info.contP<12)
		{
			x = true;
			cout<<"Cliente "<<p->info.codC<<" debe las cuotas: ";
			for(int i=0;i<12;i++)
				if(!p->info.pagos[i])
					cout<<i+1<<", ";
		}
		p=p->sig;
		cout<<endl;
	}
	if(p==lista)
		cout<<"no hay clientes"<<endl;
	if(!x)
		cout<<"no hay clientes que adeuden cuotas"<<endl;
}
