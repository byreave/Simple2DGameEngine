1. Handle 32/64 build config by defining a type with different size to store the bits in BitArray.
Can be found in BitArray.h line 3-7
2. Used _BitScanForward and _BitScanForward64 in GetFirstSetBit function
Can be found in BitArray.cpp line 109-113
3. Logged useful debug info only in debug mode.
Can be found in FixedSizeAllocator.cpp Line 104, 110
4. Implemented guardbanding and fill values.
Can be found in FixedSizeAllocator.cpp Line 21-30, 58, 77
5. Passed the given unittest
