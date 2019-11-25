#pragma once
#include <iostream>

#include <vector>
#include <stack>

using namespace std;
using std::endl;
using std::cout;

namespace BSTree {

	template <class T>

	// ���������
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
		// ��ʼ��
		BinarySearchTree() :
			_root(nullptr)
		{}

		bool Insert(const T & data) {

			// �����Ϊnullptr,ֱ�Ӳ���
			if (_root == nullptr) {
				_root = new TreeNode<T>(data);
				return true;
			}

			// �������Ϊnullptr,�����ҵ������
			TreeNode<T> * cur = _root;	// ��¼���ҵĽ��λ��
			TreeNode<T> * pre = nullptr;	// ��¼˫�׵Ľ��λ��

			while (cur) {
				// �������Ԫ���Ѵ���,ֱ�ӷ���false
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

			// data��˫�׽��д�С�Ƚ�


			if (pre->_data > data)
				pre->_left = cur;
			else
				pre->_right = cur;

			return true;
		}

		bool Erase(const T & data) {

			// �ж����Ƿ�Ϊ��
			if (_root == nullptr)
				return false;
		
			TreeNode<T> * cur = _root;
			TreeNode<T> * pre = _root;

			// ����������Ҫɾ���Ľ��
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

			// ɾ�������Ҫ���������
			// 1.���Һ��Ӷ�����
			if (cur->_left && cur->_right) {
				TreeNode<T> * cur2 = cur->_left;
				TreeNode<T> * pre2 = cur;
				
				// ֱ��������Ҷ�ӽ�����
				if (cur2->_right) {
					
					for (; cur2->_right; pre2 = cur2, cur2 = cur2->_right);
					pre2->_right = cur2->_left;
					cur2->_left = cur->_left;
				}
				// cur2ָ��cur���Һ���
				cur2->_right = cur->_right;

				// �������:Ҫɾ�����ڵ�
				// _root��Ҫ�����ַ
				if (cur == pre) {
					_root = cur2;				}

				// �ж�cur�����ӻ����Һ���,��cur�滻Ϊcur2
				if (cur->_data < pre->_data)
					pre->_left = cur2;
				else
					pre->_right = cur2;
				// �ͷŵ�cur���
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

		// ��ֵ�滻�ķ�ʽ����ɾ��
		bool Delete(const T & data) {

			// ����ɾ����
			// �ж����Ƿ�Ϊ��
			if (_root == nullptr)
				return false;

			TreeNode<T> * cur = _root;
			TreeNode<T> * pre = _root;

			// ����������Ҫɾ���Ľ��
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

			// ������������,cur == nullptr,˵��������,ֱ�ӷ���false
			if (cur == nullptr)
				return false;

			// ����������ж�
				if (cur->_left && cur->_right) {
					// ��ֵ�������������һ��
					// ���ҵ����ҽ��,����ֵ����Ҫɾ���Ľ���ֵ,Ȼ���ͷŵ����ҽ��--OK
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
// ���������������ܷ���:
// ����ɾ���Ĳ�������:�Ȳ��Һ����
// �����Ĵ���Ϊ1
// ���ҵĴ���Ϊ:log n 
// ���������,��Ϊ��ȫ������,��Ҫִ�еĴ���Ϊ:logn
// ��������,��Ϊ����֧��,��Ҫִ�еĴ���Ϊ:n / 2