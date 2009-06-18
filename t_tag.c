/*
 * t_tag.c
 *
 * tagutil's tag structures/functions.
 */
#include "t_config.h"
#include "t_toolkit.h"
#include "t_tag.h"


struct t_taglist *
t_taglist_new(void)
{
    struct t_taglist *ret;

    ret = xmalloc(sizeof(struct t_taglist) + sizeof(struct t_tag_q));
    ret->tags = (struct t_tag_q *)(ret + 1);
    ret->tcount = 0;
    t_error_init(ret);
    TAILQ_INIT(ret->tags);

    return (ret);
}


void
t_taglist_insert(struct t_taglist *restrict T,
        const char *restrict key, const char *restrict value)
{
    size_t len;
    ssize_t vlen;
    char *s;
    struct t_tag  *t, *kinq;
    struct t_tagv *v;

    assert_not_null(key);
    assert_not_null(T);

    /* create v if needed */
    if (value) {
        vlen = strlen(value);
        v = xmalloc(sizeof(struct t_tagv) + vlen + 1);
        v->vlen = vlen;
        s = (char *)(v + 1);
        (void)strlcpy(s, value, vlen + 1);
        v->value = s;
    }
    else
        v = NULL;

    /* look if a t_tag matching key already exist */
    len = strlen(key);
    kinq = NULL;
    TAILQ_FOREACH_REVERSE(t, T->tags, t_tag_q, next) {
        if (t->keylen == len && strcasecmp(key, t->key) == 0) {
            kinq = t;
            break;
        }
    }

    if (kinq == NULL) {
    /* doesn't exist, create a new t_tag (delete) */
        kinq = xmalloc(sizeof(struct t_tag) + sizeof(struct t_tagv_q) + len + 1);
        TAILQ_INSERT_TAIL(T->tags, kinq, next);
        T->tcount++;

        kinq->values = (struct t_tagv_q *)(kinq + 1);
        TAILQ_INIT(kinq->values);
        kinq->vcount = 0;

        kinq->keylen = len;
        s = (char *)(kinq->values + 1);
        (void)strlcpy(s, key, len + 1);
        kinq->key = s;

    }

    if (v) {
        TAILQ_INSERT_TAIL(kinq->values, v, next);
        kinq->vcount++;
    }
}


struct t_tag *
t_taglist_search(const struct t_taglist *restrict T, const char *restrict key)
{
    size_t len;
    struct t_tag  *t, *target;

    assert_not_null(T);
    assert_not_null(key);

    len = strlen(key);
    target = NULL;
    TAILQ_FOREACH(t, T->tags, next) {
        if (len == t->keylen && strcasecmp(t->key, key) == 0) {
            target = t;
            break;
        }
    }

    return (target);
}


void
t_taglist_destroy(const struct t_taglist *Tconst)
{
    struct t_tag  *t;
    struct t_tagv *v;
    struct t_taglist *T;

    T = (struct t_taglist *)Tconst; /* break const */

    assert_not_null(T);

    while (!TAILQ_EMPTY(T->tags)) {
        t = TAILQ_FIRST(T->tags);
        TAILQ_REMOVE(T->tags, t, next);
        while (!TAILQ_EMPTY(t->values)) {
            v = TAILQ_FIRST(t->values);
            TAILQ_REMOVE(t->values, v, next);
            freex(v);
        }
        freex(t);
    }
    t_error_clear(T);
    freex(T);
}

