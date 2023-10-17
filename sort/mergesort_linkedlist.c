#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* merge(struct ListNode* l1, struct ListNode* l2) {
    if (!l1) return l2;
    if (!l2) return l1;

    struct ListNode dummy;
    struct ListNode* tail = &dummy;
    dummy.next = NULL;

    while (l1 && l2) {
        if (l1->val < l2->val) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }

    if (l1) tail->next = l1;
    if (l2) tail->next = l2;

    return dummy.next;
}

struct ListNode* findMiddle(struct ListNode* head) {
    if (!head) return NULL;

    struct ListNode* slow = head;
    struct ListNode* fast = head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

struct ListNode* mergeSort(struct ListNode* head) {
    if (!head || !head->next) return head;

    struct ListNode* middle = findMiddle(head);
    struct ListNode* secondHalf = middle->next;
    middle->next = NULL;

    struct ListNode* left = mergeSort(head);
    struct ListNode* right = mergeSort(secondHalf);

    return merge(left, right);
}

void printList(struct ListNode* head) {
    struct ListNode* current = head;
    while (current != NULL) {
        printf("%d ", current->val);
        current = current->next;
    }
    printf("\n");
}

void insert(struct ListNode** head, int val) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->val = val;
    newNode->next = *head;
    *head = newNode;
}

int main() {
    struct ListNode* head = NULL;
    int n, val;

    printf("输入链表元素的数量: ");
    scanf("%d", &n);

    printf("请开始输入链表元素：\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        insert(&head, val);
    }

    printf("Original list:\n");
    printList(head);

    struct ListNode* sortedList = mergeSort(head);

    printf("Sorted list:\n");
    printList(sortedList);

    return 0;
}
