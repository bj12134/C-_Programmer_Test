#include "Sort.h"

// Ԫ�ؽ���
void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

// ��ӡ���
void print(int arr[], int len) {
	for (int i = 0; i < len; ++i) {
		printf("arr[%d]:%d  ", i, arr[i]);
	}
}

// ѡ������
void select_sort(int arr[], int len) {
	// ��С��������
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
	// �ɴ�С
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

// ð������
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

// �򵥿��ٲ���
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

// ϣ������
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
//****** �������� *******
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

// ****** �鲢���� ******
void merge_sort_func(int arr[], int reg[], int start, int end) {
	if (start >= end)
		return;

	int len = end - start;
	int mid = start + (len >> 1);
	int start1 = start;
	int end1 = mid;
	int start2 = mid + 1;
	int end2 = end;
	// ��������в��
	merge_sort_func(arr, reg, start1, end1);
	merge_sort_func(arr, reg, start2, end2);

	// ����һ��k�����±����
	int k = start;
	// ����:�ֿ�����ÿ�������Ԫ��
	while (start1 <= end1 && start2 <= end2) {
		reg[k++] = arr[start1] < arr[start2] ? arr[start1++] : arr[start2++];
	}
	// �ұ߷����Ѿ�������,����߻���ʣ��Ԫ��δ����
	while (start1 <= end1) {
		reg[k++] = arr[start1++];
	}
	// ��߷����Ѿ�������,���ұ߻���ʣ��Ԫ��δ����
	while (start2 <= end2) {
		reg[k++] = arr[start2++];
	}
	// ���ź���ķ���Ԫ�ز��뵽Ҫ�����������
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