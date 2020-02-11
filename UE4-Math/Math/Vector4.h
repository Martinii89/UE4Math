// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

//#include "CoreTypes.h"
//#include "Misc/Crc.h"
#include "Math/UnrealMathUtility.h"
//#include "Containers/UnrealString.h"
//#include "Misc/Parse.h"
//#include "Logging/LogMacros.h"
#include "Math/Vector2D.h"
#include "Math/Vector.h"

namespace UE4Math
{
	/**
	 * A 4D homogeneous vector, 4x1 FLOATs, 16-byte aligned.
	 */
	struct FVector4
	{
	public:

		/** The vector's X-component. */
		float X;

		/** The vector's Y-component. */
		float Y;

		/** The vector's Z-component. */
		float Z;

		/** The vector's W-component. */
		float W;

	public:

		/**
		 * Constructor.
		 *
		 * @param InVector 3D Vector to set first three components.
		 * @param InW W Coordinate.
		 */
		FVector4(const FVector& InVector, float InW = 1.0f);

		/**
		 * Creates and initializes a new vector from a color value.
		 *
		 * @param InColour Color used to set vector.
		 */
		FVector4(const FLinearColor& InColor);

		/**
		 * Creates and initializes a new vector from the specified components.
		 *
		 * @param InX X Coordinate.
		 * @param InY Y Coordinate.
		 * @param InZ Z Coordinate.
		 * @param InW W Coordinate.
		 */
		explicit FVector4(float InX = 0.0f, float InY = 0.0f, float InZ = 0.0f, float InW = 1.0f);

		/**
		 * Creates and initializes a new vector from the specified 2D vectors.
		 *
		 * @param InXY A 2D vector holding the X- and Y-components.
		 * @param InZW A 2D vector holding the Z- and W-components.
		 */
		explicit FVector4(FVector2D InXY, FVector2D InZW);

		/**
		 * Creates and initializes a new vector from an int vector value.
		 *
		 * @param InVector IntVector used to set vector.
		 */
		FVector4(const FIntVector4& InVector);

		/**
		 * Creates and initializes a new vector to zero.
		 *
		 * @param EForceInit Force Init Enum.
		 */
		explicit FVector4(EForceInit);

	public:

		/**
		 * Access a specific component of the vector.
		 *
		 * @param ComponentIndex The index of the component.
		 * @return Reference to the desired component.
		 */
		inline float& operator[](int32 ComponentIndex);

		/**
		 * Access a specific component of the vector.
		 *
		 * @param ComponentIndex The index of the component.
		 * @return Copy of the desired component.
		 */
		inline float operator[](int32 ComponentIndex) const;

		// Unary operators.

		/**
		 * Gets a negated copy of the vector.
		 *
		 * @return A negated copy of the vector.
		 */
		inline FVector4 operator-() const;

		/**
		 * Gets the result of adding a vector to this.
		 *
		 * @param V The vector to add.
		 * @return The result of vector addition.
		 */
		inline FVector4 operator+(const FVector4& V) const;

		/**
		 * Adds another vector to this one.
		 *
		 * @param V The other vector to add.
		 * @return Copy of the vector after addition.
		 */
		inline FVector4 operator+=(const FVector4& V);

		/**
		 * Gets the result of subtracting a vector from this.
		 *
		 * @param V The vector to subtract.
		 * @return The result of vector subtraction.
		 */
		inline FVector4 operator-(const FVector4& V) const;

		/**
		 * Subtracts another vector to this one.
		 *
		 * @param V The other vector to subtract.
		 * @return Copy of the vector after subtraction.
		 */
		inline FVector4 operator-=(const FVector4& V);

		/**
		 * Gets the result of scaling this vector.
		 *
		 * @param Scale The scaling factor.
		 * @return The result of vector scaling.
		 */
		inline FVector4 operator*(float Scale) const;

		/**
		 * Gets the result of dividing this vector.
		 *
		 * @param Scale What to divide by.
		 * @return The result of division.
		 */
		FVector4 operator/(float Scale) const;

		/**
		 * Gets the result of dividing this vector.
		 *
		 * @param V What to divide by.
		 * @return The result of division.
		 */
		FVector4 operator/(const FVector4& V) const;

		/**
		 * Gets the result of multiplying a vector with this.
		 *
		 * @param V The vector to multiply.
		 * @return The result of vector multiplication.
		 */
		FVector4 operator*(const FVector4& V) const;

		/**
		 * Gets the result of multiplying a vector with another Vector (component wise).
		 *
		 * @param V The vector to multiply.
		 * @return The result of vector multiplication.
		 */
		FVector4 operator*=(const FVector4& V);

		/**
		 * Gets the result of dividing a vector with another Vector (component wise).
		 *
		 * @param V The vector to divide with.
		 * @return The result of vector multiplication.
		 */
		FVector4 operator/=(const FVector4& V);

		/**
		 * Gets the result of scaling this vector.
		 *
		 * @param Scale The scaling factor.
		 * @return The result of vector scaling.
		 */
		FVector4 operator*=(float S);

		/**
		 * Calculates 3D Dot product of two 4D vectors.
		 *
		 * @param V1 The first vector.
		 * @param V2 The second vector.
		 * @return The 3D Dot product.
		 */
		friend inline float Dot3(const FVector4& V1, const FVector4& V2)
		{
			return V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z;
		}

		/**
		 * Calculates 4D Dot product.
		 *
		 * @param V1 The first vector.
		 * @param V2 The second vector.
		 * @return The 4D Dot Product.
		 */
		friend inline float Dot4(const FVector4& V1, const FVector4& V2)
		{
			return V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z + V1.W * V2.W;
		}

		/**
		 * Scales a vector.
		 *
		 * @param Scale The scaling factor.
		 * @param V The vector to scale.
		 * @return The result of scaling.
		 */
		friend inline FVector4 operator*(float Scale, const FVector4& V)
		{
			return V.operator*(Scale);
		}

		/**
		 * Checks for equality against another vector.
		 *
		 * @param V The other vector.
		 * @return true if the two vectors are the same, otherwise false.
		 */
		bool operator==(const FVector4& V) const;

		/**
		 * Checks for inequality against another vector.
		 *
		 * @param V The other vector.
		 * @return true if the two vectors are different, otherwise false.
		 */
		bool operator!=(const FVector4& V) const;

		/**
		 * Calculate Cross product between this and another vector.
		 *
		 * @param V The other vector.
		 * @return The Cross product.
		 */
		FVector4 operator^(const FVector4& V) const;

	public:

		// Simple functions.

		/**
		 * Gets a specific component of the vector.
		 *
		 * @param Index The index of the component.
		 * @return Reference to the component.
		 */
		float& Component(int32 Index);

		/**
		* Gets a specific component of the vector.
		*
		* @param Index The index of the component.
		* @return Reference to the component.
		*/
		const float& Component(int32 Index) const;

		/**
		 * Error tolerant comparison.
		 *
		 * @param V Vector to compare against.
		 * @param Tolerance Error Tolerance.
		 * @return true if the two vectors are equal within specified tolerance, otherwise false.
		 */
		bool Equals(const FVector4& V, float Tolerance = KINDA_SMALL_NUMBER) const;

		/**
		 * Check if the vector is of unit length, with specified tolerance.
		 *
		 * @param LengthSquaredTolerance Tolerance against squared length.
		 * @return true if the vector is a unit vector within the specified tolerance.
		 */
		bool IsUnit3(float LengthSquaredTolerance = KINDA_SMALL_NUMBER) const;

		/**
		 * Get a textual representation of the vector.
		 *
		 * @return Text describing the vector.
		 */
		std::string ToString() const;

		/**
		 * Initialize this Vector based on an FString. The String is expected to contain X=, Y=, Z=, W=.
		 * The FVector4 will be bogus when InitFromString returns false.
		 *
		 * @param InSourceString	FString containing the vector values.
		 * @return true if the X,Y,Z values were read successfully; false otherwise.
		 */
		bool InitFromString(const std::string& InSourceString);

		/**
		 * Returns a normalized copy of the vector if safe to normalize.
		 *
		 * @param Tolerance Minimum squared length of vector for normalization.
		 * @return A normalized copy of the vector or a zero vector.
		 */
		inline FVector4 GetSafeNormal(float Tolerance = SMALL_NUMBER) const;

		/**
		 * Calculates normalized version of vector without checking if it is non-zero.
		 *
		 * @return Normalized version of vector.
		 */
		inline FVector4 GetUnsafeNormal3() const;

		/**
		 * Return the FRotator orientation corresponding to the direction in which the vector points.
		 * Sets Yaw and Pitch to the proper numbers, and sets roll to zero because the roll can't be determined from a vector.
		 * @return FRotator from the Vector's direction.
		 */
		FRotator ToOrientationRotator() const;

		/**
		 * Return the Quaternion orientation corresponding to the direction in which the vector points.
		 * @return Quaternion from the Vector's direction.
		 */
		FQuat ToOrientationQuat() const;

		/**
		 * Return the FRotator orientation corresponding to the direction in which the vector points.
		 * Sets Yaw and Pitch to the proper numbers, and sets roll to zero because the roll can't be determined from a vector.
		 * Identical to 'ToOrientationRotator()'.
		 * @return FRotator from the Vector's direction.
		 * @see ToOrientationRotator()
		 */
		FRotator Rotation() const;

		/**
		 * Set all of the vectors coordinates.
		 *
		 * @param InX New X Coordinate.
		 * @param InY New Y Coordinate.
		 * @param InZ New Z Coordinate.
		 * @param InW New W Coordinate.
		 */
		inline void Set(float InX, float InY, float InZ, float InW);

		/**
		 * Get the length of this vector not taking W component into account.
		 *
		 * @return The length of this vector.
		 */
		float Size3() const;

		/**
		 * Get the squared length of this vector not taking W component into account.
		 *
		 * @return The squared length of this vector.
		 */
		float SizeSquared3() const;

		/**
		 * Get the length (magnitude) of this vector, taking the W component into account
		 *
		 * @return The length of this vector
		 */
		float Size() const;

		/**
		 * Get the squared length of this vector, taking the W component into account
		 *
		 * @return The squared length of this vector
		 */
		float SizeSquared() const;

		/** Utility to check if there are any non-finite values (NaN or Inf) in this vector. */
		bool ContainsNaN() const;

		/** Utility to check if all of the components of this vector are nearly zero given the tolerance. */
		bool IsNearlyZero3(float Tolerance = KINDA_SMALL_NUMBER) const;

		/** Reflect vector. */
		FVector4 Reflect3(const FVector4& Normal) const;

		/**
		 * Find good arbitrary axis vectors to represent U and V axes of a plane,
		 * given just the normal.
		 */
		void FindBestAxisVectors3(FVector4& Axis1, FVector4& Axis2) const;

#if ENABLE_NAN_DIAGNOSTIC
		inline void DiagnosticCheckNaN()
		{
			if (ContainsNaN())
			{
				logOrEnsureNanError(TEXT("FVector contains NaN: %s"), *ToString());
				*this = FVector4(FVector::ZeroVector);

			}
		}
#else
		inline void DiagnosticCheckNaN() { }
#endif


	};



	/* FVector4 inline functions
	 *****************************************************************************/

	inline FVector4::FVector4(const FVector& InVector, float InW)
		: X(InVector.X)
		, Y(InVector.Y)
		, Z(InVector.Z)
		, W(InW)
	{
		DiagnosticCheckNaN();
	}


	//inline FVector4::FVector4(const FLinearColor& InColor)
	//	: X(InColor.R)
	//	, Y(InColor.G)
	//	, Z(InColor.B)
	//	, W(InColor.A)
	//{
	//	DiagnosticCheckNaN();
	//}


	inline FVector4::FVector4(float InX, float InY, float InZ, float InW)
		: X(InX)
		, Y(InY)
		, Z(InZ)
		, W(InW)
	{
		DiagnosticCheckNaN();
	}


	inline FVector4::FVector4(EForceInit)
		: X(0.f)
		, Y(0.f)
		, Z(0.f)
		, W(0.f)
	{
		DiagnosticCheckNaN();
	}


	inline FVector4::FVector4(FVector2D InXY, FVector2D InZW)
		: X(InXY.X)
		, Y(InXY.Y)
		, Z(InZW.X)
		, W(InZW.Y)
	{
		DiagnosticCheckNaN();
	}

	inline FVector4::FVector4(const FIntVector4& InVector)
		: X(InVector.X)
		, Y(InVector.Y)
		, Z(InVector.Z)
		, W(InVector.W)
	{
	}

	inline float& FVector4::operator[](int32 ComponentIndex)
	{
		return (&X)[ComponentIndex];
	}


	inline float FVector4::operator[](int32 ComponentIndex) const
	{
		return (&X)[ComponentIndex];
	}


	inline void FVector4::Set(float InX, float InY, float InZ, float InW)
	{
		X = InX;
		Y = InY;
		Z = InZ;
		W = InW;

		DiagnosticCheckNaN();
	}


	inline FVector4 FVector4::operator-() const
	{
		return FVector4(-X, -Y, -Z, -W);
	}


	inline FVector4 FVector4::operator+(const FVector4& V) const
	{
		return FVector4(X + V.X, Y + V.Y, Z + V.Z, W + V.W);
	}


	inline FVector4 FVector4::operator+=(const FVector4& V)
	{
		X += V.X; Y += V.Y; Z += V.Z; W += V.W;
		DiagnosticCheckNaN();
		return *this;
	}


	inline FVector4 FVector4::operator-(const FVector4& V) const
	{
		return FVector4(X - V.X, Y - V.Y, Z - V.Z, W - V.W);
	}


	inline FVector4 FVector4::operator-=(const FVector4& V)
	{
		X -= V.X; Y -= V.Y; Z -= V.Z; W -= V.W;
		DiagnosticCheckNaN();
		return *this;
	}


	inline FVector4 FVector4::operator*(float Scale) const
	{
		return FVector4(X * Scale, Y * Scale, Z * Scale, W * Scale);
	}


	inline FVector4 FVector4::operator/(float Scale) const
	{
		const float RScale = 1.f / Scale;
		return FVector4(X * RScale, Y * RScale, Z * RScale, W * RScale);
	}


	inline FVector4 FVector4::operator*(const FVector4& V) const
	{
		return FVector4(X * V.X, Y * V.Y, Z * V.Z, W * V.W);
	}


	inline FVector4 FVector4::operator^(const FVector4& V) const
	{
		return FVector4(
			Y * V.Z - Z * V.Y,
			Z * V.X - X * V.Z,
			X * V.Y - Y * V.X,
			0.0f
		);
	}


	inline float& FVector4::Component(int32 Index)
	{
		return (&X)[Index];
	}

	inline const float& FVector4::Component(int32 Index) const
	{
		return (&X)[Index];
	}

	inline bool FVector4::operator==(const FVector4& V) const
	{
		return ((X == V.X) && (Y == V.Y) && (Z == V.Z) && (W == V.W));
	}


	inline bool FVector4::operator!=(const FVector4& V) const
	{
		return ((X != V.X) || (Y != V.Y) || (Z != V.Z) || (W != V.W));
	}


	inline bool FVector4::Equals(const FVector4& V, float Tolerance) const
	{
		return FMath::Abs(X - V.X) <= Tolerance && FMath::Abs(Y - V.Y) <= Tolerance && FMath::Abs(Z - V.Z) <= Tolerance && FMath::Abs(W - V.W) <= Tolerance;
	}


	inline std::string FVector4::ToString() const
	{
		char stemp[200] = "";
		snprintf(stemp, 100, "X=%3.3f Y=%3.3f Z=%3.3f W=%3.3f", X, Y, Z, W);
		return std::string(stemp);
		//return FString::Printf(TEXT("X=%3.3f Y=%3.3f Z=%3.3f W=%3.3f"), X, Y, Z, W);
	}


	inline FVector4 FVector4::GetSafeNormal(float Tolerance) const
	{
		const float SquareSum = X * X + Y * Y + Z * Z;
		if (SquareSum > Tolerance)
		{
			const float Scale = FMath::InvSqrt(SquareSum);
			return FVector4(X * Scale, Y * Scale, Z * Scale, 0.0f);
		}
		return FVector4(0.f);
	}


	inline FVector4 FVector4::GetUnsafeNormal3() const
	{
		const float Scale = FMath::InvSqrt(X * X + Y * Y + Z * Z);
		return FVector4(X * Scale, Y * Scale, Z * Scale, 0.0f);
	}


	inline float FVector4::Size3() const
	{
		return FMath::Sqrt(X * X + Y * Y + Z * Z);
	}


	inline float FVector4::SizeSquared3() const
	{
		return X * X + Y * Y + Z * Z;
	}

	inline float FVector4::Size() const
	{
		return FMath::Sqrt(X * X + Y * Y + Z * Z + W * W);
	}

	inline float FVector4::SizeSquared() const
	{
		return X * X + Y * Y + Z * Z + W * W;
	}


	inline bool FVector4::IsUnit3(float LengthSquaredTolerance) const
	{
		return FMath::Abs(1.0f - SizeSquared3()) < LengthSquaredTolerance;
	}


	inline bool FVector4::ContainsNaN() const
	{
		return (!FMath::IsFinite(X) ||
			!FMath::IsFinite(Y) ||
			!FMath::IsFinite(Z) ||
			!FMath::IsFinite(W));
	}


	inline bool FVector4::IsNearlyZero3(float Tolerance) const
	{
		return
			FMath::Abs(X) <= Tolerance
			&& FMath::Abs(Y) <= Tolerance
			&& FMath::Abs(Z) <= Tolerance;
	}


	inline FVector4 FVector4::Reflect3(const FVector4& Normal) const
	{
		return 2.0f * Dot3(*this, Normal) * Normal - *this;
	}


	inline void FVector4::FindBestAxisVectors3(FVector4& Axis1, FVector4& Axis2) const
	{
		const float NX = FMath::Abs(X);
		const float NY = FMath::Abs(Y);
		const float NZ = FMath::Abs(Z);

		// Find best basis vectors.
		if (NZ > NX&& NZ > NY)	Axis1 = FVector4(1, 0, 0);
		else					Axis1 = FVector4(0, 0, 1);

		Axis1 = (Axis1 - *this * Dot3(Axis1, *this)).GetSafeNormal();
		Axis2 = Axis1 ^ *this;
	}


	inline FVector4 FVector4::operator*=(const FVector4& V)
	{
		X *= V.X; Y *= V.Y; Z *= V.Z; W *= V.W;
		DiagnosticCheckNaN();
		return *this;
	}


	inline FVector4 FVector4::operator/=(const FVector4& V)
	{
		X /= V.X; Y /= V.Y; Z /= V.Z; W /= V.W;
		DiagnosticCheckNaN();
		return *this;
	}


	inline FVector4 FVector4::operator*=(float S)
	{
		X *= S; Y *= S; Z *= S; W *= S;
		DiagnosticCheckNaN();
		return *this;
	}


	inline FVector4 FVector4::operator/(const FVector4& V) const
	{
		return FVector4(X / V.X, Y / V.Y, Z / V.Z, W / V.W);
	}

	template <> struct TIsPODType<FVector4> { enum { Value = true }; };


	/* FVector inline functions
	 *****************************************************************************/

	inline FVector::FVector(const FVector4& V)
		: X(V.X), Y(V.Y), Z(V.Z)
	{
		DiagnosticCheckNaN();
	}

	/* FVector2D inline functions
	 *****************************************************************************/

	inline FVector2D::FVector2D(const FVector4& V)
		: X(V.X), Y(V.Y)
	{
	}
}
