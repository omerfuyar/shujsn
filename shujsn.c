#define SHU_IMPLEMENTATION
#include "shujsn.h"

int main(int argc, char **argv)
{
    // these values will keep their data after json is freed
    f64 testF = 0.0f;
    i64 testI = 0;
    SHUSlice testS = cs0;

    json("shujsn.json", SHU_LogError(SHU_JsonGetLastResult(), "failed to parse file 'shujsn.json'");)
    { // file allocated here

        // these values valid until free, garbage after free
        SHUSliceView bar = jsonString("foo", SHU_LogWarning("This would panic otherwise."););
        f64 foo = jsonDecimal("negativeFloating");

        // these values copied to buffer that will outlive json lifetime
        SHUSliceView tempString = jsonString("myString");
        testS.size = tempString.size;
        testS.data = malloc(testS.size);
        memcpy(testS.data, tempString.data, testS.size);

        testF = jsonDecimal("floating");
        testI = jsonInteger("negativeNum");

        SHUC_JSON_BOOLEAN_TYPE testBool = jsonBoolean("is_active");

        SHUJsonArrayStatic myArr = jsonArrayStatic("arrayOfNumbers");

        SHUJsonArrayDynamic myMixArr = jsonArrayDynamic("mixedArray");

        for (usz i = 0; i < myMixArr.count; i++)
        {
            switch (myMixArr.elements[i].type)
            {
            case SHUJsonType_Integer:
                i64 arrInt = *(i64 *)myMixArr.elements[i].data;
                break;
            default:
                break;
            }
        }

        json("nested")
        {
            const SHUJson *nullValue = json("metadata"); // todo free stack even if there is no braces
        }
    } // file freed here
}