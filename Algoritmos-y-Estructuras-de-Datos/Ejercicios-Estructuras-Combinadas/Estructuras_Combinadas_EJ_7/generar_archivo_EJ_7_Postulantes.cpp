#include <iostream>
using namespace std;

typedef char str7[8];

struct PostArch
{
	int leg;
	int dto;
};

int main(){
	FILE*archPost = fopen("Postulantes.dat","wb");
	PostArch postX;
	cout<<"Cod. Leg(fin=0): ";
	cin>>postX.leg;
	while(postX.leg!=0){
		cout<<"Dto: ";
		cin>>postX.dto;
		
		fwrite(&postX,sizeof(PostArch),1,archPost);
		cout<<endl;
		cout<<"Cod. Leg(fin=0): ";
		cin>>postX.leg;
	}
	fclose(archPost);
	
	return 0;
}
