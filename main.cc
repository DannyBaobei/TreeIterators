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
	std::cout<<msg<<std::endl;
	TREE_traverse(type, root, printNode);
	std::cout<<std::endl<<std::endl;
}

void TEST_iterator_method (TreeNode_p_t root, ITERATOR_type_t type, const char* msg)
{
	std::cout<<msg<<std::endl;
	Iterator *it = Iterator::AskIterator(type, root);
	for (TreeNode_p_t node = it->next();  node != NULL; node = it->next())
        printNode(node);
    Iterator::Release(it);
	std::cout<<std::endl<<std::endl;
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

TEST_iterator_procedure_t process2[]={
	{"pre-order iterator test:",            ITERATOR_PRE_ORDER},
	{"in-order iterator test:",             ITERATOR_IN_ORDER},
	{"post-order iterator test:",           ITERATOR_POST_ORDER}
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

	int count1 = sizeof(process1)/sizeof(TEST_visit_procedure_t);
	int count2 = sizeof(process2)/sizeof(TEST_visit_procedure_t);
	int count3 = count1 + count2;
	while (true)
	{
		int i= 0;
		for (; i < count1; ++i)
			printf("%d: %s\r\n", i, process1[i].msg);
		for (; i < count3 ; ++i)
			printf("%d: %s\r\n", i, process2[i-count1].msg);
		printf("%d: Test all case\r\n", i);

		printf("Enter Your test id:");
		int id=0;
		scanf("%d", &id);
		if(id<0 || id > count1+count2)
			continue;
		else if (id == count1+ count2)
		{
			for (int i= 0; i<count1; ++i)
				TEST_foreach_method(aTree, process1[i].type, process1[i].msg);

			for (int i= 0; i<count2; ++i)
				TEST_iterator_method(aTree, process2[i].type, process2[i].msg);
		}
		else if ( id < count1)
		{
				TEST_foreach_method(aTree, process1[id].type, process1[id].msg);
		}
		else
		{
				TEST_iterator_method(aTree, process2[id-count1].type, process2[id-count1].msg);
		}
	}
	return 0;
}
