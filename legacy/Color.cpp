#include<bits/stdc++.h>
using namespace std;
int n;
char col[2][100010];
inline int read_int(){
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-'){
			w=-1;
		} 
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		s=s*10+ch-'0';
		ch=getchar();
	}
	return s*w;
}
bool judge(int r,int nt,int mt,int wt,int h1,int h2,int wt2){
	if(r==1){
	}else if(r==2){
		if(nt==1 && mt==1 && wt==2 && wt2==1){
			return false;
		}
		if(nt==2 && wt==2 && wt2==2){
			return false;
		}
	}else if(r==3){
		if(mt==2){
			if(nt==1 && wt==1){
				return false;
			}
		}
		if(nt==2){
			return false;
		}
	}else if(r==4){
		return false;
	}
	return true;
}
int core(){
	int sum=0;
	for(int i=0;i<n;i++){
		if(col[0][i]=='1'){
			sum++;
		}
		if(col[1][i]=='1'){
			sum++;
		}
	}
	for(int i=0;i<n;i++){
		if(col[0][i]=='1' && col[0][i+1]=='1' && col[0][i+2]=='1' && col[1][i+1]=='1'){
			return 1;
		}
		if(col[1][i]=='1' && col[1][i+1]=='1' && col[1][i+2]=='1' && col[0][i+1]=='1'){
			return 1;
		}
		if(col[0][i]=='1' && col[0][i+1]=='1' && col[1][i]=='1' && col[1][i+1]=='1' && col[0][i+3]=='1' && col[0][i+4]=='1' && col[1][i+3]=='1' && col[1][i+4]=='1'){
			return 1;
		}
	}
	if(sum>n){
		return 1;
	}
	int r1=0,n1=0,m1=0,w1=0,h11=0,h12=0,w21=0;
	if(col[0][0]=='1'){
		r1++;
		n1++;
		h11++;
	}
	if(col[0][1]=='1'){
		r1++;
		m1++;
		h11++;
	}
	if(col[1][0]=='1'){
		r1++;
		n1++;
		h12++;
	}
	if(col[1][1]=='1'){
		r1++;
		m1++;
		h12++;
	}
	if(col[0][2]=='1'){
		w1++;
		h11++;
	}
	if(col[1][2]=='1'){
		w1++;
		h12++;
	}
	if(col[0][3]=='1'){
		w21++;
		h11++;
	}
	if(col[1][3]=='1'){
		w21++;
		h12++;
	}
	if(judge(r1,n1,m1,w1,h11,h12,w21)==false){
		return 1;
	}
	int r2=0,n2=0,m2=0,w2=0,h21=0,h22=0,w22;
	if(col[0][n-1]=='1'){
		r2++;
		n2++;
		h21++;
	}
	if(col[0][n-2]=='1'){
		r2++;
		m2++;
		h21++;
	}
	if(col[1][n-1]=='1'){
		r2++;
		n2++;
		h22++;
	}
	if(col[1][n-2]=='1'){
		r2++;
		m2++;
		h22++;
	}
	if(col[0][n-3]=='1'){
		w2++;
		h21++;
	}
	if(col[1][n-3]=='1'){
		w2++;
		h22++;
	}
	if(col[0][n-4]=='1'){
		w22++;
		h21++;
	}
	if(col[1][n-4]=='1'){
		w22++;
		h22++;
	}
	if(judge(r2,n2,m2,w2,h21,h22,w22)==false){
		return 1;
	}
	return 0;
}
int main(){
	int T=read_int();
	for(int i=0;i<T;i++){
		n=read_int();
		for(int j=0;j<2;j++){
			scanf("%s",col[j]);
		}
		if(core()==0){
			puts("RP");
		}else{
			puts("++");
		}
	}
	return 0;
} 
