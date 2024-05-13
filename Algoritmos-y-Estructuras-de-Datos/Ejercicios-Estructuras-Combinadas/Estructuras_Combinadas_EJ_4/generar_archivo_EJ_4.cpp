#include <iostream>
using namespace std;

struct Fecha
{
	int dia;
	int mes;
	int anio;
};

struct PartArch
{
	int codA;
	int nroS;
	Fecha fechaC;
	int rdo; 
};

int main(){
	FILE*archPart = fopen("Competidores.dat","wb");
	PartArch partXarch;
	cout<<"Cod. actividad(fin=0): ";
	cin>>partXarch.codA;
	while(partXarch.codA!=0){
		cout<<"Nro socio: ";
		cin>>partXarch.nroS;
		cout<<"mes: ";
		cin>>partXarch.fechaC.mes;
		cout<<"rdo: ";
		cin>>partXarch.rdo;
		
		fwrite(&partXarch,sizeof(PartArch),1,archPart);
		
		cout<<"Cod. actividad(fin=0): ";
		cin>>partXarch.codA;
	}
	fclose(archPart);
	
	return 0;
}
