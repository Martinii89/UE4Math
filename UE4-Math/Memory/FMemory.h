
#include <wchar.h>
#include <string.h>
#include <stdint.h>

namespace UE4Math
{

	/*-----------------------------------------------------------------------------
		FMemory.
	-----------------------------------------------------------------------------*/

	//template <typename T>
	//static inline void Valswap(T& A, T& B)
	//{
	//	// Usually such an implementation would use move semantics, but
	//	// we're only ever going to call it on fundamental types and MoveTemp
	//	// is not necessarily in scope here anyway, so we don't want to
	//	// #include it if we don't need to.
	//	T Tmp = A;
	//	A = B;
	//	B = Tmp;
	//}


	struct FMemory
	{
		//static void MemswapGreaterThan8(void* Ptr1, void* Ptr2, size_t Size);
		/** @name Memory functions (wrapper for FPlatformMemory) */

		static inline void* Memmove(void* Dest, const void* Src, size_t Count)
		{
			return memmove(Dest, Src, Count);
		}

		static inline int32_t Memcmp(const void* Buf1, const void* Buf2, size_t Count)
		{
			return memcmp(Buf1, Buf2, Count);
		}

		static inline void* Memset(void* Dest, uint8_t Char, size_t Count)
		{
			return memset(Dest, Char, Count);
		}

		template< class T >
		static inline void Memset(T& Src, uint8_t ValueToSet)
		{
			static_assert(!TIsPointer<T>::Value, "For pointers use the three parameters function");
			Memset(&Src, ValueToSet, sizeof(T));
		}

		static inline void* Memzero(void* Dest, size_t Count)
		{
			return memset(Dest, 0, Count);
		}

		template< class T >
		static inline void Memzero(T& Src)
		{
			static_assert(!TIsPointer<T>::Value, "For pointers use the two parameters function");
			Memzero(&Src, sizeof(T));
		}

		static inline void* Memcpy(void* Dest, const void* Src, size_t Count)
		{
			return memcpy(Dest, Src, Count);
		}

		template< class T >
		static inline void Memcpy(T& Dest, const T& Src)
		{
			static_assert(!TIsPointer<T>::Value, "For pointers use the three parameters function");
			Memcpy(&Dest, &Src, sizeof(T));
		}

		static inline void* BigBlockMemcpy(void* Dest, const void* Src, size_t Count)
		{
			return memcpy(Dest, Src, Count);
		}

		static inline void* StreamingMemcpy(void* Dest, const void* Src, size_t Count)
		{
			return memcpy(Dest, Src, Count);
		}

		//static inline void Memswap(void* Ptr1, void* Ptr2, size_t Size)
		//{
		//	switch (Size)
		//	{
		//	case 0:
		//		break;

		//	case 1:
		//		Valswap(*(uint8_t*)Ptr1, *(uint8_t*)Ptr2);
		//		break;

		//	case 2:
		//		Valswap(*(uint16_t*)Ptr1, *(uint16_t*)Ptr2);
		//		break;

		//	case 3:
		//		Valswap(*((uint16_t*&)Ptr1)++, *((uint16_t*&)Ptr2)++);
		//		Valswap(*(uint8_t*)Ptr1, *(uint8_t*)Ptr2);
		//		break;

		//	case 4:
		//		Valswap(*(uint32_t*)Ptr1, *(uint32_t*)Ptr2);
		//		break;

		//	case 5:
		//		Valswap(*((uint32_t*&)Ptr1)++, *((uint32_t*&)Ptr2)++);
		//		Valswap(*(uint8_t*)Ptr1, *(uint8_t*)Ptr2);
		//		break;

		//	case 6:
		//		Valswap(*((uint32_t*&)Ptr1)++, *((uint32_t*&)Ptr2)++);
		//		Valswap(*(uint16_t*)Ptr1, *(uint16_t*)Ptr2);
		//		break;

		//	case 7:
		//		Valswap(*((uint32_t*&)Ptr1)++, *((uint32_t*&)Ptr2)++);
		//		Valswap(*((uint16_t*&)Ptr1)++, *((uint16_t*&)Ptr2)++);
		//		Valswap(*(uint8_t*)Ptr1, *(uint8_t*)Ptr2);
		//		break;

		//	case 8:
		//		Valswap(*(uint64_t*)Ptr1, *(uint64_t*)Ptr2);
		//		break;

		//	case 16:
		//		Valswap(((uint64_t*)Ptr1)[0], ((uint64_t*)Ptr2)[0]);
		//		Valswap(((uint64_t*)Ptr1)[1], ((uint64_t*)Ptr2)[1]);
		//		break;

		//	default:
		//		MemswapGreaterThan8(Ptr1, Ptr2, Size);
		//		break;
		//	}
		//}

		//
		// C style memory allocation stubs that fall back to C runtime
		//
		static inline void* SystemMalloc(size_t Size)
		{
			return ::malloc(Size);
		}

		static inline void SystemFree(void* Ptr)
		{
			::free(Ptr);
		}

		//
		// C style memory allocation stubs.
		//

		//static void* Malloc(size_t Count, uint32 Alignment = DEFAULT_ALIGNMENT);
		//static void* Realloc(void* Original, size_t Count, uint32 Alignment = DEFAULT_ALIGNMENT);
		//static void Free(void* Original);
		//static size_t GetAllocSize(void* Original);
		///**
		//* For some allocators this will return the actual size that should be requested to eliminate
		//* internal fragmentation. The return value will always be >= Count. This can be used to grow
		//* and shrink containers to optimal sizes.
		//* This call is always fast and threadsafe with no locking.
		//*/
		//static size_t QuantizeSize(size_t Count, uint32 Alignment = DEFAULT_ALIGNMENT);

		///**
		//* Releases as much memory as possible. Must be called from the main thread.
		//*/
		//static void Trim(bool bTrimThreadCaches = true);

		///**
		//* Set up TLS caches on the current thread. These are the threads that we can trim.
		//*/
		//static void SetupTLSCachesOnCurrentThread();

		///**
		//* Clears the TLS caches on the current thread and disables any future caching.
		//*/
		//static void ClearAndDisableTLSCachesOnCurrentThread();

		///**
		// * A helper function that will perform a series of random heap allocations to test
		// * the internal validity of the heap. Note, this function will "leak" memory, but another call
		// * will clean up previously allocated blocks before returning. This will help to A/B testing
		// * where you call it in a good state, do something to corrupt memory, then call this again
		// * and hopefully freeing some pointers will trigger a crash.
		// */
		//static void TestMemory();
		///**
		//* Called once main is started and we have -purgatorymallocproxy.
		//* This uses the purgatory malloc proxy to check if things are writing to stale pointers.
		//*/
		//static void EnablePurgatoryTests();
		///**
		//* Called once main is started and we have -purgatorymallocproxy.
		//* This uses the purgatory malloc proxy to check if things are writing to stale pointers.
		//*/
		//static void EnablePoisonTests();

		/**
		* Set global allocator instead of creating it lazily on first allocation.
		* Must only be called once and only if lazy init is disabled via a macro.
		*/
	//	static void ExplicitInit(FMalloc& Allocator);
	//private:
	//	static void GCreateMalloc();
	//	// These versions are called either at startup or in the event of a crash
	//	static void* MallocExternal(size_t Count, uint32 Alignment = DEFAULT_ALIGNMENT);
	//	static void* ReallocExternal(void* Original, size_t Count, uint32 Alignment = DEFAULT_ALIGNMENT);
	//	static void FreeExternal(void* Original);
	//	static size_t GetAllocSizeExternal(void* Original);
	//	static size_t QuantizeSizeExternal(size_t Count, uint32 Alignment = DEFAULT_ALIGNMENT);
	};
}
