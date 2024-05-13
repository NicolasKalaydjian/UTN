#include <iostream>
using namespace std;

typedef char str7[8];

struct InfraccionArch
{
	str7 pat;
	int fecha; // AAMMDD
	int codI; // 1 a 100
};

int main(){
	FILE*archInfracciones = fopen("InfraccionesV2.dat","wb");
	InfraccionArch infraccionX;
	cout<<"Cod. infraccion(fin=0): ";
	cin>>infraccionX.codI;
	while(infraccionX.codI!=0){
		cout<<"Patente: ";
		fflush(stdin);
		cin.getline(infraccionX.pat,8,'\n');
		cout<<"Fecha(AAMMDD): ";
		cin>>infraccionX.fecha;
		
		fwrite(&infraccionX,sizeof(InfraccionArch),1,archInfracciones);
		cout<<endl;
		cout<<"Cod. infraccion(fin=0): ";
		cin>>infraccionX.codI;
	}
	fclose(archInfracciones);
	
	return 0;
}


