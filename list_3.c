#include <stdio.h>
#include <stdlib.h>

// 定义双向链表节点结构
typedef struct Node {
    int data;  // 节点存储的数据
    struct Node* prev;  // 指向前一个节点的指针
    struct Node* next;  // 指向后一个节点的指针
} Node;

// 创建新节点
Node* createNode(int data) {
    // 为新节点分配内存
    Node* newNode = (Node*)malloc(sizeof(Node));
    // 检查内存分配是否成功
    if (newNode == NULL) {
        printf("内存分配失败\n");
        return NULL;
    }
    // 初始化新节点的数据
    newNode->data = data;
    // 初始化新节点的前一个节点指针为 NULL
    newNode->prev = NULL;
    // 初始化新节点的后一个节点指针为 NULL
    newNode->next = NULL;
    return newNode;
}

// 在链表头部插入节点
void insertAtHead(Node** head, int data) {
    // 创建新节点
    Node* newNode = createNode(data);
    // 如果链表为空，将新节点作为头节点
    if (*head == NULL) {
        *head = newNode;
    } else {
        // 新节点的 next 指针指向原头节点
        newNode->next = *head;
        // 原头节点的 prev 指针指向新节点
        (*head)->prev = newNode;
        // 更新头节点为新节点
        *head = newNode;
    }
}

// 在链表尾部插入节点
void insertAtTail(Node** head, int data) {
    // 创建新节点
    Node* newNode = createNode(data);
    // 如果链表为空，将新节点作为头节点
    if (*head == NULL) {
        *head = newNode;
    } else {
        // 临时指针用于遍历链表
        Node* temp = *head;
        // 遍历到链表的最后一个节点
        while (temp->next != NULL) {
            temp = temp->next;
        }
        // 最后一个节点的 next 指针指向新节点
        temp->next = newNode;
        // 新节点的 prev 指针指向最后一个节点
        newNode->prev = temp;
    }
}

// 删除指定值的节点
void deleteNode(Node** head, int data) {
    // 如果链表为空，直接返回
    if (*head == NULL) return;
    // 临时指针指向头节点
    Node* temp = *head;
    // 如果头节点就是要删除的节点
    if (temp->data == data) {
        // 更新头节点为原头节点的下一个节点
        *head = temp->next;
        // 如果新的头节点不为空，将其 prev 指针置为 NULL
        if (*head != NULL) {
            (*head)->prev = NULL;
        }
        // 释放原头节点的内存
        free(temp);
        return;
    }
    // 遍历链表，查找要删除的节点
    while (temp != NULL && temp->data != data) {
        temp = temp->next;
    }
    // 如果未找到要删除的节点，直接返回
    if (temp == NULL) return;
    // 如果要删除的节点不是最后一个节点
    if (temp->next != NULL) {
        // 将下一个节点的 prev 指针指向要删除节点的前一个节点
        temp->next->prev = temp->prev;
    }
    // 如果要删除的节点不是第一个节点
    if (temp->prev != NULL) {
        // 将前一个节点的 next 指针指向要删除节点的下一个节点
        temp->prev->next = temp->next;
    }
    // 释放要删除节点的内存
    free(temp);
}

// 打印链表
void printList(Node* head) {
    // 临时指针指向头节点
    Node* temp = head;
    // 遍历链表并打印每个节点的数据
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// 释放链表内存
void freeList(Node* head) {
    Node* temp;
    // 遍历链表，逐个释放节点的内存
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    // 初始化链表头节点为 NULL
    Node* head = NULL;

    // 在链表头部插入节点 1
    insertAtHead(&head, 10);
    // 在链表尾部插入节点 2
    insertAtTail(&head, 20);
    // 在链表尾部插入节点 3
    insertAtTail(&head, 30);

    // 打印链表内容
    printf("链表内容: ");
    printList(head);

    // 删除节点 2
    deleteNode(&head, 20);
    // 打印删除节点 2 后的链表内容
    printf("删除节点 2 后链表内容: ");
    printList(head);

    // 释放链表内存
    freeList(head);
    return 0;
}      