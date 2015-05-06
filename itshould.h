#ifndef ITSHOULD_H
#define ITSHOULD_H

#include <stdio.h>
#include <stdlib.h>

#define ITSHOULD_VERSION "v0.1.1"

#define Describe(SUBJECT_STMT, BODY)            \
    do {                                        \
        ITSHOULD_print_header();                \
        printf("\n");                           \
        ITSHOULD_print_indent();                \
        ITSHOULD_inc_indent();                  \
        printf("%s\n", SUBJECT_STMT);           \
        BODY;                                   \
        ITSHOULD_dec_indent();                  \
    } while (0)

#define It(SHOULD_STMT, BODY)                   \
    do {                                        \
        ITSHOULD_print_indent();                \
        printf("%s", SHOULD_STMT);              \
        BODY;                                   \
        printf(" ... OK\n");                    \
    } while (0)

#define Assert(COND)                            \
    do {                                        \
        if (!(COND)) {                          \
            printf(" - Assertion at %s:%d failed: %s\n",  \
                __FILE__, __LINE__, #COND);     \
            ITSHOULD_summarise();               \
            exit(EXIT_FAILURE);                 \
        }                                       \
        ITSHOULD_inc_assert_count();            \
    } while (0)

#define Summarise() ITSHOULD_summarise()

int ITSHOULD_did_header = 0;
int ITSHOULD_indent = 0;
int ITSHOULD_assert_count = 0;

static inline void ITSHOULD_print_header(void) {
    if (ITSHOULD_did_header)
        return;
    printf("\nITSHOULD %s\n", ITSHOULD_VERSION);
    ITSHOULD_did_header = 1;
}

static inline void ITSHOULD_print_indent(void) {
    int i;
    for (i=0; i<ITSHOULD_indent; ++i) {
        printf("  ");
    }
}

static inline void ITSHOULD_inc_indent(void) {
    ITSHOULD_indent += 1;
}

static inline void ITSHOULD_dec_indent(void) {
    ITSHOULD_indent -= 1;
}

static inline void ITSHOULD_inc_assert_count(void) {
    ITSHOULD_assert_count += 1;
}

static inline void ITSHOULD_summarise(void) {
    printf("\n");
    printf("ITSHOULD: Completed %d asserts\n",
        ITSHOULD_assert_count);
    printf("\n");
}

#endif
