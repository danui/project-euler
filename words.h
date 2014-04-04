#ifndef WORDS_H
#define WORDS_H

struct words;

/**
 * @return empty words.
 */
struct words * new_words(void);

/**
 * Add word into W.
 */
void words_add(struct words * W, const char * word);

/**
 * Visit words in order.
 */
void words_visit(struct words * W,
    void (*accept)(const char * word, void * ctx),
    void * ctx);

int words_has(struct words * W, const char * word);

#endif
