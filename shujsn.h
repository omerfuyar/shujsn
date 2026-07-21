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

#ifndef SHUC_JSON_NUMBER_BUFFER
#define SHUC_JSON_NUMBER_BUFFER 64
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
    SHUSlice data; // todo make view
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
    SHUSlice key; // todo make view
    SHUJsonType type;
    union
    {
        struct
        {
            struct SHUJson *children;
            usz count;
        } object;
        SHUSlice string; // todo make view
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
    SHUResult lastResult;
    SHUJson *nodes;
    usz nodeCount;

    struct
    {
        SHUJson **data;
        usz stackSize;
        usz depth;
    } stack;
} SHUJSN = {0};

static bool SHUI_SliceAreSame(SHUSliceView sliceA, SHUSliceView sliceB)
{
    if (sliceA.size != sliceB.size)
    {
        return false;
    }

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

// returns the distance from current pointer of slice to end of whitespace according to json standard.
static usz SHUI_SkipWhiteSpace(SHUSliceView string)
{
    usz distance = 0;

    for (usz i = 0; i < string.size; i++)
    {
        char character = *(char *)(string.data);
        switch (character)
        {
        case ' ':
            return distance++;
        case '\n':
            return distance++;
        case '\r':
            return distance++;
        case '\t':
            return distance++;
        default:
            return distance;
        }
    }

    return distance; // distance == string.size
}

// ignores .key member
static SHUResult SHUI_JsonParseObject(SHUJson *retObject, SHUSliceView valueString)
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
        retObject->type = SHUJsonType_Boolean;
        retObject->value.boolean = true;
        return SHUResult_Ok;
    }
    else if (SHUI_SliceAreSame(valueString, csv(cs("false", 5))))
    {
        retObject->type = SHUJsonType_Boolean;
        retObject->value.boolean = false;
        return SHUResult_Ok;
    }
    else if (SHUI_SliceAreSame(valueString, csv(cs("null", 4))))
    {
        retObject->type = SHUJsonType_Null;
        return SHUResult_Ok;
    }

    return SHUResult_ErrBadData;

object:
    // todo fill retObject
    // todo recurse

    return SHUResult_Ok;

string:
    retObject->type = SHUJsonType_String;
    retObject->value.string.data = (char *)(valueString.data) + 1;
    retObject->value.string.size = valueString.size - 2;
    return SHUResult_Ok;

number:
    errno = 0;
    char *strEnd = NULL;
    char numberBuffer[SHUC_JSON_NUMBER_BUFFER] = {0};

    usz limitSize = SHUMin(valueString.size, SHUC_JSON_NUMBER_BUFFER - 1);
    memcpy(numberBuffer, valueString.data, limitSize);
    numberBuffer[limitSize] = '\0';

    for (usz i = 1; i < valueString.size; i++)
    {
        char character = *(char *)(valueString.data + i);
        if (character == '.' || character == 'e')
        {
            goto decimal;
        }
    } // fallback to integer
integer:
    SHUC_JSON_INTEGER_TYPE returnInt = (SHUC_JSON_INTEGER_TYPE)strtoll(numberBuffer, *strEnd, 10);

    if (errno != 0)
    {
        return SHUResult_ErrBadData;
    }

    if (*strEnd != '\0')
    {
        return SHUResult_ErrBadData;
    }

    retObject->type = SHUJsonType_Integer;
    retObject->value.integer = returnInt;
    return SHUResult_Ok;

decimal:
    SHUC_JSON_DECIMAL_TYPE returnDcm = (SHUC_JSON_DECIMAL_TYPE)strtod(numberBuffer, *strEnd);

    if (errno != 0)
    {
        return SHUResult_ErrBadData;
    }

    if (*strEnd != '\0')
    {
        return SHUResult_ErrBadData;
    }

    retObject->type = SHUJsonType_Decimal;
    retObject->value.decimal = returnDcm;
    return SHUResult_Ok;

array:

arrayStatic:
    retObject->type = SHUJsonType_ArrayStatic;
    retObject->value.arrayStatic = (SHUJsonArrayStatic){};
    return SHUResult_Ok;
arrayDynamic:
    retObject->type = SHUJsonType_ArrayDynamic;
    retObject->value.arrayDynamic = (SHUJsonArrayDynamic){};
    return SHUResult_Ok;
}

static SHUResult SHUI_JsonParseFile(const char *fileName)
{
    FILE *jsonFile = fopen(fileName, "rb");

    if (jsonFile == NULL)
    {
        return SHUResult_ErrNotFound;
    }

    if (fseek(jsonFile, 0, SEEK_END) != 0)
    {
        fclose(jsonFile);
        return SHUResult_ErrInternal;
    }

    SHUSlice jsonFileString = cs0;

    jsonFileString.size = ftell(jsonFile);
    if (jsonFileString.size < 0)
    {
        fclose(jsonFile);
        return SHUResult_ErrInternal;
    }

    rewind(jsonFile);

    jsonFileString.data = malloc(jsonFileString.size + 1);
    if (jsonFileString.data == NULL)
    {
        fclose(jsonFile);
        return SHUResult_ErrAllocation;
    }

    size_t bytesRead = fread(jsonFileString.data, 1, jsonFileString.size, jsonFile);
    if (bytesRead < jsonFileString.size && ferror(jsonFile))
    {
        free(jsonFileString.data);
        fclose(jsonFile);
        return SHUResult_ErrInternal;
    }
    fclose(jsonFile);

    ((char *)jsonFileString.data)[jsonFileString.size] = '\0';

    // todo parse all objects

    free(jsonFileString.data);
}

static void SHUI_JsonFree()
{
}

#pragma endregion Internals

SHUResult SHU_JsonGetLastResult(void)
{
    return SHUJSN.lastResult;
}

SHUJson SHU_JsonObject(const char *key)
{
    SHU_CheckPanicNullPointer(key);

    if (SHUJSN.stack.depth == 0) // root object
    {
    }

    // todo parse with helper functions
    // todo close root object

    SHUJSN.stack.depth++;

    SHUJSN.lastResult = SHUResult_Ok;
}

void SHU_JsonObjectDestroy(SHUJson object)
{
    if (SHUJSN.stack.depth == 1)
    {
        SHUI_JsonFree();
    }

    SHUJSN.stack.depth--;

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
