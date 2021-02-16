void quicksort(vector<int>&arr, int left, int right) {
	if (right - 1 <= left) {
		return;
	}
	int st = left;
	int ed = right;
	int pivot = left;
	int tmp;
	while (1) {
		do {
			++st;
		} while (st < right&&arr[st] < arr[pivot]);
		do {
			--ed;
		} while (left < ed&&arr[pivot] < arr[ed]);
		if (ed <= st) {
			tmp = arr[ed];
			arr[ed] = arr[pivot];
			arr[pivot] = tmp;
			break;
		} else {
			tmp = arr[st];
			arr[st] = arr[ed];
			arr[ed] = tmp;
		}
	}
	quicksort(arr, left, ed);
	quicksort(arr, ed + 1, right);
}