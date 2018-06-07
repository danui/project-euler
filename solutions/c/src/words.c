#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define ALPHABET_SIZE (1 + 10 + 26 + 1)

struct words
{
    struct words * child[ALPHABET_SIZE];
    char in_words;
    size_t longest_word;
};

static size_t index_from_char(char c)
{
    size_t b = 0;

    if ('-' == c)
        return 0;
    b += 1;

    if ('0' <= c && c <= '9')
        return b + (size_t)c - (size_t)'0';
    b += 10;

    if ('A' <= c && c <= 'Z')
        return b + (size_t)c - (size_t)'A';
    if ('a' <= c && c <= 'z')
        return b + (size_t)c - (size_t)'a';

    b += 26;
    return b;
}

static char char_from_index(size_t k)
{
    if (k < 1)
        return '-';
    k -= 1;
    if (k < 10)
        return (char)('0' + k);
    k -= 10;
    if (k < 26)
        return (char)('a' + k);
    k -= 26;
    return '_';
}

struct words * new_words(void)
{
    static size_t memused=0;
    memused += sizeof(struct words);
    //printf("memused: %zu\n", memused);
    return calloc(1, sizeof(struct words));
}

void words_add(struct words * W, const char * word)
{
    size_t i;
    size_t k;
    struct words * x;
    x = W;
    for (i=0; word[i] != (char)0; ++i)
    {
        k = index_from_char(word[i]);
        if (x->child[k] == NULL)
        {
            x->child[k] = new_words();
        }
        x = x->child[k];
    }
    x->in_words = 1;
    if (W->longest_word < i)
        W->longest_word = i;
}

static void __visit(struct words * x,
    void (*accept)(const char*, void*), void * ctx,
    char * word, size_t len)
{
    size_t i;
    if (x->in_words) {
        word[len] = (char)0;
        accept(word, ctx);
    }
    for (i=0; i < ALPHABET_SIZE; ++i)
    {
        if (x->child[i])
        {
            word[len] = char_from_index(i);
            __visit(x->child[i], accept, ctx, word, len+1);
        }
    }
}

void words_visit(struct words * W,
    void (*accept)(const char * word, void * ctx),
    void * ctx)
{
    char * word;
    word = malloc(W->longest_word + 1);
    __visit(W, accept, ctx, word, 0);
    free(word);
}

int words_has(struct words * W, const char * word)
{
    size_t idx;
    const char * cursor;

    cursor = word;
    while (cursor[0] != (char)0)
    {
        idx = index_from_char(cursor[0]);
        if (W->child[idx] == NULL)
        {
            return 0;
        }
        W = W->child[idx];
        cursor += 1;
    }
    return (W->in_words) ? 1 : 0;
}
