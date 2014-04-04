#include <stdlib.h>
#include "macros.h"
#include "tree.h"

static unsigned int work = 0;

unsigned int tree_work(void)
{
    return work;
}

void tree_init(struct tree ** T)
{
    if (T == NULL)
        exit(EXIT_FAILURE);
    (*T) = NULL;
}

int tree_is_empty(struct tree ** T)
{
    if (T == NULL)
        exit(EXIT_FAILURE);
    return ((*T) == NULL) ? 1 : 0;
}

static void __walk_inorder(struct tree * x, int height,
    void (*visit)(struct tree * x, int height))
{
    if (x) {
        if (x->left)
            __walk_inorder(x->left, height + 1, visit);
        visit(x, height);
        if (x->right)
            __walk_inorder(x->right, height + 1, visit);
    }
}

void tree_walk_inorder(struct tree ** T,
    void (*visit)(struct tree * x, int height))
{
    __walk_inorder((*T), 1, visit);
}

static void __walk_reverse(struct tree * x, int height,
    void (*visit)(struct tree * x, int height))
{
    if (x) {
        if (x->right)
            __walk_reverse(x->right, height + 1, visit);
        visit(x, height);
        if (x->left)
            __walk_reverse(x->left, height + 1, visit);
    }
}

void tree_walk_reverse(struct tree ** T,
    void (*visit)(struct tree * x, int height))
{
    __walk_reverse((*T), 1, visit);
}

static void __walk_preorder(struct tree * x, int height,
    void (*visit)(struct tree * x, int height))
{
    if (x) {
        visit(x, height);
        if (x->left)
            __walk_preorder(x->left, height + 1, visit);
        if (x->right)
            __walk_preorder(x->right, height + 1, visit);
    }
}

void tree_walk_preorder(struct tree ** T,
    void (*visit)(struct tree * x, int height))
{
    __walk_preorder((*T), 1, visit);
}

static void __walk_postorder(struct tree * x, int height,
    void (*visit)(struct tree * x, int height))
{
    if (x) {
        if (x->left)
            __walk_postorder(x->left, height + 1, visit);
        if (x->right)
            __walk_postorder(x->right, height + 1, visit);
        visit(x, height);
    }
}

void tree_walk_postorder(struct tree ** T,
    void (*visit)(struct tree * x, int height))
{
    __walk_postorder((*T), 1, visit);
}

struct tree * tree_left_most(struct tree ** T)
{
    struct tree * x;
    if ((*T) == NULL)
        return NULL;
    for (x = (*T); x->left != NULL; x = x->left)
    {
        ++work;
    }
    return x;
}

struct tree * tree_right_most(struct tree ** T)
{
    struct tree * x;
    if ((*T) == NULL)
        return NULL;
    for (x = (*T); x->right != NULL; x = x->right)
        ++work;
    return x;
}

struct tree * tree_first_left_parent(struct tree * x)
{
    ++work;
    if (x == NULL)
        return NULL;
    if (x->parent == NULL)
        return NULL;
    if (x->parent->right == x)
        return tree_first_left_parent(x->parent);
    return x->parent;
}

struct tree * tree_first_right_parent(struct tree * x)
{
    ++work;
    if (x == NULL)
        return NULL;
    if (x->parent == NULL)
        return NULL;
    if (x->parent->left == x)
        return tree_first_right_parent(x->parent);
    return x->parent;
}

struct tree * tree_successor(struct tree * x)
{
    struct tree * y;
    /* left most of the right sub-tree. */
    if (x == NULL)
        return NULL;
    if (NULL != (y = tree_left_most(&x->right)))
        return y;
    return tree_first_left_parent(x);
}

struct tree * tree_predecessor(struct tree * x)
{
    struct tree * y;
    /* right most of the left sub-tree */
    if (x == NULL)
        return NULL;
    if (NULL != (y = tree_right_most(&x->left)))
        return y;
    return tree_first_right_parent(x);
}

void tree_insert(struct tree * x, struct tree ** T,
    int (*cmp)(struct tree*, struct tree*))
{
    struct tree * p;
    if (x == NULL || T == NULL || cmp == NULL)
        exit(EXIT_FAILURE);
    x->parent = NULL;
    x->left = NULL;
    x->right = NULL;
    if (tree_is_empty(T)) {
        ++work;
        (*T) = x;
        return;
    }
    p = (*T);
    for (;;) {
        ++work;
        if (cmp(x, p) < 0) {
            if (p->left) {
                p = p->left;
            } else {
                p->left = x;
                x->parent = p;
                return;
            }
        } else {
            if (p->right) {
                p = p->right;
            } else {
                p->right = x;
                x->parent = p;
                return;
            }
        }
    }
}

struct tree * tree_search(void * k, struct tree ** T,
    int (*cmp)(void * k, struct tree*))
{
    int r;
    ++work;
    if ((*T) == NULL)
        return NULL;
    r = cmp(k, (*T));
    if (r < 0)
        return tree_search(k, &((*T)->left), cmp);
    if (r > 0)
        return tree_search(k, &((*T)->right), cmp);
    return (*T);
}

void tree_delete(struct tree * x, struct tree ** T)
{
    struct tree *y, *w, *z, *p, *A, *B, *C;
    if (x == NULL)
        return;
    ++work;
    if (x->left == NULL && x->right == NULL) {
        /*
         * x has no children.  So simply detach from its parent.
         */
        if (x->parent == NULL) {
            (*T) = NULL;
        } else if (x == x->parent->left) {
            x->parent->left = NULL;
        } else {
            x->parent->right = NULL;
        }
    } else if (x->left != NULL && x->right == NULL) {
        /*
         * x has a left child.  Replace x with its left child.
         *
         *        p          p
         *        |          |
         *        x    =>    A
         *       /
         *      A
         */
        p = x->parent;
        A = x->left;
        if (p == NULL) {
            (*T) = A;
        } else if (p->left == x) {
            p->left = A;
        } else {
            p->right = A;
        }
        A->parent = p;
    } else if (x->left == NULL && x->right != NULL) {
        /*
         * x has a right child.  Replace x with its right child.
         *
         *        p          p
         *        |          |
         *        x    =>    A
         *         \
         *          A
         */
        p = x->parent;
        A = x->right;
        if (p == NULL) {
            (*T) = A;
        } else if (p->left == x) {
            p->left = A;
        } else {
            p->right = A;
        }
        A->parent = p;
    } else {
        y = tree_left_most(&x->right);
        if (x->right == y) {
            /*
             * If y is the left-most of the right sub-tree, then the
             * following must be the case.  Because y is left-most, it
             * has no left child.
             *
             *     p                  p
             *     |                  |
             *     x         =>       y
             *    / \                / \
             *   A   y              A   B
             *        \
             *         B
             */
            p = x->parent;
            A = x->left;
            if (p == NULL)
                (*T) = y;
            else if (p->left == x)
                p->left = y;
            else
                p->right = y;
            y->parent = p;
            y->left = A;
            if (A)
                A->parent = y;
        } else {
            /*
             * y is the left most and so has no left child.
             *
             *       p              p
             *       |              |
             *       x              y
             *      / \            / \
             *     C   z          C   z
             *        / \            / \
             *       .   B  =>      .   B
             *      .              .
             *      w              w
             *     /              /
             *    y              A
             *     \
             *      A
             */
            w = y->parent;
            A = y->right;
            C = x->left;
            z = x->right;
            p = x->parent;
            if (p == NULL)
                (*T) = y;
            else if (p->left == x)
                p->left = y;
            else
                p->right = y;
            y->parent = p;
            y->left = C;
            if (C)
                C->parent = y;
            y->right = z;
            z->parent = y;
            w->left = A;
            if (A)
                A->parent = w;
        }
    }
    x->left = NULL;
    x->right = NULL;
    x->parent = NULL;
}

void tree_splay(struct tree * x, struct tree ** T)
{
    struct tree *p, *g, *q, *B, *C;
    if (x == NULL)
        return;
    while (x != (*T))
    {
        ++work;
        p = x->parent;
        g = p->parent;
        if (g == NULL) {
            if (p->left == x) {
                /*
                 *    (**T)        (**T)
                 *      |            |
                 *      p            x
                 *     / \          / \
                 *    x   C   =>   A   p
                 *   / \              / \
                 *  A   B            B   C
                 */
                B = x->right;
                (*T) = x;
                x->parent = NULL;
                x->right = p;
                p->parent = x;
                p->left = B;
                if (B)
                    B->parent = p;
            } else {
                /*
                 *    (**T)        (**T)
                 *      |            |
                 *      x            p
                 *     / \          / \
                 *    p   C   <=   A   x
                 *   / \              / \
                 *  A   B            B   C
                 */
                B = x->left;
                (*T) = x;
                x->parent = NULL;
                x->left = p;
                p->parent = x;
                p->right = B;
                if (B)
                    B->parent = p;
            }
        } else if (g->left == p && p->left == x) {
            /*
             *         q             q
             *         |             |
             *         g             x
             *        / \           / \
             *       p   D         A   p
             *      / \       =>      / \
             *     x   C             B   g
             *    / \                   / \
             *   A   B                 C   D
             */
            B = x->right;
            C = p->right;
            q = g->parent;
            if (q == NULL)
                (*T) = x;
            else if (q->left == g)
                q->left = x;
            else
                q->right = x;
            x->parent = q;
            x->right = p;
            p->parent = x;
            p->left = B;
            if (B)
                B->parent = p;
            p->right = g;
            g->parent = p;
            g->left = C;
            if (C)
                C->parent = g;
        } else if (g->right == p && p->right == x) {
            /*
             *         q             q
             *         |             |
             *         x             g
             *        / \           / \
             *       p   D         A   p
             *      / \       <=      / \
             *     g   C             B   x
             *    / \                   / \
             *   A   B                 C   D
             */
            q = g->parent;
            B = p->left;
            C = x->left;
            if (q == NULL)
                (*T) = x;
            else if (q->left == g)
                q->left = x;
            else
                q->right = x;
            x->parent = q;
            x->left = p;
            p->parent = x;
            p->right = C;
            if (C)
                C->parent = p;
            p->left = g;
            g->parent = p;
            g->right = B;
            if (B)
                B->parent = g;
        } else if (g->right == p && p->left == x) {
            /*
             *         q              q
             *         |              |
             *         g              x
             *        / \            / \
             *       A   p    =>    /   \
             *          / \        g     p
             *         x   D      / \   / \
             *        / \        A   B C   D
             *       B   C
             */
            q = g->parent;
            B = x->left;
            C = x->right;
            if (q == NULL)
                (*T) = x;
            else if (q->left == g)
                q->left = x;
            else
                q->right = x;
            x->parent = q;
            x->left = g;
            x->right = p;
            g->parent = x;
            p->parent = x;
            g->right = B;
            if (B)
                B->parent = g;
            p->left = C;
            if (C)
                C->parent = p;
        } else if (g->left == p && p->right == x) {
            /*
             *         q              q
             *         |              |
             *         g              x
             *        / \            / \
             *       p   D    =>    /   \
             *      / \            p     g
             *     A   x          / \   / \
             *        / \        A   B C   D
             *       B   C
             */
            q = g->parent;
            B = x->left;
            C = x->right;
            if (q == NULL)
                (*T) = x;
            else if (q->left == g)
                q->left = x;
            else
                q->right = x;
            x->parent = q;
            x->left = p;
            x->right = g;
            p->parent = x;
            g->parent = x;
            p->right = B;
            if (B)
                B->parent = p;
            g->left = C;
            if (C)
                C->parent = g;
        }
    }
}

void tree_delete_splay(struct tree * x, struct tree ** T)
{
    struct tree * p;
    if (x == NULL)
        return;
    p = x->parent;
    tree_delete(x, T);
    tree_splay(p, T);
}

void tree_splay_delete(struct tree * x, struct tree ** T)
{
    tree_splay(x, T);
    tree_delete(x, T);
}

void tree_insert_splay(struct tree * x, struct tree ** T,
    int (*cmp)(struct tree*, struct tree*))
{
    tree_insert(x, T, cmp);
    tree_splay(x, T);
}
