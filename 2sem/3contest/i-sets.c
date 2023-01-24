#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define aboba printf("aboba %d\n", __LINE__);

typedef long long avl_key_t;
//typedef char avl_val_t;

struct elem
{
    avl_key_t key;
};

struct node
{
    struct node *left;
    struct node *right;
    int height;
    struct elem content;
};

int avl_get_height(struct node *cur_node);

struct node *avl_get_min(struct node *cur_node);

struct node *avl_remove_old_min(struct node *cur_node);

int avl_calc_balance(struct node *cur_node);

void avl_renew_height(struct node *cur_node);

struct node *avl_rotate_left(struct node *cur_node);

struct node *avl_rotate_right(struct node *cur_node);

struct node *avl_balance(struct node *cur_node);

struct node *avl_insert(struct node *cur_node, struct elem *content);

struct node *avl_find(struct node *cur_node, struct elem *content);

struct node *avl_erase(struct node *cur_node, struct elem *content);

struct node *avl_delete(struct node *cur_node);

void avl_dump(struct node *cur_node);


int avl_get_height(struct node *cur_node)
{
    if (cur_node == NULL)
    {
        return 0;
    }
    
    return cur_node->height;
}

struct node *avl_get_min(struct node *cur_node)
{
    assert(cur_node != NULL);

    if (cur_node->left == NULL)
    {
        return cur_node;
    }
    else
    {
        return avl_get_min(cur_node->left);
    }
}

struct node *avl_remove_old_min(struct node *cur_node)
{
    assert(cur_node != NULL);

    if (cur_node->left == NULL)
    {
        return cur_node->right;
    }

    cur_node->left = avl_remove_old_min(cur_node->left);

    return avl_balance(cur_node);
}

int avl_calc_balance(struct node *cur_node)
{
    assert(cur_node != NULL);

    return avl_get_height(cur_node->right) - avl_get_height(cur_node->left);
}

void avl_renew_height(struct node *cur_node)
{
    assert(cur_node != NULL);

    int left_height  = avl_get_height(cur_node->left);
    int right_height = avl_get_height(cur_node->right);

    cur_node->height = (left_height > right_height ? left_height : right_height) + 1;
}

struct node *avl_rotate_left(struct node *cur_node)
{
    assert(cur_node != NULL);

    struct node *head = cur_node->right;
    cur_node->right   = head->left;
    head->left        = cur_node;

    avl_renew_height(cur_node);
    avl_renew_height(head);

    return head;
}

struct node *avl_rotate_right(struct node *cur_node)
{
    assert(cur_node != NULL);

    struct node *head = cur_node->left;
    cur_node->left    = head->right;
    head->right       = cur_node;

    avl_renew_height(cur_node);
    avl_renew_height(head);

    return head;
}

struct node *avl_balance(struct node *cur_node)
{
    avl_renew_height(cur_node);
    
    if (avl_calc_balance(cur_node) == 2)
    {
        if (avl_calc_balance(cur_node->right) < 0)
        {
            cur_node->right = avl_rotate_right(cur_node->right);
        }
        
        return avl_rotate_left(cur_node);
    }
    else if (avl_calc_balance(cur_node) == -2)
    { 
        if (avl_calc_balance(cur_node->left) > 0)
        {
            cur_node->left = avl_rotate_left(cur_node->left);
        }

        return avl_rotate_right(cur_node);
    }

    return cur_node;
}

struct node *avl_new_node(struct elem *content)
{
    assert(content != NULL);

    struct node *new_node = (struct node *) calloc(1, sizeof(struct node));

    new_node->content = *content;
    new_node->height = 1;

    return new_node;
};

struct node *avl_insert(struct node *cur_node, struct elem *content)
{
    assert(content != NULL);

    if (cur_node == NULL)
    {   
        cur_node = avl_new_node(content);

        return cur_node;
    }
    
    long long cmp = content->key - cur_node->content.key;
    if (cmp > 0)
    {
        cur_node->right = avl_insert(cur_node->right, content);
    }
    else if (cmp < 0)
    {
        cur_node->left  = avl_insert(cur_node->left,  content);
    }

    return avl_balance(cur_node);
}

struct node *avl_find(struct node *cur_node, struct elem *content)
{
    assert(content != NULL);

    if (cur_node == NULL)
    {
        return NULL;
    }

    long long cmp = content->key - cur_node->content.key;
    if (cmp > 0)
    {
        return avl_find(cur_node->right, content);
    }                          
    else if (cmp < 0)
    {
        return avl_find(cur_node->left,  content);
    }
    else
    {
        return cur_node;
    }
}    

struct node *avl_erase(struct node *cur_node, struct elem *content)
{
    assert(content != NULL);

    if (cur_node == NULL)
    {
        return NULL;
    }

    long long cmp = content->key - cur_node->content.key;
    if (cmp > 0)
    {
        cur_node->right = avl_erase(cur_node->right, content);
    }
    else if (cmp < 0)
    {
        cur_node->left  = avl_erase(cur_node->left,  content);
    }
    else
    {   
        if (cur_node->right == NULL)
        {
            struct node *left_son = cur_node->left;
            free(cur_node);

            return left_son;
        }

        struct node *left_of_erased  = cur_node->left;
        struct node *right_of_erased = cur_node->right;   
        free(cur_node);

        struct node *right_min = avl_get_min(right_of_erased);
        right_min->right = avl_remove_old_min(right_of_erased);
        right_min->left  = left_of_erased;

        return avl_balance(right_min);
    }

    return avl_balance(cur_node);
}

struct node *avl_delete(struct node *cur_node)
{
    if (cur_node == NULL)
    {
        return NULL;
    }

    cur_node->left  = avl_delete(cur_node->left);
    cur_node->right = avl_delete(cur_node->right);
    free(cur_node);

    return NULL;
}

void avl_dump(struct node *cur_node)
{
    assert(cur_node != NULL);
    
    //printf("key: %s\nval: %s\n\n", (avl_key_t *) cur_node->content.key, (avl_val_t *) cur_node->content.val);

    if (cur_node->left  != NULL)
    {
        avl_dump(cur_node->left);
    }
    
    if (cur_node->right != NULL)
    {
        avl_dump(cur_node->right);
    }
}

void avl_print(struct node *cur_node)
{
    if (cur_node == NULL)
    {
        return;
    }

    avl_print(cur_node->left);
    printf("%lld ", cur_node->content.key);
    avl_print(cur_node->right);
}


int main()
{
    long long N = 0;
    long long M = 0;
    scanf("%lld %lld", &N, &M);

    struct node **avl_array = (struct node **) calloc(N + 1, sizeof(struct node *));
    
    struct elem content = {};
    long long tree_index = 0;
    char lexem[3] = {};
    for (long long i = 0; i < M; ++i)
    {
        scanf("%3s", lexem);

        if (strcmp(lexem, "+") == 0)
        {
            scanf("%lld %lld", &content.key, &tree_index);
            avl_array[tree_index] = avl_insert(avl_array[tree_index], &content);
        }
        else if (strcmp(lexem, "-") == 0)
        {
            scanf("%lld %lld", &content.key, &tree_index);
            avl_array[tree_index] = avl_erase(avl_array[tree_index], &content);
        }
        else if (strcmp(lexem, "=") == 0)
        {
            scanf("%lld", &tree_index);
            avl_array[tree_index] = avl_delete(avl_array[tree_index]);
        }
        else if (strcmp(lexem, "?") == 0)
        {
            scanf("%lld", &tree_index);
            if (avl_array[tree_index] == NULL)
            {
                printf("-1");
            }
            else
            {
                avl_print(avl_array[tree_index]);
            }

            printf("\n");
        }
        else if (strcmp(lexem, "??") == 0)
        {
            scanf("%lld", &content.key);
            
            int is_absent = 1;
            for (long long j = 0; j < N + 1; ++j)
            {
                struct node *result = avl_find(avl_array[j], &content);
                if (result != NULL)
                {
                    printf("%lld ", j);
                    is_absent = 0;
                }
            }

            if (is_absent == 1)
            {
                printf("-1");
            }
            printf("\n");
        }
    }

    for (long long i = 0; i < N + 1; ++i)
    {
        avl_array[i] = avl_delete(avl_array[i]);
    }

    free(avl_array);

    return 0;
}