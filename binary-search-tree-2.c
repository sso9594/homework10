#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


void printStack();



int main()
{   
    printf("[----- [Your Name] [Student ID] -----]");
    printf("\t신승용\t2019038073\n");
	char command;
	int key;
	Node* head = NULL;

	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)	//재귀함수를 이용한 중위순회
{
	if (ptr) {
		recursiveInorder(ptr->left); //재귀함수를 이용해 왼쪽 자식노드로 이동 및 출력
		printf(" [%d] ", ptr->key); //ptr의 위치에 있는 노드 출력
		recursiveInorder(ptr->right); //재귀 함수를 이용해 오른쪽 자식노드로 이동 및 출력
	}
}


void iterativeInorder(Node* node) //반복문을 이용한 중위 순회
{
	for (;;) //break 문이 나올때 까지 무한반복
	{
		for (; node; node = node->left) //노드가 NULL이 아닐때 까지 왼쪽자식 노드로 이동하며 반복
			push(node); // 왼쪽자식 노드로 계속 이동하며 주소를 스택에 저장
		node = pop(); //스택의 top의 위치에 있는 주소를 저장하고 반환하여 반환값을 저장

		if (!node) break; //노드가 없다면 반복종료
		printf(" [%d] ", node->key); //현재 노드의 키값 출력

		node = node->right; //오른쪽 자식노드로 이동
	}
}


void levelOrder(Node* ptr) //레벨 순으로 순회하는 함수
{
	// int front = rear = -1;

	if (!ptr) return; // 트리가 비어있다면 리턴

	enQueue(ptr); //큐에 ptr 주소 입력

	for (;;)
	{
		ptr = deQueue();//큐에 저장되어있는 값 리턴
		if (ptr) {
			printf(" [%d] ", ptr->key); //큐에 저장되어있던 키값  출력

			if (ptr->left) //ptr의 왼쪽 자식노드가 있다면
				enQueue(ptr->left); // 그 노드를 큐에 추가
			if (ptr->right)//ptr의 오른쪽 자식노드가 있담녀
				enQueue(ptr->right); // 그 노드를 큐에 추가
		}
		else //더이상 노드가 없다면
			break; //종료

	}

}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while (ptr != NULL) {

		/* if there is a node for the key, then just return */
		if (ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if (ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if (parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key) //노드를 삭제하는 함수
{
	if (head == NULL) {//트리가 할당 되어있지 않은경우
		printf("\n Nothing to delete!!\n"); //에러메세지 출력
		return -1;
	}

	if (head->left == NULL) { //트리에 아무것도 없을경우
		printf("\n Nothing to delete!!\n"); //에러메세지 출력
		return -1;
	}

	/* head->left is the root */
	Node* root = head->left; //루트노드를 가리킬 노드 root 선언



	Node* parent = NULL; //부모노드를 가리킬 노드 초기화
	Node* ptr = root; //ptr을 루트노드를 가리키게 선언

	while ((ptr != NULL) && (ptr->key != key)) { //ptr이 NULL 이 아니고 키값이 찾는값과 일치하지 않는 경우 계속 반복
		if (ptr->key != key) { //ptr의 키값이 찾는 키값이 아닐경우

			parent = ptr;	// parent에 ptr 노드의 주소를 넘긴다
			
			if (ptr->key > key) //ptr의 키값이 찾는 키값보다 크다면
				ptr = ptr->left; //ptr을 왼쪽 자식노드로 이동시킨다
			else //ptr의 키값이 찾는 키값보다 작다면
				ptr = ptr->right;//ptr을 오른쪽 자식노드로 이동시킨다
		}
	}

	/* there is no node for the key */
	if (ptr == NULL) //ptr이 트리를 다 검색했지만 찾지 못했을경우
	{
		printf("No node for key [%d]\n ", key); //에러메세지 출력
		return -1;
	}

	/*
	 * case 1: the node which has to be removed is a leaf node
	 */
	if (ptr->left == NULL && ptr->right == NULL) //찾은 ptr 의 자식노드가 없을경우
	{
		if (parent != NULL) { /* parent exists, parent's left and right links are adjusted */
			if (parent->left == ptr)//부모노드의 왼쪽 자식노드가 ptr일경우
				parent->left = NULL; //부모노드의 왼쪽 자식노드 NULL로 초기화
			else//부모노드의 오른쪽 자식노드가 ptr일경우
				parent->right = NULL;//부모노드의 오른쪽 자식노드 NULL로 초기화
		}
		else { //ptr이 루트노드일경우
			/* parent is null, which means the node to be deleted is the root */
			head->left = NULL; // 루트노드 NULL로 초기화

		}

		free(ptr); //ptr 동적할당 해제
		return 1;
	}

	/**
	 * case 2: if the node to be deleted has one child
	 */
	if ((ptr->left == NULL || ptr->right == NULL)) //ptr이 하나의 자식노드가 있다면
	{
		Node* child; //자식노드를 가리킬 노드 선언
		if (ptr->left != NULL) //ptr이 왼쪽 자식노드를 갖고있다면
			child = ptr->left; //ptr의 왼쪽 자식노드 child로 선언
		else //ptr이 오른쪽 자식노드를 갖고있다면
			child = ptr->right;//ptr의 오른쪽 자식노드 child로 선언

		if (parent != NULL) //ptr이 루트노드가 아니라면
		{
			if (parent->left == ptr) //부모노드의 왼쪽 자식노드가 ptr이라면
				parent->left = child; //부모노드의 왼쪽 자식노드를 child 로 변경
			else //부모노드의 오른쪽 자식노드가 ptr이라면
				parent->right = child;//부모노드의 오른쪽 자식노드를 child 로 변경
		}
		else { //ptr이 루트노드 일 경우
			/* parent is null, which means the node to be deleted is the root
			 * and the root has one child. Therefore, the child should be the root
			 */
			root = child; //child를 루트노드로 설정
		}

		free(ptr); //ptr 동적할당 해제
		return 1;
	}

	/**
	 * case 3: the node (ptr) has two children
	 *
	 * we have to find either the biggest descendant node in the left subtree of the ptr
	 * or the smallest descendant in the right subtree of the ptr.
	 *
	 * we will find the smallest descendant from the right subtree of the ptr.
	 *
	 */

	Node* candidate;
	parent = ptr;


	candidate = ptr->right;

	/* the smallest node is left deepest node in the right subtree of the ptr */
	while (candidate->left != NULL) // ptr의 오른쪽 자식노드들중 가장 왼쪽 하위 노드를 찾는다
	{
		parent = candidate;
		candidate = candidate->left;
	}

	/* the candidate node is the right node which has to be deleted.
	 * note that candidate's left is null
	 */
	if (parent->right == candidate) //부모노드의 오른쪽자식노드와 candidate 와 같을경우
		parent->right = candidate->right; //부모노드의 오른쪽 자식노드에 candidate 의 오른쪽 자식노드 입력
	else // 다를경우
		parent->left = candidate->right; //parent의 왼쪽 자식노드에 candidate의 오른쪽 자식노드 입력

	/* instead of removing ptr, we just change the key of ptr
	 * with the key of candidate node and remove the candidate node
	 */

	ptr->key = candidate->key;//ptr의 키값에 candidate의 키값 입력

	free(candidate); //candidate 삭제
	return 1;
}


void freeNode(Node* ptr)
{
	if (ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if (head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop() //스택을 pop 하는 함수
{
	if (top < 0) return NULL; //top이 0보다 작을경우 스택이 비어있으므로 pop할수가 없기 때문에 NULL리턴
	return stack[top--]; // top 리턴하여 pop
}

void push(Node* aNode) //스택을 push 하는 함수
{
	stack[++top] = aNode; //스택에 aNode를 삽입하여 push 
}


void printStack()
{
	int i = 0;
	printf("--- stack ---\n");
	while (i <= top)
	{
		printf("stack[%d] = %d\n", i, stack[i]->key);
	}
}


Node* deQueue() //큐의 원소를 리턴하고 삭제하는 함수
{
	if (front == rear) {//front와 rear가 같을경우 큐가 비어있으므로
		
		return NULL; //NULL을 리턴
	}

	front = (front + 1) % MAX_QUEUE_SIZE; //front가 MAX_QUEUE_SIZE를 넘으면 처음으로 돌아가기 때문에 나머지 연산으로 계산
	return queue[front]; //queue 의 맨 앞 원소 리턴

}

void enQueue(Node* aNode) //큐의 원소를 입력하는 함수
{
	rear = (rear + 1) % MAX_QUEUE_SIZE; //front가 MAX_QUEUE_SIZE를 넘으면 처음으로 돌아가기 때문에 나머지 연산으로 계산
	if (front == rear) { //front와 rear가 같을경우 큐가 비어있으므로
		
		return; //함수 종료
	}

	queue[rear] = aNode; //aNode를 큐에 삽입
}
