#include <iostream>
using namespace std;

struct tVenta
{
	int codV;
	int nroF;
	float imp;
};

int main(){
	FILE*archVentas = fopen("VENTAS.dat","wb");
	tVenta ventaX;
	cout<<"Cod. vendedor: ";
	cin>>ventaX.codV;
	while(ventaX.codV!=0){
		cout<<"Nro fact: ";
		cin>>ventaX.nroF;
		cout<<"Importe: ";
		cin>>ventaX.imp;
		
		fwrite(&ventaX,sizeof(tVenta),1,archVentas);
		
		cout<<"Cod. vendedor: ";
		cin>>ventaX.codV;
	}
	fclose(archVentas);
	
	return 0;
}
