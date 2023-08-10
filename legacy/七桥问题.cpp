#include <iostream>
int data[100005];
using namespace std;
int main() {
	int point,bridge;//当成七桥问题
	cin>>point>>bridge;
	int a,b; //输入的两个数 
	for(int i=1;i<=bridge;i+=1){
		cin>>a>>b;
		data[a]+=1;
		data[b]+=1;
	}
	int odd=0;//奇数的数量
	bool safe=true;//定义地图是否被分成多份； 
	for(int k=1;k<=point;k+=1){
		if(data[k]%2==1){
			odd+=1;
		}
		if(data[k]==0){
			safe=false;
		} 
	} 
	if(safe&&(odd==0)){//情况1：全是偶点 
		cout<<"Merry Christmas";
	}else if(safe&&(odd==2)){//情况2：2个奇点 
		cout<<"Good job";
	}else{//情况3：奇点数量不是0或2；或者地图被分成多份。 
		cout<<"QAQ";
	} 
	return 0;
}
