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
			mStack.push(current);
			while (NULL != current) {
				if(NULL != current->rchild)
					mStack.push(current->rchild);
				if(NULL != current->lchild)
				{
					mStack.push(current->lchild);
					current = current->lchild;
				}
				else
					current = current->rchild;
			}
		}
		virtual TreeNode_p_t next() {
			if (mStack.empty()) {
				return NULL;
			}
			TreeNode_p_t top = mStack.top();
			mStack.pop();
			while (NULL != top->rchild) {
				TreeNode_p_t current = top->rchild;
				if(NULL != current->rchild)
					mStack.push(current->rchild);
				if(NULL != current->lchild)
				{
					mStack.push(current->lchild);
					current = current->lchild;
				}
				else
					current = current->rchild;
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
			if(NULL != current->rchild)
				mStack.push(current->rchild);
			mStack.push(current);
			
		}
		virtual TreeNode_p_t next() {
			if (mStack.empty()) {
				return NULL;
			}
			TreeNode_p_t top = mStack.top();
			mStack.pop();
			if(NULL != top->lchild) {
				TreeNode_p_t current = top->lchild;
				if(NULL != current->rchild)
					mStack.push(current->rchild);
				mStack.push(current);
			}else if(NULL != top->rchild){
				mStack.pop();
				TreeNode_p_t current = top->rchild;
				if(NULL != current->rchild)
					mStack.push(current->rchild);
				mStack.push(current);
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
