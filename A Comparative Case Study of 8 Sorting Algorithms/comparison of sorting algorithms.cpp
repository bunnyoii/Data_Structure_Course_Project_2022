#include <iostream>
#include <cstdlib>
#include <limits>
#include <chrono>
#include <iomanip>
#include <algorithm>
#define MAX_SIZE 10000

template <typename Type>
class SortingAlgorithms {
private:
	Type randNum[MAX_SIZE];
	Type sortNum[MAX_SIZE];
public:
	int chooseNum = -1;
	int maxNum = -1;
	int sortCnt = 0;
	void inputNum(int& num,bool opt);
	void generateRandomNumbers();
	void chooseAlgorithms();
	void bubbleSort();						//冒泡排序
	void selectionSort();					//选择排序
	void directInsertionSort();				//直接插入排序
	void ShellSort();						//希尔排序
	void quickSort(int left, int right);	//快速排序
	void heapify(int n, int i);		//调整堆
	void heapSort();						//堆排序
	void merge(int left, int mid, int right);			//合并有序数组
	void mergeSort(int l,int r);						//归并排序
	// 获取最大值
	int getMax() {
		int mx = sortNum[0];
		for (int i = 1; i < maxNum; i++)
			if (sortNum[i] > mx)
				mx = sortNum[i];
		return mx;
	}
	void countSort(int exp);
	void radixSort();						//基数排序
	// 打印数组函数
	void print() {
		std::cout << "\n";
		for (int i = 0; i < maxNum; i++){
			std::cout << sortNum[i] << " ";
			if (i % 9 == 0 && i != 0)
				std::cout << "\n";
		}
	}
	void initSort();
	void Exit() {
		std::cout << "按任意键继续...\n";
		// 清除输入缓冲区
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		// 等待用户按键
		std::cin.get();
	}
};

// 输入数字
template <typename Type>
void SortingAlgorithms<Type>::inputNum(int& num,bool opt)
{
	int maxSize = 0;
	if (opt) maxSize = MAX_SIZE;
	else maxSize = 9;
	while (1) {
		std::cin >> num;
		if (std::cin.fail() || num <= 0 || num > MAX_SIZE) {
			std::cin.clear();
			std::cin.ignore(65536, '\n');
			std::cout << "输入数据有误，请重新输入\n";
		}
		else {
			if (std::cin.get() == '\n')
				break;
			else {
				std::cin.clear();
				std::cin.ignore(65536, '\n');
				std::cout << "输入数据有误，请重新输入\n";
			}
		}
	}
}

// 产生随机数
template <typename Type>
void SortingAlgorithms<Type>::generateRandomNumbers()
{
	// 设置随机数种子
	srand(static_cast<unsigned int>(time(0)));

	// 生成随机数
	for (int i = 0; i < maxNum; ++i) {
		randNum[i] = rand();
	}
	std::cout << "随机数生成完毕。\n";
}

// 将排序数组初始化为随机生成数数组
template <typename Type>
void SortingAlgorithms<Type>::initSort()
{
	sortCnt = 0;
	for (int i = 0; i < maxNum; ++i)
		sortNum[i] = randNum[i];
}

// 排序算法选择
template <typename Type>
void SortingAlgorithms<Type>::chooseAlgorithms()
{
	// 定义计时变量
	std::chrono::high_resolution_clock::time_point start, stop;
	std::chrono::milliseconds duration;
	initSort();
	std::cout << std::setw(28) << std::left << "\n请选择排序算法[1-9] : ";
	inputNum(chooseNum, 0);
	switch (chooseNum) {
	case 1:
		 start = std::chrono::high_resolution_clock::now();
		bubbleSort();
		 stop = std::chrono::high_resolution_clock::now();
		 duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		std::cout << "冒泡排序时间: " << std::setiosflags(std::ios::fixed) << std::setprecision(6) << duration.count() / 1000.0<< "s" << std::endl;
		std::cout << "冒泡排序交换次数: " << std::setiosflags(std::ios::fixed) << std::setprecision(6) << sortCnt << std::endl; 
		break;
	case 2:
		 start = std::chrono::high_resolution_clock::now();
		selectionSort();
		 stop = std::chrono::high_resolution_clock::now();
		 duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		std::cout << "选择排序时间: " << std::setiosflags(std::ios::fixed) << std::setprecision(6) << duration.count() / 1000.0<< "s" << std::endl;
		std::cout << "选择排序交换次数: " << std::setiosflags(std::ios::fixed) << std::setprecision(6) << sortCnt << std::endl; 
		break;
	case 3:
		 start = std::chrono::high_resolution_clock::now();
		directInsertionSort();
		 stop = std::chrono::high_resolution_clock::now();
		 duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		std::cout << "直接插入排序时间: " << std::setiosflags(std::ios::fixed) << std::setprecision(6) << duration.count() / 1000.0<< "s" << std::endl;
		std::cout << "直接插入排序交换次数: " << std::setiosflags(std::ios::fixed) << std::setprecision(6) << sortCnt << std::endl;
		break;
	case 4:
		 start = std::chrono::high_resolution_clock::now();
		ShellSort();
		 stop = std::chrono::high_resolution_clock::now();
		 duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		std::cout << "希尔排序时间: " << std::setiosflags(std::ios::fixed) << std::setprecision(6) << duration.count() / 1000.0<< "s" << std::endl;
		std::cout << "希尔排序交换次数: " << std::setiosflags(std::ios::fixed) << std::setprecision(6) << sortCnt << std::endl;
		break;
	case 5:
		 start = std::chrono::high_resolution_clock::now();
		quickSort(0, maxNum - 1);
		 stop = std::chrono::high_resolution_clock::now();
		 duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		std::cout << "快速排序时间: " << std::setiosflags(std::ios::fixed) << std::setprecision(6) << duration.count() / 1000.0<< "s" << std::endl;
		std::cout << "快速排序交换次数: " << std::setiosflags(std::ios::fixed) << std::setprecision(6) << sortCnt << std::endl;
		break;
	case 6:
		 start = std::chrono::high_resolution_clock::now();
		heapSort();
		 stop = std::chrono::high_resolution_clock::now();
		 duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		std::cout << "堆排序时间: " << std::setiosflags(std::ios::fixed) << std::setprecision(6) << duration.count() / 1000.0<< "s" << std::endl;
		std::cout << "堆排序交换次数: " << std::setiosflags(std::ios::fixed) << std::setprecision(6) << sortCnt << std::endl;
		break;
	case 7:
		 start = std::chrono::high_resolution_clock::now();
		mergeSort(0, maxNum - 1);
		 stop = std::chrono::high_resolution_clock::now();
		 duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		std::cout << "归并排序时间: " << std::setiosflags(std::ios::fixed) << std::setprecision(6) << duration.count() / 1000.0<< "s" << std::endl;
		std::cout << "归并排序交换次数: " << std::setiosflags(std::ios::fixed) << std::setprecision(6) << sortCnt << std::endl;
		break;
	case 8:
		 start = std::chrono::high_resolution_clock::now();
		radixSort();
		 stop = std::chrono::high_resolution_clock::now();
		 duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		std::cout << "基数排序时间: " << std::setiosflags(std::ios::fixed) << std::setprecision(6) << duration.count() / 1000.0<< "s" << std::endl;
		std::cout << "基数排序交换次数: " << std::setiosflags(std::ios::fixed) << std::setprecision(6) << sortCnt << std::endl;
		break;
	case 9:
		Exit();
		break;
	}
}

// 冒泡排序
template <typename Type>
void SortingAlgorithms<Type>::bubbleSort()
{
	//升序
	bool swapped;
	for (int i = 0; i < maxNum - 1; i++) {
		swapped = false;
		for (int j = 0; j < maxNum - i - 1; j++) {
			if (sortNum[j] > sortNum[j + 1]) {
				// 交换 sortNum[j] 和 sortNum[j+1]
				sortCnt += 1;
				int temp = sortNum[j];
				sortNum[j] = sortNum[j + 1];
				sortNum[j + 1] = temp;
				swapped = true;
			}
		}
		// 如果在这一轮遍历中没有发生交换，说明数组已经排序完成
		if (!swapped)
			break;
	}
}

// 选择排序
template <typename Type>
void SortingAlgorithms<Type>::selectionSort()
{
	for (int i = 0; i < maxNum - 1; i++) {
		// 寻找最小元素的索引
		int minIndex = i;
		for (int j = i + 1; j < maxNum; j++) {
			if (sortNum[j] < sortNum[minIndex]) {
				minIndex = j;
				sortCnt += 1;
			}
		}
		// 将找到的最小元素与第i个位置的元素交换
		std::swap(sortNum[i], sortNum[minIndex]);
	}
}

// 直接插入排序
template <typename Type>
void SortingAlgorithms<Type>::directInsertionSort()
{
	int i, key, j;
	for (i = 1; i < maxNum; i++) {
		key = sortNum[i]; // 选取要插入的元素
		j = i - 1;

		// 将大于key的元素向右移动
		while (j >= 0 && sortNum[j] > key) {
			sortCnt += 1;
			sortNum[j + 1] = sortNum[j];
			j = j - 1;
		}
		sortNum[j + 1] = key; // 插入元素
	}
}

// 希尔插入排序
template <typename Type>
void SortingAlgorithms<Type>::ShellSort()
{
	// 使用希尔增量序列，初始增量设置为数组长度的一半
	for (int gap = maxNum / 2; gap > 0; gap /= 2) {
		// 对每个子列表进行插入排序
		for (int i = gap; i < maxNum; i++) {
			int temp = sortNum[i];
			int j;
			// 插入排序的变体
			for (j = i; j >= gap && sortNum[j - gap] > temp; j -= gap) {
				sortCnt += 1;
				sortNum[j] = sortNum[j - gap];
			}
			sortNum[j] = temp;
		}
	}
}

// 快速排序
template <typename Type>
void SortingAlgorithms<Type>::quickSort(int left,int right)
{
	int i = left, j = right;
	int pivot = sortNum[(left + right) / 2];

	// 分区操作
	while (i <= j) {
		while (sortNum[i] < pivot) i++;
		while (sortNum[j] > pivot) j--;
		if (i <= j) {
			std::swap(sortNum[i], sortNum[j]);
			i++;
			j--;
			sortCnt += 1;
		}
	}
	// 递归调用
	if (left < j)
		quickSort(left, j);
	if (i < right)
		quickSort(i, right);
}

/* 堆排序 */
//用于调整堆
template <typename Type>
void SortingAlgorithms<Type>::heapify(int n,int i)
{
	int largest = i; // 初始化最大值为根
	int left = 2 * i + 1; // 左子节点
	int right = 2 * i + 2; // 右子节点

	// 如果左子节点大于根
	if (left < n && sortNum[left] > sortNum[largest])
		largest = left;

	// 如果右子节点大于目前的最大值
	if (right < n && sortNum[right] >sortNum[largest])
		largest = right;

	// 如果最大值不是根
	if (largest != i) {
		std::swap(sortNum[i], sortNum[largest]);
		sortCnt++; // 在发生实际交换时计数
		// 递归地调整影响的子树
		heapify(n, largest);
	}
}
// 堆排序
template <typename Type>
void SortingAlgorithms<Type>::heapSort()
{
	// 构建堆（重新排列数组）
	for (int i = maxNum / 2 - 1; i >= 0; i--)
		heapify(maxNum, i);
	// 一个个从堆顶取出元素
	for (int i = maxNum - 1; i >= 0; i--) {
		// 将当前根移到数组末尾
		std::swap(sortNum[0], sortNum[i]);
		sortCnt++; // 在每次将根元素移到数组末尾时计数
		// 调用 heapify 函数，减小堆的大小并使其为最大堆
		heapify(i, 0);
	}
}

/* 归并排序 */
// 合并两个子数组
template <typename Type>
void SortingAlgorithms<Type>::merge(int left, int mid, int right)
{
	int const subArrayOne = mid - left + 1;
	int const subArrayTwo = right - mid;

	// 创建临时数组
	Type* leftArray = new Type[subArrayOne],
		* rightArray = new Type[subArrayTwo];

	// 复制数据到临时数组
	for (int i = 0; i < subArrayOne; i++)
		leftArray[i] = sortNum[left + i];
	for (int j = 0; j < subArrayTwo; j++)
		rightArray[j] = sortNum[mid + 1 + j];

	int indexOfSubArrayOne = 0, // 初始索引第一个子数组
		indexOfSubArrayTwo = 0; // 初始索引第二个子数组
	int indexOfMergedArray = left; // 初始索引合并后的数组

	// 合并临时数组回原数组
	while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
		sortCnt++; 
		if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
			sortNum[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
			indexOfSubArrayOne++;
		}
		else {
			sortNum[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}

	// 复制剩余元素
	while (indexOfSubArrayOne < subArrayOne) {
		sortNum[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}

	while (indexOfSubArrayTwo < subArrayTwo) {
		sortNum[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}

	// 释放临时数组的内存
	delete[] leftArray;
	delete[] rightArray;
}
// 归并排序
template <typename Type>
void SortingAlgorithms<Type>::mergeSort(int l, int r)
{
	if (l >= r)
		return;
	else {
		// 找到中点
		int m = l + (r - l) / 2;

		// 递归地对左右两半进行排序
		mergeSort(l, m);
		mergeSort(m + 1, r);

		// 合并两半
		merge(l, m, r);
	}
}

/* 基数排序 */
template <typename Type>
void SortingAlgorithms<Type>::countSort(int exp)
{
	Type output[MAX_SIZE];
	int i, count[10] = { 0 };

	// 存储指定位的计数
	for (i = 0; i < maxNum; i++)
		count[(sortNum[i] / exp) % 10]++;

	// 更改count[i]，使其包含实际位置信息
	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	// 构建输出数组
	for (i = maxNum - 1; i >= 0; i--) {
		output[count[(sortNum[i] / exp) % 10] - 1] = sortNum[i];
		count[(sortNum[i] / exp) % 10]--;
		sortCnt++;
	}

	// 将输出数组的内容复制到randNum[]
	for (i = 0; i < maxNum; i++)
		sortNum[i] = output[i];
}
template <typename Type>
void SortingAlgorithms<Type>::radixSort()
{
	// 找到最大数以确定最大位数
	int m = getMax();

	// 对每个位进行计数排序
	for (int exp = 1; m / exp > 0; exp *= 10)
		countSort(exp);
}

int main()
{
	SortingAlgorithms<int> SASolution;
	std::cout << "····················\n";
	std::cout << "·            排序算法比较            ·\n";
	std::cout << "·  Comparison of Sorting Algorithms  ·\n";
	std::cout << "····················\n\n";
	std::cout << "========================================\n";
	std::cout << "*          1 --- 冒泡排序              *\n";
	std::cout << "*          2 --- 选择排序              *\n";
	std::cout << "*          3 --- 直接插入排序          *\n";
	std::cout << "*          4 --- 希尔排序              *\n";
	std::cout << "*          5 --- 快速排序              *\n";
	std::cout << "*          6 --- 堆排序                *\n";
	std::cout << "*          7 --- 归并排序              *\n";
	std::cout << "*          8 --- 基数排序              *\n";
	std::cout << "*          9 --- 退出程序              *\n";
	std::cout << "========================================\n\n";
	std::cout << "请输入要产生的随机数的个数[1-10000] : ";
	SASolution.inputNum(SASolution.maxNum, 1);
	SASolution.generateRandomNumbers();
	SASolution.initSort();
	//SASolution.print();
	while (SASolution.chooseNum != 9) {
		SASolution.chooseAlgorithms();
		//SASolution.print();
	}
}