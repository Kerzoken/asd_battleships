#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "battleships.h"

struct encrypted_message* encrypt(char* text, char* key)
{
    // MUST input a normal string, TODO: maybe add for strange strings
    static char* cur_vector = INITIAL_VECTOR;

    int text_length = strlen(text);
    char* new_text = _strdup(text);

    // crypt with vector
    for (int i = 0; i < 32 && new_text[i]; i++)
        new_text[i] ^= cur_vector[i];

    // crypt with key
    int key_length = strlen(key);
    for (int i = 0; i < text_length; i++)
        new_text[i] += key[i % key_length];

    cur_vector = new_text;

    struct encrypted_message* res = malloc(sizeof *res + sizeof(char) * text_length);
    assert(res != NULL);
    res->text = new_text;
    res->size = text_length;

    return res;
}

char* decrypt(struct encrypted_message* msg, char* key)
{
    static char* cur_vector = INITIAL_VECTOR;

    char* new_text = malloc(msg->size + 1);
    assert(new_text != NULL);
    memcpy(new_text, msg->text, msg->size + 1);

    // decrypt with key
    int key_length = strlen(key);
    for (int i = 0; i < msg->size; i++)
        new_text[i] -= key[i % key_length];

    // decrypt with vector
    int l = min(msg->size, 32);
    for (int i = 0; i < l; i++)
        new_text[i] ^= cur_vector[i];

    cur_vector = malloc(msg->size + 1);
    assert(cur_vector != NULL);
    memcpy(cur_vector, msg->text, min(32, msg->size) + 1);
    
    return new_text;
}

//int main()
//{
//    struct encrypted_message* c1, * c2, * c3;
//
//    c1 = encrypt("Hello", "abc");
//    c2 = encrypt("World", "abc");
//    c3 = encrypt("Bye", "abc");
//
//    decrypt(c1, "abc");
//    decrypt(c2, "abc");
//    decrypt(c3, "abc");
//    return 0;
//}