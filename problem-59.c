#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "words.h"

static int verbose = 1;

/*
 * Quick and easy way to read in the numbers :)
 */
static char cipher[] = {
#include "cipher1.txt"
};
static int cipher_length = sizeof(cipher)/sizeof(cipher[0]);

char cmd[256];


char lowercase(char x)
{
    if ('a' <= x && x <= 'z')
        return x;
    if ('A' <= x && x <= 'Z')
        return x + 'a' - 'A';
    return ' ';
}

struct words * dict = NULL;

void init_dict(const char * path)
{
    FILE * fs;
    char word[256];
    int i;

    dict = new_words();
    fs = fopen(path, "r");
    while (0 < fscanf(fs, "%s", word))
    {
        i=0;
        while (word[i] != (char)0)
        {
            word[i] = lowercase(word[i]);
            ++i;
        }
        if (verbose)
            printf("add word: %s\n", word);
        words_add(dict, word);
    }
    fclose(fs);
}

int in_dict(char * tok)
{
    int in = words_has(dict, tok);
    if (in) {
        //printf("in_dict: %s\n", tok);
    }
    return in;
}

int is_letter(char x)
{
    if ('a' <= x && x <= 'z') return 1;
    if ('A' <= x && x <= 'Z') return 1;
    return 0;
}

struct dec
{
    char * cipher;
    size_t cipher_length;
    char * key;
    size_t key_length;
    size_t i;
    char token[256];
};

void dec_init(struct dec * dec, char * cipher, size_t cipher_length, char * key, size_t key_length)
{
    dec->cipher = cipher;
    dec->cipher_length = cipher_length;
    dec->key = key;
    dec->key_length = key_length;
    dec->i = 0;
}

/**
 * @return the next plain text, or (char)0 if it is complete.
 */
char dec_read(struct dec * dec)
{
    char x;
    if (dec->i < dec->cipher_length) {
        x = dec->cipher[dec->i];
        x ^= dec->key[dec->i % dec->key_length];
        dec->i += 1;
        return x;
    }
    return (char)0;
}

char * dec_token(struct dec * dec)
{
    size_t i;
    char x;

    i = 0;
    for (;;) {
        dec->token[i] = dec_read(dec);
        if (is_letter(dec->token[i])) {
            break;
        } else if (dec->token[i] == 0) {
            return NULL;
        }
    }
    i = 1;
    for (;;) {
        dec->token[i] = dec_read(dec);
        if (!is_letter(dec->token[i])) {
            dec->token[i] = (char)0;
            return dec->token;
        }
        ++i;
    }
}

/**
 * Transforms a word into a 64-bit signature.
 */
unsigned long long sign_word(char * word)
{
    unsigned long long sig;
    char * cursor;
    sig = 0;
    cursor = word;
    while (cursor[0] != (char)0) {
        if (sig > sig*26) {
            printf("word overflow: %s\n", word);
            exit(0);
        }
        sig *= 26;
        sig += (lowercase(cursor[0]) - 'a');
        cursor += 1;
    }
    return sig;
}

int satisfies(char key[4]) {
    struct dec dec;
    char * tok;
    int i;

    dec_init(&dec, cipher, cipher_length, key, 3);
    while (NULL != (tok = dec_token(&dec))) {
        i=0;
        while (tok[i] != (char)0)
        {
            tok[i] = lowercase(tok[i]);
            ++i;
        }
        if (!in_dict(tok)) {
            return 0;
        }
    }
    return 1;
}

double score(char key[4]) {
    struct dec dec;
    char * tok;
    int i;
    size_t k, n;

    k = 0;
    n = 0;
    dec_init(&dec, cipher, cipher_length, key, 3);
    while (NULL != (tok = dec_token(&dec))) {
        i=0;
        while (tok[i] != (char)0)
        {
            tok[i] = lowercase(tok[i]);
            ++i;
        }
        if (in_dict(tok)) {
            k += 1;
        }
        n += 1;
    }
    return (double)k / (double)n;
}


int main(void)
{
    int i;
    char x;
    struct dec dec;
    char * tok;
    char key[4];

    if (0) {
        for (i=0; i<cipher_length; ++i) {
            printf("%c", lowercase(cipher[i]));
        }
        printf("\n");

        dec_init(&dec, cipher, cipher_length, "aaa", 3);
        while (0 != (x = dec_read(&dec))) {
            printf("%c", lowercase(x));
        }
        printf("\n");

        /* tokenizer. */
        dec_init(&dec, cipher, cipher_length, "aab", 3);
        while (NULL != (tok = dec_token(&dec))) {
            printf("%s   -> sig: %llu\n", tok, sign_word(tok));
        }

        return 0;
    }

    /* key generator */
    double max_score, curr_score;
    char max_key[4];
    init_dict("/usr/share/dict/words");
    key[3] = (char)0;
    for (key[0]='a'; key[0] <= 'z'; ++key[0])
        for (key[1]='a'; key[1] <= 'z'; ++key[1])
            for (key[2]='a'; key[2] <= 'z'; ++key[2]) {

                if (1) {
                    curr_score = score(key);
                    if (verbose)
                        printf("key: %s  score: %.6lf\n", key, curr_score);
                    if (curr_score > max_score)
                    {
                        max_score = curr_score;
                        memcpy(max_key, key, 4);
                        if (verbose)
                        {
                            printf("\n\n----- new max -- key: %s ---- score: %lf ----\n", max_key, max_score);
                            dec_init(&dec, cipher, cipher_length, max_key, 3);
                            while (0 != (x = dec_read(&dec))) {
                                printf("%c", lowercase(x));
                            }
                            printf("\n\n\n");
                            usleep(250000);
                        }
                    }
                }
                if (0) {
                    if (satisfies(key)) {
                        printf("good_key: %s\n", key);
                        fprintf(stderr, "good_key: %s\n", key);
                    } else {
                        printf("bad_key: %s\n", key);
                    }
                }
            }
    printf("\n\n------- key: %s ---- score: %lf ----\n", max_key, max_score);
    int sum = 0;
    dec_init(&dec, cipher, cipher_length, max_key, 3);
    while (0 != (x = dec_read(&dec))) {
        sum += x;
        printf("%c", x);
    }
    printf("\n\n\n");
    printf("sum: %d\n", sum);

    return 0;
}
