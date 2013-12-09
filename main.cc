#include "tree.h"
#include <iostream>
#include <stdio.h>

void printNode(TreeNode_p_t node)
{
    const char* data =NULL;
    TREE_get_node_value(node, (const void **) &data);
	printf("%c", *((const char* )data));
}


void TEST_method (TreeNode_p_t root, TRAVEL_type_t type, const char* msg)
{
	std::cout<<msg<<std::endl;
	TREE_traverse(type, root, printNode);
	std::cout<<std::endl<<std::endl;
}

typedef struct TEST_procedure_s{
	const char*   msg;
	TRAVEL_type_t type;
}TEST_procedure_t;

TEST_procedure_t process[]={
	{"pre-order recursive traverse test:",  TRAVEL_R_PRE_ORDER},
	{"pre-order goto traverse test:",       TRAVEL_G_PRE_ORDER},
	{"pre-order loop traverse test:",       TRAVEL_L_PRE_ORDER},
	{"in-order recursive traverse test:",   TRAVEL_R_IN_ORDER},
	{"in-order goto traverse test:",        TRAVEL_G_IN_ORDER},
	{"in-order loop traverse test:",        TRAVEL_L_IN_ORDER},
	{"post-order recursive traverse test:", TRAVEL_R_POST_ORDER},
	{"post-order goto traverse test:",      TRAVEL_G_POST_ORDER},
	{"post-order loop traverse test:",      TRAVEL_L_POST_ORDER}
};

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		std::cout<<" arguments less than 2"<< std::endl;
		return 0;
	}
	TreeNode_p_t aTree = NULL;
	TREE_constuct( aTree, NULL, argv[1]);

	for (int i= 0; i<sizeof(process)/sizeof(TEST_procedure_t); ++i)
		TEST_method(aTree, process[i].type, process[i].msg);

	//std::cout<<"in-order iterator test:"<<std::endl;
	//InorderIterator *it = new InorderIterator(aTree);
	//for (TreeNode_p_t node = it->next();  node != NULL; node = it->next())
	//	std::cout<<node->data;
	//delete it;
	//std::cout<<std::endl<<std::endl;

	//std::cout<<"post-order traverse test:"<<std::endl;
	//postorder_traverse_NR(aTree);
	//std::cout<<std::endl<<std::endl;
	return 0;
}
