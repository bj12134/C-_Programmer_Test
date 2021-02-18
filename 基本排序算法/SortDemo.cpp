#include "Sort.h"

// 元素交换
void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

// 打印结果
void print(int arr[], int len) {
	for (int i = 0; i < len; ++i) {
		printf("arr[%d]:%d  ", i, arr[i]);
	}
}

// 选择排序
void select_sort(int arr[], int len) {
	// 由小到大排序
	for (int i = 0; i < len - 1; ++i) {
		int min = arr[0];
		for (int j = i + 1; j < len; ++j) {
			if (arr[i] > arr[j]) {
				swap(&arr[i], &arr[j]);
			}
		}
	}
	print(arr, len);
	printf("*******************************");
	// 由大到小
	for (int i = 0; i < len - 1; ++i) {
		int max = arr[0];
		for (int j = i + 1; j < len; ++j) {
			if (arr[i] < arr[j]) {
				swap(&arr[i], &arr[j]);
			}
		}
	}
	print(arr, len);
}

// 冒泡排序
void bubble_sort(int arr[], int len) {
	for (int i = 0; i < len - 1; ++i) {
		for (int j = 0; j < len - i - 1; ++j) {
			if (arr[j] < arr[j + 1]) {
				swap(&arr[j], &arr[j + 1]);
			}
		}
	}
	print(arr, len);
	printf("*******************************");
	for (int i = 0; i < len - 1; ++i) {
		for (int j = 0; j < len - i - 1; ++j) {
			if (arr[j] < arr[j + 1]) {
				swap(&arr[j], &arr[j + 1]);
			}
		}
	}
	print(arr, len);
}

// 简单快速插入
void sp_insert_sort(int arr[], int len) {
	for (int i = 1; i < len; ++i) {
		int tmp = arr[i];
		int j = i;
		for (; j > 0 && arr[j - 1] > tmp; --j) {
			arr[j] = arr[j - 1];
		}
		arr[j] = tmp;
	}
}

// 希尔排序
void shell_sort(int arr[], int len) {
	for (int gap = len >> 1; gap > 0; gap = gap >> 1) {
		for (int i = gap; i < len; ++i) {
			int tmp = arr[i];
			int j = i - gap;
			for (; j >= 0 && arr[j] > tmp; j -= gap) {
				arr[j + gap] = arr[j];
			}
			arr[j + gap] = tmp;
		}
		print(arr, len);
	}
}
//****** 快速排序 *******
int get_mid(int arr[], int left, int right) {
	int pivot = arr[left];

	while (left < right) {
		while (pivot < arr[right] && left < right) {
			right--;
		}
		arr[left] = arr[right];
		while (pivot > arr[left] && left < right) {
			left++;
		}
		arr[right] = arr[left];
	}
	arr[left] = pivot;
	return left;
}

void sort_func(int arr[], int start, int end) {
	if (start < end) {
		int mid = get_mid(arr, start, end);
		sort_func(arr, start, mid - 1);
		sort_func(arr, mid + 1, end);
	}
	return;
}

void quick_sort(int arr[], int len) {
	sort_func(arr, 0, len - 1);
	print(arr, len);
}

// ****** 归并排序 ******
void merge_sort_func(int arr[], int reg[], int start, int end) {
	if (start >= end)
		return;

	int len = end - start;
	int mid = start + (len >> 1);
	int start1 = start;
	int end1 = mid;
	int start2 = mid + 1;
	int end2 = end;
	// 将数组进行拆分
	merge_sort_func(arr, reg, start1, end1);
	merge_sort_func(arr, reg, start2, end2);

	// 设置一个k进行下标计数
	int k = start;
	// 分治:分开排序每个分组的元素
	while (start1 <= end1 && start2 <= end2) {
		reg[k++] = arr[start1] < arr[start2] ? arr[start1++] : arr[start2++];
	}
	// 右边分组已经处理完,但左边还有剩余元素未处理
	while (start1 <= end1) {
		reg[k++] = arr[start1++];
	}
	// 左边分组已经处理完,但右边还有剩余元素未处理
	while (start2 <= end2) {
		reg[k++] = arr[start2++];
	}
	// 将排好序的分组元素插入到要排序的数组中
	for (k = start; k < end; ++k) {
		arr[k] = reg[k];
	}
}
void merge_sort(int arr[], int len) {
	int reg[SIZE] = { 0 };
	merge_sort_func(arr, reg, 0, len - 1);
	print(arr, len);
}
}