#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define aboba printf("aboba %d\n", __LINE__);

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

size_t Crc32Hash(const unsigned char *key, size_t bytes_to_hash);

int Comparator(const void *val1, const void *val2);

int main()
{       
    long long N = 0;
    long long M = 0;
    long long K = 0;
    scanf("%lld %lld %lld", &N, &M, &K);

    struct hash_table *ht = hash_table_new(HASH_TABLE_SIZE);

    int *set = (int *) calloc(M, sizeof(int));
    for (long long i = 0; i < N; ++i)
    {
        for (long long j = 0; j < M; ++j)
        {
            scanf("%d", &set[j]);
        }

        qsort(set, M, sizeof(int), Comparator);
        size_t hash = Crc32Hash((const unsigned char *) set, M * sizeof(int));
        hash_table_insert(ht, (ht_key_t *) &hash, &i);
    }

    for (long long i = 0; i < K; ++i)
    {
        for (long long j = 0; j < M; ++j)
        {
            scanf("%d", &set[j]);
        }

        qsort(set, M, sizeof(int), Comparator);
        size_t hash = Crc32Hash((const unsigned char *) set, M * sizeof(int));
        struct list *result = hash_table_find(ht, (ht_key_t *) &hash);
        if (result == NULL)
        {
            printf("0\n");
        }
        else
        {
            printf("1\n");
        }
    }

    free(set);
    ht = hash_table_destroy(ht);

    return 0;
}

int Comparator(const void *val1, const void *val2)
{
    assert(val1 != NULL);
    assert(val2 != NULL);

    return *((int *) val1) - *((int *) val2);
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

    return Crc32Hash((const unsigned char *) key, sizeof(ht_key_t)) % ht->capacity;
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


struct list *delete_node(struct list **node)
{
    free(*node);
    *node = NULL;
    
    return NULL;
}

size_t Crc32Hash(const unsigned char *key, size_t bytes_to_hash)
{
    assert(key != NULL);

    const size_t polynom = 0x04C11DB7;
    const size_t old_bit_checker = 1 << 26;

    size_t hash = 0;

    while (bytes_to_hash > 0)
    {
        for (int bit = 7; bit >= 0; --bit)                              // 8 bits in one byte
        {
            hash = (hash << 1) + ((*key >> bit) & 1);

            if (hash & old_bit_checker)
            {
                hash ^= polynom;
            }
        }
        ++key;
        --bytes_to_hash;
    }
    return hash;
}