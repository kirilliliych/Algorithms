#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define aboba printf("aboba %d\n", __LINE__);

typedef long long ht_val_t;
typedef char ht_key_t;

struct list
{
    struct list *next;
    ht_val_t value;
    ht_key_t *key;
    long long num_in_queue;
};

struct hash_table 
{
    size_t capacity;    
    size_t size;
    struct list **data;
};

struct name_value
{
    long long value;
    long long num_in_queue;
    char *name;
};

const size_t HASH_TABLE_SIZE = (1 << 19) - 1;
const size_t MAX_NAME_SIZE   = 40;

struct list *list_new(ht_key_t *key, ht_val_t *value, long long num_in_queue);

struct list *list_insert(struct list *head, ht_key_t *key, ht_val_t *value, long long num_in_queue);

struct list *list_find(struct list *head, ht_key_t *key);

struct list *list_erase(struct list *head, ht_key_t *key);

struct list *list_delete(struct list *head);

struct list *delete_node(struct list *node);

void list_print(struct list const *head);

size_t hash_table_get_index(struct hash_table *ht, ht_key_t *key);

struct hash_table *hash_table_new(size_t capacity);

void hash_table_insert(struct hash_table *ht, ht_key_t *key, ht_val_t *value, long long num_in_queue);

struct list *hash_table_find(struct hash_table *ht, ht_key_t *key);

void hash_table_erase(struct hash_table *ht, ht_key_t *key);

size_t hash_table_size(struct hash_table *ht);

struct hash_table *hash_table_delete(struct hash_table *ht);

void hash_table_dump(struct hash_table *ht);

size_t HashFunc(ht_key_t *key);

struct list *list_new(ht_key_t *key, ht_val_t *value, long long num_in_queue)
{
    assert(key   != NULL);
    assert(value != NULL);

    struct list *node = (struct list *) calloc(1, sizeof(struct list));
    node->key = (ht_key_t *) calloc(MAX_NAME_SIZE + 1, sizeof(ht_key_t *));

    strncpy(node->key, key, MAX_NAME_SIZE);
    node->value = *value;
    node->num_in_queue = num_in_queue; 

    node->next = NULL;

    return node;
}

struct list *list_insert(struct list *head, ht_key_t *key, ht_val_t *value, long long num_in_queue)
{
    assert(key   != NULL);
    assert(value != NULL);

    if (head == NULL)
    {
        head = list_new(key, value, num_in_queue);
        return head;    
    }

    struct list *temp = head;
    
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = list_new(key, value, num_in_queue);

    return head;      
}

struct list *list_find(struct list *head, ht_key_t *key)
{
    assert(key != NULL);
    
    if (head == NULL)
    {
        return NULL;
    }   

    while (strcmp(key, head->key) != 0)
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

    while (strcmp(key, head->key) != 0)
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
            printf("(%s, %lld, %lld), ", temp->key, temp->value, temp->num_in_queue);
            temp = temp->next;
        }

        printf("(%s, %lld, %lld)", temp->key, temp->value, temp->num_in_queue);
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

void hash_table_insert(struct hash_table *ht, ht_key_t *key, ht_val_t *value, long long num_in_queue)
{
    assert(ht    != NULL);
    assert(key   != NULL);
    assert(value != NULL);
    
    size_t index = hash_table_get_index(ht, key);
    
    ht->data[index] = list_insert(ht->data[index], key, value, num_in_queue);
}

struct list *hash_table_find(struct hash_table *ht, ht_key_t *key)
{
    assert(ht  != NULL);
    assert(key != NULL);
    
    size_t index = hash_table_get_index(ht, key);
    
    return list_find(ht->data[index], key);
}

void hash_table_erase(struct hash_table *ht, ht_key_t *key)
{
    assert(ht  != NULL);
    assert(key != NULL);

    size_t index = hash_table_get_index(ht, key);

    ht->data[index] = list_erase(ht->data[index], key);
    --ht->size;
}

size_t hash_table_size(struct hash_table *ht)
{
    assert(ht != NULL);

    return ht->size;
}

struct hash_table *hash_table_delete(struct hash_table *ht)
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
/*
size_t HashFunc(ht_key_t *key)
{
    assert(key != NULL);

    size_t key_value = *key;
    key_value = ((key_value >> 16) ^ key_value) * 0x45d9f3b;
    key_value = ((key_value >> 16) ^ key_value) * 0x45d9f3b;

    return (key_value >> 16)^ key_value;
}
*/

size_t HashFunc(ht_key_t *key)
{
    assert(key != NULL);

    const size_t polynom = 0x04C11DB7;
    const size_t old_bit_checker = 1 << 26;

    size_t hash = 0;

    while (*key != '\0')
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
    }

    return hash;
}

struct list *delete_node(struct list *node)
{
    free(node->key);
    free(node);
    
    return NULL;
}

int Comparator(const void *participant1, const void *participant2)
{
    assert(participant1 != NULL);
    assert(participant2 != NULL);

    long long cmp = ((struct name_value *) participant1)->value - ((struct name_value *) participant2)->value;

    if (cmp == 0)
    {
        return ((struct name_value *) participant1)->num_in_queue > ((struct name_value *) participant2)->num_in_queue;
    }

    else return ((struct name_value *) participant1)->value < ((struct name_value *) participant2)->value;
}

void ProcessNewAttempt(struct hash_table *ht, char **names, char *received_name, long long received_value, long long *participant_index, long long num_in_queue)
{
    assert(ht                != NULL);
    assert(names             != NULL);
    assert(received_name     != NULL);
    assert(participant_index != NULL);

    struct list *result = hash_table_find(ht, received_name);
    if (result == NULL)
    {
        hash_table_insert(ht, received_name, &received_value, num_in_queue);

        strcpy(names[*participant_index], received_name);

        ++(*participant_index);
    }
    else
    {
        if (received_value > result->value)
        {
            result->value = received_value;
            result->num_in_queue = num_in_queue;
        }
    }
}

void FormSortedParticipantsList(struct hash_table *ht, struct name_value *participants, char **names, long long M)
{
    assert(ht           != NULL);
    assert(participants != NULL);
    assert(names        != NULL);

    for (long long i = 0; i < M; ++i)
    {
        participants[i].name = names[i];

        struct list *result = hash_table_find(ht, names[i]);
        if (result == NULL)
        {
            continue;
        }
        participants[i].value = result->value;
        participants[i].num_in_queue = result->num_in_queue;
    }

    qsort(participants, M, sizeof(struct name_value), Comparator);
}

int main()
{
    long long M = 0;
    long long N = 0;
    scanf("%lld %lld", &M, &N);

    char **names = (char **) calloc(M, sizeof(char *));
    for (long long i = 0; i < M; ++i)
    {
        names[i] = (char *) calloc(MAX_NAME_SIZE + 1, sizeof(char));
    }

    struct hash_table *ht = hash_table_new(HASH_TABLE_SIZE);
    char cur_name[41] = {};
    long long value = 0;

    long long participant_index = 0;
    for (long long i = 0; i < N; ++i)
    {
        scanf("%s %lld", cur_name, &value);
        ProcessNewAttempt(ht, names, cur_name, value, &participant_index, i);
    }
    
    struct name_value *participants = (struct name_value *) calloc(M, sizeof(struct name_value));
    FormSortedParticipantsList(ht, participants, names, M);

    for (long long i = 0; i < M; ++i)
    {
        if (participants[i].name != NULL)
        {
            printf("%s\n", participants[i].name);
        }
    }

    free(participants);

    ht = hash_table_delete(ht);
    for (long long i = 0; i < M; ++i)
    {
        free(names[i]);    
    }
    free(names);

    return 0;
}   