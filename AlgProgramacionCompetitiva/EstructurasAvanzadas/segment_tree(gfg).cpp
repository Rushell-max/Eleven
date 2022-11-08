/*
https://www.geeksforgeeks.org/segment-tree-set-1-sum-of-given-range/
*/

#include <bits/stdc++.h>
#define vi vector<int>
using namespace std;

vi arr;
vi st;

int getMid(int l, int r) { return l + (r -l)/2; }

int getSumUtil(int st_l, int st_r, int l, int r, int st_i)
{
	if (l <= st_l && st_r <= r) // el segento esta dentro del rango que quiero
		return st[st_i];
	if (st_r < l || r < st_l)   // fuera del rango
		return 0;
	int mid = getMid(st_l, st_r);       // el segmento traslapa con el rango pedido
	return getSumUtil(st_l, mid, l, r, 2*st_i+1) +      // hijo izq
		getSumUtil(mid+1, st_r, l, r, 2*st_i+2);        // hijo der
}

void updateValueUtil(int st_l, int st_r, int i, int diff, int st_i)
{
	if (i < st_l || st_r < i)       // indice fuera del segmento
		return;
	st[st_i] = st[st_i] + diff;     // dentro del segmento
	if (st_l != st_r)
	{
		int mid = getMid(st_l, st_r);
		updateValueUtil(st_l, mid, i, diff, 2*st_i + 1);
		updateValueUtil(mid+1, st_r, i, diff, 2*st_i + 2);
	}
}

void updateValue(int n, int i, int new_val)
{
	if (i < 0 || n-1 < i)       // indice fuera de rango
	{
		cout<<"Invalid Input";
		return;
	}
	int diff = new_val - arr[i];
	arr[i] = new_val;
	updateValueUtil(0, n-1, i, diff, 0);        // actualiza valores en el ST
}

int getSum(int n, int l, int r)
{
	if (l < 0 || n-1 < r || l > r)      // indices falsos
	{
		cout<<"Invalid Input";
		return -1;
	}
	return getSumUtil(0, n-1, l, r, 0);
}

int constructSTUtil(int st_l, int st_r, int st_i)
{
	if (st_l == st_r)           // si es una hoja
	{
		st[st_i] = arr[st_l];
		return arr[st_l];
	}
	int mid = getMid(st_l, st_r);
	st[st_i] = constructSTUtil(st_l, mid, st_i*2+1) +
			constructSTUtil(mid+1, st_r, st_i*2+2);
	return st[st_i];
}

void constructST(int n)
{
	int x = (int)(ceil(log2(n)));
	int max_size = 2*(int)pow(2, x) - 1;
	st.resize(max_size);
	constructSTUtil(0, n-1, 0);
}

int main()
{
	arr = {1, 3, 5, 7, 9, 11};
	int n = arr.size();
	constructST(n);

	cout<<"Sum of values in given range = "<<getSum(n, 1, 3)<<endl;

	// Update: set arr[1] = 10 and update corresponding
	// segment tree nodes
	updateValue(n, 1, 10);

	// Find sum after the value is updated
	cout<<"Updated sum of values in given range = "<<getSum(n, 1, 3)<<endl;
	return 0;
}