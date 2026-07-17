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
    SHUJsonType_Invalid,
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
    // struct SHUJson *parent;
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
    } value;
} SHUJson;

/// @brief Gets the result of the last executed function.
/// @return Result of the last executed shujsn function.
SHUResult SHU_JsonGetLastResult(void);

/// !!! DO NOT USE THIS FUNCTION ALONE, USE `json` MACRO INSTEAD !!!
SHUJson SHU_JsonObject(const char *key);

/// !!! DO NOT USE THIS FUNCTION, USE `json` MACRO WITH BRACES INSTEAD !!!
void SHU_JsonObjectDestroy(SHUJson object);

/// @brief Explores a Json object inside the current object. Searches for a file if the object stack is empty.
/// @param key Key of the Json object member. Left side of `:`. Cannot be NULL.
/// @param onFail Code section to call if this operation fails. Panics on fail if this section is empty. Do not forget semicolons. (eg. SHU_LogError(SHU_JsonGetLastResult(), "failed to parse file 'shujsn.json'");)
/// @note You can retrieve the error code by calling function `SHU_JsonGetLastResult`.
#define json(key, ...)                                   \
    SHUJson __tempJsonObject = SHU_JsonObject(key);      \
    SHUM_JSON_CHECK(key, ##__VA_ARGS__)                  \
    for (; __tempJsonObject.type != SHUJsonType_Invalid; \
         SHU_JsonObjectDestroy(__tempJsonObject), __tempJsonObject.type = SHUJsonType_Invalid)

/// @brief Gets the object with specified key. Used for all type of members, not only objects with braces. But its easier to use specific typed functions if you know the type you are looking for.
/// @param key Key of the Json object member. Left side of `:`. Cannot be NULL.
/// @param onFail Code section to call if this operation fails. Panics on fail if this section is empty. Do not forget semicolons. (eg. SHU_LogError(SHU_JsonGetLastResult(), "failed to parse file 'shujsn.json'");)
/// @return The object struct itself.
/// @note You can retrieve the error code by calling function `SHU_JsonGetLastResult`.
#define jsonObject(key, ...) \
    SHU_JsonObject(key);     \
    SHUM_JSON_CHECK(key, ##__VA_ARGS__)

/// !!! DO NOT USE THIS FUNCTION ALONE, USE `jsonString` MACRO INSTEAD !!!
SHUSliceView SHU_JsonString(const char *key);

/// @brief Gets the object with specified key as string, fails if it's not a string.
/// @param key Key of the Json object member. Left side of `:`. Cannot be NULL.
/// @param onFail Code section to call if this operation fails. Panics on fail if this section is empty. Do not forget semicolons. (eg. SHU_LogError(SHU_JsonGetLastResult(), "failed to parse file 'shujsn.json'");)
/// @return The slice view to the string.
/// @note You can retrieve the error code by calling function `SHU_JsonGetLastResult`.
#define jsonString(key, ...) \
    SHU_JsonString(key);     \
    SHUM_JSON_CHECK(key, ##__VA_ARGS__)

/// !!! DO NOT USE THIS FUNCTION ALONE, USE `jsonInteger` MACRO INSTEAD !!!
SHUC_JSON_INTEGER_TYPE SHU_JsonInteger(const char *key);

/// @brief Gets the object with specified key as integer, fails if it's not an integer.
/// @param key Key of the Json object member. Left side of `:`. Cannot be NULL.
/// @param onFail Code section to call if this operation fails. Panics on fail if this section is empty. Do not forget semicolons. (eg. SHU_LogError(SHU_JsonGetLastResult(), "failed to parse file 'shujsn.json'");)
/// @return The integer itself. See also macro `SHUC_JSON_INTEGER_TYPE`.
/// @note You can retrieve the error code by calling function `SHU_JsonGetLastResult`.
#define jsonInteger(key, ...) \
    SHU_JsonInteger(key);     \
    SHUM_JSON_CHECK(key, ##__VA_ARGS__)

/// !!! DO NOT USE THIS FUNCTION ALONE, USE `jsonDecimal` MACRO INSTEAD !!!
SHUC_JSON_DECIMAL_TYPE SHU_JsonDecimal(const char *key);

/// @brief Gets the object with specified key as decimal number, fails if it's not a decimal number.
/// @param key Key of the Json object member. Left side of `:`. Cannot be NULL.
/// @param onFail Code section to call if this operation fails. Panics on fail if this section is empty. Do not forget semicolons. (eg. SHU_LogError(SHU_JsonGetLastResult(), "failed to parse file 'shujsn.json'");)
/// @return The decimal number itself. See also macro `SHUC_JSON_DECIMAL_TYPE`.
/// @note You can retrieve the error code by calling function `SHU_JsonGetLastResult`.
#define jsonDecimal(key, ...) \
    SHU_JsonDecimal(key);     \
    SHUM_JSON_CHECK(key, ##__VA_ARGS__)

/// !!! DO NOT USE THIS FUNCTION ALONE, USE `jsonBoolean` MACRO INSTEAD !!!
SHUC_JSON_BOOLEAN_TYPE SHU_JsonBoolean(const char *key);

/// @brief Gets the object with specified key as boolean, fails if it's not a boolean.
/// @param key Key of the Json object member. Left side of `:`. Cannot be NULL.
/// @param onFail Code section to call if this operation fails. Panics on fail if this section is empty. Do not forget semicolons. (eg. SHU_LogError(SHU_JsonGetLastResult(), "failed to parse file 'shujsn.json'");)
/// @return The boolean itself. See also macro `SHUC_JSON_BOOLEAN_TYPE`.
/// @note You can retrieve the error code by calling function `SHU_JsonGetLastResult`.
#define jsonBoolean(key, ...) \
    SHU_JsonBoolean(key);     \
    SHUM_JSON_CHECK(key, ##__VA_ARGS__)

/// !!! DO NOT USE THIS FUNCTION ALONE, USE `jsonArrayStatic` MACRO INSTEAD !!!
SHUJsonArrayStatic SHU_JsonArrayStatic(const char *key);

/// @brief Gets the object with specified key as static array (array that all of its members are the same type), fails if it's not a static array.
/// @param key Key of the Json object member. Left side of `:`. Cannot be NULL.
/// @param onFail Code section to call if this operation fails. Panics on fail if this section is empty. Do not forget semicolons. (eg. SHU_LogError(SHU_JsonGetLastResult(), "failed to parse file 'shujsn.json'");)
/// @return The static array struct itself.
/// @note You can retrieve the error code by calling function `SHU_JsonGetLastResult`.
#define jsonArrayStatic(key, ...) \
    SHU_JsonArrayStatic(key);     \
    SHUM_JSON_CHECK(key, ##__VA_ARGS__)

/// !!! DO NOT USE THIS FUNCTION ALONE, USE `jsonArrayDynamic` MACRO INSTEAD !!!
SHUJsonArrayDynamic SHU_JsonArrayDynamic(const char *key);

/// @brief Gets the object with specified key as dynamic array (array that its members are different types), fails if it's not a dynamic array. See also `jsonArrayDynamicIterate`.
/// @param key Key of the Json object member. Left side of `:`. Cannot be NULL.
/// @param onFail Code section to call if this operation fails. Panics on fail if this section is empty. Do not forget semicolons. (eg. SHU_LogError(SHU_JsonGetLastResult(), "failed to parse file 'shujsn.json'");)
/// @return The dynamic array struct itself.
/// @note You can retrieve the error code by calling function `SHU_JsonGetLastResult`.
#define jsonArrayDynamic(key, ...) \
    SHU_JsonArrayDynamic(key);     \
    SHUM_JSON_CHECK(key, ##__VA_ARGS__)

/// @brief Iterates over a dynamic array, assigning an object on each iteration.
/// @param array Array to iterate over.
/// @param currentObject The current object struct, ignoring the key member.
#define jsonArrayDynamicIterate(array, currentObject) // todo

#pragma endregion Declarations

#pragma region Definitions

#ifdef SHU_IMPLEMENTATION

#pragma region Internals

static struct
{
    FILE *file;
    SHUResult lastResult;
    SHUJson *objects; // malloced
    usz currentDepth;
} SHUJSN = {0};

bool SHUI_SliceAreSame(SHUSliceView sliceA, SHUSliceView sliceB)
{
    usz cap = SHUMin(sliceA.size, sliceB.size);
    for (usz i = 0; i < cap; i++)
    {
        u8 byteA = *(u8 *)(sliceA.data + i);
        u8 byteB = *(u8 *)(sliceB.data + i);

        if (byteA != byteB)
        {
            return false;
        }
    }

    return true;
}

static SHUJson SHUI_JsonParseObject(SHUSliceView keyString, SHUSliceView valueString)
{
    char firstCharacter = *(char *)(valueString.data);
    switch (firstCharacter)
    {
    case '{':
        goto object;
    case '\"':
        goto string;
    case '[':
        goto array;
    }

    if ((firstCharacter >= '0' && firstCharacter <= '9') || firstCharacter == '-')
    {
        goto number;
    }

    if (SHUI_SliceAreSame(valueString, csv(cs("true", 4))))
    {
        return (SHUJson){.key = keyString, .type = SHUJsonType_Boolean, .value.boolean = true};
    }
    else if (SHUI_SliceAreSame(valueString, csv(cs("false", 5))))
    {
        return (SHUJson){.key = keyString, .type = SHUJsonType_Boolean, .value.boolean = false};
    }
    else if (SHUI_SliceAreSame(valueString, csv(cs("null", 4))))
    {
        return (SHUJson){.key = keyString, .type = SHUJsonType_Null, .value = {0}};
    }

    return (SHUJson){.key = csv(cs0), .type = SHUJsonType_Invalid, .value = {0}};

object:
string:
number:
    for (usz i = 1; i < valueString.size; i++)
    {
        char character = *(char *)(valueString.data + i);
        if (character != '.' && character < '0' && character > '9') // todo exponent 'e'
        {
        }
    }
integer:
decimal:
array:
arrayStatic:
arrayDynamic:
}

#pragma endregion Internals

SHUResult SHU_JsonGetLastResult(void)
{
    return SHUJSN.lastResult;
}

SHUJson SHU_JsonObject(const char *key)
{
    SHU_CheckPanicNullPointer(key);

    if (SHUJSN.file == NULL) // root object
    {
        SHUJSN.file = fopen(key, "r");
        if (SHUJSN.file == NULL)
        {
            SHUJSN.lastResult = SHUResult_ErrNotFound;
            return (SHUJson){0};
        }
    }

    // todo parse with helper functions
    // todo close root object

    SHUJSN.lastResult = SHUResult_Ok;
}

void SHU_JsonObjectDestroy(SHUJson object)
{
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
