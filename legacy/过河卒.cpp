#include<bits/stdc++.h>
using namespace std;
long long data[30][30];
bool panduan[30][30];
int main() {
	int add_x_b;
	int add_y_b;
	int add_x_h;
	int add_y_h; 
	cin>>add_x_b>>add_y_b>>add_x_h>>add_y_h;
	panduan[add_x_h][add_y_h] = 1;
	if(add_x_h > 1 && add_y_h != 0)   panduan[add_x_h - 2][add_y_h - 1] = 1;
	if(add_x_h < 19 && add_y_h != 0)  panduan[add_x_h + 2][add_y_h - 1] = 1;
	if(add_x_h > 1 && add_y_h != 20)  panduan[add_x_h - 2][add_y_h + 1] = 1;
	if(add_x_h < 19 && add_y_h != 20) panduan[add_x_h + 2][add_y_h + 1] = 1;
	if(add_x_h != 0 && add_y_h > 1)   panduan[add_x_h - 1][add_y_h - 2] = 1;
	if(add_x_h != 0 && add_y_h < 19)  panduan[add_x_h - 1][add_y_h + 2] = 1;
	if(add_x_h != 20 && add_y_h > 1)  panduan[add_x_h + 1][add_y_h - 2] = 1;
	if(add_x_h != 20 && add_y_h < 19) panduan[add_x_h + 1][add_y_h + 2] = 1;
	for(int i = 0; i <= add_x_b; ++i) {
		for(int j = 0; j <= add_y_b; ++j) {
			if(!panduan[i][j]) {
				if(i == 0 && j == 0)
					data[0][0] = 1;
				else if(i == 0 && j > 0)
					data[0][j] = data[0][j - 1];
				else if(i > 0 && j == 0)
					data[i][0] = data[i - 1][0];
				else
					data[i][j] = data[i - 1][j] + data[i][j - 1];
			}
		}
	}

	printf("%lld\n", data[add_x_b][add_y_b]);
	return 0;
}
