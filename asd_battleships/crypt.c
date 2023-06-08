#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct encrypted_message
{
    char* text;
    int size;
};

struct encrypted_message* encrypt(char* text, char* iv, char* key)
{
    static char* cur_vector = 0;
    static int cur_vector_size;

    if (!cur_vector) {
        cur_vector = iv;
        cur_vector_size = strlen(iv);
    }

    int text_length = strlen(text);

    char* new_text = _strdup(text);

    // crypt with vector
    for (char* tmp = new_text; *tmp; tmp++)
        *tmp ^= cur_vector[(tmp - new_text) % cur_vector_size];

    // crypt with key
    for (int i = 0; i < text_length; i++)
        new_text[i] += key[i % strlen(key)];

    cur_vector = new_text;
    cur_vector_size = text_length;

    struct encrypted_message* res = malloc(sizeof * res + text_length);
    res->text = new_text;
    res->size = text_length;

    return res;
}

char* decrypt(struct encrypted_message* msg, char* iv, char* key)
{
    static struct encrypted_message* cur_vector = 0;

    if (!cur_vector) {
        cur_vector = malloc(sizeof * cur_vector);
        cur_vector->text = iv;
        cur_vector->size = strlen(iv);
    }

    int text_length = msg->size;
    char* new_text = malloc(msg->size + 1);
    for (int i = 0; i <= msg->size; i++)
        new_text[i] = msg->text[i];

    // decrypt with key
    for (int i = 0; i < text_length; i++)
        new_text[i] -= key[i % strlen(key)];

    // decrypt with vector
    for (int i = 0; i < text_length; i++)
        new_text[i] ^= cur_vector->text[i % cur_vector->size];

    cur_vector = msg;
    return new_text;
}

//int main()
//{
//    struct encrypted_message* c1, * c2, * c3;
//
//    c1 = encrypt("Hello", "test", "abc");
//    c2 = encrypt("World", "test", "abc");
//    c3 = encrypt("Bye", "test", "abc");
//
//    decrypt(c1, "test", "abc");
//    decrypt(c2, "test", "abc");
//    decrypt(c3, "test", "abc");
//    return 0;
//}