#include "FMemory.h"
#include "Math/UnrealMathUtility.h"

//void UE4Math::FMemory::MemswapGreaterThan8(void* Ptr1, void* Ptr2, size_t Size)
//{
//	union PtrUnion
//	{
//		void* PtrVoid;
//		uint8_t* Ptr8;
//		uint16_t* Ptr16;
//		uint32_t* Ptr32;
//		uint64_t* Ptr64;
//		UPTRINT PtrUint;
//	};
//
//	PtrUnion Union1 = { Ptr1 };
//	PtrUnion Union2 = { Ptr2 };
//
//	//checkf(Union1.PtrVoid && Union2.PtrVoid, TEXT("Pointers must be non-null: %p, %p"), Union1.PtrVoid, Union2.PtrVoid);
//
//	// We may skip up to 7 bytes below, so better make sure that we're swapping more than that
//	// (8 is a common case that we also want to inline before we this call, so skip that too)
//	//check(Size > 8);
//
//	if (Union1.PtrUint & 1)
//	{
//		Valswap(*Union1.Ptr8++, *Union2.Ptr8++);
//		Size -= 1;
//	}
//	if (Union1.PtrUint & 2)
//	{
//		Valswap(*Union1.Ptr16++, *Union2.Ptr16++);
//		Size -= 2;
//	}
//	if (Union1.PtrUint & 4)
//	{
//		Valswap(*Union1.Ptr32++, *Union2.Ptr32++);
//		Size -= 4;
//	}
//
//	uint32_t CommonAlignment = FMath::Min(FMath::CountTrailingZeros(Union1.PtrUint - Union2.PtrUint), 3u);
//	switch (CommonAlignment)
//	{
//	default:
//		for (; Size >= 8; Size -= 8)
//		{
//			Valswap(*Union1.Ptr64++, *Union2.Ptr64++);
//		}
//
//	case 2:
//		for (; Size >= 4; Size -= 4)
//		{
//			Valswap(*Union1.Ptr32++, *Union2.Ptr32++);
//		}
//
//	case 1:
//		for (; Size >= 2; Size -= 2)
//		{
//			Valswap(*Union1.Ptr16++, *Union2.Ptr16++);
//		}
//
//	case 0:
//		for (; Size >= 1; Size -= 1)
//		{
//			Valswap(*Union1.Ptr8++, *Union2.Ptr8++);
//		}
//	}
//}
