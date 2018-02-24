#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<queue>
#define  m  3   /// B���Ľף�����Ϊ4
using namespace std;
struct ddd
{
    int name;
    int tt;
};
typedef struct BTNode
{
    int keynum;                    /// ����йؼ��ָ����������Ĵ�С
    struct BTNode  *parent;        /// ָ�򸸽��
    int key[m + 1];                /// �ؼ���������0�ŵ�Ԫδ��
    struct BTNode  *ptr[m + 1];    /// ����ָ������
} BTNode, *BTree;

///*************************B��*********************************

void printt(BTree Q)///��������������     1
{
    if(!Q) printf("[ ]\n");
    else{
        printf("[ ");
        for(int i=1;i<=Q->keynum;i++){
            printf("%d ",Q->key[i]);
        }
        printf("] ");
    }
}
void ppp(BTree T)///���     1
{
    BTree Q;
    queue<BTree>Q1,Q2;
    while(!Q1.empty()) Q1.pop();
    while(!Q2.empty()) Q2.pop();
    Q1.push(T);
    while(Q1.front()||Q2.front()){
    while(!Q1.empty()){
        Q2.push(Q1.front());
        Q1.pop();
    }
    while(!Q2.empty()){
        Q=Q2.front();
        printt(Q);
        if(Q->ptr[0]){
        for(int i=0;i<=Q->keynum;i++){
            Q1.push(Q->ptr[i]);
            }
        }
        Q2.pop();
    }
    printf("\n");
    }
}
void initBtree(BTree &Q)///��ʼ�����    1
{
    Q->keynum=0;
    Q->parent=NULL;
    for(int i = 0;i <= m+1; i++){
        Q->key[i]=0;
        Q->ptr[i]=NULL;
    }
}
void findmax(BTree T, BTree &p, int &ans)///Ѱ�����ؼ��ֵĽ��,TΪҪѰ�ҵ�����pΪ���صĽڵ�,ansΪ�ڼ���   1
{
    if (T == NULL) return;
    p = T;
    while (p->ptr[p->keynum]){
        p = p->ptr[p->keynum];
    }
    ans = p->keynum;
}
bool findBTree(BTree T, BTree &p, int &ans, int k)///���ң�TΪҪѰ�ҵ�����pΪ���صĽڵ㣬ansΪ�ڼ���Ԫ�أ�kΪҪ�ҵ�ֵ  1
{
    BTree q;
    int i;
    int keynow;
    if (!T)
        return false;
    q = T;
    keynow = T->key[1];
    while (q){
        i = 1;
        keynow = q->key[i];
        while (i <= q->keynum){
            if (k == keynow){
                p = q;
                ans = i;
                return true;
            }
            if (keynow < k){
                if (i == q->keynum){
                    if (!q->ptr[i]){
                        p = q;
                        ans = q->keynum + 1;
                        return false;
                    }
                    q = q->ptr[i];
                    break;
                }
                i++;
                keynow = q->key[i];
                continue;
            }
            if (keynow > k){
                if (!q->ptr[i - 1]){
                    p = q;
                    ans = i;
                    return false;
                }
                q = q->ptr[i - 1];
                break;
            }
        }
    }

    return false;
}
void renewparent(BTree p)///�����ϸ��ڵ�      1
{
    if (!p) return;
    for (int i = 0;i <= p->keynum;i++){
        if (p->ptr[i] != NULL){
            p->ptr[i]->parent = p;
            renewparent(p->ptr[i]);
        }
    }
}
int whichson(BTree T)///�ҳ��Ǹ��׵ĵڼ�������   1
{
    if (T == NULL) return -1;
    for (int i = 0;i <= T->parent->keynum;i++){
        if (T->parent->ptr[i] == T) return i;
    }
    return -1;
}
bool splitBTree(BTree T) ///��ʱ���ѵĽڵ�һ�����ǳ������ֵ�ġ�   1
{
    BTree t1, t2;
    int i;
    if (T->parent == NULL){
        t1 = (BTree)malloc(sizeof(BTNode));
        initBtree(t1);
        t2 = (BTree)malloc(sizeof(BTNode));
        initBtree(t2);
        t1->keynum = m / 2;
        t2->keynum = m - (m / 2) - 1;
        t1->parent = T;
        t2->parent = T;
        for (i = 0;i <= m / 2; i++){  ///��ʼ��t1
            t1->ptr[i] = T->ptr[i];
            t1->key[i] = T->key[i];
        }
        t2->ptr[0] = T->ptr[(m / 2) + 1];
        for (i = (m / 2) + 2;i <= m; i++){  ///��ʼ��t2
            t2->ptr[i - ((m / 2) + 1)] = T->ptr[i];
            t2->key[i - ((m / 2) + 1)] = T->key[i];
        }
        T->keynum = 1;
        T->ptr[0] = t1;
        T->ptr[1] = t2;
        T->key[1] = T->key[m / 2 + 1];
        for (i = 2;i <= m; i++){  ///��ʼ��T
            T->ptr[i] = NULL;
            T->key[i] = 0;
        }
        return true;
    }
    i = whichson(T);
    for (int j = T->parent->keynum;j > i; j--){   ///�ڳ����׵�λ��
        T->parent->ptr[j + 1] = T->parent->ptr[j];
        T->parent->key[j + 1] = T->parent->key[j];
    }
    T->parent->keynum++;
    T->parent->key[i + 1] = T->key[m / 2 + 1];
    t2 = T->parent->ptr[i + 1] = (BTree)malloc(sizeof(BTNode));
    initBtree(t2);
    t2->keynum = m - (m / 2) - 1;
    t2->parent = T->parent;
    t2->ptr[0] = T->ptr[(m / 2) + 1];
    for (i = (m / 2) + 2;i <= m; i++){  ///��ʼ��t2
        t2->ptr[i - ((m / 2) + 1)] = T->ptr[i];
        t2->key[i - ((m / 2) + 1)] = T->key[i];
    }
    T->keynum = m / 2;
    for (i = (m / 2) + 1;i <= m; i++){  ///��ʼ��T
        T->ptr[i] = NULL;
        T->key[i] = 0;
    }
    if (T->parent->keynum == m){
        splitBTree(T->parent);
    }
    return true;
}
bool insertBTree(BTree &T,int key)///����Ԫ��      1
{
    BTree p;
    int temp;
    if (!T){
        T = (BTree)malloc(sizeof(BTNode));
        initBtree(T);
        T->keynum = 1;
        T->key[1] = key;
        return true;
    }
    if (findBTree(T, p, temp, key)) return false;
    else{    ///����������ֱ�Ӳ���
        p->keynum++;
        for (int i = p->keynum;i > temp; i--){
            p->key[i] = p->key[i - 1];
            p->ptr[i] = p->ptr[i - 1];
        }
        p->key[temp] = key;
        if (p->keynum == m){      ///����
            splitBTree(p);
        }
        renewparent(T);
        return true;
    }
}
bool borrowbnode(BTree T)///���ֵܽڵ��Ԫ��  1
{
    int mynum, bronum;
    BTree b = NULL, f = NULL;
    f = T->parent;
    if (!f){ ///���׽�㲻����
        if (T->keynum == 0){
            f = T->ptr[0];
            if (!f){
                free(T);
                return false;
            }
            for (int i = 0;i <= f->keynum;i++){
                T->key[i] = f->key[i];
                T->ptr[i] = f->ptr[i];
            }
            T->keynum = f->keynum;
            free(f);
            renewparent(T);
        }
        return true;
    }
    mynum = whichson(T);
    if (mynum == 0)
        bronum = 1;
    else
        bronum = mynum - 1;
    b = f->ptr[bronum];
    if (b->keynum == (m + 1) / 2 - 1){ ///����ֵܲ����裬�ϲ�
        if (bronum < mynum){                    ///����Ҳ��ǵ�һ��
            b->keynum++;
            b->key[b->keynum] = f->key[mynum];
            b->ptr[b->keynum] = T->ptr[0];
            for (int i = 1;i <= T->keynum;i++){
                b->key[i + b->keynum] = T->key[i];
                b->ptr[i + b->keynum] = T->ptr[i];
                b->keynum++;
            }
            free(T);
            for (int i = mynum;i <= f->keynum;i++){
                f->key[i] = f->key[i + 1];
                f->ptr[i] = f->ptr[i + 1];
            }
            f->keynum--;
        }
        else{
            T->keynum++;
            T->key[T->keynum] = f->key[bronum];
            T->ptr[T->keynum] = b->ptr[0];
            for (int i = 1;i <= b->keynum;i++){
                T->key[i + T->keynum] = b->key[i];
                T->ptr[i + T->keynum] = b->ptr[i];
                T->keynum++;
            }
            free(b);
            for (int i = bronum;i <= f->keynum;i++){
                f->key[i] = f->key[i + 1];
                f->ptr[i] = f->ptr[i + 1];
            }
            f->keynum--;
        }
        renewparent(f);
        if (f->keynum == (m + 1) / 2 - 2){///���ý��ֵܵĺ���
            return borrowbnode(f);
        }
    }
    else{///����ֵ��ܹ�����
        if (mynum > 0){                    ///����Ҳ��ǵ�һ��
            for (int i = 1;i <= T->keynum;i++){
                T->key[i + 1] = T->key[i];
                T->ptr[i + 1] = T->ptr[i];
            }
            T->ptr[1] = T->ptr[0];
            T->key[1] = f->key[mynum];
            T->ptr[0] = b->ptr[b->keynum];
            T->keynum++;
            f->key[mynum] = b->key[b->keynum];
            b->key[b->keynum] = 0;
            b->ptr[b->keynum] = NULL;
            b->keynum--;
        }
        else{                                    ///������ǵ�һ��
            T->keynum++;
            T->key[T->keynum] = f->key[1];
            T->ptr[T->keynum] = b->ptr[0];
            f->key[1] = b->key[1];
            b->ptr[0] = b->ptr[1];
            for (int i = 1;i <= b->keynum;i++){
                b->key[i] = b->key[i + 1];
                b->ptr[i] = b->ptr[i + 1];
            }
            b->keynum--;
        }
    }
    return true;
}
void deletebtreerecord(BTree &T, int key)///ɾ��Ԫ��   1
{
    BTree p, q;
    int num, temp;
    if (!findBTree(T, p, temp, key)) return;
    else{
        if (!p->ptr[temp]){                ///�����Ҷ�ӽڵ�Ļ�
            for (int i = temp;i <= p->keynum; i++){
                p->key[i] = p->key[i + 1];
                p->ptr[i] = p->ptr[i + 1];
            }
            p->keynum--;
            if (p->keynum == (m + 1) / 2 - 2){ ///���ý��ֵܵĺ���
                if (!borrowbnode(p)) T = NULL;
                else renewparent(T);
            }
            return;
        }
        else{                                    ///����Ҷ�ӽ��Ļ�����
            findmax(p->ptr[temp - 1], q, num);   ///���ص�qһ������Ҷ�ӽڵ�
            p->key[temp] = q->key[num];
            q->key[num] = 0;
            q->keynum--;
            if (q->keynum == (m + 1) / 2 - 2){///���ý��ֵܵĺ���
                if (!borrowbnode(q)) T = NULL;
                else renewparent(T);
            }
        }
    }
}
int  main()
{
    int i,n;
    int arr[50];
    BTree a=NULL;
    int key=0;
    printf("B���Ľ�Ϊ:%d,������������:",m+1);
    scanf("%d",&n);
    printf("���������ݣ����ظ���:\n");
    for (i = 0;i < n;i++){
        printf("��%d�β���:",i+1);
        scanf("%d", &key);
        arr[i] = key;
        if (!insertBTree(a, key)){
            printf("Ԫ���ظ��������²���:\n");
            i--;
            continue;
        }
        ppp(a);
    }
    for (i = 0;i < n;i++){
        key = arr[i];
        deletebtreerecord(a,key);
        printf("��%d��ɾ��:%d\n", i + 1, key);
        ppp(a);
    }
    return 0;
}
