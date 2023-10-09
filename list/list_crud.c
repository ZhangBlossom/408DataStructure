#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构
struct Node {
    int data;
    struct Node* next;
};

// 初始化链表
struct Node* initializeList() {
    return NULL; // 返回一个空链表
}

// 在链表尾部插入节点
struct Node* insertAtEnd(struct Node* head, int data) {
    //先申请并开辟空间
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;

    if (head == NULL) {
        return newNode; // 如果链表为空，新节点成为链表头
    }

    struct Node* current = head;
    while (current->next != NULL) {
        current = current->next; // 移动到链表末尾
    }

    current->next = newNode;
    return head;
}

// 在链表头部插入节点
struct Node* insertAtBeginning(struct Node* head, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = head;
    return newNode; // 新节点成为链表头
}

// 删除节点
struct Node* deleteNode(struct Node* head, int data) {
    if (head == NULL) {
        return NULL; // 空链表，无需删除
    }
    //要删除的数据就是链表头节点
    if (head->data == data) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
        return head; // 删除链表头节点
    }
    //要删除的数据不是链表头节点 从链表头下一个结点开始寻找要删除的数据
    struct Node* current = head;
    while (current->next != NULL && current->next->data != data) {
        current = current->next;
    }
    //停止时存在条件1：没有找到要删除的 2：cur-next-data是要删除的数据
    if (current->next != NULL) {
        struct Node* temp = current->next; //temp就是要删除的数据
        current->next = current->next->next;
        free(temp); // 删除中间或末尾节点
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

// 打印链表
void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
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

    list = insertAtEnd(list, 10);
    list = insertAtEnd(list, 20);
    list = insertAtBeginning(list, 5);

    printf("Original List: ");
    printList(list);

    modifyNode(list, 20, 25);
    printf("Modified List: ");
    printList(list);

    list = deleteNode(list, 10);
    printf("List after deleting 10: ");
    printList(list);

    struct Node* foundNode = searchNode(list, 5);
    if (foundNode != NULL) {
        printf("Found node with data 5\n");
    } else {
        printf("Node with data 5 not found\n");
    }

    freeList(list); // 释放链表内存

    return 0;
}
