#include <stdio.h>
#include <stdlib.h>

// 定义双向链表节点结构
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// 初始化双向链表
struct Node* initializeList() {
    return NULL; // 返回一个空链表
}

// 在链表尾部插入节点
struct Node* insertAtEnd(struct Node* head, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;

    if (head == NULL) {
        newNode->prev = NULL;
        return newNode; // 如果链表为空，新节点成为链表头
    }

    struct Node* current = head;
    while (current->next != NULL) {
        current = current->next; // 移动到链表末尾
    }

    current->next = newNode;
    newNode->prev = current;
    return head;
}

// 在链表头部插入节点
struct Node* insertAtBeginning(struct Node* head, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = head;
    newNode->prev = NULL;
    if (head != NULL) {
        head->prev = newNode;
    }
    return newNode; // 新节点成为链表头
}

// 删除节点
struct Node* deleteNode(struct Node* head, int data) {
    if (head == NULL) {
        return NULL; // 空链表，无需删除
    }

    if (head->data == data) {
        struct Node* temp = head;
        head = head->next;
        if (head != NULL) {
            head->prev = NULL;
        }
        free(temp);
        return head; // 删除链表头节点
    }

    struct Node* current = head;
    while (current != NULL && current->data != data) {
        current = current->next;
    }

    if (current != NULL) {
        struct Node* prevNode = current->prev;
        struct Node* nextNode = current->next;

        if (prevNode != NULL) {
            prevNode->next = nextNode;
        }
        if (nextNode != NULL) {
            nextNode->prev = prevNode;
        }

        free(current); // 删除中间或末尾节点
    }

    return head;
}

// 查找节点
struct Node* searchNode(struct Node* head, int data) {
    struct Node* current = head;
    while (current != NULL) {
        if (current->data == data) {
            return current; // 找到匹配的节点
        }
        current = current->next;
    }
    return NULL; // 未找到匹配的节点
}

// 修改节点的数据
void modifyNode(struct Node* head, int oldData, int newData) {
    struct Node* nodeToModify = searchNode(head, oldData);
    if (nodeToModify != NULL) {
        nodeToModify->data = newData; // 修改节点的数据
    }
}

// 打印链表（正向）
void printListForward(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// 打印链表（反向）
void printListBackward(struct Node* tail) {
    struct Node* current = tail;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->prev;
    }
    printf("NULL\n");
}

// 释放链表内存
void freeList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    struct Node* list = initializeList();
    int choice, data, oldData, newData;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert at the end\n");
        printf("2. Insert at the beginning\n");
        printf("3. Delete node\n");
        printf("4. Search node\n");
        printf("5. Modify node\n");
        printf("6. Print list forward\n");
        printf("7. Print list backward\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                list = insertAtEnd(list, data);
                break;
            case 2:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                list = insertAtBeginning(list, data);
                break;
            case 3:
                printf("Enter data to delete: ");
                scanf("%d", &data);
                list = deleteNode(list, data);
                break;
            case 4:
                printf("Enter data to search: ");
                scanf("%d", &data);
                if (searchNode(list, data) != NULL) {
                    printf("Found node with data %d\n", data);
                } else {
                    printf("Node with data %d not found\n", data);
                }
                break;
            case 5:
                printf("Enter data to modify: ");
                scanf("%d", &oldData);
                printf("Enter new data: ");
                scanf("%d", &newData);
                modifyNode(list, oldData, newData);
                break;
            case 6:
                printf("List (forward): ");
                printListForward(list);
                break;
            case 7:
                printf("List (backward): ");
                printListBackward(list);
                break;
            case 8:
                freeList(list);
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
