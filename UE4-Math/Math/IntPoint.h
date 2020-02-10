// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Misc/CoreMiscDefines.h"
#include "Math/UnrealMathUtility.h"
#include <string>
//#include "CoreTypes.h"
//#include "Misc/AssertionMacros.h"
//#include "Containers/UnrealString.h"
//#include "Templates/TypeHash.h"

namespace UE4Math
{

	/**
	 * Structure for integer points in 2-d space.
	 *
	 * @todo Docs: The operators need better documentation, i.e. what does it mean to divide a point?
	 */
	struct FIntPoint
	{
		/** Holds the point's x-coordinate. */
		int32_t X;

		/** Holds the point's y-coordinate. */
		int32_t Y;

	public:

		/** An integer point with zeroed values. */
		static const FIntPoint ZeroValue;

		/** An integer point with INDEX_NONE values. */
		static const FIntPoint NoneValue;

	public:

		/** Default constructor (no initialization). */
		FIntPoint();

		/**
		 * Create and initialize a new instance with the specified coordinates.
		 *
		 * @param InX The x-coordinate.
		 * @param InY The y-coordinate.
		 */
		FIntPoint(int32_t InX, int32_t InY);

		/**
		 * Create and initialize a new instance to zero.
		 *
		 * @param EForceInit Force init enum
		 */
		explicit inline FIntPoint(EForceInit);

	public:

		/**
		 * Get specific component of a point.
		 *
		 * @param PointIndex Index of point component.
		 * @return const reference to component.
		 */
		const int32_t& operator()(int32_t PointIndex) const;

		/**
		 * Get specific component of a point.
		 *
		 * @param PointIndex Index of point component
		 * @return reference to component.
		 */
		int32_t& operator()(int32_t PointIndex);

		/**
		 * Compare two points for equality.
		 *
		 * @param Other The other int point being compared.
		 * @return true if the points are equal, false otherwise.
		 */
		bool operator==(const FIntPoint& Other) const;

		/**
		 * Compare two points for inequality.
		 *
		 * @param Other The other int point being compared.
		 * @return true if the points are not equal, false otherwise.
		 */
		bool operator!=(const FIntPoint& Other) const;

		/**
		 * Scale this point.
		 *
		 * @param Scale What to multiply the point by.
		 * @return Reference to this point after multiplication.
		 */
		FIntPoint& operator*=(int32_t Scale);

		/**
		 * Divide this point by a scalar.
		 *
		 * @param Divisor What to divide the point by.
		 * @return Reference to this point after division.
		 */
		FIntPoint& operator/=(int32_t Divisor);

		/**
		 * Add another point component-wise to this point.
		 *
		 * @param Other The point to add to this point.
		 * @return Reference to this point after addition.
		 */
		FIntPoint& operator+=(const FIntPoint& Other);

		/**
		 * Subtract another point component-wise from this point.
		 *
		 * @param Other The point to subtract from this point.
		 * @return Reference to this point after subtraction.
		 */
		FIntPoint& operator-=(const FIntPoint& Other);

		/**
		 * Divide this point component-wise by another point.
		 *
		 * @param Other The point to divide with.
		 * @return Reference to this point after division.
		 */
		FIntPoint& operator/=(const FIntPoint& Other);

		/**
		 * Assign another point to this one.
		 *
		 * @param Other The point to assign this point from.
		 * @return Reference to this point after assignment.
		 */
		FIntPoint& operator=(const FIntPoint& Other);

		/**
		 * Get the result of scaling on this point.
		 *
		 * @param Scale What to multiply the point by.
		 * @return A new scaled int point.
		 */
		FIntPoint operator*(int32_t Scale) const;

		/**
		 * Get the result of division on this point.
		 *
		 * @param Divisor What to divide the point by.
		 * @return A new divided int point.
		 */
		FIntPoint operator/(int32_t Divisor) const;

		/**
		 * Get the result of addition on this point.
		 *
		 * @param Other The other point to add to this.
		 * @return A new combined int point.
		 */
		FIntPoint operator+(const FIntPoint& Other) const;

		/**
		 * Get the result of subtraction from this point.
		 *
		 * @param Other The other point to subtract from this.
		 * @return A new subtracted int point.
		 */
		FIntPoint operator-(const FIntPoint& Other) const;

		/**
		 * Get the result of division on this point.
		 *
		 * @param Other The other point to subtract from this.
		 * @return A new subtracted int point.
		 */
		FIntPoint operator/(const FIntPoint& Other) const;

		/**
		* Get specific component of the point.
		*
		* @param Index the index of point component
		* @return reference to component.
		*/
		int32_t& operator[](int32_t Index);

		/**
		* Get specific component of the point.
		*
		* @param Index the index of point component
		* @return copy of component value.
		*/
		int32_t operator[](int32_t Index) const;

	public:

		/**
		 * Get the component-wise min of two points.
		 *
		 * @see ComponentMax, GetMax
		 */
		inline FIntPoint ComponentMin(const FIntPoint& Other) const;

		/**
		 * Get the component-wise max of two points.
		 *
		 * @see ComponentMin, GetMin
		 */
		inline FIntPoint ComponentMax(const FIntPoint& Other) const;

		/**
		 * Get the larger of the point's two components.
		 *
		 * @return The maximum component of the point.
		 * @see GetMin, Size, SizeSquared
		 */
		int32_t GetMax() const;

		/**
		 * Get the smaller of the point's two components.
		 *
		 * @return The minimum component of the point.
		 * @see GetMax, Size, SizeSquared
		 */
		int32_t GetMin() const;

		/**
		 * Get the distance of this point from (0,0).
		 *
		 * @return The distance of this point from (0,0).
		 * @see GetMax, GetMin, SizeSquared
		 */
		int32_t Size() const;

		/**
		 * Get the squared distance of this point from (0,0).
		 *
		 * @return The squared distance of this point from (0,0).
		 * @see GetMax, GetMin, Size
		 */
		int32_t SizeSquared() const;

		/**
		 * Get a textual representation of this point.
		 *
		 * @return A string describing the point.
		 */
		std::string ToString() const;

	public:

		/**
		 * Divide an int point and round up the result.
		 *
		 * @param lhs The int point being divided.
		 * @param Divisor What to divide the int point by.
		 * @return A new divided int point.
		 * @see DivideAndRoundDown
		 */
		static FIntPoint DivideAndRoundUp(FIntPoint lhs, int32_t Divisor);
		static FIntPoint DivideAndRoundUp(FIntPoint lhs, FIntPoint Divisor);

		/**
		 * Divide an int point and round down the result.
		 *
		 * @param lhs The int point being divided.
		 * @param Divisor What to divide the int point by.
		 * @return A new divided int point.
		 * @see DivideAndRoundUp
		 */
		static FIntPoint DivideAndRoundDown(FIntPoint lhs, int32_t Divisor);

		/**
		 * Get number of components point has.
		 *
		 * @return number of components point has.
		 */
		static int32_t Num();
	};


	/* FIntPoint inline functions
	 *****************************************************************************/

	inline FIntPoint::FIntPoint() { }


	inline FIntPoint::FIntPoint(int32_t InX, int32_t InY)
		: X(InX)
		, Y(InY)
	{ }


	inline FIntPoint::FIntPoint(EForceInit)
		: X(0)
		, Y(0)
	{ }


	inline const int32_t& FIntPoint::operator()(int32_t PointIndex) const
	{
		return (&X)[PointIndex];
	}


	inline int32_t& FIntPoint::operator()(int32_t PointIndex)
	{
		return (&X)[PointIndex];
	}


	inline int32_t FIntPoint::Num()
	{
		return 2;
	}


	inline bool FIntPoint::operator==(const FIntPoint& Other) const
	{
		return X == Other.X && Y == Other.Y;
	}


	inline bool FIntPoint::operator!=(const FIntPoint& Other) const
	{
		return (X != Other.X) || (Y != Other.Y);
	}


	inline FIntPoint& FIntPoint::operator*=(int32_t Scale)
	{
		X *= Scale;
		Y *= Scale;

		return *this;
	}


	inline FIntPoint& FIntPoint::operator/=(int32_t Divisor)
	{
		X /= Divisor;
		Y /= Divisor;

		return *this;
	}


	inline FIntPoint& FIntPoint::operator+=(const FIntPoint& Other)
	{
		X += Other.X;
		Y += Other.Y;

		return *this;
	}


	inline FIntPoint& FIntPoint::operator-=(const FIntPoint& Other)
	{
		X -= Other.X;
		Y -= Other.Y;

		return *this;
	}


	inline FIntPoint& FIntPoint::operator/=(const FIntPoint& Other)
	{
		X /= Other.X;
		Y /= Other.Y;

		return *this;
	}


	inline FIntPoint& FIntPoint::operator=(const FIntPoint& Other)
	{
		X = Other.X;
		Y = Other.Y;

		return *this;
	}


	inline FIntPoint FIntPoint::operator*(int32_t Scale) const
	{
		return FIntPoint(*this) *= Scale;
	}


	inline FIntPoint FIntPoint::operator/(int32_t Divisor) const
	{
		return FIntPoint(*this) /= Divisor;
	}


	inline int32_t& FIntPoint::operator[](int32_t Index)
	{
		//check(Index >= 0 && Index < 2);
		return ((Index == 0) ? X : Y);
	}


	inline int32_t FIntPoint::operator[](int32_t Index) const
	{
		//check(Index >= 0 && Index < 2);
		return ((Index == 0) ? X : Y);
	}


	inline FIntPoint FIntPoint::ComponentMin(const FIntPoint& Other) const
	{
		return FIntPoint(FMath::Min(X, Other.X), FMath::Min(Y, Other.Y));
	}


	inline FIntPoint FIntPoint::ComponentMax(const FIntPoint& Other) const
	{
		return FIntPoint(FMath::Max(X, Other.X), FMath::Max(Y, Other.Y));
	}

	inline FIntPoint FIntPoint::DivideAndRoundUp(FIntPoint lhs, int32_t Divisor)
	{
		return FIntPoint(FMath::DivideAndRoundUp(lhs.X, Divisor), FMath::DivideAndRoundUp(lhs.Y, Divisor));
	}

	inline FIntPoint FIntPoint::DivideAndRoundUp(FIntPoint lhs, FIntPoint Divisor)
	{
		return FIntPoint(FMath::DivideAndRoundUp(lhs.X, Divisor.X), FMath::DivideAndRoundUp(lhs.Y, Divisor.Y));
	}

	inline FIntPoint FIntPoint::DivideAndRoundDown(FIntPoint lhs, int32_t Divisor)
	{
		return FIntPoint(FMath::DivideAndRoundDown(lhs.X, Divisor), FMath::DivideAndRoundDown(lhs.Y, Divisor));
	}


	inline FIntPoint FIntPoint::operator+(const FIntPoint& Other) const
	{
		return FIntPoint(*this) += Other;
	}


	inline FIntPoint FIntPoint::operator-(const FIntPoint& Other) const
	{
		return FIntPoint(*this) -= Other;
	}


	inline FIntPoint FIntPoint::operator/(const FIntPoint& Other) const
	{
		return FIntPoint(*this) /= Other;
	}


	inline int32_t FIntPoint::GetMax() const
	{
		return FMath::Max(X, Y);
	}


	inline int32_t FIntPoint::GetMin() const
	{
		return FMath::Min(X, Y);
	}


	inline int32_t FIntPoint::Size() const
	{
		int64 X64 = (int64)X;
		int64 Y64 = (int64)Y;
		return int32_t(FMath::Sqrt(float(X64 * X64 + Y64 * Y64)));
	}

	inline int32_t FIntPoint::SizeSquared() const
	{
		return X * X + Y * Y;
	}

	inline std::string FIntPoint::ToString() const
	{
		char stemp[100] = "";
		snprintf(stemp, 100, "X=%d Y=%d", X, Y);
		return std::string(stemp);
		//return FString::Printf(TEXT("X=%d Y=%d"), X, Y);
	}

	template <> struct TIsPODType<FIntPoint> { enum { Value = true }; };

}
