#pragma once
#include <iostream>

#include <vector>
#include <stack>

using namespace std;
using std::endl;
using std::cout;

namespace BSTree {

	template <class T>

	// 定义树结点
	class TreeNode {
		T _data;
		TreeNode<T> * _left;
		TreeNode<T> * _right;

	public:
		TreeNode(const T & data = T()) :
			_data(data),
			_left(nullptr),
			_right(nullptr)
		{}

	template <class T>
	friend class BinarySearchTree;
	};

	template <class T>


	class BinarySearchTree {

		TreeNode<T> * _root;
	public:
		// 初始化
		BinarySearchTree() :
			_root(nullptr)
		{}

		bool Insert(const T & data) {

			// 如果根为nullptr,直接插入
			if (_root == nullptr) {
				_root = new TreeNode<T>(data);
				return true;
			}

			// 如果根不为nullptr,遍历找到插入点
			TreeNode<T> * cur = _root;	// 记录查找的结点位置
			TreeNode<T> * pre = nullptr;	// 记录双亲的结点位置

			while (cur) {
				// 如果插入元素已存在,直接返回false
				if (cur->_data == data) {
					return false;
				}
				pre = cur;
				if (data < cur->_data ) {
					cur = cur->_left;
				}
				else {
					cur = cur->_right;
				}
			}

			cur = new TreeNode<T>(data);

			// data与双亲进行大小比较


			if (pre->_data > data)
				pre->_left = cur;
			else
				pre->_right = cur;

			return true;
		}

		bool Erase(const T & data) {

			// 判断树是否为空
			if (_root == nullptr)
				return false;
		
			TreeNode<T> * cur = _root;
			TreeNode<T> * pre = _root;

			// 遍历查找所要删除的结点
			while (cur) {
				if (data < cur->_data) {
					pre = cur;
					cur = cur->_left;
				}
				else if (data > cur->_data) {
					pre = cur;
					cur = cur->_right;
				}
				else {
					break;
				}
			}

			if (cur == nullptr)
				return false;

			// 删除结点需要分情况讨论
			// 1.左右孩子都存在
			if (cur->_left && cur->_right) {
				TreeNode<T> * cur2 = cur->_left;
				TreeNode<T> * pre2 = cur;
				
				// 直接往最右叶子结点查找
				if (cur2->_right) {
					
					for (; cur2->_right; pre2 = cur2, cur2 = cur2->_right);
					pre2->_right = cur2->_left;
					cur2->_left = cur->_left;
				}
				// cur2指向cur的右孩子
				cur2->_right = cur->_right;

				// 极端情况:要删除根节点
				// _root需要变更地址
				if (cur == pre) {
					_root = cur2;				}

				// 判断cur是左孩子还是右孩子,将cur替换为cur2
				if (cur->_data < pre->_data)
					pre->_left = cur2;
				else
					pre->_right = cur2;
				// 释放掉cur结点
				delete cur;
			}
			else if (cur->_left) {
				if (cur == pre) {
					_root = cur->_left;
				}
				else {
					if (cur->_data < pre->_data)
						pre->_left = cur->_left;
					else
						pre->_right = cur->_left;
				}

				delete cur;
			}
			else {
				if (cur == pre) {
					_root = cur->_right;
				}
				else {
					if (cur->_data < pre->_data)
						pre->_left = cur->_right;
					else
						pre->_right = cur->_right;
				}

				delete cur;
			}
			return true;
		}

		// 用值替换的方式进行删除
		bool Delete(const T & data) {

			// 查找删除点
			// 判断树是否为空
			if (_root == nullptr)
				return false;

			TreeNode<T> * cur = _root;
			TreeNode<T> * pre = _root;

			// 遍历查找所要删除的结点
			while (cur) {
				
				if (data < cur->_data) {
					pre = cur;
					cur = cur->_left;
				}
				else if (data > cur->_data) {
					pre = cur;
					cur = cur->_right;
				}
				else {
					break;
				}
			}

			// 如果遍历到最后,cur == nullptr,说明不存在,直接返回false
			if (cur == nullptr)
				return false;

			// 分情况进行判断
				if (cur->_left && cur->_right) {
					// 赋值操作起来会更简单一点
					// 先找到最右结点,将其值赋给要删除的结点的值,然后释放掉最右结点--OK
					TreeNode<T> * cur2 = cur->_left;
					TreeNode<T> * pre2 = cur2;
					for (; cur2->_right; pre2 = cur2, cur2 = cur2->_right);
					
					cur->_data = cur2->_data;
					pre->_right = cur2->_right;
					delete cur2;
				}
			else if (cur->_left) {
				if (cur->_data < pre->_data)
					pre->_left = cur->_left;
				else
					pre->_right = cur->_left;
				delete cur;
			}
			else {
				if (cur->_data < pre->_data)
					pre->_left = cur->_right;
				else
					pre->_right = cur->_right;
				delete cur;
			}

			return true;
		}

		void Find(const T & data) {
			
			if (_root == nullptr)
				return;
			TreeNode<T> * cur = _root;
			while (cur) {
				if (data < cur->_data)
					cur = cur->_left;
				else if (data > cur->_data)
					cur = cur->_right;
				else
					break;
			}
			if (cur == nullptr) 
				return;

			cout << " cur->_data :" << cur->_data << endl;
			delete cur;
		}


	};
};
// 搜索二叉树的性能分析:
// 插入删除的操作都是:先查找后操作
// 操作的次数为1
// 查找的次数为:log n 
// 最优情况下,其为完全二叉树,所要执行的次数为:logn
// 最差情况下,其为单分支树,所要执行的次数为:n / 2