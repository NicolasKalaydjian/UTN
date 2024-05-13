/*
7) En una empresa se quiere hacer una reestructuración de sus departamentos
administrativos, ofreciendo la posibilidad de cambios voluntarios de
departamentos a sus empleados.

Para ello cuenta con los siguientes archivos:

“Empleados.dat”, con un registro por cada empleado de la empresa, ordenado por
número de legajo, según el siguiente diseño:
	Número de legajo (int)
	Apellido y nombre
	Dni
	Código de departamento actual
	
“Vacantes.dat”, con un registro por cada departamento en el que hay vacantes a
ofrecer a los empleados, sin orden, según el siguiente diseño:
	Código de departamento (1 a 50)
	Cantidad de vacantes
	
“Postulantes.dat”, con un registro por cada postulación realizada, cada empleado
solo se pudo postular a una vacante, ordenado según se han postulado, con el
siguiente diseño:
	Número de legajo
	Código de departamento
	
Se pide desarrollar la metodología necesaria para realizar un algoritmo que
permita:
a) Hacer un listado, ordenado por código de departamento, con todos los
empleados postulados al mismo por orden de llegada (número de legajo,
dni y apellido y nombre).
b) Asignar los postulantes a los departamentos según el orden de llegada y la
cantidad de vacantes requeridas, actualizando el archivo “Empleados.dat”.
*/
/*
SOLUCION:
Vector de colas.
Cada elementos del vector tiene vacantes de ese dto y lista de postulaciones.
*/

// 168 lineas

#include <iostream> // cin / cout
#include <string.h> // strcpy / strcmp / strlen / strcmpi
using namespace std;

typedef char str30[31];

struct VacArch // para archivo Vacantes
{
	int dto;
	int cantV;
};
struct PostArch // para archivo Postulantes
{
	int leg;
	int dto;
};
struct EmpArch
{
	int leg;
	str30 nombre;
	int dni;
	int dto;
};
struct NodoCola
{
	int info; // legajo
	NodoCola* sig;
};
struct Depto
{
	int cantV;
	NodoCola* pri;
	NodoCola* ult;
};

void inicializarVector(Depto vector[]);
void cargarVacantes(Depto vector[]);
void encolar(NodoCola*&pri,NodoCola*&ult,int dato);
void cargarPostulaciones(Depto vector[]);
int desencolar(NodoCola*&pri,NodoCola*&ult);
int busquedaBinariaArch(FILE* arch,int bus,EmpArch &reg);
void mostrarAsignar(Depto vector[]);
void mostrarArchivoEmp();

int main(){
	Depto vDepartamentos[50];
	inicializarVector(vDepartamentos);
	cargarVacantes(vDepartamentos);
	cargarPostulaciones(vDepartamentos);
	mostrarAsignar(vDepartamentos);
	mostrarArchivoEmp();
	return 0;
}

void inicializarVector(Depto vector[])
{
	for(int i=0;i<50;i++){
		vector[i].cantV= 0;
		vector[i].pri= NULL;
		vector[i].ult= NULL;
	}
}

void cargarVacantes(Depto vector[])
{
	FILE*archVac=fopen("Vacantes.dat","rb");
	VacArch vacanteX;
	fread(&vacanteX,sizeof(VacArch),1,archVac);
	while(!feof(archVac))
	{
		vector[vacanteX.dto-1].cantV = vacanteX.cantV;
		fread(&vacanteX,sizeof(VacArch),1,archVac);
	}
	fclose(archVac);
}

void encolar(NodoCola*&pri,NodoCola*&ult,int dato)
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

void cargarPostulaciones(Depto vector[])
{
	FILE*archPost=fopen("Postulantes.dat","rb");
	PostArch postX;
	fread(&postX,sizeof(PostArch),1,archPost);
	while(!feof(archPost))
	{
		encolar(vector[postX.dto-1].pri,vector[postX.dto-1].ult,postX.leg);
		fread(&postX,sizeof(PostArch),1,archPost);
	}
	fclose(archPost);
}

int desencolar(NodoCola*&pri,NodoCola*&ult)
{
    NodoCola*p;
    p=pri;
    int dato=p->info;
    pri=p->sig;
    delete p;
    if(pri==NULL)
        ult=NULL;
    return dato;
}

int busquedaBinariaArch(FILE* arch,int bus,EmpArch &reg)
{
    int desde,hasta,medio,cantRegistros;
    int pos=-1;
    desde=0;
    fseek(arch,0,SEEK_END);
    cantRegistros=ftell(arch)/sizeof(EmpArch);
    hasta=cantRegistros-1;
    while(pos==-1 && desde<=hasta)
    {
        medio=(desde+hasta)/2;
        fseek(arch,medio*sizeof(EmpArch),SEEK_SET);
        fread(&reg,sizeof(EmpArch),1,arch);
        if(reg.leg==bus)
            pos=medio;
        else
        {
            if(bus<reg.leg)
                hasta=medio-1;
            else
                desde=medio+1;
        }
    }
    return pos;
}

void mostrarAsignar(Depto vector[])
{
	FILE*archEmp=fopen("Empleados.dat","rb+");
	EmpArch empleadoX;
	int legX,pos;
	for(int i=0;i<50;i++)
	{
		if(vector[i].pri!=NULL)
		{
			cout<<"Departamento "<<i+1<<endl<<endl;
			while(vector[i].pri!=NULL)
			{
				legX = desencolar(vector[i].pri,vector[i].ult);
				pos = busquedaBinariaArch(archEmp,legX,empleadoX);
				cout<<"Legajo: "<<empleadoX.leg<<endl;
				cout<<"DNI: "<<empleadoX.dni<<endl;
				cout<<"Nombre y Apellido: "<<empleadoX.nombre<<endl<<endl;
				if(vector[i].cantV>0)
				{
					empleadoX.dto = i+1;
					fseek(archEmp,pos*sizeof(EmpArch),SEEK_SET);
					fwrite(&empleadoX,sizeof(EmpArch),1,archEmp);
					vector[i].cantV--;
				}
			}
		}
	}
	fclose(archEmp);
}

void mostrarArchivoEmp()
{
	cout<<"Archivo empleados actualizado"<<endl<<endl;
	FILE*archEmp=fopen("Empleados.dat","rb");
	EmpArch empleadoX;
	fread(&empleadoX,sizeof(EmpArch),1,archEmp);
	while(!feof(archEmp))
	{
		cout<<"Legajo: "<<empleadoX.leg<<endl;
		cout<<"Nombre y Apellido: "<<empleadoX.nombre<<endl;
		cout<<"DNI: "<<empleadoX.dni<<endl;
		cout<<"Dto: "<<empleadoX.dto<<endl<<endl;
		fread(&empleadoX,sizeof(EmpArch),1,archEmp);
	}
	fclose(archEmp);
}
