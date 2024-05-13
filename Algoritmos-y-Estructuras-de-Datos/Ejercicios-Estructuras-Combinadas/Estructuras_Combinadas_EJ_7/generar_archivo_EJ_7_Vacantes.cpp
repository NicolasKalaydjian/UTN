#include <iostream>
using namespace std;

typedef char str7[8];

struct VacArch
{
	int dto;
	int cantV;
};

int main(){
	FILE*archVac = fopen("Vacantes.dat","wb");
	VacArch vacanteX;
	cout<<"Dto(fin=0): ";
	cin>>vacanteX.dto;
	while(vacanteX.dto!=0){
		cout<<"Cant. Vacantes: ";
		cin>>vacanteX.cantV;
		
		fwrite(&vacanteX,sizeof(VacArch),1,archVac);
		cout<<endl;
		cout<<"Dto(fin=0): ";
		cin>>vacanteX.dto;
	}
	fclose(archVac);
	
	return 0;
}


