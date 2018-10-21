#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int palindromeRadius(string str, int center){//以center位置为中心的最大回文半径
	int index = center;
	int radius = 0;
	while (index >= 0){
		if (str[index] == str[2 * center - index]){
			index--;
			radius++;
		}
		else{
			break;
		}
	}
	return radius;
}

string manacher(string str){
	string temp = "#";
	for (int i = 0; i < str.size(); i++){
		temp = temp + str[i] + "#";
	}
	int *arr = new int[temp.size()];
	int radius = -1;//回文半径
	int center = -1;//回文中心
	int right = -1;//最大回文右边界
	int left = -1;//左边界
	int maxCenter = INT_MIN;//最大回文中心
	for (int i = 0; i < temp.size(); i++){
		//当前位置在最大回文右边界之外，直接暴力求回文半径
		if (i >= right){
			center = i;
			radius = palindromeRadius(temp, center);
			right = center + radius - 1;
			arr[i] = radius;
		}
		else{
			left = 2 * center - i;
			
			if (arr[left] < left - (2 * center - right) + 1){
				arr[i] = arr[left];
			}
			//当前位置关于回文中心的对称位置的回文半径部分在回文内部
			else if (arr[left] > left - (2 * center - right) + 1){
				arr[i] = right - i;
			}
			//当前位置关于回文中心的对称位置的回文半径刚好与回文重合
			else{
				arr[i] = palindromeRadius(temp, i);
			}
		}
		if (arr[i] >= arr[maxCenter]){
			maxCenter = i;//最大回文中心位置
		}
	}

	/*
	int C = -1;
	int R = -1;
	int maxLength = INT_MIN;
	int *pArr = new int[temp.size()];
	for (int i = 0; i!=temp.size(); i++){
		pArr[i] = R > i ? min(arr[2 * C - i], R - i) : 1;
		while (i + pArr[i] < temp.size() && i - pArr[i]>-1){
			if (temp[i + pArr[i]] == temp[i - pArr[i]]){
				pArr[i]++;
			}
			else{
				break;
			}
		}
		if (i + pArr[i] > R){
			R = i + pArr[i];
			C = i;
		}
		maxLength = max(maxLength, pArr[i]);
	}
	*/
	return temp.substr(maxCenter - arr[maxCenter] + 1, 2 * arr[maxCenter] - 1);
}

int main(){
	string str;
	cin >> str;
	
	string temp, res;
	temp = manacher(str);
	for (int i = 0; i < temp.size(); i++){
		if (i % 2 != 0){
			res = res + temp[i];
		}
	}
	cout << res << endl;

	system("pause");
	return 0;
}