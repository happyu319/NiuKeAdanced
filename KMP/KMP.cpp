#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int>getNextArray(string str){
	vector<int>next;
	next.reserve(str.size());
	for (int index = 0; index < str.size(); index++){
		if (index == 0){
			next.push_back(-1);
			continue;
		}
		if (index == 1){
			next.push_back(0);
			continue;
		}
		int temp = next[index - 1];
		while (temp != -1){
			if (str[index - 1] == str[temp]){
				next.push_back(temp + 1);
				break;
			}
			else{
				temp = next[temp];
			}
		}
		if (temp == -1){
			next.push_back(0);
		}
	}
	return next;
}

int getIndexOf(string str1, string str2){
	if (str1.size() == 0 || str2.size() == 0 || str1.size() < str2.size()){
		return -1;
	}
	vector<int>next = getNextArray(str2);
	int i = 0, j = 0;
	while (i < str1.size() && j < str2.size()){
		if (str1[i] == str2[j]){
			i++;
			j++;
		}
		else if (next[j] == -1){
			i++;
		}
		else{
			j = next[j];
		}
	}
	return j == str2.size() ? i - j : -1;
}

int main(){
	string str1 = "asdfasdfgdfghjhjkghjkl";
	string str2 = "dfgdfghjhjk";
	int pos = getIndexOf(str1, str2);
	if (pos < 0){
		cout << "Str2 is not in Str1 !" << endl;
	}
	else{
		cout << "Str2 is in Str1 and the first position is at " << pos << " !" << endl;
	}
	system("pause");
	return 0;
}