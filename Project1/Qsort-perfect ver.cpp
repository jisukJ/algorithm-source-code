#include <iostream>

using namespace std;
int arr[1000];
bool cmp(int a, int b)
{
	return a < b;
}
int partition(int left, int right)
{
	int low = left;
	int high = right;
	while (1) {
		do {
			low++;
		} while (low < right&&cmp(arr[low], arr[left]));
		do {
			high--;
		} while (left < high&&cmp(arr[left], arr[high]));
		if (high < low)
			break;
		swap(arr[low], arr[high]);
	}
	swap(arr[left], arr[high]);
	return high;
}

void quicksort(int left, int right) {
	if (right <= left)
		return;
	int pivot = partition(left, right);
	quicksort(left, pivot);
	quicksort(pivot + 1, right);
}


int main()
{
	for (int i = 0; i < 1000; ++i)
		arr[i] = rand() % 100;
	for (int i = 0; i < 1000; ++i)
		cout << arr[i] << " ";
	cout << endl;
	quicksort(0, 1000);
	for (int i = 0; i < 1000; ++i)
		cout << arr[i] << " ";
	cout << endl;
}