
//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024
///////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode;   // You should not change the definition of BSTNode

typedef struct _QueueNode {
	BSTNode *data;
	struct _QueueNode *nextPtr;
}QueueNode; // You should not change the definition of QueueNode


typedef struct _queue
{
	QueueNode *head;
	QueueNode *tail;
}Queue; // You should not change the definition of queue

///////////////////////////////////////////////////////////////////////////////////

// You should not change the prototypes of these functions
void levelOrderTraversal(BSTNode *node);

void insertBSTNode(BSTNode **node, int value);

BSTNode* dequeue(QueueNode **head, QueueNode **tail);
void enqueue(QueueNode **head, QueueNode **tail, BSTNode *node);
int isEmpty(QueueNode *head);
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
	printf("2: Print the level-order traversal of the binary search tree;\n");
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
			printf("The resulting level-order traversal of the binary search tree is: ");
			levelOrderTraversal(root); // You need to code this function
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

void levelOrderTraversal(BSTNode* root) {
	/* add your code here */
	Queue queue;
	queue.head = NULL;
	queue.tail = NULL;

	enqueue(&queue.head, &queue.tail, root);

	while (!isEmpty(queue.head)) {
		BSTNode* current_node = dequeue(&queue.head, &queue.tail);
		printf("%d ", current_node->item);

		if (current_node->left != NULL) {
			enqueue(&queue.head, &queue.tail, current_node->left);
		}

		if (current_node->right != NULL) {
			enqueue(&queue.head, &queue.tail, current_node->right);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////


/*
 * 이진 탐색 트리에 새로운 노드를 삽입하는 함수
 * 매개변수:
 *   - node: 이진 탐색 트리의 노드에 대한 이중 포인터
 *   - value: 삽입할 값
 * 동작:
 *   1. 노드가 NULL인 경우 새로운 노드를 생성하고 값을 저장
 *   2. 삽입할 값이 현재 노드의 값보다 작으면 왼쪽 서브트리로 이동
 *   3. 삽입할 값이 현재 노드의 값보다 크면 오른쪽 서브트리로 이동
 *   4. 값이 이미 존재하는 경우 삽입하지 않고 반환
 */
void insertBSTNode(BSTNode **node, int value){
	if (*node == NULL) // 현재 노드가 비어있는지 확인 -> 트리가 비어있거나, 새로운 노드를 삽입할 위치를 찾았을 때
	{
		// BSTNode 구조체 크기만큼 힙(heap) 메모리를 동적으로 할당받기
		*node = malloc(sizeof(BSTNode));

		if (*node != NULL) {		// 메모리가 할당되었다면
			(*node)->item = value;  // 새 노드의 item 에 value 를 저장
			(*node)->left = NULL;   // 새 노드의 왼쪽 자식 포인터를 NULL 로 초기화
			(*node)->right = NULL;  // 새 노드의 오른쪽 자식 포인터를 NULL 로 초기화
		}
	}
	else  // 이미 현재 위치에 노드가 존재하는 경우
	{
		if (value < (*node)->item) // 삽입할 값이 현재 노드의 값보다 작을 경우 -> 왼쪽으로 탐색
		{
			insertBSTNode(&((*node)->left), value);
		}
		else if (value >(*node)->item) // 삽입할 값이 현재의 노드의 값보다 클 경우 -> 오른쪽으로 탐색
		{
			insertBSTNode(&((*node)->right), value);
		}
		else
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////

// enqueue node
/**
 *
 * @param headPtr : 큐의 맨 앞을 가리키는 head 포인터 주소
 * @param tailPtr : 큐의 맨 뒤를 가리키는 tail 포인터 주소
 * @param node : 큐에 담을 이진 탐색 트리 노드의 포인터
 */
void enqueue(QueueNode **headPtr, QueueNode **tailPtr, BSTNode *node)
{
	// dynamically allocate memory
	QueueNode *newPtr = malloc(sizeof(QueueNode));

	// if newPtr does not equal NULL
	if (newPtr != NULL) {		// 메모리 할당에 성공했으면
		newPtr->data = node;    // 큐 노드의 data 필드에 node 주소 저장.
		newPtr->nextPtr = NULL; // 다음 노드를 가리키는 포인터는 NULL 로 초기화.

		// if queue is empty, insert at head
		if (isEmpty(*headPtr)) {   // head 포인터가 NULL 이라면 = 큐가 비어있다면
			*headPtr = newPtr;     // 새로 만든 큐 노드를 head 포인터가 가리키도록 해야 한다.
		}
		else { // insert at tail
			(*tailPtr)->nextPtr = newPtr; // 큐의 마지막 노드의 nextPtr 이 새 노드를 가리키게 한다.
		}

		*tailPtr = newPtr; // 새로 생성한 노드가 큐의 tail 노드가 된다.
	}
	else {
		printf("Node not inserted");
	}
}

/**
 * 큐의 첫 번째 BSTNode 포인터를 반환한다.
 *
 * @param headPtr 큐의 첫 번째 노드를 가리키는 포인터의 주소
 * @param tailPtr 큐의 마지막 노드를 가리키는 포인터의 주소
 * @return 큐의 첫 번째 노드를 가리키는 포인터
 */
BSTNode* dequeue(QueueNode **headPtr, QueueNode **tailPtr)
{
	BSTNode *node = (*headPtr)->data;  // 큐의 맨 앞에 있는 노드(*headPtr)에 담겨있는 BSTNode 의 포인터(data)에 접근
	QueueNode *tempPtr = *headPtr;     // 현재 큐의 맨 앞 노드를 제거하기 위해, 해당 노드의 주소를 임시 포인터에 저장
	*headPtr = (*headPtr)->nextPtr;    // head 포인터를 다음 노드(*headPtr->nextPtr)로 이동 = 큐의 맨 앞 노드를 제거

	if (*headPtr == NULL) {  // 만약 head 포인터가 다음 노드로 이동했는데 NULL이 됐다면 -> 큐의 노드가 하나였다면
		*tailPtr = NULL;     // 큐가 비워진 것이므로, tail 포인터도 NULL 로 설정한다.
	}

	free(tempPtr); // 메모리 누수 방지를 위해서 임시 노드의 메모리를 해제한다.

	return node;
}

/**
 * 큐가 비어있는지 확인한다.
 *
 * @param head 큐의 맨 앞에 위치한 노드
 * @return head 포인터가 NULL인지 1(true) or 0(false)
 */
int isEmpty(QueueNode *head)
{
	return head == NULL;
}

/**
 * 이진 탐색 트리의 모든 노드를 재귀적으로 순회하며 메모리를 해제한다.
 *
 * @param node 메모리를 해제할 시작 노드
 */
void removeAll(BSTNode **node)
{
	if (*node != NULL) // 현재 노드가 존재한다면
	{
		removeAll(&((*node)->left));  // 왼쪽 서브트리를 재귀적으로 호출
		removeAll(&((*node)->right)); // 오른쪽 서브트리를 재귀적으로 호출
		free(*node);                  // 현재 노드의 메모리를 해제
		*node = NULL;                 // 해당 노드를 가리키던 포인터를 NULL 로 설정
									  // 이미 해제한 메모리를 가리키는 댕글링 포인터(dangling pointer) 를 방지할 수 있다.
	}
}
