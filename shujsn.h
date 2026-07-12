#pragma once

#ifndef SHU_HEADER
#ifdef SHU
#include SHU
#else
#include "../shu/shu.h"
#endif
#endif

#pragma region Macros

#ifndef SHUC_JSON_DECIMAL_TYPE
#define SHUC_JSON_DECIMAL_TYPE f64
#endif

#ifndef SHUC_JSON_INTEGER_TYPE
#define SHUC_JSON_INTEGER_TYPE i64
#endif

#ifndef SHUC_JSON_BOOLEAN_TYPE
#define SHUC_JSON_BOOLEAN_TYPE bool
#endif

#define SHUM_JSON_CHECK(key, ...)                                                     \
    if (SHU_JsonGetLastResult())                                                      \
    {                                                                                 \
        if (0 __VA_OPT__(+1))                                                         \
        {                                                                             \
            __VA_ARGS__                                                               \
        }                                                                             \
        else                                                                          \
        {                                                                             \
            SHU_LogError(SHU_JsonGetLastResult(), "Failed to get JSON element" #key); \
        }                                                                             \
    }

#pragma endregion Macros

#pragma region Declarations

typedef enum SHUJsonType
{
    SHUJsonType_Object,
    SHUJsonType_String,
    SHUJsonType_Integer,
    SHUJsonType_Decimal,
    SHUJsonType_Boolean,
    SHUJsonType_ArrayStatic,
    SHUJsonType_ArrayDynamic,
} SHUJsonType;

typedef struct SHUJsonArrayStatic
{
    SHUSliceView data;
    const usz typeSize;
} SHUJsonArrayStatic;

typedef struct SHUJsonArrayDynamic
{

} SHUJsonArrayDynamic;

typedef union SHUJson
{
    SHUJson *object;
    SHUSlice string;
    SHUC_JSON_INTEGER_TYPE integer;
    SHUC_JSON_DECIMAL_TYPE decimal;
    SHUC_JSON_BOOLEAN_TYPE boolean;
    SHUJsonArrayStatic staticArray;
} SHUJson;

SHUResult SHU_JsonGetLastResult(void);

#define json(...)

const SHUJson *SHU_JsonObject(const char *key);

#define jsonObject(key, ...) \
    SHU_JsonObject(key);     \
    SHUM_JSON_CHECK(key, __VA_ARGS__)

SHUSliceView SHU_JsonString(const char *key);

#define jsonString(key, ...) \
    SHU_JsonString(key);     \
    SHUM_JSON_CHECK(key, __VA_ARGS__)

SHUC_JSON_INTEGER_TYPE SHU_JsonInteger(const char *key);

#define jsonInteger(key, ...) \
    SHU_JsonInteger(key);     \
    SHUM_JSON_CHECK(key, __VA_ARGS__)

SHUC_JSON_DECIMAL_TYPE SHU_JsonDecimal(const char *key);

#define jsonDecimal(key, ...) \
    SHU_JsonDecimal(key);     \
    SHUM_JSON_CHECK(key, __VA_ARGS__)

SHUC_JSON_BOOLEAN_TYPE SHU_JsonBoolean(const char *key);

#define jsonBoolean(key, ...) \
    SHU_JsonBoolean(key);     \
    SHUM_JSON_CHECK(key, __VA_ARGS__)

SHUJsonArrayStatic SHU_JsonArrayStatic(const char *key);

#define jsonArrayStatic(key, ...) \
    SHU_JsonArrayStatic(key);     \
    SHUM_JSON_CHECK(key, __VA_ARGS__)

#define jsonArrayDynamic(...)

#pragma endregion Declarations

#pragma region Definitions

#ifdef SHU_IMPLEMENTATION

static struct
{
    SHUResult lastResult;
    SHUJson *objects;
} SHUJSN = {0};

SHUResult SHU_JsonGetLastResult(void)
{
    return SHUJSN.lastResult;
}

const SHUJson *SHU_JsonObject(const char *key)
{
}

SHUSliceView SHU_JsonString(const char *key)
{
}

SHUC_JSON_INTEGER_TYPE SHU_JsonInteger(const char *key)
{
}

SHUC_JSON_DECIMAL_TYPE SHU_JsonDecimal(const char *key)
{
}

SHUC_JSON_BOOLEAN_TYPE SHU_JsonBoolean(const char *key)
{
}

SHUJsonArrayStatic SHU_JsonArrayStatic(const char *key)
{
}

#endif // SHU_IMPLEMENTATION

#pragma endregion Definitions
