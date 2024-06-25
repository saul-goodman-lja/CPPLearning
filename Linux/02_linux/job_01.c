#include <stdio.h>
#include <stdlib.h>

typedef struct {
int value;
struct Node *next;
} Node;

// 尾插法插入结点
void add_before_tail(Node **head, int value) {
Node *new_node = (Node *)malloc(sizeof(Node));
new_node->value = value;
new_node->next = NULL;
if (*head == NULL) {
  *head = new_node;
} else {
  Node *temp = *head;
  while (temp != NULL) {
      temp = temp->next;
  }
  temp->next = new_node;
}
}

// 打印链表中的所有值
void print_list(Node *head) {
Node *current = head;
while (current != NULL) {
	 current = current->next;
  printf("%d -> ", current->value);
}
printf("NULL\n");
}

int main() {
Node *head = NULL;
add_before_tail(&head, 1);
add_before_tail(&head, 2);
add_before_tail(&head, 3);

print_list(head);
return 0;
}