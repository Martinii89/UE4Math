// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

//#include "CoreTypes.h"
//#include "Misc/Crc.h"
#include "Math/UnrealMathUtility.h"
//#include "Containers/UnrealString.h"
//#include "Serialization/StructuredArchive.h"

namespace UE4Math
{
	/**
 * Structure for integer vectors in 3-d space.
 */
	struct FIntVector
	{
		/** Holds the point's x-coordinate. */
		int32 X;

		/** Holds the point's y-coordinate. */
		int32 Y;

		/**  Holds the point's z-coordinate. */
		int32 Z;

	public:

		/** An int point with zeroed values. */
		static const FIntVector ZeroValue;

		/** An int point with INDEX_NONE values. */
		static const FIntVector NoneValue;

	public:

		/**
		 * Default constructor (no initialization).
		 */
		FIntVector();

		/**
		 * Creates and initializes a new instance with the specified coordinates.
		 *
		 * @param InX The x-coordinate.
		 * @param InY The y-coordinate.
		 * @param InZ The z-coordinate.
		 */
		FIntVector(int32 InX, int32 InY, int32 InZ);

		/**
		 * Constructor
		 *
		 * @param InValue replicated to all components
		 */
		explicit FIntVector(int32 InValue);

		/**
		 * Constructor
		 *
		 * @param InVector float vector converted to int
		 */
		explicit FIntVector(FVector InVector);

		/**
		 * Constructor
		 *
		 * @param EForceInit Force init enum
		 */
		explicit inline FIntVector(EForceInit);

	public:

		/**
		 * Gets specific component of a point.
		 *
		 * @param ComponentIndex Index of point component.
		 * @return const reference to component.
		 */
		const int32& operator()(int32 ComponentIndex) const;

		/**
		 * Gets specific component of a point.
		 *
		 * @param ComponentIndex Index of point component.
		 * @return reference to component.
		 */
		int32& operator()(int32 ComponentIndex);

		/**
		 * Gets specific component of a point.
		 *
		 * @param ComponentIndex Index of point component.
		 * @return const reference to component.
		 */
		const int32& operator[](int32 ComponentIndex) const;

		/**
		 * Gets specific component of a point.
		 *
		 * @param ComponentIndex Index of point component.
		 * @return reference to component.
		 */
		int32& operator[](int32 ComponentIndex);

		/**
		 * Compares points for equality.
		 *
		 * @param Other The other int point being compared.
		 * @return true if the points are equal, false otherwise..
		 */
		bool operator==(const FIntVector& Other) const;

		/**
		 * Compares points for inequality.
		 *
		 * @param Other The other int point being compared.
		 * @return true if the points are not equal, false otherwise..
		 */
		bool operator!=(const FIntVector& Other) const;

		/**
		 * Scales this point.
		 *
		 * @param Scale What to multiply the point by.
		 * @return Reference to this point after multiplication.
		 */
		FIntVector& operator*=(int32 Scale);

		/**
		 * Divides this point.
		 *
		 * @param Divisor What to divide the point by.
		 * @return Reference to this point after division.
		 */
		FIntVector& operator/=(int32 Divisor);

		/**
		 * Adds to this point.
		 *
		 * @param Other The point to add to this point.
		 * @return Reference to this point after addition.
		 */
		FIntVector& operator+=(const FIntVector& Other);

		/**
		 * Subtracts from this point.
		 *
		 * @param Other The point to subtract from this point.
		 * @return Reference to this point after subtraction.
		 */
		FIntVector& operator-=(const FIntVector& Other);

		/**
		 * Assigns another point to this one.
		 *
		 * @param Other The point to assign this point from.
		 * @return Reference to this point after assignment.
		 */
		FIntVector& operator=(const FIntVector& Other);

		/**
		 * Gets the result of scaling on this point.
		 *
		 * @param Scale What to multiply the point by.
		 * @return A new scaled int point.
		 */
		FIntVector operator*(int32 Scale) const;

		/**
		 * Gets the result of division on this point.
		 *
		 * @param Divisor What to divide the point by.
		 * @return A new divided int point.
		 */
		FIntVector operator/(int32 Divisor) const;

		/**
		 * Gets the result of addition on this point.
		 *
		 * @param Other The other point to add to this.
		 * @return A new combined int point.
		 */
		FIntVector operator+(const FIntVector& Other) const;

		/**
		 * Gets the result of subtraction from this point.
		 *
		 * @param Other The other point to subtract from this.
		 * @return A new subtracted int point.
		 */
		FIntVector operator-(const FIntVector& Other) const;

		/**
		 * Shifts all components to the right.
		 *
		 * @param Shift The number of bits to shift.
		 * @return A new shifted int point.
		 */
		FIntVector operator>>(int32 Shift) const;

		/**
		 * Shifts all components to the left.
		 *
		 * @param Shift The number of bits to shift.
		 * @return A new shifted int point.
		 */
		FIntVector operator<<(int32 Shift) const;

		/**
		 * Component-wise AND.
		 *
		 * @param Value Number to AND with the each component.
		 * @return A new shifted int point.
		 */
		FIntVector operator&(int32 Val) const;

		/**
		 * Component-wise OR.
		 *
		 * @param Value Number to OR with the each component.
		 * @return A new shifted int point.
		 */
		FIntVector operator|(int32 Value) const;

		/**
		 * Component-wise XOR.
		 *
		 * @param Value Number to XOR with the each component.
		 * @return A new shifted int point.
		 */
		FIntVector operator^(int32 Value) const;

		/**
		 * Is vector equal to zero.
		 * @return is zero
		*/
		bool IsZero() const;

	public:

		/**
		 * Gets the maximum value in the point.
		 *
		 * @return The maximum value in the point.
		 */
		int32 GetMax() const;

		/**
		 * Gets the minimum value in the point.
		 *
		 * @return The minimum value in the point.
		 */
		int32 GetMin() const;

		/**
		 * Gets the distance of this point from (0,0,0).
		 *
		 * @return The distance of this point from (0,0,0).
		 */
		int32 Size() const;

		/**
		 * Get a textual representation of this vector.
		 *
		 * @return A string describing the vector.
		 */
		std::string ToString() const;

	public:

		/**
		 * Divide an int point and round up the result.
		 *
		 * @param lhs The int point being divided.
		 * @param Divisor What to divide the int point by.
		 * @return A new divided int point.
		 */
		static FIntVector DivideAndRoundUp(FIntVector lhs, int32 Divisor);
		static FIntVector DivideAndRoundUp(FIntVector lhs, FIntVector Divisor);

		/**
		 * Gets the number of components a point has.
		 *
		 * @return Number of components point has.
		 */
		static int32 Num();

	};


	/* FIntVector inline functions
	 *****************************************************************************/

	inline FIntVector::FIntVector()
	{ }


	inline FIntVector::FIntVector(int32 InX, int32 InY, int32 InZ)
		: X(InX)
		, Y(InY)
		, Z(InZ)
	{ }


	inline FIntVector::FIntVector(int32 InValue)
		: X(InValue)
		, Y(InValue)
		, Z(InValue)
	{ }


	inline FIntVector::FIntVector(EForceInit)
		: X(0)
		, Y(0)
		, Z(0)
	{ }


	inline const int32& FIntVector::operator()(int32 ComponentIndex) const
	{
		return (&X)[ComponentIndex];
	}


	inline int32& FIntVector::operator()(int32 ComponentIndex)
	{
		return (&X)[ComponentIndex];
	}


	inline const int32& FIntVector::operator[](int32 ComponentIndex) const
	{
		return (&X)[ComponentIndex];
	}


	inline int32& FIntVector::operator[](int32 ComponentIndex)
	{
		return (&X)[ComponentIndex];
	}

	inline bool FIntVector::operator==(const FIntVector& Other) const
	{
		return X == Other.X && Y == Other.Y && Z == Other.Z;
	}


	inline bool FIntVector::operator!=(const FIntVector& Other) const
	{
		return X != Other.X || Y != Other.Y || Z != Other.Z;
	}


	inline FIntVector& FIntVector::operator*=(int32 Scale)
	{
		X *= Scale;
		Y *= Scale;
		Z *= Scale;

		return *this;
	}


	inline FIntVector& FIntVector::operator/=(int32 Divisor)
	{
		X /= Divisor;
		Y /= Divisor;
		Z /= Divisor;

		return *this;
	}


	inline FIntVector& FIntVector::operator+=(const FIntVector& Other)
	{
		X += Other.X;
		Y += Other.Y;
		Z += Other.Z;

		return *this;
	}


	inline FIntVector& FIntVector::operator-=(const FIntVector& Other)
	{
		X -= Other.X;
		Y -= Other.Y;
		Z -= Other.Z;

		return *this;
	}


	inline FIntVector& FIntVector::operator=(const FIntVector& Other)
	{
		X = Other.X;
		Y = Other.Y;
		Z = Other.Z;

		return *this;
	}


	inline FIntVector FIntVector::operator*(int32 Scale) const
	{
		return FIntVector(*this) *= Scale;
	}


	inline FIntVector FIntVector::operator/(int32 Divisor) const
	{
		return FIntVector(*this) /= Divisor;
	}


	inline FIntVector FIntVector::operator+(const FIntVector& Other) const
	{
		return FIntVector(*this) += Other;
	}

	inline FIntVector FIntVector::operator-(const FIntVector& Other) const
	{
		return FIntVector(*this) -= Other;
	}

	inline FIntVector FIntVector::operator>>(int32 Shift) const
	{
		return FIntVector(X >> Shift, Y >> Shift, Z >> Shift);
	}

	inline FIntVector FIntVector::operator<<(int32 Shift) const
	{
		return FIntVector(X << Shift, Y << Shift, Z << Shift);
	}

	inline FIntVector FIntVector::operator&(int32 Value) const
	{
		return FIntVector(X & Value, Y & Value, Z & Value);
	}

	inline FIntVector FIntVector::operator|(int32 Value) const
	{
		return FIntVector(X | Value, Y | Value, Z | Value);
	}

	inline FIntVector FIntVector::operator^(int32 Value) const
	{
		return FIntVector(X ^ Value, Y ^ Value, Z ^ Value);
	}

	inline FIntVector FIntVector::DivideAndRoundUp(FIntVector lhs, int32 Divisor)
	{
		return FIntVector(FMath::DivideAndRoundUp(lhs.X, Divisor), FMath::DivideAndRoundUp(lhs.Y, Divisor), FMath::DivideAndRoundUp(lhs.Z, Divisor));
	}

	inline FIntVector FIntVector::DivideAndRoundUp(FIntVector lhs, FIntVector Divisor)
	{
		return FIntVector(FMath::DivideAndRoundUp(lhs.X, Divisor.X), FMath::DivideAndRoundUp(lhs.Y, Divisor.Y), FMath::DivideAndRoundUp(lhs.Z, Divisor.Z));
	}


	inline int32 FIntVector::GetMax() const
	{
		return FMath::Max(FMath::Max(X, Y), Z);
	}


	inline int32 FIntVector::GetMin() const
	{
		return FMath::Min(FMath::Min(X, Y), Z);
	}


	inline int32 FIntVector::Num()
	{
		return 3;
	}


	inline int32 FIntVector::Size() const
	{
		int64 X64 = (int64)X;
		int64 Y64 = (int64)Y;
		int64 Z64 = (int64)Z;
		return int32(FMath::Sqrt(float(X64 * X64 + Y64 * Y64 + Z64 * Z64)));
	}

	inline bool FIntVector::IsZero() const
	{
		return *this == ZeroValue;
	}


	inline std::string FIntVector::ToString() const
	{
		char stemp[100] = "";
		snprintf(stemp, 100, "X=%d Y=%d Z=%d", X, Y, Z);
		return std::string(stemp);
		//return FString::Printf(TEXT("X=%d Y=%d Z=%d"), X, Y, Z);
	}


	struct FIntVector4
	{
		int32 X, Y, Z, W;

		inline FIntVector4()
		{
		}

		inline FIntVector4(int32 InX, int32 InY, int32 InZ, int32 InW)
			: X(InX)
			, Y(InY)
			, Z(InZ)
			, W(InW)
		{
		}

		inline explicit FIntVector4(int32 InValue)
			: X(InValue)
			, Y(InValue)
			, Z(InValue)
			, W(InValue)
		{
		}

		inline FIntVector4(EForceInit)
			: X(0)
			, Y(0)
			, Z(0)
			, W(0)
		{
		}

		/**
		 * Gets specific component of a point.
		 *
		 * @param ComponentIndex Index of point component.
		 * @return const reference to component.
		 */
		const int32& operator()(int32 ComponentIndex) const;

		/**
		 * Gets specific component of a point.
		 *
		 * @param ComponentIndex Index of point component.
		 * @return reference to component.
		 */
		int32& operator()(int32 ComponentIndex);

		/**
		 * Gets specific component of a point.
		 *
		 * @param ComponentIndex Index of point component.
		 * @return const reference to component.
		 */
		const int32& operator[](int32 ComponentIndex) const;

		/**
		 * Gets specific component of a point.
		 *
		 * @param ComponentIndex Index of point component.
		 * @return reference to component.
		 */
		int32& operator[](int32 ComponentIndex);

		/**
		 * Compares points for equality.
		 *
		 * @param Other The other int point being compared.
		 * @return true if the points are equal, false otherwise..
		 */
		bool operator==(const FIntVector4& Other) const;

		/**
		 * Compares points for inequality.
		 *
		 * @param Other The other int point being compared.
		 * @return true if the points are not equal, false otherwise..
		 */
		bool operator!=(const FIntVector4& Other) const;

		/**
		 * Scales this point.
		 *
		 * @param Scale What to multiply the point by.
		 * @return Reference to this point after multiplication.
		 */
		FIntVector4& operator*=(int32 Scale);

		/**
		 * Divides this point.
		 *
		 * @param Divisor What to divide the point by.
		 * @return Reference to this point after division.
		 */
		FIntVector4& operator/=(int32 Divisor);

		/**
		 * Adds to this point.
		 *
		 * @param Other The point to add to this point.
		 * @return Reference to this point after addition.
		 */
		FIntVector4& operator+=(const FIntVector4& Other);

		/**
		 * Subtracts from this point.
		 *
		 * @param Other The point to subtract from this point.
		 * @return Reference to this point after subtraction.
		 */
		FIntVector4& operator-=(const FIntVector4& Other);

		/**
		 * Assigns another point to this one.
		 *
		 * @param Other The point to assign this point from.
		 * @return Reference to this point after assignment.
		 */
		FIntVector4& operator=(const FIntVector4& Other);

		/**
		 * Gets the result of scaling on this point.
		 *
		 * @param Scale What to multiply the point by.
		 * @return A new scaled int point.
		 */
		FIntVector4 operator*(int32 Scale) const;

		/**
		 * Gets the result of division on this point.
		 *
		 * @param Divisor What to divide the point by.
		 * @return A new divided int point.
		 */
		FIntVector4 operator/(int32 Divisor) const;

		/**
		 * Gets the result of addition on this point.
		 *
		 * @param Other The other point to add to this.
		 * @return A new combined int point.
		 */
		FIntVector4 operator+(const FIntVector4& Other) const;

		/**
		 * Gets the result of subtraction from this point.
		 *
		 * @param Other The other point to subtract from this.
		 * @return A new subtracted int point.
		 */
		FIntVector4 operator-(const FIntVector4& Other) const;

		/**
		 * Shifts all components to the right.
		 *
		 * @param Shift The number of bits to shift.
		 * @return A new shifted int point.
		 */
		FIntVector4 operator>>(int32 Shift) const;

		/**
		 * Shifts all components to the left.
		 *
		 * @param Shift The number of bits to shift.
		 * @return A new shifted int point.
		 */
		FIntVector4 operator<<(int32 Shift) const;

		/**
		 * Component-wise AND.
		 *
		 * @param Value Number to AND with the each component.
		 * @return A new shifted int point.
		 */
		FIntVector4 operator&(int32 Val) const;

		/**
		 * Component-wise OR.
		 *
		 * @param Value Number to OR with the each component.
		 * @return A new shifted int point.
		 */
		FIntVector4 operator|(int32 Value) const;

		/**
		 * Component-wise XOR.
		 *
		 * @param Value Number to XOR with the each component.
		 * @return A new shifted int point.
		 */
		FIntVector4 operator^(int32 Value) const;
	};

	inline const int32& FIntVector4::operator()(int32 ComponentIndex) const
	{
		return (&X)[ComponentIndex];
	}


	inline int32& FIntVector4::operator()(int32 ComponentIndex)
	{
		return (&X)[ComponentIndex];
	}


	inline const int32& FIntVector4::operator[](int32 ComponentIndex) const
	{
		return (&X)[ComponentIndex];
	}


	inline int32& FIntVector4::operator[](int32 ComponentIndex)
	{
		return (&X)[ComponentIndex];
	}

	inline bool FIntVector4::operator==(const FIntVector4& Other) const
	{
		return X == Other.X && Y == Other.Y && Z == Other.Z;
	}


	inline bool FIntVector4::operator!=(const FIntVector4& Other) const
	{
		return X != Other.X || Y != Other.Y || Z != Other.Z || W != Other.W;
	}


	inline FIntVector4& FIntVector4::operator*=(int32 Scale)
	{
		X *= Scale;
		Y *= Scale;
		Z *= Scale;
		W *= Scale;

		return *this;
	}


	inline FIntVector4& FIntVector4::operator/=(int32 Divisor)
	{
		X /= Divisor;
		Y /= Divisor;
		Z /= Divisor;
		W /= Divisor;

		return *this;
	}


	inline FIntVector4& FIntVector4::operator+=(const FIntVector4& Other)
	{
		X += Other.X;
		Y += Other.Y;
		Z += Other.Z;
		W += Other.W;

		return *this;
	}


	inline FIntVector4& FIntVector4::operator-=(const FIntVector4& Other)
	{
		X -= Other.X;
		Y -= Other.Y;
		Z -= Other.Z;
		W -= Other.W;

		return *this;
	}


	inline FIntVector4& FIntVector4::operator=(const FIntVector4& Other)
	{
		X = Other.X;
		Y = Other.Y;
		Z = Other.Z;
		W = Other.W;

		return *this;
	}


	inline FIntVector4 FIntVector4::operator*(int32 Scale) const
	{
		return FIntVector4(*this) *= Scale;
	}


	inline FIntVector4 FIntVector4::operator/(int32 Divisor) const
	{
		return FIntVector4(*this) /= Divisor;
	}


	inline FIntVector4 FIntVector4::operator+(const FIntVector4& Other) const
	{
		return FIntVector4(*this) += Other;
	}

	inline FIntVector4 FIntVector4::operator-(const FIntVector4& Other) const
	{
		return FIntVector4(*this) -= Other;
	}

	inline FIntVector4 FIntVector4::operator>>(int32 Shift) const
	{
		return FIntVector4(X >> Shift, Y >> Shift, Z >> Shift, W >> Shift);
	}

	inline FIntVector4 FIntVector4::operator<<(int32 Shift) const
	{
		return FIntVector4(X << Shift, Y << Shift, Z << Shift, W << Shift);
	}

	inline FIntVector4 FIntVector4::operator&(int32 Value) const
	{
		return FIntVector4(X & Value, Y & Value, Z & Value, W & Value);
	}

	inline FIntVector4 FIntVector4::operator|(int32 Value) const
	{
		return FIntVector4(X | Value, Y | Value, Z | Value, W | Value);
	}

	inline FIntVector4 FIntVector4::operator^(int32 Value) const
	{
		return FIntVector4(X ^ Value, Y ^ Value, Z ^ Value, W ^ Value);
	}


	struct FUintVector4
	{
		uint32 X, Y, Z, W;

		inline FUintVector4()
		{
		}

		inline FUintVector4(uint32 InX, uint32 InY, uint32 InZ, uint32 InW)
			: X(InX)
			, Y(InY)
			, Z(InZ)
			, W(InW)
		{
		}

		inline explicit FUintVector4(uint32 InValue)
			: X(InValue)
			, Y(InValue)
			, Z(InValue)
			, W(InValue)
		{
		}

		inline FUintVector4(EForceInit)
			: X(0)
			, Y(0)
			, Z(0)
			, W(0)
		{
		}

		inline const uint32& operator[](int32 ComponentIndex) const
		{
			return (&X)[ComponentIndex];
		}


		inline uint32& operator[](int32 ComponentIndex)
		{
			return (&X)[ComponentIndex];
		}

		inline bool operator==(const FUintVector4& Other) const
		{
			return X == Other.X && Y == Other.Y && Z == Other.Z && W == Other.W;
		}


		inline bool operator!=(const FUintVector4& Other) const
		{
			return X != Other.X || Y != Other.Y || Z != Other.Z || W != Other.W;
		}
	};

	template <> struct TIsPODType<FIntVector> { enum { Value = true }; };
	template <> struct TIsPODType<FIntVector4> { enum { Value = true }; };
	template <> struct TIsPODType<FUintVector4> { enum { Value = true }; };

}
