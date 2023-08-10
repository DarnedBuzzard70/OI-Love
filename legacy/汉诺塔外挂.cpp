#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
int cnt;
void MouseMove(int x, int y){
	double fScreenWidth = ::GetSystemMetrics(SM_CXSCREEN) - 1;
	double fScreenHeight = ::GetSystemMetrics(SM_CYSCREEN) - 1;
	double fx = x*(65535.0f / fScreenWidth);
	double fy = y*(65535.0f / fScreenHeight);
	INPUT  Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
	Input.mi.dx = fx;
	Input.mi.dy = fy;
	SendInput(1, &Input, sizeof(INPUT));
}
void MouseLeftDown(){
	INPUT  Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &Input, sizeof(INPUT));
}
void MouseLeftUp(){
	INPUT  Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &Input, sizeof(INPUT));
	
}
void hanoi(int n,char a,char b,char c){
	if(n==0){
		return; 
	}
	hanoi(n-1,a,c,b);
	printf("Step %d: Move %d from %c to %c\n",++cnt,n,a,c);
//	cout<<"Step "<<++cnt<<": Move"<<n<<" from "<<a<<" to "<<c<<endl;
	int x,t1x=735,t2x=950,t3x=1155;
	if(a=='A'){
		x=t1x;
	}else if(a=='B'){
		x=t2x;
	}else if(a=='C'){
		x=t3x;
	}
	MouseMove(x,580);
	Sleep(10);
	MouseLeftDown();
	Sleep(20);
	MouseLeftUp();
	Sleep(300);
	if(c=='A'){
		x=t1x;
	}else if(c=='B'){
		x=t2x;
	}else if(c=='C'){
		x=t3x;
	}
	
	MouseMove(x,580);
	Sleep(10);
	MouseLeftDown();
	Sleep(20);
	MouseLeftUp();
	Sleep(300);
	hanoi(n-1,b,a,c);
}
int main(){
	int  n;
	scanf("%d",&n);
	hanoi(n,'A','B','C'); 
	return 0;
}
