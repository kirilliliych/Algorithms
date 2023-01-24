#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define aboba printf("aboba %d\n", __LINE__);

typedef char ht_val_t;
typedef char ht_key_t;

struct list
{
    struct list *next;
    ht_key_t    *key;
    ht_val_t    *value;
};

struct hash_table 
{
    size_t capacity;    
    size_t size;
    struct list **data;
};

const size_t MAX_VALUE_KEY_LENGTH = 30;

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

size_t Crc32Hash(ht_key_t *key);


int main()
{
    long long N = 0;
    scanf("%lld", &N);

    char *new_word = (char *) calloc(MAX_VALUE_KEY_LENGTH + 1, sizeof(char));
    struct hash_table *ht = hash_table_new((1 << 19) - 1);

    while (fscanf(stdin, "%30s", new_word) != EOF)
    {
        if (strcmp(new_word, "ADD") == 0)
        {
            fscanf(stdin, "%30s", new_word);
            char *value = (char *) calloc(MAX_VALUE_KEY_LENGTH + 1, sizeof(char));
            fscanf(stdin, "%30s", value);

            hash_table_insert(ht, new_word, value);

            free(value);

            continue;
        }

        if (strcmp(new_word, "DELETE") == 0)
        {
            fscanf(stdin, "%30s", new_word);
            hash_table_delete(ht, new_word);

            continue;
        }

        if (strcmp(new_word, "EDITPHONE") == 0)
        {
            fscanf(stdin, "%30s", new_word);
            char *value = (char *) calloc(MAX_VALUE_KEY_LENGTH + 1, sizeof(char));
            fscanf(stdin, "%30s", value);

            struct list *node_to_edit = hash_table_find(ht, new_word);
            if (node_to_edit == NULL)
            {
                printf("ERROR\n");
            }
            else
            {
                strncpy(node_to_edit->value, value, MAX_VALUE_KEY_LENGTH);
            }

            free(value);

            continue;
        }

        if (strcmp(new_word, "PRINT") == 0)
        {
            fscanf(stdin, "%30s", new_word);
            
            struct list *node_to_print = hash_table_find(ht, new_word);
            if (node_to_print == NULL)
            {
                printf("ERROR\n");
            }
            else
            {
                printf("%s %s\n", node_to_print->key, node_to_print->value);
            }


            continue;
        }

    }

    hash_table_destroy(ht);
    free(new_word);

    return 0;
}


struct list *list_new(ht_key_t *key, ht_val_t *value)
{
    assert(key   != NULL);
    assert(value != NULL);

    struct list *node = (struct list *) calloc(1, sizeof(struct list));

    node->key   = (ht_key_t *) calloc(MAX_VALUE_KEY_LENGTH + 1, sizeof(ht_key_t));
    node->value = (ht_val_t *) calloc(MAX_VALUE_KEY_LENGTH + 1, sizeof(ht_val_t)); 
    strncpy(node->key,     key, MAX_VALUE_KEY_LENGTH);
    strncpy(node->value, value, MAX_VALUE_KEY_LENGTH);

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
    
    struct list *temp = head;
    
    while (strcmp(key, temp->key) != 0)
    {
        if (temp->next == NULL)
        {
            return NULL;
        }

        temp = temp->next;
    }

    return temp;    
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

    while (strcmp(key, temp->key) != 0)
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
            printf("(%s, %s), ", temp->key, temp->value);
            temp = temp->next;
        }

        printf("(%s, %s)", temp->key, temp->value);
    }
    printf("]\n");
}

size_t hash_table_get_index(struct hash_table *ht, ht_key_t *key)
{
    assert(ht  != NULL);
    assert(key != NULL);

    return Crc32Hash(key) % ht->capacity;
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
    
    printf("ERROR\n");

    return;

    //strncpy(elem_place->value, value, MAX_VALUE_KEY_LENGTH);
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
        printf("ERROR\n");

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

size_t Crc32Hash(ht_key_t *key)
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

struct list *delete_node(struct list **node)
{
    if (*node != NULL)
    {
        free((*node)->key);
        free((*node)->value);

        (*node)->key = NULL;
        (*node)->value = NULL; 
    }

    free(*node);
    *node = NULL;
    
    return NULL;
}
