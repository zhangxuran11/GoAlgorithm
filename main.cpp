#include <iostream>
#include <map>
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
//递归实现
ListNode* rotateRight_recursive(ListNode* head, int k) {
    ListNode* head_new = head;
    ListNode* tail_new = head;
    if(tail_new->next != nullptr && k > 0){
        while(tail_new->next->next)
            tail_new = tail_new->next;
        head_new = tail_new->next;
        head_new->next = head;
        tail_new->next = nullptr;
        head_new = rotateRight_recursive(head_new,k-1);
    }
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
    int left = 0,right = 0;
    const  char* dst = "",*dst_end = "";
    int match = 0;
    int needs['z'-'A'] = {0};
    int count['z'-'A'] = {0};
    int match_num = 0;
    const char* p = T;

    for(int i =0;i < strlen(T);i++){
        if(++needs[T[i]-'A'] == 1)
            match_num++;
    }

    while(S[right] != '\0'){
        count[S[right] - 'A']++;
        if(count[S[right] - 'A'] == needs[S[right] - 'A'])
            match++;
        right++;
        while(match == match_num){
            if(strcmp(dst,"") == 0 || right-left < dst_end-dst){
                dst = S+left;
                dst_end = S+right;
            }
            if(--count[S[left]-'A'] < needs[S[left]-'A'])
                match--;
            left++;
        }
    }
    return strndup(dst,dst_end-dst);
}
//c++
const char* minWindow_cpp(const char* S,const char* T){
    int left = 0,right = 0;
    const  char* dst = "",*dst_end = "";
    int match = 0;
    std::map<char,int> needs;
    std::map<char,int> count;
    int needs_num = 0;
    const char* p = T;

    for(int i =0;i < strlen(T);i++)
        needs[T[i]]++;

    while(S[right] != '\0'){
        if(needs.count(S[right]) == 1){
            count[S[right]]++;
            if(count[S[right]] == needs[S[right]])
                match++;
        }
        right++;
        while(match == needs.size()){
            if(strcmp(dst,"") == 0 || right-left < dst_end-dst){
                dst = S+left;
                dst_end = S+right;
            }
            if(needs.count(S[left]) == 1){
                if(--count[S[left]] < needs[S[left]])
                    match--;
            }
            left++;
        }
    }
    return strndup(dst,dst_end-dst);
}
int main(){
    ListNode* head = new ListNode(1);
    ListAppend(head,2);
    ListAppend(head,3);
    ListAppend(head,4);
    ListAppend(head,5);
    ListPrint(head);
    head = rotateRight_recursive(head,2);
    ListPrint(head);

    std::cout<<minWindow_cpp("ADOBECODEBANC",  "ABC")<<std::endl;
    return 0;
}