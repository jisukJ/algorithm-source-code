#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

void Nomal_SA()
{
	string str[1000];
	cin >> str[0];
	int len = str[0].size();
	for (int i = 1; i < len; ++i)
	{
		str[i] = str[0].substr(i);
	}
		sort(str, str + len);
			for (int i = 0; i < len; ++i)
				cout << str[i] << endl;
			//N^2logN
			cout << endl;
}

const int MAX = 1 <<10;
string S;
int N,d,SA[MAX],group[MAX];
//group 안에는 상대적인 등수 마킹
//group[0]=3 group[1]=2 라고 하면 S[1....end]에가
//group[시작번째]= 등수;
//S[0..end]보다 사전적으로 앞에 있다는 이야기
//SA[등수]=str 시작 번째;

bool cmp(int i, int j)
{
	if (group[i] != group[j])
		return group[i] < group[j];
	i += d;
	j += d;
	return (i < N&&j < N) ? (group[i] < group[j]) : i >j;
}

void Manber_Myers()
{
	cin >> S;
	N = S.size();
	for (int i = 0; i < N; ++i)
	{
		SA[i] = i;
		group[i] = S[i];
	}

	cout << "SA = ";
	for (int i = 0; i < N; ++i)
		cout << SA[i] << " ";
	cout << endl;
	cout << "group = ";
	for (int i = 0; i < N; ++i)
		cout << group[i] << " ";
	cout << endl;

	for (d = 1;; d *= 2)
	{
		sort(SA, SA + N, cmp);
		cout << "SA = ";
		for (int i = 0; i < N; ++i)
			cout << SA[i] << " ";
		cout << endl;
		
		int temp[100] = { 0 };
		for (int i = 0; i < N - 1; ++i)
			temp[i + 1] = temp[i] + cmp(SA[i], SA[i + 1]);
		for (int i = 0; i < N; ++i)
			group[SA[i]] = temp[i];

		cout << "group = ";
		for (int i = 0; i < N; ++i)
			cout << group[i] << " ";
		cout << endl;

		if (temp[N - 1] == N - 1)
			break;
	}
	cout << endl;
	cout << "연산 후" << endl;
	for (int i = 0; i < N; ++i)
		cout << S.substr(SA[i], S.size()) <<" "<< S.substr(SA[i], S.size()) .size()<< endl;
	
	for (int i = 0; i < N; ++i)
		cout << SA[i] << " ";
	cout << endl;
	for (int i = 0; i < N; ++i)
		cout << group[i] << " ";
}

int LCP[1 << 10];

void constructLCP() {
	for (int i = 0, k = 0; i < N; ++i, k = max(k - 1, 0)) {
		if (group[i] == N - 1)
		{
			//cout << "예외상황 발생 이떄 i= "<<i <<" group[i]= " << group[i] << endl;
			continue;
		}
		for (int j = SA[group[i] + 1]; S[i + k] == S[j + k]; ++k);
		LCP[group[i]] = k;
	}
	cout << endl;
	cout << "LCP ";
	for (int i = 0; i < N; ++i)
		cout << LCP[i] << " ";
}

int main()
{
	//Nomal_SA();
	Manber_Myers();
	constructLCP();


}