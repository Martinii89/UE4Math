#pragma once
#include <stdint.h>
#include "Misc/IsPODType.h"

#define ensure(           InExpression                ) (!!(InExpression))

namespace UE4Math
{
	enum { INDEX_NONE = -1 };

	enum EForceInit
	{
		ForceInit,
		ForceInitToZero
	};
	enum ENoInit { NoInit };
	enum EInPlace { InPlace };

	typedef  uint64_t uint64;
	typedef  uint32_t uint32;
	typedef  uint16_t uint16;
	typedef  uint8_t  uint8;

	typedef  int64_t int64;
	typedef  int32_t int32;
	typedef  int16_t int16;
	typedef  int8_t  int8;
}
