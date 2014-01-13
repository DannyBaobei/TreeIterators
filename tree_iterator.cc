#include "tree_definition.h"
#include <cstddef>
#include <stack>


class InorderIterator : public Iterator {
	public:
		InorderIterator(TreeNode_p_t node) {
			TreeNode_p_t current = node;
			while (NULL != current) {
				mStack.push(current);
				current = current->lchild;
			}
		}
		virtual TreeNode_p_t next() {
			if (mStack.empty()) {
				return NULL;
			}
			TreeNode_p_t top = mStack.top();
			mStack.pop();
			if (NULL != top->rchild) {
				TreeNode_p_t current = top->rchild;
				while (NULL != current) {
					mStack.push(current);
					current = current->lchild;
				}
			}
			return top;
		}
	private:
		std::stack<TreeNode_p_t> mStack;
};

class PostorderIterator : public Iterator {
	public:
		PostorderIterator(TreeNode_p_t node) {
			TreeNode_p_t current = node;
			while(NULL != current){
				mStack.push(current);
				while (NULL != current->lchild) {
					mStack.push(current->lchild);
					current = current->lchild;
				}
				current = current->rchild;
			}
		}
		virtual TreeNode_p_t next() {
			if (mStack.empty()) {
				return NULL;
			}
			TreeNode_p_t result = mStack.top();
			mStack.pop();
			if(mStack.empty())
				return result;
			TreeNode_p_t top = mStack.top();
			if(top->rchild == result)
				return result;
			TreeNode_p_t current = top->rchild;
			while(NULL != current){
				mStack.push(current);
				while (NULL != current->lchild) {
					mStack.push(current->lchild);
					current = current->lchild;
				}
				current = current->rchild;
			}
			return result;
		}
	private:
		std::stack<TreeNode_p_t> mStack;
};

class PreorderIterator : public Iterator {
	public:
		PreorderIterator(TreeNode_p_t node) {
			TreeNode_p_t current = node;
			mStack.push(current);

		}
		virtual TreeNode_p_t next() {
			if (mStack.empty()) {
				return NULL;
			}
			TreeNode_p_t top = mStack.top();
			mStack.pop();
			if(NULL != top->rchild){
				TreeNode_p_t current = top->rchild;
				mStack.push(current);
			}
			if(NULL != top->lchild) {
				TreeNode_p_t current = top->lchild;
				mStack.push(current);
			}
			return top;
		}
	private:
		std::stack<TreeNode_p_t> mStack;
};

class InorderLazyIterator : public Iterator {
	public:
		InorderLazyIterator(TreeNode_p_t node):m_list(NULL) {
			m_list = make_inorder_tree_iterator(node);
		}
		virtual TreeNode_p_t next() {
			TreeNode_p_t node = first(m_list);
			m_list = rest(m_list);
			return node;
		}
	private:
		List_p_t m_list;
};

class PreorderLazyIterator : public Iterator {
	public:
		PreorderLazyIterator(TreeNode_p_t node):m_list(NULL) {
			m_list = make_preorder_tree_iterator(node);
		}
		virtual TreeNode_p_t next() {
			TreeNode_p_t node = first(m_list);
			m_list = rest(m_list);
			return node;
		}
	private:
		List_p_t m_list;
};

class PostorderLazyIterator : public Iterator {
	public:
		PostorderLazyIterator(TreeNode_p_t node):m_list(NULL) {
			m_list = make_postorder_tree_iterator(node);
		}
		virtual TreeNode_p_t next() {
			TreeNode_p_t node = first(m_list);
			m_list = rest(m_list);
			return node;
		}
	private:
		List_p_t m_list;
};

Iterator* Iterator::AskIterator(ITERATOR_type_t type, TreeNode_p_t root)
{
	switch(type)
	{
		case ITERATOR_PRE_ORDER:
			return new PreorderIterator(root);
			break;
		case ITERATOR_IN_ORDER:
			return new InorderIterator(root);
			break;
		case ITERATOR_POST_ORDER:
			return new PostorderIterator(root);
			break;
		case ITERATOR_PRE_ORDER_LAZY:
			return new PreorderLazyIterator(root);
			break;
		case ITERATOR_IN_ORDER_LAZY:
			return new InorderLazyIterator(root);
			break;
		case ITERATOR_POST_ORDER_LAZY:
			return new PostorderLazyIterator(root);
			break;
		default:
			break;
	};
	return NULL;
}
void Iterator::Release(Iterator* iter)
{
	delete iter;
}
