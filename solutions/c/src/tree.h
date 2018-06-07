#ifndef TREE_H
#define TREE_H


/**
 * \brief Tree Node structure.
 *
 * A tree is represented by a pointer to a pointer.  E.g. T below.
 *
 *      struct tree ** T;
 *
 * A tree node is a pointer.
 *
 *      struct tree * x;
 *
 * The left child of x.
 *
 *      x->left;
 *
 * The left sub-tree of x.
 *
 *      &x->left;
 *
 */
struct tree
{
    struct tree *parent, *left, *right;
};

/**
 * Steps odometer.
 */
unsigned int tree_work(void);

/**
 * \brief Initialize an empty tree.
 */
void tree_init(struct tree ** T);

/**
 * @return 1 if T is empty.
 */
int tree_is_empty(struct tree ** T);

/**
 * \brief Walk tree inorder.
 */
void tree_walk_inorder(struct tree ** T,
    void (*visit)(struct tree * x, int height));

/**
 * \brief Walk tree reverse inorder.
 */
void tree_walk_reverse(struct tree ** T,
    void (*visit)(struct tree * x, int height));

/**
 * \brief Walk tree in preorder.
 */
void tree_walk_preorder(struct tree ** T,
    void (*visit)(struct tree * x, int height));

/**
 * \brief Walk tree in postorder
 */
void tree_walk_postorder(struct tree ** T,
    void (*visit)(struct tree * x, int height));

/**
 * @return Left most item in T.
 */
struct tree * tree_left_most(struct tree ** T);

/**
 * @return Right most item in T.
 */
struct tree * tree_right_most(struct tree ** T);

/**
 * @return Successor of item x.
 */
struct tree * tree_successor(struct tree * x);

/**
 * @return Predecessor of item x.
 */
struct tree * tree_predecessor(struct tree * x);

/**
 * \brief Insert x into T.
 *
 * @param x [in] Item to insert.
 * @param T [in] Tree to insert x into.
 * @param cmp [in] Comparator function for struct tree.
 */
void tree_insert(struct tree * x, struct tree ** T,
    int (*cmp)(struct tree*, struct tree*));

/**
 * \brief Search for an x matching k in T.
 */
struct tree * tree_search(void * k, struct tree ** T,
    int (*cmp)(void * k, struct tree*));

/**
 * \brief Delete x from T.  x must be in T!
 */
void tree_delete(struct tree * x, struct tree ** T);

/**
 * \brief Splay x.
 */
void tree_splay(struct tree * x, struct tree ** T);

/**
 * \brief Delete item x and then splay the former parent of x.
 */
void tree_delete_splay(struct tree * x, struct tree ** T);

/**
 * \brief Splay item x and then delete it.
 */
void tree_splay_delete(struct tree * x, struct tree ** T);

/**
 * \brief Insert item x and then splay it.
 */
void tree_insert_splay(struct tree * x, struct tree ** T,
    int (*cmp)(struct tree*, struct tree*));

#define tree_for_each(PTR, TREE)\
    for ((PTR) = tree_left_most(TREE);            \
         (PTR) != NULL;                           \
         (PTR) = tree_successor(PTR))

#define tree_for_each_reverse(PTR, TREE)\
    for ((PTR) = tree_right_most(TREE);           \
         (PTR) != NULL;                           \
         (PTR) = tree_predecessor(PTR))

#define tree_for_each_safe(PTR, TMP, TREE)              \
    for ((PTR) = tree_left_most(TREE),                  \
             (TMP) = tree_successor(PTR);               \
         (PTR) != NULL;                                 \
         (PTR) = (TMP), (TMP) = tree_successor(TMP))

#define tree_for_each_reverse_safe(PTR, TMP, TREE)      \
    for ((PTR) = tree_right_most(TREE),                 \
             (TMP) = tree_predecessor(PTR);             \
         (PTR) != NULL;                                 \
         (PTR) = (TMP), (TMP) = tree_predecessor(TMP))

#endif
