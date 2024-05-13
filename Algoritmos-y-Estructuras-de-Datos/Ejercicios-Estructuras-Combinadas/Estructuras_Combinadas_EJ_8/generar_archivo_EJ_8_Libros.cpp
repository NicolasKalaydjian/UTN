#include <iostream>
using namespace std;

struct Libro
{
	int cod;
	char tit[31];
	char ape[16];
	int nac;
	int cant;
};

int main(){
	FILE*archLibros = fopen("Libros.dat","wb");
	Libro libroX;
	cout<<"Cod. Libro(fin=0): ";
	cin>>libroX.cod;
	while(libroX.cod!=0){
		cout<<"Titulo: ";
		fflush(stdin);
		cin.getline(libroX.tit,31,'\n');
		cout<<"Apellido del Autor: ";
		fflush(stdin);
		cin.getline(libroX.ape,16,'\n');
		cout<<"Nacionalidad: ";
		cin>>libroX.nac;
		cout<<"Cant. de ejemplares: ";
		cin>>libroX.cant;
		
		fwrite(&libroX,sizeof(Libro),1,archLibros);
		cout<<endl;
		
		cout<<"Cod. Libro(fin=0): ";
		cin>>libroX.cod;
	}
	fclose(archLibros);
	return 0;
}
