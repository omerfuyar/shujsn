#pragma once

#ifndef SHU_HEADER
#ifdef SHU
#include SHU
#else
#include "../shu/shu.h"
#endif
#endif

#define json(...)
#define jsonObject(...)
#define jsonString(...)
#define jsonInteger(...)
#define jsonDecimal(...)
#define jsonBoolean(...)
#define jsonArrayStatic(...)
#define jsonArrayDynamic(...)

#pragma region Macros

#ifndef SHUC_JSON_DECIMAL_TYPE
#define SHUC_JSON_DECIMAL_TYPE f64
#endif

#ifndef SHUC_JSON_INTEGER_TYPE
#define SHUC_JSON_INTEGER_TYPE i64
#endif

#pragma endregion Macros

#pragma region Declarations

typedef struct SHUJson
{

} SHUJson;

#pragma endregion Declarations

#pragma region Definitions

#ifdef SHU_IMPLEMENTATION
#endif // SHU_IMPLEMENTATION

#pragma endregion Definitions
