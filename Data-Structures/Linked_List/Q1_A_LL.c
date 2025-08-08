//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;		// 실제 데이터를 저장할 변수
	struct _listnode *next;	// 다음 노드의 주소를 저장하는 포인터
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist{
	int size;		// 연결 리스트의 크기 = 저장된 노드의 개수
	ListNode *head;		// 연결 리스트 안의 첫 번째 노드
} LinkedList;			// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

//You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
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

	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	// 사용자가 0을 입력할 때까지 입력을 받는다.
	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:	// 연결 리스트에 넣을 정수값을 입력하세요.
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2: // 가장 최근에 추가된 노드의 값과 인덱스를 출력한다.
			printf("The value %d was added at index %d\n", i, j);
			break;
		case 3: // 현재까지의 연결 리스트를 출력하고, 리스트 안의 모든 노드를 제거한다.
			printf("The resulting sorted linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0: // 리스트 안의 모든 노드를 제거한다.
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}


	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

int insertSortedLL(LinkedList *ll, int item)
{
	/* add your code here */
	// 새로운 정수를 담을 노드를 만들고, 그 노드의 포인터를 저장할 변수를 선언한 다음
	// malloc 으로 노드에 필요한 만큼의 메모리를 할당한다.
	ListNode *newNode = malloc(sizeof(ListNode));

	if (newNode == NULL) {
		printf("Memory allocation failed.\n");
		return -1;
	}
	// 새 노드의 item 변수에 현재 삽입하려는 item을 넣어준다.
	// -> 연산자는 포인터가 가리키는 구조체의 멤버에 접근할 때 사용한다.
	newNode->item = item;
	newNode->next = NULL;

	// 리스트가 비어 있는 경우: 첫 번째 노드인 head가 되어야 한다.
	if (ll->head == NULL) {
		ll->head = newNode;
		ll->size++;
		return 0;	// 첫 번째 노드의 인덱스인 0을 반환
	}

	// 리스트에 노드가 있는 경우
	ListNode *pre = NULL;		// 이전 노드를 가리키는 포인터
	ListNode *cur = ll->head;	// 현재 노드를 가리키는 포인터
	int count = 0;				// 인덱스를 추적할 변수

	while (cur != NULL && cur->item < item) {
		pre = cur;
		cur = cur->next;
		count++;
	}

	// 새 노드를 첫 번째 위치에 삽입해야 하는 경우
	// while 반복문이 한 번도 실행되지 않은 경우
	// => newNode->item  < head->item
	if (pre == NULL) {
		newNode->next = ll->head;
		ll->head = newNode;
		// Q. 이 다음에 head의 next 를 NULL로 설정해야 하지 않나? 이미 head의 next가 NULL로 초기화되어 있나?
	}
	else { // 새 노드를 중간 또는 마지막 위치에 삽입해야 하는 경우
		newNode->next = cur;
		pre->next = newNode;
	}

	ll->size++;

	return count;
}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){
	// 노드를 가리킬 포인터 변수
	ListNode *cur;

	// 현재 리스트가 없다면 함수를 종료한다.
	if (ll == NULL)
		return;

	// cur가 head 를 가리키도록 연결한다.
	cur = ll->head;

	// head 노드가 없다면 리스트가 비어있는 것이다.
	if (cur == NULL)
		printf("Empty");

	// 현재 노드가 NULL이 아닐 때까지 = 리스트의 끝에 도달할 때까지
	while (cur != NULL)
	{
		// 현재 노드의 값을 출력하고
		printf("%d ", cur->item);
		// 다음 노드로 이동한다.
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;	// head 를 가리킨다.
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;	// tmp에 cur가 가리키는 노드의 다음 노드의 주소를 저장한다.
		free(cur);		// 현재 노드가 차지하는 메모리를 해제한다.
		// 메모리 해제 전에 다음 노드의 주소를 tmp에 저장하지 않으면 해제된 메모리에 접근하게 되어 오류가 발생할 수 있다.
		cur = tmp;		// 현재 노드가 다음 노드 주소를 바라보게 한다.
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){
	// index 에 해당하는 노드를 찾아서 그 노드의 주소(포인터)를 반환한다.

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
	// 리스트가 비어있거나, 첫 번째에 삽입할 경우
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));	// 새로운 노드를 위한 메모리를 할당한다.
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	// 리스트의 중간에 삽입할 경우
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
	if (index == 0){		// 첫 번째 노드를 삭제할 경우
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){	// 중간에 있는 노드를 삭제할 경우

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
