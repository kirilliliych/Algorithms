#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef int ht_val_t;
typedef int ht_key_t;

struct list
{
    struct list *next;
    ht_key_t key;
};

struct hash_table 
{
    size_t capacity;    
    size_t size;
    struct list **data;
};

const size_t HASH_TABLE_SIZE = (1 << 19) - 1;

 struct list *list_new(ht_key_t key);

 struct list *list_insert(struct list *head, ht_key_t key);

struct list *list_find(struct list *head, ht_key_t key);

struct list *list_delete(struct list *head);

struct list *delete_node(struct list *node);

 size_t hash_table_get_index(struct hash_table *ht, ht_key_t key);

 struct hash_table *hash_table_new(size_t capacity);

 void hash_table_insert(struct hash_table *ht, ht_key_t key);

 struct list *hash_table_find(struct hash_table *ht, ht_key_t key);

 struct hash_table *hash_table_delete(struct hash_table *ht);

 size_t HashFunc(ht_key_t key);



inline struct list *list_new(ht_key_t key)
{
    // assert(key != NULL);

    struct list *node = (struct list *) calloc(1, sizeof(struct list));

    node->key  = key;
    node->next = NULL;

    return node;
}

inline struct list *list_insert(struct list *head, ht_key_t key)
{
    // assert(key != NULL);

    if (head == NULL)
    {
        head = list_new(key);
        return head;    
    }

    struct list *temp = head;
    
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = list_new(key);

    return head;      
}

inline struct list *list_find(struct list *head, ht_key_t key)
{
    // assert(key != NULL);
    
    if (head == NULL)
    {
        return NULL;
    }   

    while (key != head->key)
    {
        if (head->next == NULL)
        {
            return NULL;
        }

        head = head->next;
    }

    return head;    
}

inline struct list *list_delete(struct list *head)
{
    while (head != NULL)
    {
        struct list *temp = head;
        head = head->next;
        temp = delete_node(temp);
    }

    return NULL;
}

inline size_t hash_table_get_index(struct hash_table *ht, ht_key_t key)
{
    // assert(ht  != NULL);
    // assert(key != NULL);

    return HashFunc(key) % ht->capacity;
}

inline struct hash_table *hash_table_new(size_t capacity)
{
    struct hash_table *new_ht = (struct hash_table *) calloc(1, sizeof(struct hash_table));
    // assert(new_ht != NULL);

    new_ht->data = (struct list **) calloc(capacity, sizeof(struct list *));
    // assert(new_ht->data != NULL);
    
    new_ht->capacity = capacity;
    
    return new_ht;
}

inline void hash_table_insert(struct hash_table *ht, ht_key_t key)
{
    // assert(ht    != NULL);
    // assert(key   != NULL);
    
    size_t index = hash_table_get_index(ht, key);
    
    ht->data[index] = list_insert(ht->data[index], key);
}

inline struct list *hash_table_find(struct hash_table *ht, ht_key_t key)
{
    // assert(ht  != NULL);
    // assert(key != NULL);
    
    size_t index = hash_table_get_index(ht, key);
    
    return list_find(ht->data[index], key);
}

inline struct hash_table *hash_table_delete(struct hash_table *ht)
{
    if (ht == NULL)
    {
        return NULL;    
    }

    for (size_t list_index = 0; list_index < ht->capacity; ++list_index)
    {
        ht->data[list_index] = list_delete(ht->data[list_index]);
    }
    free(ht->data);
    free(ht);

    return NULL;
}

inline size_t HashFunc(ht_key_t key)
{
    // assert(key != NULL);

    size_t key_value = key;
    //key_value = ((key_value >> 16) ^ key_value) * 0x45d9f3b;
    //key_value = ((key_value >> 16) ^ key_value) * 0x45d9f3b;

    return (key_value >> 16) ^ key_value;
}

inline struct list *delete_node(struct list *node)
{
    free(node);
    
    return NULL;
}

int main()
{
    int N = 0;
    int M = 0;
    scanf("%d %d", &N, &M);

    int **sets_array = (int **) calloc(N, sizeof(int *));
    for (int i = 0; i < N; ++i)
    {
        sets_array[i] = calloc(M, sizeof(int));
    }

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            scanf("%d", &sets_array[i][j]);
        }
    }

    int max_overlap_size = 0;

    for (int compared_set_index = 0; compared_set_index < N - 1; ++compared_set_index)                              // N - 1
    {
        struct hash_table *ht = hash_table_new(M * 20);

        for (int i = 0; i < M; ++i)                                                                                 // inserting compared_set
        {
            hash_table_insert(ht, sets_array[compared_set_index][i]);
        }

        for (int compare_with_index = compared_set_index + 1; compare_with_index < N; ++compare_with_index)
        {   
            int overlap_size = 0;

            for (int j = 0; j < M; ++j)                                                                             // searching 4 elements                                                              
            {
                struct list *searching_result = hash_table_find(ht, sets_array[compare_with_index][j]);

                if (searching_result != NULL)
                {
                    ++overlap_size;
                }
            }

            if (max_overlap_size < overlap_size)
            {
                max_overlap_size = overlap_size;
            }
        }

        ht = hash_table_delete(ht);
    }

    printf("%d", max_overlap_size);


    for (int i = 0; i < N; ++i)
    {
        free(sets_array[i]);
    }
    free(sets_array);

    return 0;
}   