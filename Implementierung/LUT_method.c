#include "LUT_method.h"

// LUT for fast sqrt of floats. Table will be consist of 2 parts, half for sqrt(X) and half for sqrt(2X).

const int nPrecision = 15;                     // we use 15 bits from the 23 of float for precision.
const int notRelevBits = 23 - nPrecision;      // not relevant bits
const int SizeTable = (1 << (nPrecision + 1)); // the entire table which consists of two tables (2^nBits *2) .
static short LUT[65536];                       // declare table of square roots

void construct_table()
{

    /* to access the bits of a float in
     C  we must use union */
    union
    {
        float f;
        int32_t n;
    } conv;
    int SizeHalfTable = (SizeTable >> 1);
    for (short unsigned i = 0; i < SizeHalfTable; i++)
    {
        conv.n = 0;
        // we create a float using the exponent 0 stored as 127 and the mantissa i using bitwise or

        conv.n = (i << notRelevBits) | (127 << 23);

        conv.f = sqrtf(conv.f);

        // we take the root of the float and  then add nPrecision bits of the mantissa in the table

        LUT[i] = (conv.n & 0x7fffff) >> notRelevBits;

        // now we create a float using the exponent 1 stored as 128 and the mantissa i using bitwise or
        conv.n = 0;
        conv.n = (i << notRelevBits) | (128 << 23);
        conv.f = sqrtf(conv.f);
        LUT[i + SizeHalfTable] = (conv.n & 0x7fffff) >> notRelevBits;
    }
}

// square root by table lookup

float LUT_sqrt(float n)
{

    /* to access the bits of a float in
    C  we must use union */
    union
    {
        float f;
        int32_t n;
    } conv;

    conv.f = n;

    short exp; /* exponent */

    exp = (conv.n >> 23) - 127; // exponent is stored with 127 added

    conv.n = conv.n & 0x7fffff; // we leave only the mantissa
    int SizeHalfTable = (SizeTable >> 1);
    int highBit = SizeHalfTable << notRelevBits;
    if (exp & 0x01) /*when the exponent is not even we have to use the second half of the table,which has the exponent 1
                     so we set the high bit*/
        conv.n = conv.n | highBit;

    exp = exp >> 1; // now we divide the exponent by two( we use the shift operators because they  preserve the sign in c)

    /* use the exponent and the mantissa to create the float, then return it as a  float*/
    conv.n = ((LUT[conv.n >> notRelevBits]) << notRelevBits) | ((exp + 127) << 23);

    return (conv.f);
}

float birthday_eq_V1(unsigned long n)
{

    return 0.5 + LUT_sqrt(0.25 + 2 * n * 0.693147);
}