//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 2 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode;   // You should not change the definition of BSTNode

typedef struct _stackNode{
	BSTNode *data;
	struct _stackNode *next;
}StackNode; // You should not change the definition of StackNode

typedef struct _stack
{
	StackNode *top;
}Stack; // You should not change the definition of Stack

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void inOrderTraversal(BSTNode *node);

void insertBSTNode(BSTNode **node, int value);

void push(Stack *stack, BSTNode *node);
BSTNode *pop(Stack *s);
BSTNode *peek(Stack *s);
int isEmpty(Stack *s);
void removeAll(BSTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	//Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode *root;
	root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the in-order traversal of the binary search tree;\n");
	printf("0: Quit;\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("The resulting in-order traversal of the binary search tree is: ");
			inOrderTraversal(root); // You need to code this function
			printf("\n");
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void inOrderTraversal(BSTNode *root) {
    /* add your code here */
	Stack stack;
	stack.top = NULL;

	// 스택이 비어 있지 않다면 비우기
	if (!isEmpty(&stack)) {
		while (!isEmpty(&stack)) {
			pop(&stack);
		}
	}

	BSTNode* current = root;

	while (current != NULL || !isEmpty(&stack)) {

		while (current != NULL) {
			// 왼쪽 자식 노드들을 스택에 모두 푸시하기
			push(&stack, current);
			current = current->left;
		}

		// while 문이 끝나면 왼쪽 끝에 도달하면 스택에서 노드를 팝하기
		current = pop(&stack);

		// pop한 노드의 값 출력하기
		printf("%d ", current->item);

		// pop한 노드의 오른쪽 자식으로 이동해서 다음 반복
		current = current->right;
	}
}

///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value){
	if (*node == NULL)
	{
		*node = malloc(sizeof(BSTNode));

		if (*node != NULL) {
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}
	}
	else
	{
		if (value < (*node)->item)
		{
			insertBSTNode(&((*node)->left), value);
		}
		else if (value >(*node)->item)
		{
			insertBSTNode(&((*node)->right), value);
		}
		else
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////


void push(Stack *stack, BSTNode *node) {
	// 새로운 스택 노드를 위한 메모리 할당
	StackNode *temp;
	temp = malloc(sizeof(StackNode));

	// 메모리 할당 실패 시 함수 종료
	if (temp == NULL)
		return;
	// 새로운 노드에 BST 노드 데이터 저장
	temp->data = node;

	// 스택이 비어있는 경우
	if (stack->top == NULL) {
		stack->top = temp;   // 새로운 노드가 top 이 된다.
		temp->next = NULL;   // 아직 노드가 1개 뿐이므로, 가리킬 다음 노드가 없다.
	}
	// 스택이 비어있지 않은 경우 = 다른 노드들이 이미 들어있는 경우
	else
	{
		temp->next = stack->top; // 현재 top을 가리키고 있는 노드를 새로 생성한 다음 노드의 next 로 가리킨다.
		stack->top = temp;       // 새로 생성한 노드를 top 으로 가리키게 한다.
	}
}

BSTNode * pop(Stack * s)
{
	StackNode *temp, *t;    // temp: 삭제될 노드의 다음 노드를 임시로 가리킬 포인터
							// t: 스택의 현재 top을 가리킬 포인터
	BSTNode * ptr;          // 스택에서 꺼내질 BSTNode의 주소를 가진 포인터
	ptr = NULL;

	t = s->top;             // 포인터 t가 현재 맨 위 노드를 바라본다.
	if (t != NULL)          // top != NULL, 즉 스택이 비어 있지 않다면
	{
		temp = t->next;     // temp 포인터가 "현재 맨 위 노드의 다음 노드"를 가리키도록 한다.
		ptr = t->data;      // t가 가리키는 맨 위 스택 노드가 담고 있는 BSTNode 의 주소를 ptr 에 저장한다.

		s->top = temp;      // top이 가리키는 노드를 temp 로 변경한다. -> 맨 위 노드는 스택에서 분리된다.
		free(t);            // 기존 top이 가리키는 노드의 메모리를 해제한다.
		t = NULL;           // 메모리 주소도 NULL 로 초기화한다.
	}

	return ptr;             // 스택에서 꺼낸 BSTNode 의 주소가 반환된다.
}


BSTNode * peek(Stack * s)
{
	StackNode *temp;		// 스택의 맨 위 노드를 가리킬 임시 포인터
	temp = s->top;
	if (temp != NULL)		// 스택이 비어있지 않다면
		return temp->data;  // 스택의 맨 위 노드의 주소를 반환한다.
	else
		return NULL;        // 스택이 비어있다면 NULL 을 반환한다.
}


int isEmpty(Stack *s)
{
	if (s->top == NULL)     // 스택이 비어 있다면 1, 그렇지 않다면 0을 반환한다.
		return 1;
	else
		return 0;
}


void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}
