#include <iostream>
int data[100005];
using namespace std;
int main() {
	int point,bridge;//������������
	cin>>point>>bridge;
	int a,b; //����������� 
	for(int i=1;i<=bridge;i+=1){
		cin>>a>>b;
		data[a]+=1;
		data[b]+=1;
	}
	int odd=0;//����������
	bool safe=true;//�����ͼ�Ƿ񱻷ֳɶ�ݣ� 
	for(int k=1;k<=point;k+=1){
		if(data[k]%2==1){
			odd+=1;
		}
		if(data[k]==0){
			safe=false;
		} 
	} 
	if(safe&&(odd==0)){//���1��ȫ��ż�� 
		cout<<"Merry Christmas";
	}else if(safe&&(odd==2)){//���2��2����� 
		cout<<"Good job";
	}else{//���3�������������0��2�����ߵ�ͼ���ֳɶ�ݡ� 
		cout<<"QAQ";
	} 
	return 0;
}
