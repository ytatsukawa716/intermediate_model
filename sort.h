#ifndef SORT_H
#define SORT_H
#include <vector>

template<typename _T> 
_T _MAX(_T x, _T y) { return x < y ? y : x; }

template<typename _T>
_T _MIN(_T x, _T y) { return x > y ? y : x; }

class Sort {
public:
	std::vector<int> number;

	template<typename _T>
	void ascending_sort(std::vector<_T>& A) {
		int left = 0;
		int right = A.size() - 1;
		_Create_number(A.size());
		ascendingsort(&A, left, right);
	}

	template<typename _T>
	void descending_sort(std::vector<_T>& A) {
		int left = 0;
		int right = A.size() - 1;
		_Create_number(A.size());
		descendingsort(&A, left, right);
	}

private:
	template<typename _T>
	_T med3(_T x, _T y, _T z) { return _MIN(_MAX(x, y), z); }

	void _Create_number(int size) {
		number = std::vector<int>(size);
		for (int i = 0; i < size; i++) number[i] = i;
	}

	template<typename _T>
	void ascendingsort(std::vector<_T>* A, int left, int right) {
		if (left < right) {
			_T pivot = med3((*A)[left], (*A)[left + (right - left) / 2], (*A)[right]);
			int l = left;
			int r = right;
			while (true) {
				while ((*A)[l] < pivot) l++;
				while ((*A)[r] > pivot) r--;
				if (l >= r) break;
				std::swap((*A)[l], (*A)[r]);
				std::swap(number[l], number[r]);
				l++;
				r--;
			}
			ascendingsort(A, left, l - 1);
			ascendingsort(A, r + 1, right);
		}
	}

	template<typename _T>
	void descendingsort(std::vector<_T>* A, int left, int right) {
		if (left < right) {
			_T pivot = med3((*A)[left], (*A)[left + (right - left) / 2], (*A)[right]);
			int l = left;
			int r = right;
			while (true) {
				while ((*A)[l] > pivot) l++;
				while ((*A)[r] < pivot) r--;
				if (l >= r) break;
				std::swap((*A)[l], (*A)[r]);
				std::swap(number[l], number[r]);
				l++;
				r--;
			}
			descendingsort(A, left, l - 1);
			descendingsort(A, r + 1, right);
		}
	}
};

#endif //SORT_H
