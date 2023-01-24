#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef long long ht_val_t;
typedef long long ht_key_t;

struct list
{
    struct list *next;
    ht_val_t value;
    ht_key_t key;
};

struct hash_table 
{
    size_t capacity;    
    size_t size;
    struct list **data;
};

const size_t HASH_TABLE_SIZE = (1 << 19) - 1;

struct list *list_new(ht_key_t *key, ht_val_t *value);

struct list *list_insert(struct list *head, ht_key_t *key, ht_val_t *value);

struct list *list_find(struct list *head, ht_key_t *key);

struct list *list_erase(struct list *head, ht_key_t *key);

struct list *list_delete(struct list *head);

struct list *delete_node(struct list **node);

void list_print(struct list const *head);

size_t hash_table_get_index(struct hash_table *ht, ht_key_t *key);

struct hash_table *hash_table_new(size_t capacity);

void hash_table_insert(struct hash_table *ht, ht_key_t *key, ht_val_t *value);

struct list *hash_table_find(struct hash_table *ht, ht_key_t *key);

void hash_table_delete(struct hash_table *ht, ht_key_t *key);

size_t hash_table_size(struct hash_table *ht);

struct hash_table *hash_table_destroy(struct hash_table *ht);

void hash_table_dump(struct hash_table *ht);

size_t HashFunc(ht_key_t *key);

long long Swap(struct hash_table *ht, long long *x, long long *y);


int main()
{       
    long long N = 0;
    scanf("%lld", &N);

    struct hash_table *ht = hash_table_new(HASH_TABLE_SIZE);

    long long x = 0;
    long long y = 0;
    for (size_t request_num = 0; request_num < N; ++request_num)
    {
        scanf("%lld %lld", &x, &y);
        printf("%lld\n", Swap(ht, &x, &y));
    }

    hash_table_destroy(ht);

    return 0;
}

long long Swap(struct hash_table *ht, long long *x, long long *y)
{
    assert(ht != NULL);
    assert(x  != NULL);
    assert(y  != NULL);

    struct list *x_node = hash_table_find(ht, x);
    if (x_node == NULL)
    {
        hash_table_insert(ht, x, x);
        x_node = hash_table_find(ht, x);
    }

    struct list *y_node = hash_table_find(ht, y);
    if (y_node == NULL)
    {
        hash_table_insert(ht, y, y);
        y_node = hash_table_find(ht, y);
    }
    
    long long temp_value = x_node->value;
    x_node->value = y_node->value;
    y_node->value = temp_value;

    return abs(x_node->value - y_node->value);
}


struct list *list_new(ht_key_t *key, ht_val_t *value)
{
    assert(key   != NULL);
    assert(value != NULL);

    struct list *node = (struct list *) calloc(1, sizeof(struct list));

    node->key   = *key;
    node->value = *value; 

    node->next = NULL;

    return node;
}

struct list *list_insert(struct list *head, ht_key_t *key, ht_val_t *value)
{
    assert(key   != NULL);
    assert(value != NULL);

    if (head == NULL)
    {
        head = list_new(key, value);
        return head;    
    }

    struct list *temp = head;
    
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = list_new(key, value);

    return head;      
}

struct list *list_find(struct list *head, ht_key_t *key)
{
    assert(key != NULL);
    
    if (head == NULL)
    {
        return NULL;
    }   

    
    while (*key != head->key)
    {
        if (head->next == NULL)
        {
            return NULL;
        }

        head = head->next;
    }

    return head;    
}

struct list *list_erase(struct list *head, ht_key_t *key)
{
    assert(key != NULL);

    if (head == NULL)
    {
        return NULL;
    }

    struct list *temp_prev = NULL;
    struct list *temp      = head;

    while (*key != temp->key)
    {
        if (temp->next == NULL)
        {
            return head;
        }

        temp_prev = temp;
        temp = temp->next;
    }
    
    if (temp == head)
    {   
        head = head->next;
        delete_node(&temp);
        
        return head;
    }
    
    if (temp->next == NULL)
    {
        temp_prev->next = NULL;
        delete_node(&temp);

        return head;
    }
    
    temp_prev->next = temp->next;
    delete_node(&temp);

    return head;
}

struct list *list_delete(struct list *head)
{
    while (head != NULL)
    {
        struct list *temp = head;
        head = head->next;
        delete_node(&temp);
    }

    return NULL;
}

void list_print(struct list const *head)
{
    printf("[");

    if (head != NULL)
    {
        struct list const *temp = head;

        while (temp->next != NULL)
        {
            printf("(%lld, %lld), ", temp->key, temp->value);
            temp = temp->next;
        }

        printf("(%lld, %lld)", temp->key, temp->value);
    }
    printf("]\n");
}

size_t hash_table_get_index(struct hash_table *ht, ht_key_t *key)
{
    assert(ht  != NULL);
    assert(key != NULL);

    return HashFunc(key) % ht->capacity;
}

struct hash_table *hash_table_new(size_t capacity)
{
    struct hash_table *new_ht = (struct hash_table *) calloc(1, sizeof(struct hash_table));
    assert(new_ht != NULL);

    new_ht->data = (struct list **) calloc(capacity, sizeof(struct list *));
    assert(new_ht->data != NULL);
    
    new_ht->capacity = capacity;
    
    return new_ht;
}

void hash_table_insert(struct hash_table *ht, ht_key_t *key, ht_val_t *value)
{
    assert(ht    != NULL);
    assert(key   != NULL);
    assert(value != NULL);
    
    size_t index = hash_table_get_index(ht, key);
    
    struct list *elem_place = list_find(ht->data[index], key);
    
    if (elem_place == NULL)
    { 
        ++ht->size;
        ht->data[index] = list_insert(ht->data[index], key, value);

        return;
    }
    
    elem_place->value = *value;
}

struct list *hash_table_find(struct hash_table *ht, ht_key_t *key)
{
    assert(ht  != NULL);
    assert(key != NULL);
    
    size_t index = hash_table_get_index(ht, key);
    
    return list_find(ht->data[index], key);
}

void hash_table_delete(struct hash_table *ht, ht_key_t *key)
{
    assert(ht  != NULL);
    assert(key != NULL);

    size_t index = hash_table_get_index(ht, key);

    struct list *place = list_find(ht->data[index], key);
    if (place == NULL)
    {
        return;
    }

    ht->data[index] = list_erase(ht->data[index], key);
    --ht->size;
}

size_t hash_table_size(struct hash_table *ht)
{
    assert(ht != NULL);

    return ht->size;
}

struct hash_table *hash_table_destroy(struct hash_table *ht)
{
    assert(ht != NULL);

    for (size_t list_index = 0; list_index < ht->capacity; ++list_index)
    {
        ht->data[list_index] = list_delete(ht->data[list_index]);
    }
    free(ht->data);
    free(ht);

    return NULL;
}

void hash_table_dump(struct hash_table *ht)
{
    assert(ht != NULL);

    printf("hash_table_mem_address: %p\n", ht);

    for (size_t list_index = 0; list_index < ht->capacity; ++list_index)
    {
        if (ht->data[list_index] != NULL)
        {
            printf("\tht->data[%lu]: ", list_index);    
            list_print(ht->data[list_index]);
        }
    }

    printf("\n");
}

size_t HashFunc(ht_key_t *key)
{
    assert(key != NULL);

    size_t key_value = *key;
    key_value = ((key_value >> 16) ^ key_value) * 0x45d9f3b;
    key_value = ((key_value >> 16) ^ key_value) * 0x45d9f3b;

    return (key_value >> 16)^ key_value;
}

struct list *delete_node(struct list **node)
{
    free(*node);
    *node = NULL;
    
    return NULL;
}