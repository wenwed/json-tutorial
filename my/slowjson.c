#include "slowjson.h"
#include <assert.h> /* assert() */
#include <stdlib.h> /* NULL */

#define EXPECT(c, ch)             \
    do                            \
    {                             \
        assert(*c->json == (ch)); \
        c->json++;                \
    } while (0)

typedef struct
{
    const char *json;
} slow_context;

// 去掉空白
static void slow_parse_whitespace(slow_context *c)
{
    const char *p = c->json;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
        p++;
    c->json = p;
}

// 解析null
static int slow_parse_null(slow_context *c, slow_value *v)
{
    EXPECT(c, 'n');
    if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l')
        return SLOW_PARSE_INVALID_VALUE;
    c->json += 3;
    v->type = SLOW_NULL;
    return SLOW_PARSE_OK;
}

// 解析true
static int slow_parse_true(slow_context *c, slow_value *v)
{
    EXPECT(c, 't');
    if (c->json[0] != 'r' || c->json[1] != 'u' || c->json[2] != 'e')
        return SLOW_PARSE_INVALID_VALUE;
    c->json += 3;
    v->type = SLOW_TRUE;
    return SLOW_PARSE_OK;
}

// 解析false
static int slow_parse_false(slow_context *c, slow_value *v)
{
    EXPECT(c, 'f');
    if (c->json[0] != 'a' || c->json[1] != 'l' || c->json[2] != 's' || c->json[3] != 'e')
        return SLOW_PARSE_INVALID_VALUE;
    c->json += 4;
    v->type = SLOW_FALSE;
    return SLOW_PARSE_OK;
}

static int slow_parse_value(slow_context *c, slow_value *v)
{
    switch (*c->json)
    {
    case 'n':
        return slow_parse_null(c, v);
    case 't':
        return slow_parse_true(c, v);
    case 'f':
        return slow_parse_false(c, v);
    case '\0':
        return SLOW_PARSE_EXPECT_VALUE;
    default:
        return SLOW_PARSE_INVALID_VALUE;
    }
}

int slow_parse(slow_value *v, const char *json)
{
    slow_context c;
    assert(v != NULL);
    c.json = json;
    v->type = SLOW_NULL;
    slow_parse_whitespace(&c);
    return slow_parse_value(&c, v);
}

slow_type slow_get_type(const slow_value *v)
{
    assert(v != NULL);
    return v->type;
}
