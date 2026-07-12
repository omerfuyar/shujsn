#define SHU_IMPLEMENTATION
#include "shujsn.h"

int main(int argc, char **argv)
{
    json("ignore.json", )
    {
        jsonString("myString", myString);
        jsonF64("floating", testDouble);
        jsonI64("negativeNum", testInt);
        jsonBool("is_active", testBool);
        jsonArray("arrayOfNumbers", );

        json("nested")
        {
            primitive("metadata", char *, metadata);
        }
    }
}