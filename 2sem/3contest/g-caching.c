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

struct list *delete_node(struct list *node);

void list_print(struct list const *head);

size_t hash_table_get_index(struct hash_table *ht, ht_key_t *key);

struct hash_table *hash_table_new(size_t capacity);

void hash_table_insert(struct hash_table *ht, ht_key_t *key, ht_val_t *value);

struct list *hash_table_find(struct hash_table *ht, ht_key_t *key);

void hash_table_erase(struct hash_table *ht, ht_key_t *key);

size_t hash_table_size(struct hash_table *ht);

struct hash_table *hash_table_destroy(struct hash_table *ht);

void hash_table_dump(struct hash_table *ht);

size_t HashFunc(ht_key_t *key);

long long CountLongRequests(long long *requests, struct hash_table *ht_requests,
                            long long cache_capacity, long long requests_quantity);

long long GetCacheLowestPriority(long long *requests, long long *cache, struct hash_table *ht_requests,
                                 long long cache_capacity, long long cur_request_number);


int main()
{       
    long long N = 0;
    long long M = 0;
    scanf("%lld %lld", &N, &M);
    
    long long *requests = (long long *) calloc(M, sizeof(long long));
    struct hash_table *ht = hash_table_new(HASH_TABLE_SIZE);
    
    for (long long i = 0; i < M; ++i)
    {
        scanf("%lld", &requests[i]);
        hash_table_insert(ht, &requests[i], &i);
    }

    printf("\n%lld", CountLongRequests(requests, ht, N, M));

    ht = hash_table_destroy(ht);
    free(requests);

    return 0;
}


long long CountLongRequests(long long *requests, struct hash_table *ht_requests, 
                            long long cache_capacity, long long requests_quantity)
{
    assert(requests != NULL);
    
    long long long_requests_quantity = 0;
    long long *cache = (long long *) calloc(cache_capacity, sizeof(long long));
    struct hash_table *ht_cache = hash_table_new(HASH_TABLE_SIZE);

    for (long long i = 0; i < requests_quantity; ++i)
    {
        struct list *searching_in_cache = hash_table_find(ht_cache, &requests[i]);
        if (searching_in_cache == NULL)
        {
            long long fictive_value = 1;

            size_t cache_size = hash_table_size(ht_cache);
            
            if (cache_size < cache_capacity)
            {
                cache[cache_size] = requests[i];

                hash_table_insert(ht_cache, &requests[i], &fictive_value);
            }
            else
            {
                long long erase_from_cache_index = GetCacheLowestPriority(requests, cache, ht_requests, cache_capacity, i);
                if (erase_from_cache_index != -1)
                {
                    hash_table_erase(ht_cache, &cache[erase_from_cache_index]);
                    hash_table_insert(ht_cache, &requests[i], &fictive_value);
                    cache[erase_from_cache_index] = requests[i];
                }
            }

            ++long_requests_quantity;
        }
    }

    ht_cache = hash_table_destroy(ht_cache);
    free(cache);

    return long_requests_quantity;
}

long long GetCacheLowestPriority(long long *requests, long long *cache, struct hash_table *ht_requests, 
                                 long long cache_capacity, long long cur_request_number)
{
    assert(requests    != NULL);
    assert(cache       != NULL);
    assert(ht_requests != NULL);

    long long max_next_index = cur_request_number;
    long long lowest_priority_index = 0;

    for (long long i = 0; i < cache_capacity; ++i)
    {
        struct list *next_item = hash_table_find(ht_requests, &cache[i]);

        if (next_item == NULL)
        {
            return i;
        }

        int exists = 0;
        long long closest_position = 1000000;
        while (next_item != NULL)
        {
            if (next_item->key == cache[i])
            {
                if (next_item->value > cur_request_number)
                {
                    exists = 1;
                    
                    if (next_item->value < closest_position)
                    {
                        closest_position = next_item->value;
                    }
                }
            }

            next_item = next_item->next;
        }

        if (max_next_index < closest_position)
        {
            max_next_index = closest_position;
            lowest_priority_index = i;
        }

        if (exists == 0)
        {
            return i;
        }
    }

    return lowest_priority_index;
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
        temp = delete_node(temp);
        
        return head;
    }
    
    if (temp->next == NULL)
    {
        temp_prev->next = NULL;
        temp = delete_node(temp);

        return head;
    }
    
    temp_prev->next = temp->next;
    temp = delete_node(temp);

    return head;
}

struct list *list_delete(struct list *head)
{
    while (head != NULL)
    {
        struct list *temp = head;
        head = head->next;
        temp = delete_node(temp);
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
    
    if ((elem_place == NULL) || (elem_place->value != *value))
    { 
        ++ht->size;
        ht->data[index] = list_insert(ht->data[index], key, value); 
    }
}

struct list *hash_table_find(struct hash_table *ht, ht_key_t *key)
{
    assert(ht    != NULL);
    assert(key   != NULL);
    
    size_t index = hash_table_get_index(ht, key);
    
    return list_find(ht->data[index], key);
}

void hash_table_erase(struct hash_table *ht, ht_key_t *key)
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


struct list *delete_node(struct list *node)
{
    free(node);
    
    return NULL;
}

size_t HashFunc(ht_key_t *key)
{
    assert(key != NULL);

    size_t key_value = *key;
	key_value = ((key_value >> 16) ^ key_value) * 0x45d9f3b;
	key_value = ((key_value >> 16) ^ key_value) * 0x45d9f3b;
	key_value =  (key_value >> 16) ^ key_value;

	return key_value;
}