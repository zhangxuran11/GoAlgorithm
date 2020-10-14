#include <iostream>
#include <string.h>
struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(nullptr) {}
 };
 void ListAppend(ListNode* head,int d){
     while(head->next) head = head->next;
     head->next = new ListNode(d);
 }
 void ListPrint(ListNode* head){
     while(head){
        std::cout<<head->val<<" ";
        head = head->next;
     }
     std::cout<<std::endl;
     
 }
/**************************
 * 旋转列表
输入: 1->2->3->4->5->NULL, k = 2
输出: 4->5->1->2->3->NULL
***************************/
ListNode* rotateRight(ListNode* head, int k) {
    ListNode* tmp = head;
    int len = 0;
    while(tmp) {
        tmp = tmp->next;
        len++;
    }
    k %= len;
    int pos = len-k-1;

    tmp = head;
    while( pos > 0 ){
        tmp = tmp->next;
        pos--;
    }
    ListNode* head_new = tmp->next; 
    tmp->next = nullptr;
    tmp = head_new;
    while( tmp->next  ){tmp = tmp->next;}
    tmp->next = head;
    return head_new;
}
/************************
给你一个字符串 S、一个字符串 T 。请你设计一种算法，可以在 O(n) 的时间复杂度内，从字符串 S 里面找出：包含 T 所有字符的最小子串。
示例：
输入：S = "ADOBECODEBANC", T = "ABC"
输出："BANC"

提示：
如果 S 中不存这样的子串，则返回空字符串 ""。
如果 S 中存在这样的子串，我们保证它是唯一的答案。
 * *********************/
const char* minWindow(const char* S,const char* T){
    const char *left = S,*right = S;
    const  char* dst = "",*dst_end = "";
    int match = 0;
    int needs['z'-'A'] = {0};
    int count['z'-'A'] = {0};
    int needs_num = 0;
    const char* p = T;

    while(*p != '\0')
    {
        if(++needs[*p - 'A'] == 1)
            needs_num++;
        p++;
    }

    while(*right != '\0'){
        count[*right - 'A']++;
        if(count[*right - 'A'] == needs[*right - 'A'])
            match++;
        right++;
        while(match == needs_num){
            if(strcmp(dst,"") == 0 || right-left < dst_end-dst){
                dst = left;
                dst_end = right;
            }
            if(--count[*left-'A'] < needs[*left-'A'])
                match--;
            left++;
        }
    }
    char* dst_new = (char*)malloc(dst_end-dst+1);
    strncpy(dst_new,dst,dst_end-dst);
    return dst_new;
}
int main(){
    ListNode* head = new ListNode(1);
    ListAppend(head,2);
    ListAppend(head,3);
    ListAppend(head,4);
    ListAppend(head,5);
    ListPrint(head);
    head = rotateRight(head,2);
    ListPrint(head);

    std::cout<<minWindow("ADOBECODEBANC",  "ABC")<<std::endl;
    return 0;
}