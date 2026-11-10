#include <string>
#include <iostream>
#include <sstream>
#include "PackedSize.h"

#pragma pack(push, 1)
#include "ComplexPriv.h"
#include "ComplexPub.h"
#pragma pack(pop)

size_t SizeComplexPacked() { return sizeof(Complex); }
size_t SizeComplexPubPacked() { return sizeof(ComplexPub); }
size_t SizeComplexPrivPacked() { return sizeof(ComplexPriv); }