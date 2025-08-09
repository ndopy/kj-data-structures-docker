//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 6 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
int moveMaxToFront(ListNode **ptrHead);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	int c, i, j;
	c = 1;

	LinkedList ll;
	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move the largest stored value to the front of the list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j=insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("case 2 execute");
			moveMaxToFront(&(ll.head));  // You need to code this function
			printf("The resulting linked list after moving largest stored value to the front of the list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////

int moveMaxToFront(ListNode **ptrHead)
{
    // 예외 처리 : 빈 리스트이거나 유효하지 않은 포인터인 경우
	if (ptrHead == NULL || *ptrHead == NULL) {
		return -1;
	}

	// 리스트에 노드가 하나만 있다면 : 이동할 필요가 없다.
	if ((*ptrHead)->next == NULL) {
		return 0;
	}

	ListNode *current = *ptrHead;		// 리스트를 순회할 노드
	ListNode *prev_of_current = NULL;   // current 이전 노드
	ListNode *max_node = *ptrHead;      // 현재까지 발견한 최대값을 가진 노드
	ListNode *prev_of_max_node = NULL;  // max_node 이전 노드
	int max_value = (*ptrHead)->item;   // 현재까지의 최대값

	while (current != NULL) {
		// 최대값인지 비교하기
		if (current->item > max_value) {
			max_value = current->item;
			max_node = current;
			prev_of_max_node = prev_of_current;
		}

		// 다음 노드로 이동하기 전에 현재 노드를 prev_of_current 로 저장
		prev_of_current = current;
		current = current->next;
	}
	// while 문이 종료되면 max_value, max_node, prev_of_max_node 가 결정된다.

	// 만약 max_node 가 head 라면 : 리스트를 변경할 필요가 없다.
	if (max_node == *ptrHead) {
		return 0;
	}

	// 1. max_node 분리하기
	// prev_of_max_node 의 next 를 max_node 의 다음 노드를 가리키도록 연결하기
	if (prev_of_max_node != NULL) {
		prev_of_max_node->next = max_node->next;
	}

	// 2. max_node 를 새로운 head 로 만들기
	max_node->next = *ptrHead;
	*ptrHead = max_node;

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}

ListNode * findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}

void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}
