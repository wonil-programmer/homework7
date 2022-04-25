#include<stdio.h>
#include<stdlib.h>

/* 이중 연결리스트에 사용될 노드 구조체 listNode 선언 */
typedef struct Node {
	int key; // 노드에 저장되는 값 key
	struct Node* llink; // 이전 노드를 가리킬 노드 구조체 포인터 llink
	struct Node* rlink; // 다음 노드를 가리킬 노드 구조체 포인터 rlink
} listNode;

/* 이중 연결리스트의 헤드 노드를 가리킬 headNode 선언 */
typedef struct Head {
	struct Node* first;
}headNode;


/* 함수 원형 정의 */
int initialize(headNode** h);
int freeList(headNode* h);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);
void printList(headNode* h);


int main()
{
    printf("------ [허원일] [2019036068] ------\n");
	char command;
	int key;
	headNode* headnode=NULL; // 헤드 노드 포인터 초기화

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
            /* 이중 연결리스트 초기화 */
			initialize(&headnode);
			break;
		case 'p': case 'P':
            /* 이중 연결리스트 출력 */
			printList(headnode);
			break;
		case 'i': case 'I':
            /* 이중 연결리스트에 노드 삽입 */
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
            /* 이중 연결리스트에서 노드 삭제 */
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
            /* 이중 연결리스트 마지막에 노드 삽입 */
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
            /* 이중 연결리스트 마지막 노드 삭제 */
			deleteLast(headnode);
			break;
		case 'f': case 'F':
            /* 이중 연결리스트 처음에 노드 삽입 */
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
            /* 이중 연결리스트 처음 노드 삭제 */
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
            /* 이중 연결리스트 뒤집기 */
			invertList(headnode);
			break;
		case 'q': case 'Q':
            /* 프로그램 종료 */
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

/* 이중 연결리스트 초기화 함수 */
int initialize(headNode** h) {

	/* headNode가 NULL이 아닌 경우 즉, 연결리스트가 존재할 경우 헤드노드 포인터에 할당된 메모리 반납 */
	if(*h != NULL)
		freeList(*h);

	/* headNode가 NULL인 경우 즉, 연결리스트가 존재하지 않는 경우 headNode에 대한 메모리를 할당하여 리턴 */
	*h = (headNode*)malloc(sizeof(headNode));
	(*h)->first = NULL;
	return 1;
}

/* 이중 연결리스트에 할당된 메모리를 해제하는 함수 */
int freeList(headNode* h){
	// headNode의 first를 가리키는 임시 노드 구조체 포인터 p
	listNode* p = h->first;
    // p를 따라가며 삭제할 노드를 가리킬 구조체 포인터 prev
	listNode* prev = NULL;
    // p가 마지막 노드까지 방문하며 p 이전 노드를 가리키는 포인터 prev가 가리키는 노드에 할당된 메모리 반납
	while(p != NULL) {
		prev = p;
		p = p->rlink;
		free(prev);
	}
    // headNode에 할당된 메모리 반납
	free(h);
	return 0;
}

/* 이중 연결리스트를 출력하는 함수 */
void printList(headNode* h) {
	int i = 0;
    // 임시 노드 구조체 포인터 p
	listNode* p; 

	printf("\n---PRINT\n");

    // headNode가 NULL인 경우 즉, 이중 연결리스트가 존재하지 않는 경우 함수 경고문 출력 후 리턴
	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

    // p가 headNode의 first를 가리키도록 함
	p = h->first;
    // p가 마지막 노드까지 방문하며 노드의 key 출력
	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink; // p를 p 다음 노드를 가리키게함
		i++;
	}

	printf("  items = %d\n", i);
}


/* 리스트를 탐색하며 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입하는 함수 */
int insertNode(headNode* h, int key) {

    /* 삽입할 노드 생성 (메모리 할당) */
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;

    /* headNode의 first값이 NULL인 경우 즉, 연결리스트가 비어있는 경우 first에 노드 삽입 */
	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first; // 임시 노드구조체 포인터 n

	/* key를 기준으로 삽입할 위치를 찾음 */
	while(n != NULL) {
		if(n->key >= key) {
			/* 첫번째 노드 앞쪽에 삽입해야할 경우인지 검사 */
			if(n == h->first) {
				insertFirst(h, key); // key를 가진 노드를 첫번째 노드 앞에 삽입
			} /* 중간이거나 마지막인 경우 */
			else { 
				node->rlink = n; // node의 다음노드를 n으로 지정
				node->llink = n->llink; // node의 이전노드를 n의 이전노드와 같게 지정
				n->llink = node; // n의 이전노드를 node로 지정
				n->llink->rlink = node; // n의 이전노드의 다음노드를 node로 지정
			}
			return 0;
		}

		n = n->rlink; // n을 다음 노드로 이동
	}

	/* 마지막 노드까지 탐색했음에도 key 없을 경우, 마지막에 삽입 */
	insertLast(h, key);
	return 0;
}

/* 연결리스트의 마지막에 노드를 삽입하는 함수 */
int insertLast(headNode* h, int key) {

	/* 삽입할 노드 생성 (메모리 할당) */
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	/* headNode의 first값이 NULL인 경우 즉, 연결리스트가 비어있는 경우 first에 노드 삽입 */
	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}


	listNode* n = h->first; // 임시 노드구조체 포인터 n

	// 마지막노드가 나올때까지 n 이동
	while(n->rlink != NULL) {
		n = n->rlink;
	}
	n->rlink = node; // 기존의 마지막노드 뒤에 node로 지정
	node->llink = n; // node의 이전노드를 n으로 지정

	return 0;
}

/* 연결리스트의 마지막노드를 삭제하는 함수 */
int deleteLast(headNode* h) {

	/* headNode의 first값이 NULL인 경우 즉, 연결리스트가 비어있는 경우 경고메시지 출력 후 함수 종료 */
	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}


	listNode* n = h->first; // 임시 노드구조체 포인터 n
	listNode* trail = NULL; // 임시 노드구조체 포인터 trail

	/* n의 다음노드가 NULL인 경우 즉, 노드가 하나인 경우 처리 */
	if(n->rlink == NULL) {
		h->first = NULL; // headNode를 NULL로 지정
		free(n); // n에 할당된 메모리 해제

		return 0;
	}

	/* 마지막 노드까지 이동 */
	while(n->rlink != NULL) {
		trail = n; // n을 따라가는 trail
		n = n->rlink; // n을 다음노드로 이동
	}

	trail->rlink = NULL; // 마지막 이전 노드의 다음노드 NULL 지정
	free(n); // n에 할당된 메모리 해제

	return 0;
}



/* 연결리스트 처음에 노드를 삽입하는 함수 */
int insertFirst(headNode* h, int key) {

	/* 삽입할 노드 생성 (메모리 할당) */
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = node->llink = NULL;

	/* headNode의 first값이 NULL인 경우 즉, 연결리스트가 비어있는 경우 headNode에 node 삽입후 함수 종료 */
	if(h->first == NULL)
	{
		h->first = node;
		return 1;
	}

	node->rlink = h->first; // node의 다음노드를 기존 headNode로 지정
	node->llink = NULL; // node의 이전노드를 NULL로 지정 

	listNode *p = h->first; // 임시 노드구조체 포인터 p (headNode 가리킴)
	p->llink = node; // p의 이전노드를 node로 지정
	h->first = node; // node를 headNode로 지정

	return 0;
}

/* 연결리스트의 첫번째 노드를 삭제하는 함수 */
int deleteFirst(headNode* h) {

    /* 연결리스트가 비어있을 경우 경고문 출력 후 함수 종료 */
	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first; // headNode의 first를 가리키는 임시 노드구조체 포인터 n
	h->first = n->rlink; // n의 다음 노드를 새로운 headNode의 first로 지정

	free(n); // n에 할당된 메모리 해제

	return 0;
}



/* 이중 연결리스트를 역순으로 재배치하는 함수 */
int invertList(headNode* h) {

	/* headNode의 first값이 NULL인 경우 즉, 연결리스트가 비어있는 경우 경고문 출력 후 함수 종료 */
	if(h->first == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}

	listNode *n = h->first; // 임시 노드구조체 포인터 n
	listNode *middle = NULL; // 임시 노드구조체 포인터 middle (n을 따라가며 n의 이전노드를 가리킴 = 연결을 바꿀 노드를 가리킴)
	listNode *trail = NULL; // 임시 노드구조체 포인터 trail (middle을 따라가며 middle의 이전노드를 가리킴)

	/* 마지막 노드까지 이동 */
	while(n != NULL){
		trail = middle; // trail이 다음노드로 이동
		middle = n; // middle이 다음노드로 이동
		n = n->rlink; // n이 다음노드로 이동
		middle->rlink = trail; // middle의 다음노드를 이전노드(trail)로 지정
		middle->llink = n; // middle의 이전노드를 다음노드(n)로 지정
	}

	/* 역순 배치 완료 후 headNode 초기화 */
	h->first = middle; 

	return 0;
}





/* 이중 연결리스트에서 특정 key의 노드를 삭제하는 함수 */
int deleteNode(headNode* h, int key) {

	/* headNode의 first값이 NULL인 경우 즉, 연결리스트가 비어있는 경우 경고문 출력 후 함수 종료 */
	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* n = h->first; // 임시 노드구조체 포인터 n

	/* key를 기준으로 삭제할 위치를 찾음 */
	while(n != NULL) {
		if(n->key == key) {
			/* 첫번째 노드인 경우 */
			if(n == h->first) {
				deleteFirst(h); // deleteFirst() 호출
			} 
			/* 마지막 노드인 경우 */
			else if (n->rlink == NULL){ 
				deleteLast(h); // deleteLast() 호출
			/* 중간인 경우 */
			} else { 
				n->llink->rlink = n->rlink; // n의 이전노드의 다음노드를 기존의 n 다음노드로 지정
				n->rlink->llink = n->llink; // n의 다음노드의 이전노드를 기존의 n 이전노드로 지정
				free(n); // n에 할당된 메모리 해제 (n의 연결 포인터 llink, rlink에 할당된 메모리들도 해제)
			}
			return 1;
		}

		n = n->rlink; // n을 다음노드로 이동
	}

	/* 찾는 key값이 없는 경우 경고문 출력 */
	printf("cannot find the node for key = %d\n", key);
	return 1;
}


