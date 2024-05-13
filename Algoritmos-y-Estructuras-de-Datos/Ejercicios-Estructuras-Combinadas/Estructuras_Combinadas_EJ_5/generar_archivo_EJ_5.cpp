#include <iostream>
using namespace std;

struct cobroArch
{
	int codC; 
	int nroC; // 1 a 12
};

int main(){
	FILE*archCobros = fopen("Cobranzas.dat","wb");
	cobroArch cobroXarch;
	cout<<"Cod. cliente(fin=0): ";
	cin>>cobroXarch.codC;
	while(cobroXarch.codC!=0){
		cout<<"Nro cuota: ";
		cin>>cobroXarch.nroC;
		
		fwrite(&cobroXarch,sizeof(cobroArch),1,archCobros);
		
		cout<<"Cod. cliente(fin=0): ";
		cin>>cobroXarch.codC;
	}
	fclose(archCobros);
	
	return 0;
}
