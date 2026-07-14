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
    SHUJsonType_Null,
} SHUJsonType;

typedef struct SHUJsonArrayStatic
{
    SHUSliceView data;
    SHUJsonType type;
} SHUJsonArrayStatic;

typedef struct SHUJsonArrayDynamic
{
    struct
    {
        void *data;
        SHUJsonType type;
    } *elements;
    usz count;
} SHUJsonArrayDynamic;

typedef struct SHUJson
{
    SHUSliceView key;
    SHUJsonType type;
    union
    {
        struct
        {
            struct SHUJson *children;
            usz count;
        } object;
        SHUSliceView string;
        SHUC_JSON_INTEGER_TYPE integer;
        SHUC_JSON_DECIMAL_TYPE decimal;
        SHUC_JSON_BOOLEAN_TYPE boolean;
        SHUJsonArrayStatic arrayStatic;
        SHUJsonArrayDynamic arrayDynamic;
    } data;
} SHUJson;

/// @brief Gets the result of the last executed function.
/// @return Result of the last executed shujsn function.
SHUResult SHU_JsonGetLastResult(void);

/// !!! DO NOT USE THIS FUNCTION ALONE, USE `json` MACRO INSTEAD !!!
const SHUJson *SHU_JsonObject(const char *key);

/// @brief
/// @param key Key of the Json object member. Left side of `:`.
/// @param onFail Code section to call if this operation fails. Do not forget semicolons. (eg. SHU_LogError(SHU_JsonGetLastResult(), "failed to parse file 'shujsn.json'");)
/// @return
/// @note You can retrieve the error code by calling function `SHU_JsonGetLastResult`.
#define json(key, ...)   \
    SHU_JsonObject(key); \
    SHUM_JSON_CHECK(key, ##__VA_ARGS__)

/// !!! DO NOT USE THIS FUNCTION ALONE, USE `jsonString` MACRO INSTEAD !!!
SHUSliceView SHU_JsonString(const char *key);

/// @brief
/// @param key Key of the Json object member. Left side of `:`.
/// @param onFail Code section to call if this operation fails. Do not forget semicolons. (eg. SHU_LogError(SHU_JsonGetLastResult(), "failed to parse file 'shujsn.json'");)
/// @return
/// @note You can retrieve the error code by calling function `SHU_JsonGetLastResult`.
#define jsonString(key, ...) \
    SHU_JsonString(key);     \
    SHUM_JSON_CHECK(key, ##__VA_ARGS__)

/// !!! DO NOT USE THIS FUNCTION ALONE, USE `jsonInteger` MACRO INSTEAD !!!
SHUC_JSON_INTEGER_TYPE SHU_JsonInteger(const char *key);

/// @brief
/// @param key Key of the Json object member. Left side of `:`.
/// @param onFail Code section to call if this operation fails. Do not forget semicolons. (eg. SHU_LogError(SHU_JsonGetLastResult(), "failed to parse file 'shujsn.json'");)
/// @return
/// @note You can retrieve the error code by calling function `SHU_JsonGetLastResult`.
#define jsonInteger(key, ...) \
    SHU_JsonInteger(key);     \
    SHUM_JSON_CHECK(key, ##__VA_ARGS__)

/// !!! DO NOT USE THIS FUNCTION ALONE, USE `jsonDecimal` MACRO INSTEAD !!!
SHUC_JSON_DECIMAL_TYPE SHU_JsonDecimal(const char *key);

/// @brief
/// @param key Key of the Json object member. Left side of `:`.
/// @param onFail Code section to call if this operation fails. Do not forget semicolons. (eg. SHU_LogError(SHU_JsonGetLastResult(), "failed to parse file 'shujsn.json'");)
/// @return
/// @note You can retrieve the error code by calling function `SHU_JsonGetLastResult`.
#define jsonDecimal(key, ...) \
    SHU_JsonDecimal(key);     \
    SHUM_JSON_CHECK(key, ##__VA_ARGS__)

/// !!! DO NOT USE THIS FUNCTION ALONE, USE `jsonBoolean` MACRO INSTEAD !!!
SHUC_JSON_BOOLEAN_TYPE SHU_JsonBoolean(const char *key);

/// @brief
/// @param key Key of the Json object member. Left side of `:`.
/// @param onFail Code section to call if this operation fails. Do not forget semicolons. (eg. SHU_LogError(SHU_JsonGetLastResult(), "failed to parse file 'shujsn.json'");)
/// @return
/// @note You can retrieve the error code by calling function `SHU_JsonGetLastResult`.
#define jsonBoolean(key, ...) \
    SHU_JsonBoolean(key);     \
    SHUM_JSON_CHECK(key, ##__VA_ARGS__)

/// !!! DO NOT USE THIS FUNCTION ALONE, USE `jsonArrayStatic` MACRO INSTEAD !!!
SHUJsonArrayStatic SHU_JsonArrayStatic(const char *key);

/// @brief
/// @param key Key of the Json object member. Left side of `:`.
/// @param onFail Code section to call if this operation fails. Do not forget semicolons. (eg. SHU_LogError(SHU_JsonGetLastResult(), "failed to parse file 'shujsn.json'");)
/// @return
/// @note You can retrieve the error code by calling function `SHU_JsonGetLastResult`.
#define jsonArrayStatic(key, ...) \
    SHU_JsonArrayStatic(key);     \
    SHUM_JSON_CHECK(key, ##__VA_ARGS__)

/// !!! DO NOT USE THIS FUNCTION ALONE, USE `jsonArrayDynamic` MACRO INSTEAD !!!
SHUJsonArrayDynamic SHU_JsonArrayDynamic(const char *key);

/// @brief
/// @param key Key of the Json object member. Left side of `:`.
/// @param onFail Code section to call if this operation fails. Do not forget semicolons. (eg. SHU_LogError(SHU_JsonGetLastResult(), "failed to parse file 'shujsn.json'");)
/// @return
/// @note You can retrieve the error code by calling function `SHU_JsonGetLastResult`.
#define jsonArrayDynamic(key, ...) \
    SHU_JsonArrayDynamic(key);     \
    SHUM_JSON_CHECK(key, ##__VA_ARGS__)

// todo iterator for dynamic array

#pragma endregion Declarations

#pragma region Definitions

#ifdef SHU_IMPLEMENTATION

#pragma region Internals

static struct
{
    FILE *file;
    SHUResult lastResult;
    SHUJson *objects;
    usz objectCount;
} SHUJSN = {0};

static SHUJsonType SHUI_JsonGetTypeOfValue(SHUSliceView valueString)
{
    for (usz i = 0; i < valueString.size; i++)
    {
        char character = *(char *)(valueString.data + i);
        switch (character)
        {
        case '\"':
            break;
        case '.':
            break;
        default:
            break;
        }
    }

    if (strncmp((const char *)valueString.data, "true", valueString.size) == 0)
    {
        goto boolean;
    }

    goto final;

    // validation
string:
integer:
decimal:
boolean:
array:
arrayStatic:
arrayDynamic:
null:

final:
    SHUJSN.lastResult = SHUResult_Ok;
}

#pragma endregion Internals

SHUResult SHU_JsonGetLastResult(void)
{
    return SHUJSN.lastResult;
}

const SHUJson *SHU_JsonObject(const char *key)
{
    SHU_CheckPanicNullPointer(key);

    if (SHUJSN.file == NULL) // root object
    {
        SHUJSN.file = fopen(key, "r");
        if (SHUJSN.file == NULL)
        {
            SHUJSN.lastResult = SHUResult_ErrNotFound;
            return NULL;
        }
    }

    // todo parse with helper functions
    // todo close root object

    SHUJSN.lastResult = SHUResult_Ok;
}

SHUSliceView SHU_JsonString(const char *key)
{
    SHU_CheckPanicNullPointer(key);
    SHUJSN.lastResult = SHUResult_Ok;
}

SHUC_JSON_INTEGER_TYPE SHU_JsonInteger(const char *key)
{
    SHU_CheckPanicNullPointer(key);
    SHUJSN.lastResult = SHUResult_Ok;
}

SHUC_JSON_DECIMAL_TYPE SHU_JsonDecimal(const char *key)
{
    SHU_CheckPanicNullPointer(key);
    SHUJSN.lastResult = SHUResult_Ok;
}

SHUC_JSON_BOOLEAN_TYPE SHU_JsonBoolean(const char *key)
{
    SHU_CheckPanicNullPointer(key);
    SHUJSN.lastResult = SHUResult_Ok;
}

SHUJsonArrayStatic SHU_JsonArrayStatic(const char *key)
{
    SHU_CheckPanicNullPointer(key);
    SHUJSN.lastResult = SHUResult_Ok;
}

SHUJsonArrayDynamic SHU_JsonArrayDynamic(const char *key)
{
    SHU_CheckPanicNullPointer(key);
    SHUJSN.lastResult = SHUResult_Ok;
}

#endif // SHU_IMPLEMENTATION

#pragma endregion Definitions
