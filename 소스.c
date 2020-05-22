#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX 50
#define TRUE 1
#define FALSE 0

typedef char element;

typedef struct DlistNode {
	element data;
	struct DlistNode *link_L;
	struct DlistNode *link_R;
} DlistNode;

typedef struct DequeType {
	DlistNode *head;
	DlistNode *tail;
}DequeType;

void error(char *message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init(DequeType *dq) {
	dq->head = dq->tail = NULL;

}

DlistNode *create_node(DlistNode *link_L, element item, DlistNode *link_R) {
	DlistNode *node = (DlistNode *)malloc(sizeof(DlistNode));
	if (node == NULL) error("메모리 할당 오류");
	node->link_L = link_L;
	node->data = item;
	node->link_R = link_R;

	return node;
}

char is_full(DequeType *dq) {

}

int is_empty(DequeType *dq) {
	if (dq->head == NULL && dq->tail == NULL) return TRUE;
	else return FALSE;
}

char get_front(DequeType *dq) {
	return dq->head->data;
}

char get_rear(DequeType *dq) {
	return dq->tail->data;
}

void add_front(DequeType *dq, element item) {
	DlistNode *new_node = create_node(NULL, item, dq->head);

	if (is_empty(dq)) dq->tail = new_node;
	else dq->head->link_L = new_node;
	dq->head = new_node;
}

void add_rear(DequeType *dq, element item) {
	DlistNode *new_node = create_node(dq->tail, item, NULL);
	if (is_empty(dq)) dq->head = new_node;
	else dq->tail->link_R = new_node;
	dq->tail = new_node;
}

element delete_front(DequeType *dq) {
	element item;
	DlistNode *removed_node;

	if (is_empty(dq)) error("삭제할 노드가 존재하지 않음");
	else {
		removed_node = dq->head;
		item = removed_node->data;
		dq->head = dq->head->link_R;
		free(removed_node);
		if (dq->head == NULL) dq->tail = NULL;
		else dq->head->link_L = NULL;
	}

	return item;
}

element delete_rear(DequeType *dq) {
	element item;
	DlistNode *removed_node;

	if (is_empty(dq)) error("삭제할 노드가 존재하지 않음");
	else {
		removed_node = dq->tail;
		item = removed_node->data;
		dq->tail = dq->tail->link_L;
		free(removed_node);
		if (dq->tail == NULL) dq->head = NULL;
		else dq->tail->link_R = NULL;
	}

	return item;
}

void display(DequeType *dq) {
	DlistNode *p;
	
	printf("─┃ display┃──────────────\n\n");
	for (p = dq->head; p != NULL; p = p->link_R) {
		printf("%c", p->data);
	}
	printf("\n\n─────────────────────────\n");

}

int check_palindrome(DequeType *dq) {
	if (dq->head != dq->tail) return TRUE;
	else return FALSE;
}

void Palindrome(DequeType deque) {
	while (check_palindrome(&deque)) {
		if (get_front(&deque) == get_rear(&deque)) {
			delete_front(&deque);
			delete_rear(&deque);
		}
		else {
			printf("\n***Not Palindrome****\n\n");
			return;
		}
	}

	printf("\n***It's Palindrome***\n\n");
	return;
}


void main() {

	DequeType deque;

	char alpha = NULL;
	int select = 1;

	init(&deque);

	while (select != 0) {
		printf("┌──────────────┐\n");
		printf("│ 1.삽입(front)│\n");
		printf("│ 2.삽입(rear) │\n");
		printf("│ 3.삭제(front)│\n");
		printf("│ 4.삭제(rear) │\n");
		printf("│ 5.회문판정   │\n");
		printf("│              │\n");
		printf("│ etc. 종료    │\n");
		printf("└──────────────┘\n");

		printf(" ⇒입력 : ");
		scanf("%d", &select);
		scanf("%c", &alpha);//enter누르면 '\n'가 버퍼에 남아있는거 없애주기위함

		switch (select)
		{
		case 1:
			alpha = NULL;
			printf("\n삽입(front)값 입력 : ");
			scanf("%c", &alpha);
			printf("─────────────────────────\n");
			while (alpha != '\n') {
				add_front(&deque, alpha);
				printf("[Front]%c  ", get_front(&deque));
				printf("[Rear]%c\n", get_rear(&deque));

				scanf("%c", &alpha);
			}
			display(&deque);
			break;
		case 2:
			printf("\n삽입(rear)값 입력\n");
			scanf("%c", &alpha);
			printf("─────────────────────────\n");
			while (alpha != '\n') {
				add_rear(&deque, alpha);
				printf("[Front]%c  ", get_front(&deque));
				printf("[Rear]%c\n", get_rear(&deque));

				scanf("%c", &alpha);
			}
			display(&deque);
			break;
		case 3:
			printf("\n[삭제(front)] %c\n", delete_front(&deque));
			display(&deque);
			break;
		case 4:
			printf("\n[삭제(rear)] %c\n", delete_rear(&deque));
			display(&deque);
			break;
		case 5:
			printf("\n[회문판정]\n");
			Palindrome(deque);
			break;
		default:
			select = 0;
			break;
		}

	}


}
