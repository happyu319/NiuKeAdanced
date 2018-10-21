#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int GetPivotIndex(vector<int>&arr, int left, int right);
int partition(vector<int>&arr, int left, int right, int middleValue);
int BFPRT(vector<int>&arr);

void swap(vector<int>&arr, int i, int j) {
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void InsertionSort(vector<int>&arr, int begin, int end) {
	for (int i = begin + 1; i < end; i++) {
		for (int j = i - 1; j >= begin; j--) {
			if (arr[j] > arr[j + 1]) {
				swap(arr, j, j + 1);
			}
			else
				break;
		}
	}
}

int GetPivotIndex(vector<int>&arr, int left, int right){//获取中位数，用于数组划分
	int size = right - left + 1;
	if (size <= 5){
		InsertionSort(arr, left, right + 1);
		return arr[(size - 1) / 2 + left];
	}
	vector<int>temp;
	for (int i = left; i + 4 <= right; i += 5){
		InsertionSort(arr, i, i + 5);
		temp.push_back(arr[i + 2]);
	}
	return GetPivotIndex(temp, 0, temp.size() - 1);
}

int partition(vector<int>&arr, int left, int right, int middleValue){//对数组进行划分
	if (arr.size() == 0 && left>right){
		return -1;
	}
	int L = left - 1;
	int R = right + 1;
	for (int cur = left; cur < R; cur++){
		if (arr[cur] < middleValue){
			swap(arr, cur, ++L);
		}
		else if (arr[cur]>middleValue){
			swap(arr, cur, --R);
			cur--;
		}
	}
	return L + 1;
}

int BFPRT(vector<int>&arr, int left, int right, int K){
	int middleValue = GetPivotIndex(arr, left, right);
	int pos = partition(arr, left, right, middleValue);
	if (pos == K){
		return arr[K];
	}
	else if (pos < K){
		return BFPRT(arr, pos + 1, right, K);
	}
	else{
		return BFPRT(arr, left, pos - 1, K);
	}
}


int Comparator(vector<int>&arr, int k) {
	sort(arr.begin(), arr.end());
	return arr[k];
}

vector<int>generatorRandomArray(int size, int maxValue) {
	vector<int>arr;
	for (int i = 0; i < size; i++) {
		arr.push_back(rand() % maxValue - rand() % (maxValue - 1));
	}
	return arr;
}

vector<int>copyArray(vector<int>&arr) {
	vector<int>newArray;
	for (int i = 0; i < arr.size(); i++) {
		newArray.push_back(arr[i]);
	}
	return newArray;
}

bool isEqual(vector<int>&arr1, vector<int>&arr2) {
	for (int i = 0; i < arr1.size(); i++) {
		if (arr1[i] != arr2[i]) {
			return false;
		}
	}
	return true;
}

void printArray(vector<int>&arr) {
	for (int i = 0; i < arr.size(); i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

int main(){
	int testTime = 5000;
	int maxSize = 1000;
	int maxValue = 100;
	bool succeed = true;
	for (int i = 0; i < testTime; i++) {
		int size = rand() % maxSize + 1;
		int K = rand() % size;
		vector<int>arr1 = generatorRandomArray(size, maxValue);
		vector<int>arr2(arr1);
		int num1 = BFPRT(arr1, 0, arr1.size() - 1, K);
		int num2 = Comparator(arr2, K);
		if (num1 != num2){
			succeed = false;
			cout << i << ":" << num1 << " " << num2 << endl;
			break;
		}
		
	}
	if (succeed)
		cout << "Nice!" << endl;
	else
		cout << "Fucking!" << endl;
	system("pause");
	return 0;
}