#include <iostream>
using namespace std;

typedef char str30[31];

struct EmpArch
{
	int leg;
	str30 nombre;
	int dni;
	int dto;
};

int main(){
	FILE*archEmp=fopen("Empleados.dat","wb");
	EmpArch empleadoX;
	cout<<"Legajo(fin=0): ";
	cin>>empleadoX.leg;
	while(empleadoX.leg!=0){
		cout<<"Nombre y Apellido: ";
		fflush(stdin);
		cin.getline(empleadoX.nombre,31,'\n');
		cout<<"DNI: ";
		cin>>empleadoX.dni;
		cout<<"Dto: ";
		cin>>empleadoX.dto;
		
		fwrite(&empleadoX,sizeof(EmpArch),1,archEmp);
		cout<<endl;
		cout<<"Legajo(fin=0): ";
		cin>>empleadoX.leg;
	}
	fclose(archEmp);
	
	return 0;
}


