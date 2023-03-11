#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */


/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *new = malloc(sizeof(struct list_head));
    if (!new) {
        return NULL;  // malloc fail
    }
    INIT_LIST_HEAD(new);
    return new;
}

/* Free all storage used by queue */
void q_free(struct list_head *l)
{
    if (l == NULL) {
        return;
    }
    struct list_head *tmp = l->next;
    while (tmp != l) {
        element_t *del = container_of(tmp, element_t, list);
        tmp = tmp->next;
        free(del->value);
        free(del);
    }
    free(tmp);
}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    if (head == NULL)
        return false;
    element_t *new = malloc(sizeof(element_t));
    if (new == NULL)
        return false;
    int char_size = strlen(s);
    new->value = malloc(char_size + 1);
    if (new->value == NULL) {
        free(new);
        return false;
    }
    memcpy(new->value, s, char_size);  // memcpy(dst, src, size)
    new->value[char_size] = '\0';
    list_add(&new->list, head);
    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    if (head == NULL) {
        return false;
    }
    element_t *new = malloc(sizeof(element_t));
    if (new == NULL) {
        return false;
    }
    int char_size = strlen(s);
    new->value = malloc(char_size + 1);
    if (new->value == NULL) {
        free(new);
        return false;
    }
    memcpy(new->value, s, char_size);  // memcpy(dst, src, size)
    new->value[char_size] = '\0';
    list_add_tail(&new->list, head);
    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (head == NULL || list_empty(head)) {
        return NULL;
    }
    element_t *rm_head =
        list_first_entry(head, element_t, list);  // for head entry
    if (rm_head == NULL) {
        return NULL;
    }
    list_del(&rm_head->list);
    if (sp) {
        memcpy(sp, rm_head->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }
    return rm_head;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (head == NULL || list_empty(head)) {
        return NULL;
    }
    element_t *rm_tail = list_last_entry(head, element_t, list);
    if (rm_tail == NULL) {
        return NULL;
    }
    list_del(&rm_tail->list);
    if (sp) {
        memcpy(sp, rm_tail->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }
    return rm_tail;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head)
        return 0;

    int len = 0;
    struct list_head *li;

    list_for_each (li, head)
        len++;
    return len;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    if (head == NULL || list_empty(head)) {
        return false;
    }
    struct list_head *slow_ptr = head;
    struct list_head *fast_ptr = head;
    do {
        slow_ptr = slow_ptr->next;
        fast_ptr = fast_ptr->next->next;
    } while (fast_ptr->next != NULL && fast_ptr != head);
    element_t *mid_node = list_entry(slow_ptr, element_t, list);
    list_del(slow_ptr);
    free(mid_node->value);
    free(mid_node);
    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head)
{
    if (head == NULL || list_empty(head)) {
        return;
    }
    struct list_head *cur = head;
    struct list_head *tmp;
    do {
        tmp = cur->prev;
        cur->prev = cur->next;
        cur->next = tmp;
        cur = cur->prev;
    } while (cur != head);
}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending order */
void q_sort(struct list_head *head) {}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending order */
int q_merge(struct list_head *head)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
