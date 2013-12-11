#include "tree.h"
#include <iostream>
#include <stdio.h>

#define RB_TREE
void printNode(TreeNode_p_t node)
{
    const char* data =NULL;
    TREE_get_node_value(node, (const void **) &data);
    std::cout<< *data;
}


void TEST_foreach_method (TreeNode_p_t root, TRAVEL_type_t type, const char* msg)
{
	std::cout<<msg<<":";
	TREE_traverse(type, root, printNode);
}

void TEST_iterator_method (TreeNode_p_t root, ITERATOR_type_t type, const char* msg)
{
	std::cout<<msg<<":";
	Iterator *it = Iterator::AskIterator(type, root);
	for (TreeNode_p_t node = it->next();  node != NULL; node = it->next())
        printNode(node);
    Iterator::Release(it);
}

typedef struct TEST_visit_procedure_s{
	const char*   msg;
	TRAVEL_type_t   type;
}TEST_visit_procedure_t;

typedef struct TEST_iterator_procedure_s{
	const char*   msg;
    ITERATOR_type_t type;
}TEST_iterator_procedure_t;

TEST_visit_procedure_t process1[]={
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

TEST_visit_procedure_t process11[]={
	{"pre-order result should be",  TRAVEL_R_PRE_ORDER},
	{"goto",                    TRAVEL_G_PRE_ORDER},
	{"loop",                    TRAVEL_L_PRE_ORDER},
	{"in-order result should be",   TRAVEL_R_IN_ORDER},
	{"goto",                    TRAVEL_G_IN_ORDER},
	{"loop",                    TRAVEL_L_IN_ORDER},
	{"post-order result should be",   TRAVEL_R_POST_ORDER},
	{"goto",                    TRAVEL_G_POST_ORDER},
	{"loop",                    TRAVEL_L_POST_ORDER}
};
TEST_iterator_procedure_t process2[]={
	{"iterator",            ITERATOR_PRE_ORDER},
	{"iterator",             ITERATOR_IN_ORDER},
	{"iterator",           ITERATOR_POST_ORDER}
};
const char* process[]={ "pre-order  test:", "in-order  test:", "post-order  test:" };
int main(int argc, char* argv[])
{

	FILE *pFile = NULL;
	if(argc > 2) {
		std::cout<<" arguments more than 2"<< std::endl;
		return 0;
	} else if (argc == 2){
		pFile = fopen (argv[1] , "r");
		if (pFile == NULL)
        {
            printf ("Error opening file\r\n");
            return 0;
        }
	} else {
		pFile = stdin;
	}

	while (!feof(pFile)) {
		TreeNode_p_t aTree = NULL;
		char keys[256]={0};
		std::cin.getline (keys,256);
        char* keywds = keys;
		TREE_constuct( aTree, NULL, keywds);
		if(!aTree) break;
		for(int id = 0; id< 3; ++id) {
			TEST_foreach_method(aTree, process11[id*3].type,   process11[id*3].msg);
			std::cout<< std::endl;
			TEST_foreach_method(aTree, process11[id*3+1].type, process11[id*3+1].msg);
			std::cout<< std::endl;
			TEST_foreach_method(aTree, process11[id*3+2].type, process11[id*3+2].msg);
			std::cout<< std::endl;
			TEST_iterator_method(aTree, process2[id].type, process2[id].msg);
			std::cout<< std::endl;
			std::cout<< std::endl;
		}
		TREE_destroy(&aTree);
	}
    fclose(pFile);
    printf("test end!\r\n");
	return 0;
}
