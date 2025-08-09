//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 7 */

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
void RecursiveReverse(ListNode **ptrHead);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;
	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Reversed the linked list:\n");
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
			j = insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			RecursiveReverse(&(ll.head)); // You need to code this function
			printf("The resulting linked list after reversed the given linked list is: ");
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
static ListNode* newHeadOfReversedList = NULL;

void RecursiveReverse(ListNode **ptrHead)
{
	ListNode *current_node = *ptrHead;

	// 기저 조건
	// 1. 리스트가 비어있는 경우 (NULL 포인터에 도달)
	// 2. 현재 노드가 리스트의 마지막 노드일 경우 (next 가 NULL 인 경우)
	if (current_node == NULL || current_node->next == NULL) {
		// 현재 노드가 마지막 노드라면, 이 노드가 역방향 리스트의 새로운 head 이다.
		if (current_node != NULL) {
			newHeadOfReversedList = current_node;
		}
		return; // 재귀 종료
	}

	// 다음 노드를 저장해두기
	ListNode *next_node = current_node->next;

	// 재귀 호출하기
	RecursiveReverse(&next_node);

	// 포인터 뒤집기 (재귀 호출이 돌아올 때)
	// 현재 노드의 다음 노드가 이제 current_node 를 가리키게 한다.
	// ex. 2 -> 3 이었다면 3 -> 2 로 만든다.
	current_node->next->next = current_node;

	// current_node 의 next 를 NULL 로 설정해서 원래 연결을 끊어서 순환을 방지한다.
	// ex. 3 -> 2 로 만들었어도 아직 2 -> 3 으로도 연결되어 있으므로 이것을 끊는다.
	current_node->next = NULL;

	// 최종 head 포인터 업데이트
	// -> ptrHead 가 ll.head 였을 때만, 즉 최초 호출에만 실행한다.
	if (*ptrHead == current_node) {			// current_node 는 최초 호출 시 ll.head 가 가리키는 노드였다.
		*ptrHead = newHeadOfReversedList;   // newHeadOfReversedList 는 재귀의 가장 깊은 곳에서 설정된 최종 새로운 head 이다.
	}
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
