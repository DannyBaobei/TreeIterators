#include "tree_definition.h"
#include <iostream>
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

class PreorderIterator : public Iterator {
	public:
		PreorderIterator(TreeNode_p_t node) {
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
    };
}
void Iterator::Release(Iterator* iter)
{
    delete iter;
}
