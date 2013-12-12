#include "tree.h"
#include <iostream>
#include <string>
#include <stdio.h>

#define RB_TREE
static std::string __result[2];
static int __resultId = 0;

void printNode(TreeNode_p_t node)
{
	const char* data =NULL;
	TREE_get_node_value(node, (const void **) &data);
	std::cout<< *data;
    __result[__resultId].push_back(*data);
}


void TEST_foreach_method (TreeNode_p_t root, TRAVEL_type_t type, const char* msg)
{
    __result[__resultId].clear();
	std::cout<<msg<<":";
	TREE_traverse(type, root, printNode);
    if(__resultId == 0 )
        return;
    if(__result[0] == __result[1] )
        std::cout<<":pass";
    else
        std::cout<<":fail";

}

void TEST_iterator_method (TreeNode_p_t root, ITERATOR_type_t type, const char* msg)
{
    __result[__resultId].clear();
	std::cout<<msg<<":";
	Iterator *it = Iterator::AskIterator(type, root);
	for (TreeNode_p_t node = it->next();  node != NULL; node = it->next())
		printNode(node);
	Iterator::Release(it);
    if(__resultId == 0 )
        return;
    if(__result[0] == __result[1] )
        std::cout<<":pass";
    else
        std::cout<<":fail";
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
	{"pre-order result\r\nexpect",  TRAVEL_R_PRE_ORDER},
	{"goto  ",                        TRAVEL_G_PRE_ORDER},
	{"loop  ",                        TRAVEL_L_PRE_ORDER},
	{"in-order result\r\nexpect",   TRAVEL_R_IN_ORDER},
	{"goto  ",                        TRAVEL_G_IN_ORDER},
	{"loop  ",                        TRAVEL_L_IN_ORDER},
	{"post-order result\r\nexpect", TRAVEL_R_POST_ORDER},
	{"goto  ",                        TRAVEL_G_POST_ORDER},
	{"loop  ",                        TRAVEL_L_POST_ORDER}
};
TEST_iterator_procedure_t process2[]={
	{"iter  ",            ITERATOR_PRE_ORDER},
	{"iter  ",             ITERATOR_IN_ORDER},
	{"iter  ",           ITERATOR_POST_ORDER}
};

int main(int argc, char* argv[])
{
	FILE *pFile = NULL;
	if(argc > 2) {
		std::cerr<<" arguments more than 2"<< std::endl;
		return 0;
	} else if (argc == 2){
		pFile = fopen (argv[1] , "r");
		if (pFile == NULL)
		{
            std::cerr<< "Error opening file"<<std::endl;
			return 0;
		}
	} else {
		pFile = stdin;
	}

	while (!feof(pFile)) {
		printf ("type a tree key words:\r\n");
		TreeNode_p_t aTree = NULL;
		char keys[256]={0};
		std::cin.getline (keys,256);
		char* keywds = keys;
		TREE_constuct( aTree, NULL, keywds);
		if(!aTree) break;
		for(int id = 0; id< 3; ++id) {
            __resultId = 0;
			TEST_foreach_method(aTree, process1[id*3].type,   process1[id*3].msg);
			std::cout<< std::endl;
            __resultId++;
			TEST_foreach_method(aTree, process1[id*3+1].type, process1[id*3+1].msg);
			std::cout<< std::endl;
			TEST_foreach_method(aTree, process1[id*3+2].type, process1[id*3+2].msg);
			std::cout<< std::endl;
			TEST_iterator_method(aTree, process2[id].type, process2[id].msg);
			std::cout<< std::endl;
			std::cout<< std::endl;
		}
		TREE_destroy(&aTree);
		printf ("\r\n");
	}
	fclose(pFile);
	printf("test end!\r\n");
	return 0;
}
