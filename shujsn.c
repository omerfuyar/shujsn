#define SHU_IMPLEMENTATION
#include "shujsn.h"

int main(int argc, char **argv)
{
    // these values will keep their data after json is freed
    f64 testF = 0.0f;
    i64 testI = 0;
    SHUSlice testS = cs0;

    json("shujsn.json", SHU_LogError(SHUResult_ErrFile, "failed to parse file 'shujsn.json'");)
    { // file allocated here

        // these values valid until free, garbage afterwards
        const SHUJson *root = jsonObject(NULL);
        SHUSliceView bar = jsonString("foo", SHU_LogWarning("This would panic otherwise."););

        // these values copied to buffer before starting json
        SHUSliceView tempString = jsonString("myString");
        testS.size = tempString.size;
        testS.data = malloc(testS.size);
        memcpy(testS.data, tempString.data, testS.size);

        testF = jsonDecimal("floating");
        testI = jsonInteger("negativeNum");

        SHUC_JSON_BOOLEAN_TYPE testBool = jsonBoolean("is_active");

        SHUSliceView myArr = jsonArrayStatic("arrayOfNumbers", i64);

        jsonArrayDynamic("mixedArray") // iterates over elements
        {
            switch (arrElementType)
            {
            case SHUJsonType_Integer:
                i64 arrInt = jsonInteger(NULL);
                break;
            default:
                break;
            }
        }

        json("nested")
        {
            const SHUJson *nullValue = jsonObject("metadata");
        }
    } // file freed here
}