// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

//#include "CoreTypes.h"
//#include "Containers/UnrealString.h"
#include "Math/Vector2D.h"
#include "Math/Float16.h"

namespace UE4Math
{
	/**
	 * Structure for two dimensional vectors with half floating point precision.
	 */
	struct FVector2DHalf
	{
		/** Holds the vector's X-component. */
		FFloat16 X;

		/** Holds the vector's Y-component. */
		FFloat16 Y;

	public:

		/** Default Constructor (no initialization). */
		inline FVector2DHalf() { }

		/**
		 * Constructor.
		 *
		 * InX half float X value
		 * Iny half float Y value
		 */
		inline FVector2DHalf(const FFloat16& InX, const FFloat16& InY);

		/** Constructor
		 *
		 * InX float X value
		 * Iny float Y value
		 */
		inline FVector2DHalf(float InX, float InY);

		/** Constructor
		 *
		 * Vector2D float vector
		 */
		inline FVector2DHalf(const FVector2D& Vector2D);

	public:

		/**
		 * Assignment operator.
		 *
		 * @param Vector2D The value to assign.
		 */
		FVector2DHalf& operator=(const FVector2D& Vector2D);

		/** Implicit conversion operator for conversion to FVector2D. */
		operator FVector2D() const;

	public:

		/**
		 * Get a textual representation of the vector.
		 *
		 * @return Text describing the vector.
		 */
		std::string ToString() const;

	public:

	};


	/* FVector2DHalf inline functions
	 *****************************************************************************/

	inline FVector2DHalf::FVector2DHalf(const FFloat16& InX, const FFloat16& InY)
		: X(InX), Y(InY)
	{ }


	inline FVector2DHalf::FVector2DHalf(float InX, float InY)
		: X(InX), Y(InY)
	{ }


	inline FVector2DHalf::FVector2DHalf(const FVector2D& Vector2D)
		: X(Vector2D.X), Y(Vector2D.Y)
	{ }


	inline FVector2DHalf& FVector2DHalf::operator=(const FVector2D& Vector2D)
	{
		X = FFloat16(Vector2D.X);
		Y = FFloat16(Vector2D.Y);

		return *this;
	}


	inline std::string FVector2DHalf::ToString() const
	{
		char stemp[100] = "";
		snprintf(stemp, 100, "X=%3.3f Y=%3.3f", (float)X, (float)Y);
		return std::string(stemp);
		//return FString::Printf(TEXT("X=%3.3f Y=%3.3f"), (float)X, (float)Y);
	}


	inline FVector2DHalf::operator FVector2D() const
	{
		return FVector2D((float)X, (float)Y);
	}

}
