/*
2_4. Дан отсортированный массив различных целых чисел A[0..n-1] и массив целых чисел B[0..m-1].
Для каждого элемента массива B[i] найдите минимальный индекс элемента массива A[k], ближайшего по значению к B[i].
*/
#include <iostream>
#include <cmath>

//чтобы функция expSearch могла вернуть 2 int
struct twoInt {
	int first, last;

	twoInt(int first, int last) : first(first), last(last) {}
};


//функция возвращает правую границу бинарного поиска, левую можно получить побитовым сдвигом 
twoInt expSearch (int* arr, int n, int elem) {
	int i = 1;
	for ( ; i < n; i=i<<1) {
		if (elem < arr[i])
			return twoInt(i>>1, i);
	}
	return twoInt(i>>1, n - 1);
}

//функция для нахождения минимального индекса ближайшего по значению к B[i]
int binarySearch (int* arr, int n, int elem) {
	twoInt range = expSearch(arr, n, elem);
	int first = range.first;
	int last = range.last;
    while (first < last) {
        int middle = (last + first) / 2;
        if (arr[middle] < elem)
            first = middle + 1;
        else
            last = middle;
    }
	if ((first!=0 && std::abs(arr[first] - elem) >= std::abs(arr[first - 1] - elem)))
		return first - 1;
    return first;
}

int main() {
	int n, m;
	
	std::cin >> n;
	int* A = new int[n];
	for (int i = 0; i < n; i++) {
		std::cin >> A[i];
	}

	std::cin >> m;
	int* B = new int[m];
	for (int i = 0; i < m; i++) {
		std::cin >> B[i];
	}
	
	for (int i = 0; i < m; i++) {
		std::cout << binarySearch(A, n, B[i]);
		if (i < m - 1)
			std::cout << ' ';
	}

	delete[] A;
	delete[] B;
}
