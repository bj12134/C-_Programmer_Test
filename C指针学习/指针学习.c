#include <stdio.h>
#include <malloc.h>
int my_strlen(char* s) {
	char* p = s;
	while (*p != 0) {
		p++;
	}
	return p - s;
}


void test() {	// 指针的初级认识
	// 指针类型---不同的类型存放不同的值
	int num = 1024;
	char* pc = (char*)&num;
	int* pi = &num;
	printf("pc: 0x%p   pc + 1: 0x%p   pc + 2: 0x%p\n",pc, pc + 1, pc + 2);
	printf("pi: 0x%p   pi + 1: 0x%p   pi + 2: 0x%p\n",pi, pi + 1, pi + 2);
	/*
	pc: 0x0000004[4]   pc + 1: 0x0000004[5]   pc + 2: 0x0000004[6]
	pi: 0x00F3F84[4]   pi + 1: 0x00F3F84[8]   pi + 2: 0x00F3F84[C]
	*/
	// 结论：指针的类型决定了指针向前或向后走一步的移动距离
	printf("pc-sizeof: %u\n", sizeof(pc));
	printf("pi-sizeof: %u\n", sizeof(pi));
	// 结论：指针类型的大小:x86<->为4个字节	x64<->大小为8个字节
}
void test_02(){
	// 指针的解引用
	int n = 0x11223344;
	char* pc = (char*)&n;
	int* pi = &n;
	printf("*pc = %d , *pi = %d\n", *pc, *pi);
	*pc = 0x55;
	printf("*pc = %d , *pi = %d\n", *pc, *pi);
	*pi = 0;
	printf("*pc = %d , *pi = %d\n", *pc, *pi);
	// 结论：指针的解引用其实就是对指针存放的地址进行查找
	//		 >>即将指针所存放的地址所指向的变量解析出来并进行引用
	//		 指针的类型决定了对指针引用的时候能访问/操作几个字节，
	//		 >>通过上面代码测出：char*对n的访问/操作为一个字节，int*对n的访问/操作为四个字节	
}

void test_03(){	
	/*
		指针运算：
			1.指针 +,-变量
			2.指针-指针
			3.指针的关系运算符
	*/
	// 1.指针 + - 变量
	int arr[10] = { 1,2,3,4,5,6,7,8,9,0 };
	int* p1 = arr;
	printf("使用指针进行打印：");
	for (int i = 0; i < 10; ++i) {
		if (i % 5 == 0) {
			printf("\n");
		}
		printf("p1 + %d : %d     ", i, *(p1 + i));
	}
	printf("\n");
	printf("使用数组进行打印：");
	for (int i = 0; i < 10; ++i) {
		if (i % 5 == 0) {
			printf("\n");
		}
		printf("arr[%d] : %d     ", i, arr[i]);
	}
	printf("\n");
	printf("使用指针加法运算打印：");
	for (int i = 0; i < 10; ++i) {
		if (i % 5 == 0) {
			printf("\n");
		}
		printf("p1 + %d : %d     ", i, *p1++);
	}
	printf("arr: %d\n", *arr);
	// 结论：
	//		1.指针与变量进行运算，类似于使用数组名+数组下标
	//		2.数组名是数组首元素的地址(由打印结果可以看出<arr: 1>)
	//		>>但是二者有着区分，如可以使用指针进行++运算,数组名便不可以
	printf("\n");
	printf("Hello World有多长 : %d\n", my_strlen("Hello World"));
	int n1 = 10;
	int n2 = 20;
	int* pn1 = &n1;
	int* pn2 = &n2;
	printf("n1_addr: %p\n",&n1);
	printf("n2_addr: %p\n", &n2);
	printf("pn1 - pn2 : %u\n", pn1 - pn2);
	pn1 = arr;
	pn2 = pn1 + 9;
	printf("pn1 - pn2 : %u\n", pn1 - pn2);
	/* 
		测试结果：
			n1_addr: 004FF618
			n2_addr: 004FF60C
			pn1 - pn2 : 3
			3是如何来的？(004FF618 - 004FF60C<>) / 4 = 3
			为啥 /4？指针定义为int*，而int* 在x86下大小为4个字节
			这也整好验证我们上面得出的结论：指针的类型决定了对指针引用的时候能访问/操作几个字节
	*/
	// 结论：
	//		1.同类型：指针与指针进行相减(从高位向低位减)，可以得到两个指针的相对位置
}

void test_04() {
	// 二级指针
	int n = 10;
	int* pn = &n;
	int** ppn = &pn;
	printf("n_addr = %p\n", &n);
	printf("pn_addr = %p\n",&pn);
	printf("ppn_addr = %p\n",&ppn);
	// 通过打印出的数据显示：指针也是个变量，也有着自己的变量地址
	printf("对pn和*ppn进行测试：\n");
	printf("&pn = %p\n", &pn);
	printf("pn = %p\n", pn);
	printf("*ppn = %p\n", *ppn);
	// 结论：二级指针的解引用就是一级指针，二次解引用就是对一级指针进行解引用
	//		 例如：ppn = &pn;	此时就是二级指针ppn指向一级指针pn的地址
	//			   pn = &n;		就是一级指针pn指向变量n的地址
	//			   *ppn => pn;	代表对pn的地址进行解析，得到pn所存放的n的地址
	//			   **pn => *pn => n	二次解引用,在上述结论的基础上再次解析,
	//							就是对pn进行解引用，得到n的地址，以%d打印输出和n的值一样
}
void print_arr(int(*arr)[4], int row, int col) {
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			printf("arr[%d][%d] = %d   ", i, j, *(*(arr+i))+j);
			// *(arr + i)[j] = *(arr + i + j)
		}
		printf("\n");
	}
}
void test_05() {
	// 指针数组 和 数组指针
	/*
		先来认识一下什么是指针数组，什么是数组指针
		指针数组：int* arr[3];	 -- 是数组,是一个指针指向一个大小为3的整形数组
		数组指针：int (*arr)[3]; -- 是指针
		数组指针是一个指向数组的指针
		指针数组是一个存放指针的数组
	*/
	int n1 = 10;
	int n2 = 20;
	int n3 = 30;
	int* p1 = &n1;
	int* p2 = &n2;
	int* p3 = &n3;
	int* arr[3] = {p1,p2,p3};	// arr[3]是一个数组，有3个元素，每个元素都是一个指针
	for (int i = 0; i < 3; ++i) {
		printf("arr[%d] -- 0x%p -- %d\n", i, arr[i], *arr[i]);
	}
	/*
		测试结果：
		arr[0] -- 0x007CFCF0 -- 10
		arr[1] -- 0x007CFCE4 -- 20
		arr[2] -- 0x007CFCD8 -- 30
		arr[i] --> 找出数组该位置存放的元素
		0x007CFCF0 --> 打印出arr[i]的值，发现是一个十六进制的地址，表明该数组中存放的元素为指针
		10 --> 对数组存放元素(指针)进行解引用，打印出指针指向变量的值
	*/
	int arr1[3][5] = { 1,2,3, 1,2,3, 1,2,3, 1,2,3, 1,2,3, };
	//print_arr(arr, 3, 5);
	// arr1是二维数组的首元素的地址，也是二维数组的第一行
	// 传arr，相当于传二维数组的首地址过去，可以用数组指针进行接收
	// arr传参过去 == int *[3]
}

void test_06() {
	// 字符指针 -- char* 
	char str1[] = "hello bit.";
	char str2[] = "hello bit.";
	char* str3 = "hello bit.";
	char* str4 = "hello bit.";
	printf("&str1 : 0x%p\n", &str1);
	//printf("str1 : 0x%p\n", str1);

	printf("&str1 + 1 : 0x%p\n", &str1 + 1);
	//printf("str1 + 1 : 0x%p\n", str1 + 1);
	printf("&str1 + 2 : 0x%p\n", &str1 + 2);
	printf("(&str1 + 1) - &str1 : %u\n", 0x010FF707 - 0x010FF6FC);
	printf("(&str1 + 2) - (&str1 + 1) : %u\n", 0x010FF712 - 0x010FF707);
	/*
	&str1 : 0x010FF6FC
&str1 + 1 : 0x010FF707
&str1 + 2 : 0x010FF712
		测试结果：
		&str1 : 0x00F7FAA8
		str1 : 0x00F7FAA8
		&str1 + 1 : 0x00F7FAB3
		str1 + 1 : 0x00F7FAA9
		0x00F7FAA8 - 0x00F7FAB3 = 11 说明+1 直接
		发现：&str1 与 str1 的值虽然一样，但是&str1 + 1 与 str1 + 1 不一样
			结论：&数组名 与 数组名 代表的含义不同
			数组的地址+1，结果移动了整个数组的大小
			数组首元素的地址+1，结果移动了一个数组元素大小的地址
			&str1 表示 str1数组的首地址
			str1 表示str1数组的首元素的地址
	*/
	//// 打印各自的地址
	//printf("str1 : 0x%p\n", str1);
	//printf("str2 : 0x%p\n", str2);
	//printf("str3 : 0x%p\n", str3);
	//printf("str4 : 0x%p\n", str4);
	if (str1 == str2)
		printf("str1 and str2 are same\n");
	else
		printf("str1 and str2 are not same\n");

	if (str3 == str4)
		printf("str3 and str4 are same\n");
	else
		printf("str1 and str2 are not same\n");
	/*
		输出结果：
			str1 and str2 are not same
			str3 and str4 are same
		结果分析：
			str1 == str2 进行比较，实质上是两个数组的首元素的地址进行比较
			由于str1、str2是数组，一开始内存就会给他们各自分配一段内存空间进行数据存储
			所以str1 和 str2 首元素地址是不同的，if判定为假，但str1和str2存储的内容是一样的
			str3 == str4 进行比较，由于常量字符串会被单独存放到一个内存区域，所以
			str3 和 str4 都指向常量字符串的首地址，指向是一样的
			验证上述结论：指针和数组名作用不一样
	*/
}

// 数组传参
//void test_arr1_01(int arr[]) {}
//void test_arr1_02(int arr[10]) {}
//void test_arr1_03(int* arr) {}
//void test_arr1_04(int* arr[10]) {}
//void test_arr1_05(int** arr) {}

void test_arr2_01(int arr[3][5]) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 5; ++j) {
			printf("arr[%d][%d] = %d   ", i,j,arr[i][j]);
		}
		printf("\n");
	}
}
//void test_arr2_02(int arr[3][]) {}
//void test_arr2_03(int arr[][]) {}
// -- 数组传参，可以不知道有多少行，但是必须知道一行多少个元素
// 所以上面两个函数传参是有错误的
void test_arr2_04(int arr[][5]) {}
void test_arr2_05(int *arr[5]) {}
void test_arr2_06(int ** arr) {}
void test_arr2_08(int *arr) {}
void test_arr2_07(int (*arr)[5]) {}
// 上面俩函数是不可以传入二维数组的，*arr是一级指针，
void test_07() {
	// 数组传参：一维数组 和 二维数组
	// 指针传参：一级指针 和 二级指针
	// 一维数组传参
	int arr1[10] = { 0 };
	int* arr1_p[10] = { 0 };
	int arr2[3][4] = { 1,2,3, 4,5,6, 7,8,9, 10,11,12 };

	// 一维数组  指针数组  二维数组
	//test_arr1_01(arr1);
	//test_arr1_02(arr1);
	//test_arr1_03(arr1);

	//test_arr1_04(arr1_p);
	//test_arr1_05(arr1_p);

	//print_arr(arr2,3,4);
	//test_arr2_04(arr2);
	//test_arr2_05(arr2);
	//test_arr2_06(arr2);
	//test_arr2_07(arr2);
	//test_arr2_08(arr2);
} 
/*
	int (*func)();	函数指针，是一个指向函数的指针
	int (*func)(int (*f)());	函数指针(里面嵌套了一个形参：函数指针)
	
	int (*func[5])();	指针数组，是一个数组，然后里面是个指针，里面存放的是一个个函数指针
	int (*(*func)[5])();	指向指针数组的一个指针，即二维指针数组
	类比：int arr[5]; int* p = arr;
	int (*(*func)())[5];	返回值为二维数组，返回类型为函数声明的类型
	类似：int (*func)()[][5]
	int func(void)[5]		
	int func[5](void)
*/

typedef int (*func)(); // 函数指针，可以参考左右原则
int tmp() {
	printf("Hello World\n");
	return 1;
}
typedef int (*func1)(int (*f)());
int tmp1(func func) {
	printf("func1\n");
	(*func)();
	return 1;
}

typedef int (*func2[5])();
typedef int (*(*func3)[5])();
//typedef int(*(*func4)())[4];
typedef int(*array)[5];
typedef array (*func4)();
int arr_4[][5] = { 1,2,342,2,432 };
array test_func() {
	printf("Func4\n");
	return arr_4;
}
void test_08() {
	// 函数指针
	func pfun = tmp;
	(*pfun)();
	//func1 pfun1 = tmp1;
	//(*pfun1)(pfun);
	func2 pfun2[5] = {pfun, tmp};
	//(*pfun2[0])();
	func2* ppfun2 = pfun2;
	(*(*ppfun2))();
	func3 fun3 = pfun2;
	(*(*fun3))();
	(fun3[0][0])();

	test_func();
	func4 pfun4 = test_func();
	pfun4();
}
int main() {
	//test();
	//test_02();
	//test_03();
	//test_04();
	//test_05();
	//test_06();
	//test_07();
	test_08();
	return 0;
}