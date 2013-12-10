#ifndef TREE_H
#define TREE_H

#define DATA_type char

typedef struct TreeNode_s TreeNode_t;
typedef struct TreeNode_s* TreeNode_p_t;


typedef enum TRAVEL_type_e {
	TRAVEL_R_PRE_ORDER =0,
	TRAVEL_R_IN_ORDER  ,
	TRAVEL_R_POST_ORDER,
	TRAVEL_G_PRE_ORDER,
	TRAVEL_G_IN_ORDER ,
	TRAVEL_G_POST_ORDER, 
	TRAVEL_L_PRE_ORDER,
	TRAVEL_L_IN_ORDER ,
	TRAVEL_L_POST_ORDER 
}TRAVEL_type_t;

typedef enum ITERATOR_type_e {
	ITERATOR_PRE_ORDER =0,
	ITERATOR_IN_ORDER  ,
	ITERATOR_POST_ORDER,
}ITERATOR_type_t;

class Iterator {
    protected:
		virtual ~Iterator() {}
	public:
		virtual TreeNode_p_t next() = 0;
    static Iterator* AskIterator(ITERATOR_type_t type, TreeNode_p_t root);
    static void Release(Iterator*);
};

typedef void (*funcVisitor) ( TreeNode_p_t node);
typedef void (*funcTravel) ( TreeNode_p_t root, funcVisitor fn);

extern void TREE_traverse(TRAVEL_type_t mode, TreeNode_p_t root, funcVisitor fn);
extern void TREE_constuct( TreeNode_p_t &theTree, TreeNode_p_t  parentTree,  char* &theKeyWds);
extern void TREE_get_node_value( TreeNode_p_t &theTree, const void** data );





















#endif
