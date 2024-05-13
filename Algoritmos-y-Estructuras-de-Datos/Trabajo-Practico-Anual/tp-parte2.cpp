#include <iostream>
#include <string.h>
using namespace std;

typedef char str30[31];

struct Docente 
{
	str30 nombre;
	int dni;
};
struct cursoArch
{
	int codigo;
	int cupo;
	Docente docente;
	int nivel;
	str30 idioma;
};
struct Estudiante
{
	str30 nom;
	int dni;
};
struct NodoCola
{
	Estudiante info;
	NodoCola* sig;
};
struct NodoEst
{
	Estudiante info;
	NodoEst* sig;
};
struct Curso
{
	NodoEst* lista;
	NodoCola* pri;
	NodoCola* ult;
	int codigo;
	int cupo;
	int cantEst;
	Docente docente;
};
struct DocenteArbol
{
	str30 nombre;
	int dni;
	int cantEst;
};
struct NodoArbol
{
    DocenteArbol info;
    NodoArbol* izq;
    NodoArbol* der;
};

void cargarVector(Curso vCursos[],str30 vIdiomas[],int&cant);
void ordenarVector(Curso v[],int t);
void ejecutarOpcion(Curso vCursos[],int cantCursos);
int elegirOpcion();
void inscribirEstudiante(Curso vCursos[],int cantCursos);
int busquedaBinaria(Curso v[],int t,int bus);
NodoEst* buscarLista(NodoEst*lista,int dni);
void insertarLista(NodoEst*&lista,Estudiante estX);
void encolar(NodoCola*&pri,NodoCola*&ult,Estudiante dato);
void bajarEstudiante(Curso vCursos[],int cantCursos);
void eliminarEstudiante(NodoEst*&lista,int dni,bool&x);
Estudiante desencolar(NodoCola*&pri,NodoCola*&ult);
void mostrarEstado(Curso vCursos[],int cantCursos);
void mostrarEstudiantes(NodoEst* lista);
void mostrarColas(Curso vCursos[],int cantCursos);
void cargarArbol(NodoArbol*&raiz,Curso v[],int cant);
NodoArbol* buscarInsertar(NodoArbol*&raiz,DocenteArbol docX,bool&x);
void mostrarArbol(NodoArbol*raiz);
void generarArchivos(Curso v[],int cant);
void mostrarArchivos(Curso v[],int cant);

int main(){
	str30 vIdiomas[] = {"Ingles","Frances","Portugues","Italiano","Aleman","Chino"};
	Curso vCursos[48];
	int cantCursos = 0;
	cargarVector(vCursos,vIdiomas,cantCursos);
	ejecutarOpcion(vCursos,cantCursos);
	mostrarArchivos(vCursos,cantCursos);
	return 0;
}

void cargarVector(Curso vCursos[],str30 vIdiomas[],int&cant)
{
	FILE*archIdioma;
	str30 nomArch;
	cursoArch cursoXarch;
	for(int i=0;i<6;i++)
	{
		strcpy(nomArch,vIdiomas[i]);
		strcat(nomArch,".dat");
		archIdioma = fopen(nomArch,"rb");
		if(archIdioma==NULL)
			cout<<"Error al intentar abrir el archivo "<<nomArch<<endl;
		else
		{
			fread(&cursoXarch,sizeof(cursoArch),1,archIdioma);
			while(!feof(archIdioma))
			{
				vCursos[cant].codigo = cursoXarch.codigo;
				vCursos[cant].cupo = cursoXarch.cupo;
				strcpy(vCursos[cant].docente.nombre,cursoXarch.docente.nombre);
				vCursos[cant].docente.dni = cursoXarch.docente.dni;
				vCursos[cant].cantEst = 0;
				vCursos[cant].lista = NULL;
				vCursos[cant].pri = NULL;
				vCursos[cant].ult = NULL;
				cant++;
				fread(&cursoXarch,sizeof(cursoArch),1,archIdioma);
			}
		}
		fclose(archIdioma);
	}
	ordenarVector(vCursos,cant);
}

void ordenarVector(Curso v[],int t)
{
    int i=1,j;
    Curso aux;
    bool cambio;
    do
    {
        cambio=false;
        for(j=0;j<t-i;j++)
        {
            if(v[j].codigo>v[j+1].codigo)
            {
                aux=v[j];
                v[j]=v[j+1];
                v[j+1]=aux;
                cambio=true;
            }
        }
        i++;
    }while(i<t && cambio);
}

void ejecutarOpcion(Curso vCursos[],int cantCursos)
{
	cout<<"Opciones:"<<endl;
	cout<<"1. Inscribir estudiante"<<endl;
	cout<<"2. Dar de baja estudiante"<<endl;
	cout<<"3. Mostrar estado de inscripciones"<<endl;
	cout<<"4. Salir"<<endl<<endl;
	int opcion;
	opcion = elegirOpcion();
	while(opcion!=4)
	{
		switch(opcion)
		{
			case 1:
				inscribirEstudiante(vCursos,cantCursos);
				opcion = elegirOpcion();
				break;
			case 2:
				bajarEstudiante(vCursos,cantCursos);
				opcion = elegirOpcion();
				break;
			case 3:
				mostrarEstado(vCursos,cantCursos);
				opcion = elegirOpcion();
				break;
		}
	}
	mostrarColas(vCursos,cantCursos);
	
	NodoArbol*raizArbol = NULL;
	cargarArbol(raizArbol,vCursos,cantCursos);
	mostrarArbol(raizArbol);
	
	generarArchivos(vCursos,cantCursos);
}

int elegirOpcion()
{
	int opcion;
	do
	{
		cout<<"Elija que desea hacer(1 a 4): ";
		cin>>opcion;
		cout<<endl;
		if(opcion<1||opcion>4)
			cout<<"opcion no valida"<<endl<<endl;
	} while(opcion<1||opcion>4);
	return opcion;
}

void inscribirEstudiante(Curso vCursos[],int cantCursos)
{
	int cod;
	Estudiante estX;
	NodoEst* p,*q;
	cout<<"Nombre del estudiante: ";
	fflush(stdin);
	cin.getline(estX.nom,31);
	cout<<"DNI del estudiante: ";
	cin>>estX.dni;
	cout<<"Cod. Curso al que desea inscribirse: ";
	cin>>cod;
	cout<<endl;
	int pos = busquedaBinaria(vCursos,cantCursos,cod);
	if(pos>-1)
	{
		p = buscarLista(vCursos[pos].lista,estX.dni);
		if(p==NULL)
		{
			if(vCursos[pos].cantEst<vCursos[pos].cupo)
			{
				insertarLista(vCursos[pos].lista,estX);
				vCursos[pos].cantEst++;
				cout<<"Estudiante agregado al curso"<<endl<<endl;
			}
			else
			{
				encolar(vCursos[pos].pri,vCursos[pos].ult,estX);
				cout<<"No hay cupo. Estudiante puesto en cola de espera"<<endl<<endl;
			}
		} else cout<<"Estudiante ya esta en el curso"<<endl;
	} else cout<<"codigo de curso incorrecto"<<endl<<endl;
}

int busquedaBinaria(Curso v[],int t,int bus)
{
	int desde=0,hasta=t-1,medio;
   	do
    {
        medio=(desde+hasta)/2;

        if(bus<v[medio].codigo)
                hasta=medio-1;
        else
                desde=medio+1;

    } while(desde<=hasta && v[medio].codigo!=bus);
    if(v[medio].codigo==bus)
        return medio;
    else
        return -1;
}

NodoEst* buscarLista(NodoEst*lista,int dni)
{
    NodoEst*p=lista;
    while(p!=NULL && p->info.dni<dni)
        p=p->sig;
    if(p==NULL || p->info.dni!=dni)
        return NULL;
    else
        return p;
}

void insertarLista(NodoEst*&lista,Estudiante estX)
{
    NodoEst*n,*p,*ant;
    n=new NodoEst;
    n->info=estX;
    p=lista;
    while(p!=NULL && p->info.dni < estX.dni)
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

void encolar(NodoCola*&pri,NodoCola*&ult,Estudiante dato)
{
    NodoCola*p;
    p=new NodoCola;
    p->info=dato;
    p->sig=NULL;
    if(ult!=NULL)
        ult->sig=p;
    else
        pri=p;
    ult=p;
}

void bajarEstudiante(Curso vCursos[],int cantCursos)
{
	int cod;
	int dni;
	bool x = false;
	NodoEst* p;
	Estudiante estX;
	cout<<"DNI del estudiante: ";
	cin>>dni;
	cout<<"Cod. Curso del que desea darse de baja: ";
	cin>>cod;
	cout<<endl;
	int pos = busquedaBinaria(vCursos,cantCursos,cod);
	if(pos>-1)
	{
		eliminarEstudiante(vCursos[pos].lista,dni,x);
		if(!x)
		{
			vCursos[pos].cantEst--;
			cout<<"Estudiante dado de baja"<<endl<<endl;
		}
		if(vCursos[pos].pri!=NULL)
		{
			estX = desencolar(vCursos[pos].pri,vCursos[pos].ult);
			insertarLista(vCursos[pos].lista,estX);
			vCursos[pos].cantEst++;
			cout<<"Estudiante en la cola de espera agregado al curso"<<endl<<endl;
		}
	} else cout<<"codigo de curso incorrecto"<<endl<<endl;
}

void eliminarEstudiante(NodoEst*&lista,int dni,bool&x)
{
    NodoEst*ant,*p=lista;
    while(p!=NULL && p->info.dni<dni)
    {
        ant=p;
        p=p->sig;
    }

    if(p==NULL || p->info.dni!=dni)
    {
    	x = true;
        cout<<"no se encontro el estudiante"<<endl<<endl;
	}
    else
    {
        if(p!=lista)
            ant->sig=p->sig;
        else
            lista=p->sig;
        delete p;
    }
}

Estudiante desencolar(NodoCola*&pri,NodoCola*&ult)
{
    NodoCola*p;
    p=pri;
    Estudiante dato=p->info;
    pri=p->sig;
    delete p;
    if(pri==NULL)
        ult=NULL;
    return dato;
}

void mostrarEstado(Curso vCursos[],int cantCursos)
{
	for(int i=0;i<cantCursos;i++)
	{
		cout<<"Cod. de Curso: "<<vCursos[i].codigo<<endl;
		cout<<"Cant. de vacantes ocupadas: "<<vCursos[i].cantEst<<endl;
		cout<<"Cant. de vacantes disponibles: "<<vCursos[i].cupo-vCursos[i].cantEst<<endl;
		cout<<"Listado de estudiantes: "<<endl<<endl;
		mostrarEstudiantes(vCursos[i].lista);
	}
}

void mostrarEstudiantes(NodoEst* lista)
{
	if(lista==NULL)
		cout<<"no hay estudiantes"<<endl<<endl;
	else 
	{
		NodoEst*p=lista;
		while(p!=NULL)
		{
			cout<<"DNI: "<<p->info.dni<<endl;
			cout<<"Nombre: "<<p->info.nom<<endl<<endl;
			p=p->sig;
		}
	}
}

void mostrarColas(Curso vCursos[],int cantCursos)
{
	cout<<"Estudiantes que no obtuvieron vacantes: "<<endl<<endl;
	bool x = true;
	NodoEst* p;
	Estudiante estX;
	for(int i=0;i<cantCursos;i++)
	{
		if(vCursos[i].pri!=NULL)
		{
			x = false;
			do
			{
				estX = desencolar(vCursos[i].pri,vCursos[i].ult);
				cout<<"DNI: "<<estX.dni<<endl;
				cout<<"Nombre: "<<estX.nom<<endl<<endl;
			} while (vCursos[i].pri!=NULL);
		}
	}
	if(x)
		cout<<"no quedaron estudiantes sin vacante"<<endl<<endl;
}

void cargarArbol(NodoArbol*&raiz,Curso v[],int cant)
{
	NodoArbol* p;
	DocenteArbol docX;
	docX.cantEst = 0;
	bool x = false;
	for(int i=0;i<cant;i++)
	{
		docX.dni = v[i].docente.dni;
		strcpy(docX.nombre,v[i].docente.nombre);
		p = buscarInsertar(raiz,docX,x);
		if(!x)
			p->info.cantEst = v[i].cantEst;
		else
			p->info.cantEst += v[i].cantEst;
	}
}

NodoArbol* buscarInsertar(NodoArbol*&raiz,DocenteArbol docX,bool&x)
{
    NodoArbol*r,*ant;
    r=raiz;
    while(r!=NULL && r->info.dni!=docX.dni)
    {
    	ant=r;
        if(docX.dni < r->info.dni)
            r=r->izq;
        else
            r=r->der;
    }
	if(r==NULL)
    {
    	NodoArbol*n = new NodoArbol;
	    n->info=docX;
	    n->der=n->izq=NULL;
    	if(raiz==NULL)
    		raiz=n;
    	else
    	{
	        if(docX.dni < ant->info.dni)
	        	ant->izq = n;
	        else
	        	ant->der = n;
		}
	    return n;
    }
    else
    	x = true;
        return r;
}

void mostrarArbol(NodoArbol*raiz)
{
	if(raiz!=NULL)
    {
        mostrarArbol(raiz->izq);
        cout<<"Nombre del Docente: "<<raiz->info.nombre<<endl;
        cout<<"DNI del Docente: "<<raiz->info.dni<<endl;
        cout<<"Cant. estudiantes a cargo: "<<raiz->info.cantEst<<endl<<endl;
        mostrarArbol(raiz->der);
    }
}

void generarArchivos(Curso v[],int cant)
{
	FILE*archCurso;
	str30 nomArch;
	NodoEst* p;
	Estudiante estX;
	for(int i=0;i<cant;i++)
	{
		sprintf(nomArch, "%d", v[i].codigo);
		strcat(nomArch,".dat");
		archCurso = fopen(nomArch,"wb");
		p = v[i].lista;
		while(p!=NULL)
		{
			strcpy(estX.nom,p->info.nom);
			estX.dni = p->info.dni;
			fwrite(&estX,sizeof(Estudiante),1,archCurso);
			p=p->sig;
		}
		fclose(archCurso);
		cout<<"Archivo "<<nomArch<<" generado"<<endl;
	}
	cout<<endl;
}

void mostrarArchivos(Curso v[],int cant)
{
	FILE*archCurso;
	str30 nomArch;
	Estudiante estX;
	for(int i=0;i<cant;i++)
	{
		sprintf(nomArch, "%d", v[i].codigo);
		strcat(nomArch,".dat");
		archCurso = fopen(nomArch,"rb");
		cout<<"Archivo "<<nomArch<<" abierto"<<endl;
		cout<<"Estudiantes del curso: "<<endl<<endl;
		fread(&estX,sizeof(Estudiante),1,archCurso);
		if(feof(archCurso))
			cout<<"no hay estudiantes"<<endl<<endl;
		while(!feof(archCurso))
		{
			cout<<"DNI: "<<estX.dni<<endl;
			cout<<"Nombre: "<<estX.nom<<endl<<endl;
			fread(&estX,sizeof(Estudiante),1,archCurso);
		}
	}
}