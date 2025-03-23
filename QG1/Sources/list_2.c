#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100
typedef int ElemType;

typedef struct node{
    ElemType date;
    struct node *next;
}Node;
//初始化链表
Node *initList()
{
    Node *head = (Node*)malloc(sizeof(Node));
    head->date = 0;
    head->next = NULL;
    return head;
}
//头插法
int insertHead(Node *L, ElemType e)
{
    Node *p = (Node*)malloc(sizeof(Node));
    p->date = e;
    p->next = L->next;
    L->next = p;
    return 1;
}
//遍历
void listNode(Node *L)
{
    Node *p = L->next;
    while (p!=NULL)
    {
        printf("%d ", p->date);
        p = p->next;
    }
    printf("\n");
}
//获取尾结点
Node* get_tail(Node *L)
{
    Node *p = L;
    while(p->next != NULL)
    {
        p =  p->next;
    }
    return p;
}
//尾插法
Node* insertTail(Node *tail, ElemType e)
{
    Node *p = (Node*)malloc(sizeof(Node));
    p->date = e;
    tail->next = p;
    p->next = NULL;
    return p;
}
//指定位置插入
int insertNode(Node *L, int pos, ElemType  e)
{
    //用来保存插入位置的前驱节点
    Node *p = L;
    int i = 0;
    //遍历链表找到插入位置的前驱节点
    while(i < pos-1)
    {
        p = p->next;
        i++;
        if(p == NULL)
        {
            return 0;
        }
    }
    //要插入的新节点
    Node *q = (Node*)malloc(sizeof(Node));
    q->date = e;
    q->next = p->next;
    p->next = q;
    return 1;
}
//删除节点
int deleteNode(Node*L, int pos)
{
    //删除节点的前驱
    Node*p = L;
    int i = 0;
    //遍历链表找到要删除节点的前驱
    while(i < pos - 1)
    {
        p = p->next;
        i++;
        if(p == NULL)
        {
            return 0;
        }
    }
    if(p->next == NULL)
    {
        printf("要删除的位置错误\n");
        return 0;
    }
    //q指向要删除的节点
    Node *q = p->next;
    //让要删除节点的前驱指向要删除节点的后继
    p->next = q->next;
    //释放要删除节点的内存空间
    free(q);
    return 1;
}
//获取链表的长度
int listLength(Node *L)
{
    Node *P = L;
    int len = 0;
    while(P != NULL)
    {
        P = P->next;
        len++;
    }
    return len;
}
//释放链表
void freeList(Node *L)
{
    Node *p = L->next;
    Node *q;
    while (p != NULL)
    {
        q = p->next;
        free(p);
        p = q;
    }
    L->next = NULL;
}
//反转链表
Node *reverseList(Node *head)
{
    Node *first = NULL;
    Node *second = head->next;
    Node *third;
    while (second != NULL)
    {
        third = second->next;
        second->next = first;
        first = second;
        second = third;
    }
    Node *hd = initList();
    hd->next = first;

    return hd;
}
//删除链表中间节点
int delMiddleNode(Node *head)
{
    Node *fast = head->next->next;
    Node *slow = head;
    while(fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    Node *q = slow->next;
    slow->next = q->next;
    free(q);
    return 1;
}
//判断链表是否有环
int isCycle(Node *head)
{
    Node *fast = head;
    Node *slow = head;

    while(fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
        if(fast == slow)
        {
            return 1;
        }
    }

    return 0;
}
int main(int argc, char const *argv[])
{
    Node *list = initList();
    // // insertHead(list, 10);
    // // insertHead(list, 20);
    // // insertHead(list, 30);
    // // listNode(list);
    Node *tail = get_tail(list);
    // tail = insertTail(tail, 70);
    // tail = insertTail(tail, 80);
    // tail = insertTail(tail, 90);
    // listNode(list);
    // // insertNode(list, 2, 24);
    // // listNode(list);
    // // deleteNode(list,2);
    // // listNode(list);
    // // printf("%d\n", listLength(list));
    // // freeList(list);
    // // printf("%d\n", listLength(list));
    // Node *reverse = reverseList(list);
    // listNode(reverse);
    // delMiddleNode(reverse);
    // listNode(reverse);

    tail = insertTail(tail, 1);
    tail = insertTail(tail, 2);
    tail = insertTail(tail, 3);
    Node *three = tail;
    tail = insertTail(tail, 4);
    tail = insertTail(tail, 5);
    tail = insertTail(tail, 6);
    tail = insertTail(tail, 7);
    tail = insertTail(tail, 8);
    tail->next = three;
    if(isCycle(list))
    {
        printf("有环\n");
    }
    else
    {
        printf("无环\n");
    }
    return 0;
}