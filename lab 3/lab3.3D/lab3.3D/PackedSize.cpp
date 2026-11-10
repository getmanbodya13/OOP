#include <string>
#include <iostream>
#include <sstream>
#include "PackedSize.h"

#pragma pack(push, 1)
#include "RealPriv.h"
#include "RealPub.h"
#pragma pack(pop)

size_t SizeObjectPacked() { return sizeof(Object); }
size_t SizeNumberPacked() { return sizeof(Number); }
size_t SizeRealPubPacked() { return sizeof(RealPub); }
size_t SizeRealPrivPacked() { return sizeof(RealPriv); }