#define SHU_IMPLEMENTATION
#include "shujsn.h"

int main(int argc, char **argv)
{
    json("shujsn.json", SHU_LogError(SHUResult_ErrFile, "failed to parse file 'shujsn.json'");)
    {
        jsonObject(NULL, root);

        jsonString("foo", bar, SHU_LogWarning("This would panic otherwise."););
        jsonString("myString", myString);
        jsonDecimal("floating", testDouble);
        jsonInteger("negativeNum", testInt);
        jsonBoolean("is_active", testBool);
        jsonArrayStatic("arrayOfNumbers", I64, myArr);
        jsonArrayDynamic("mixedArray", arrElement) // iterates over elements
        {
            switch (arrElement->type)
            {
            case:
                break;
            default:
                break;
            }
        }

        json("nested")
        {
            jsonObject("metadata", metadata);
        }
    }
}