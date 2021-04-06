#ifndef SLOWJSON_H__
#define SLOWJSON_H__

typedef enum
{
    SLOW_NULL,
    SLOW_FALSE,
    SLOW_TRUE,
    SLOW_NUMBER,
    SLOW_STRING,
    SLOW_ARRAY,
    SLOW_OBJECT
} slow_type;

typedef struct
{
    slow_type type;
} slow_value;

enum
{
    SLOW_PARSE_OK = 0,
    SLOW_PARSE_EXPECT_VALUE,
    SLOW_PARSE_INVALID_VALUE,
    SLOW_PARSE_ROOT_NOT_SINGULAR
};

// 解析JSON
int slow_parse(slow_value *v, const char *json);

// 访问结果函数
slow_type slow_get_type(const slow_value *v);

#endif /* SLOWJSON_H__ */
