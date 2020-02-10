// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

//#include "CoreTypes.h"
//#include "HAL/UnrealMemory.h"
#include "Math/UnrealMathUtility.h"
//#include "Containers/UnrealString.h"
#include "Math/Vector.h"
#include "Math/Vector4.h"
#include "Math/Plane.h"
#include "Math/Rotator.h"
#include "Math/Axis.h"

namespace UE4Math
{
	/**
 * 4x4 matrix of floating point values.
 * Matrix-matrix multiplication happens with a pre-multiple of the transpose --
 * in other words, Res = Mat1.operator*(Mat2) means Res = Mat2^T * Mat1, as
 * opposed to Res = Mat1 * Mat2.
 * Matrix elements are accessed with M[RowIndex][ColumnIndex].
 */
	struct FMatrix
	{
	public:
		union
		{
			float M[4][4];
		};

		//Identity matrix
		static const FMatrix Identity;

		// Constructors.
		inline FMatrix();

		/**
		 * Constructor.
		 *
		 * @param EForceInit Force Init Enum.
		 */
		explicit inline FMatrix(EForceInit)
		{
			M[0][0]=0; M[0][1] = 0; M[0][2] = 0; M[0][3] = 0;
			M[1][0]=0; M[1][1] = 0; M[1][2] = 0; M[1][3] = 0;
			M[2][0]=0; M[2][1] = 0; M[2][2] = 0; M[2][3] = 0;
			M[3][0]=0; M[3][1] = 0; M[3][2] = 0; M[3][3] = 0;
			//FMemory::Memzero(this, sizeof(*this));
		}

		/**
		 * Constructor.
		 *
		 * @param InX X plane
		 * @param InY Y plane
		 * @param InZ Z plane
		 * @param InW W plane
		 */
		inline FMatrix(const FPlane& InX, const FPlane& InY, const FPlane& InZ, const FPlane& InW);

		/**
		 * Constructor.
		 *
		 * @param InX X vector
		 * @param InY Y vector
		 * @param InZ Z vector
		 * @param InW W vector
		 */
		inline FMatrix(const FVector& InX, const FVector& InY, const FVector& InZ, const FVector& InW);

		// Set this to the identity matrix
		inline void SetIdentity();

		/**
		 * Gets the result of multiplying a Matrix to this.
		 *
		 * @param Other The matrix to multiply this by.
		 * @return The result of multiplication.
		 */
		inline FMatrix operator* (const FMatrix& Other) const;

		/**
		 * Multiply this by a matrix.
		 *
		 * @param Other the matrix to multiply by this.
		 * @return reference to this after multiply.
		 */
		inline void operator*=(const FMatrix& Other);

		/**
		 * Gets the result of adding a matrix to this.
		 *
		 * @param Other The Matrix to add.
		 * @return The result of addition.
		 */
		inline FMatrix operator+ (const FMatrix& Other) const;

		/**
		 * Adds to this matrix.
		 *
		 * @param Other The matrix to add to this.
		 * @return Reference to this after addition.
		 */
		inline void operator+=(const FMatrix& Other);

		/**
		  * This isn't applying SCALE, just multiplying the value to all members - i.e. weighting
		  */
		inline FMatrix operator* (float Other) const;

		/**
		 * Multiply this matrix by a weighting factor.
		 *
		 * @param other The weight.
		 * @return a reference to this after weighting.
		 */
		inline void operator*=(float Other);

		/**
		 * Checks whether two matrix are identical.
		 *
		 * @param Other The other matrix.
		 * @return true if two matrix are identical, otherwise false.
		 */
		inline bool operator==(const FMatrix& Other) const;

		/**
		 * Checks whether another Matrix is equal to this, within specified tolerance.
		 *
		 * @param Other The other Matrix.
		 * @param Tolerance Error Tolerance.
		 * @return true if two Matrix are equal, within specified tolerance, otherwise false.
		 */
		inline bool Equals(const FMatrix& Other, float Tolerance = KINDA_SMALL_NUMBER) const;

		/**
		 * Checks whether another Matrix is not equal to this, within specified tolerance.
		 *
		 * @param Other The other Matrix.
		 * @return true if two Matrix are not equal, within specified tolerance, otherwise false.
		 */
		inline bool operator!=(const FMatrix& Other) const;

		// Homogeneous transform.
		inline FVector4 TransformFVector4(const FVector4& V) const;

		/** Transform a location - will take into account translation part of the FMatrix. */
		inline FVector4 TransformPosition(const FVector& V) const;

		/** Inverts the matrix and then transforms V - correctly handles scaling in this matrix. */
		inline FVector InverseTransformPosition(const FVector& V) const;

		/**
		 *	Transform a direction vector - will not take into account translation part of the FMatrix.
		 *	If you want to transform a surface normal (or plane) and correctly account for non-uniform scaling you should use TransformByUsingAdjointT.
		 */
		inline FVector4 TransformVector(const FVector& V) const;

		/**
		 *	Transform a direction vector by the inverse of this matrix - will not take into account translation part.
		 *	If you want to transform a surface normal (or plane) and correctly account for non-uniform scaling you should use TransformByUsingAdjointT with adjoint of matrix inverse.
		 */
		inline FVector InverseTransformVector(const FVector& V) const;

		// Transpose.

		inline FMatrix GetTransposed() const;

		// @return determinant of this matrix.

		inline float Determinant() const;

		/** @return the determinant of rotation 3x3 matrix */
		inline float RotDeterminant() const;

		/** Fast path, doesn't check for nil matrices in final release builds */
		inline FMatrix InverseFast() const;

		/** Fast path, and handles nil matrices. */
		inline FMatrix Inverse() const;

		inline FMatrix TransposeAdjoint() const;

		// NOTE: There is some compiler optimization issues with WIN64 that cause inline to cause a crash
		// Remove any scaling from this matrix (ie magnitude of each row is 1) with error Tolerance
		inline void RemoveScaling(float Tolerance = SMALL_NUMBER);

		// Returns matrix after RemoveScaling with error Tolerance
		inline FMatrix GetMatrixWithoutScale(float Tolerance = SMALL_NUMBER) const;

		/** Remove any scaling from this matrix (ie magnitude of each row is 1) and return the 3D scale vector that was initially present with error Tolerance */
		inline FVector ExtractScaling(float Tolerance = SMALL_NUMBER);

		/** return a 3D scale vector calculated from this matrix (where each component is the magnitude of a row vector) with error Tolerance. */
		inline FVector GetScaleVector(float Tolerance = SMALL_NUMBER) const;

		// Remove any translation from this matrix
		inline FMatrix RemoveTranslation() const;

		/** Returns a matrix with an additional translation concatenated. */
		inline FMatrix ConcatTranslation(const FVector& Translation) const;

		/** Returns true if any element of this matrix is NaN */
		inline bool ContainsNaN() const;

		/** Scale the translation part of the matrix by the supplied vector. */
		inline void ScaleTranslation(const FVector& Scale3D);

		/** @return the maximum magnitude of any row of the matrix. */
		inline float GetMaximumAxisScale() const;

		/** Apply Scale to this matrix **/
		inline FMatrix ApplyScale(float Scale) const;

		// @return the origin of the co-ordinate system
		inline FVector GetOrigin() const;

		/**
		 * get axis of this matrix scaled by the scale of the matrix
		 *
		 * @param i index into the axis of the matrix
		 * @ return vector of the axis
		 */
		inline FVector GetScaledAxis(EAxis::Type Axis) const;

		/**
		 * get axes of this matrix scaled by the scale of the matrix
		 *
		 * @param X axes returned to this param
		 * @param Y axes returned to this param
		 * @param Z axes returned to this param
		 */
		inline void GetScaledAxes(FVector& X, FVector& Y, FVector& Z) const;

		/**
		 * get unit length axis of this matrix
		 *
		 * @param i index into the axis of the matrix
		 * @return vector of the axis
		 */
		inline FVector GetUnitAxis(EAxis::Type Axis) const;

		/**
		 * get unit length axes of this matrix
		 *
		 * @param X axes returned to this param
		 * @param Y axes returned to this param
		 * @param Z axes returned to this param
		 */
		inline void GetUnitAxes(FVector& X, FVector& Y, FVector& Z) const;

		/**
		 * set an axis of this matrix
		 *
		 * @param i index into the axis of the matrix
		 * @param Axis vector of the axis
		 */
		inline void SetAxis(int32 i, const FVector& Axis);

		// Set the origin of the coordinate system to the given vector
		inline void SetOrigin(const FVector& NewOrigin);

		/**
		 * Update the axes of the matrix if any value is NULL do not update that axis
		 *
		 * @param Axis0 set matrix row 0
		 * @param Axis1 set matrix row 1
		 * @param Axis2 set matrix row 2
		 * @param Origin set matrix row 3
		 */
		inline void SetAxes(FVector* Axis0 = NULL, FVector* Axis1 = NULL, FVector* Axis2 = NULL, FVector* Origin = NULL);


		/**
		 * get a column of this matrix
		 *
		 * @param i index into the column of the matrix
		 * @return vector of the column
		 */
		inline FVector GetColumn(int32 i) const;

		/**
		 * Set a column of this matrix
		 *
		 * @param i index of the matrix column
		 * @param Value new value of the column
		 */
		inline void SetColumn(int32 i, FVector Value);

		/** @return rotator representation of this matrix */
		FRotator Rotator() const;

		/**
		 * Transform a rotation matrix into a quaternion.
		 *
		 * @warning rotation part will need to be unit length for this to be right!
		 */
		FQuat ToQuat() const;

		// Frustum plane extraction.
		/** @param OutPlane the near plane of the Frustum of this matrix */
		inline bool GetFrustumNearPlane(FPlane& OutPlane) const;

		/** @param OutPlane the far plane of the Frustum of this matrix */
		inline bool GetFrustumFarPlane(FPlane& OutPlane) const;

		/** @param OutPlane the left plane of the Frustum of this matrix */
		inline bool GetFrustumLeftPlane(FPlane& OutPlane) const;

		/** @param OutPlane the right plane of the Frustum of this matrix */
		inline bool GetFrustumRightPlane(FPlane& OutPlane) const;

		/** @param OutPlane the top plane of the Frustum of this matrix */
		inline bool GetFrustumTopPlane(FPlane& OutPlane) const;

		/** @param OutPlane the bottom plane of the Frustum of this matrix */
		inline bool GetFrustumBottomPlane(FPlane& OutPlane) const;

		/**
		 * Utility for mirroring this transform across a certain plane, and flipping one of the axis as well.
		 */
		inline void Mirror(EAxis::Type MirrorAxis, EAxis::Type FlipAxis);

		/**
		 * Get a textual representation of the vector.
		 *
		 * @return Text describing the vector.
		 */
		std::string ToString() const;

		/** Output ToString */
		void DebugPrint() const;

		/** For debugging purpose, could be changed */
		uint32 ComputeHash() const;


		/**
		 * Convert this Atom to the 3x4 transpose of the transformation matrix.
		 */
		void To3x4MatrixTranspose(float* Out) const
		{
			const float* __restrict Src = &(M[0][0]);
			float* __restrict Dest = Out;

			Dest[0] = Src[0];   // [0][0]
			Dest[1] = Src[4];   // [1][0]
			Dest[2] = Src[8];   // [2][0]
			Dest[3] = Src[12];  // [3][0]

			Dest[4] = Src[1];   // [0][1]
			Dest[5] = Src[5];   // [1][1]
			Dest[6] = Src[9];   // [2][1]
			Dest[7] = Src[13];  // [3][1]

			Dest[8] = Src[2];   // [0][2]
			Dest[9] = Src[6];   // [1][2]
			Dest[10] = Src[10]; // [2][2]
			Dest[11] = Src[14]; // [3][2]
		}

	private:

		/**
		 * Output an error message and trigger an ensure
		 */
		static void ErrorEnsure(const char* Message);
	};


	/**
	 * A storage class for compile-time fixed size matrices.
	 */
	template<uint32 NumRows, uint32 NumColumns>
	class TMatrix
	{
	public:

		// Variables.
		float M[NumRows][NumColumns];

		// Constructor
		TMatrix();

		/**
		 * Constructor
		 *
		 * @param InMatrix FMatrix reference
		 */
		TMatrix(const FMatrix& InMatrix);
	};


	template<uint32 NumRows, uint32 NumColumns>
	inline TMatrix<NumRows, NumColumns>::TMatrix() { }


	template<uint32 NumRows, uint32 NumColumns>
	inline TMatrix<NumRows, NumColumns>::TMatrix(const FMatrix& InMatrix)
	{
		for (uint32 RowIndex = 0; (RowIndex < NumRows) && (RowIndex < 4); RowIndex++)
		{
			for (uint32 ColumnIndex = 0; (ColumnIndex < NumColumns) && (ColumnIndex < 4); ColumnIndex++)
			{
				M[RowIndex][ColumnIndex] = InMatrix.M[RowIndex][ColumnIndex];
			}
		}
	}


	struct FBasisVectorMatrix : FMatrix
	{
		// Create Basis matrix from 3 axis vectors and the origin
		FBasisVectorMatrix(const FVector& XAxis, const FVector& YAxis, const FVector& ZAxis, const FVector& Origin);
	};


	struct FLookAtMatrix : FMatrix
	{
		/**
		 * Creates a view matrix given an eye position, a position to look at, and an up vector.
		 * This does the same thing as D3DXMatrixLookAtLH.
		 */
		FLookAtMatrix(const FVector& EyePosition, const FVector& LookAtPosition, const FVector& UpVector);
	};


	template <> struct TIsPODType<FMatrix> { enum { Value = true }; };


	// very high quality 4x4 matrix inverse
	static inline void Inverse4x4(double* dst, const float* src)
	{
		const double s0 = (double)(src[0]); const double s1 = (double)(src[1]); const double s2 = (double)(src[2]); const double s3 = (double)(src[3]);
		const double s4 = (double)(src[4]); const double s5 = (double)(src[5]); const double s6 = (double)(src[6]); const double s7 = (double)(src[7]);
		const double s8 = (double)(src[8]); const double s9 = (double)(src[9]); const double s10 = (double)(src[10]); const double s11 = (double)(src[11]);
		const double s12 = (double)(src[12]); const double s13 = (double)(src[13]); const double s14 = (double)(src[14]); const double s15 = (double)(src[15]);

		double inv[16];
		inv[0] = s5 * s10 * s15 - s5 * s11 * s14 - s9 * s6 * s15 + s9 * s7 * s14 + s13 * s6 * s11 - s13 * s7 * s10;
		inv[1] = -s1 * s10 * s15 + s1 * s11 * s14 + s9 * s2 * s15 - s9 * s3 * s14 - s13 * s2 * s11 + s13 * s3 * s10;
		inv[2] = s1 * s6 * s15 - s1 * s7 * s14 - s5 * s2 * s15 + s5 * s3 * s14 + s13 * s2 * s7 - s13 * s3 * s6;
		inv[3] = -s1 * s6 * s11 + s1 * s7 * s10 + s5 * s2 * s11 - s5 * s3 * s10 - s9 * s2 * s7 + s9 * s3 * s6;
		inv[4] = -s4 * s10 * s15 + s4 * s11 * s14 + s8 * s6 * s15 - s8 * s7 * s14 - s12 * s6 * s11 + s12 * s7 * s10;
		inv[5] = s0 * s10 * s15 - s0 * s11 * s14 - s8 * s2 * s15 + s8 * s3 * s14 + s12 * s2 * s11 - s12 * s3 * s10;
		inv[6] = -s0 * s6 * s15 + s0 * s7 * s14 + s4 * s2 * s15 - s4 * s3 * s14 - s12 * s2 * s7 + s12 * s3 * s6;
		inv[7] = s0 * s6 * s11 - s0 * s7 * s10 - s4 * s2 * s11 + s4 * s3 * s10 + s8 * s2 * s7 - s8 * s3 * s6;
		inv[8] = s4 * s9 * s15 - s4 * s11 * s13 - s8 * s5 * s15 + s8 * s7 * s13 + s12 * s5 * s11 - s12 * s7 * s9;
		inv[9] = -s0 * s9 * s15 + s0 * s11 * s13 + s8 * s1 * s15 - s8 * s3 * s13 - s12 * s1 * s11 + s12 * s3 * s9;
		inv[10] = s0 * s5 * s15 - s0 * s7 * s13 - s4 * s1 * s15 + s4 * s3 * s13 + s12 * s1 * s7 - s12 * s3 * s5;
		inv[11] = -s0 * s5 * s11 + s0 * s7 * s9 + s4 * s1 * s11 - s4 * s3 * s9 - s8 * s1 * s7 + s8 * s3 * s5;
		inv[12] = -s4 * s9 * s14 + s4 * s10 * s13 + s8 * s5 * s14 - s8 * s6 * s13 - s12 * s5 * s10 + s12 * s6 * s9;
		inv[13] = s0 * s9 * s14 - s0 * s10 * s13 - s8 * s1 * s14 + s8 * s2 * s13 + s12 * s1 * s10 - s12 * s2 * s9;
		inv[14] = -s0 * s5 * s14 + s0 * s6 * s13 + s4 * s1 * s14 - s4 * s2 * s13 - s12 * s1 * s6 + s12 * s2 * s5;
		inv[15] = s0 * s5 * s10 - s0 * s6 * s9 - s4 * s1 * s10 + s4 * s2 * s9 + s8 * s1 * s6 - s8 * s2 * s5;

		double det = s0 * inv[0] + s1 * inv[4] + s2 * inv[8] + s3 * inv[12];
		if (det != 0.0)
		{
			det = 1.0 / det;
		}
		for (int i = 0; i < 16; i++)
		{
			dst[i] = inv[i] * det;
		}
	}

	/**
	 * FMatrix inline functions.
	 */

	 // Constructors.

	inline FMatrix::FMatrix()
	{
	}

	inline FMatrix::FMatrix(const FPlane& InX, const FPlane& InY, const FPlane& InZ, const FPlane& InW)
	{
		M[0][0] = InX.X; M[0][1] = InX.Y;  M[0][2] = InX.Z;  M[0][3] = InX.W;
		M[1][0] = InY.X; M[1][1] = InY.Y;  M[1][2] = InY.Z;  M[1][3] = InY.W;
		M[2][0] = InZ.X; M[2][1] = InZ.Y;  M[2][2] = InZ.Z;  M[2][3] = InZ.W;
		M[3][0] = InW.X; M[3][1] = InW.Y;  M[3][2] = InW.Z;  M[3][3] = InW.W;
	}

	inline FMatrix::FMatrix(const FVector& InX, const FVector& InY, const FVector& InZ, const FVector& InW)
	{
		M[0][0] = InX.X; M[0][1] = InX.Y;  M[0][2] = InX.Z;  M[0][3] = 0.0f;
		M[1][0] = InY.X; M[1][1] = InY.Y;  M[1][2] = InY.Z;  M[1][3] = 0.0f;
		M[2][0] = InZ.X; M[2][1] = InZ.Y;  M[2][2] = InZ.Z;  M[2][3] = 0.0f;
		M[3][0] = InW.X; M[3][1] = InW.Y;  M[3][2] = InW.Z;  M[3][3] = 1.0f;
	}


	inline void FMatrix::SetIdentity()
	{
		M[0][0] = 1; M[0][1] = 0;  M[0][2] = 0;  M[0][3] = 0;
		M[1][0] = 0; M[1][1] = 1;  M[1][2] = 0;  M[1][3] = 0;
		M[2][0] = 0; M[2][1] = 0;  M[2][2] = 1;  M[2][3] = 0;
		M[3][0] = 0; M[3][1] = 0;  M[3][2] = 0;  M[3][3] = 1;
	}


	inline void FMatrix::operator*=(const FMatrix& Other)
	{
		VectorMatrixMultiply(this, this, &Other);
	}


	inline FMatrix FMatrix::operator*(const FMatrix& Other) const
	{
		FMatrix Result;
		VectorMatrixMultiply(&Result, this, &Other);
		return Result;
	}


	inline FMatrix	FMatrix::operator+(const FMatrix& Other) const
	{
		FMatrix ResultMat;

		for (int32 X = 0; X < 4; X++)
		{
			for (int32 Y = 0; Y < 4; Y++)
			{
				ResultMat.M[X][Y] = M[X][Y] + Other.M[X][Y];
			}
		}

		return ResultMat;
	}

	inline void FMatrix::operator+=(const FMatrix& Other)
	{
		*this = *this + Other;
	}

	inline FMatrix	FMatrix::operator*(float Other) const
	{
		FMatrix ResultMat;

		for (int32 X = 0; X < 4; X++)
		{
			for (int32 Y = 0; Y < 4; Y++)
			{
				ResultMat.M[X][Y] = M[X][Y] * Other;
			}
		}

		return ResultMat;
	}

	inline void FMatrix::operator*=(float Other)
	{
		*this = *this * Other;
	}

	// Comparison operators.

	inline bool FMatrix::operator==(const FMatrix& Other) const
	{
		for (int32 X = 0; X < 4; X++)
		{
			for (int32 Y = 0; Y < 4; Y++)
			{
				if (M[X][Y] != Other.M[X][Y])
				{
					return false;
				}
			}
		}

		return true;
	}

	// Error-tolerant comparison.
	inline bool FMatrix::Equals(const FMatrix& Other, float Tolerance/*=KINDA_SMALL_NUMBER*/) const
	{
		for (int32 X = 0; X < 4; X++)
		{
			for (int32 Y = 0; Y < 4; Y++)
			{
				if (FMath::Abs(M[X][Y] - Other.M[X][Y]) > Tolerance)
				{
					return false;
				}
			}
		}

		return true;
	}

	inline bool FMatrix::operator!=(const FMatrix& Other) const
	{
		return !(*this == Other);
	}


	// Homogeneous transform.

	inline FVector4 FMatrix::TransformFVector4(const FVector4& P) const
	{
		FVector4 Result;
		VectorRegister VecP = VectorLoadAligned(&P);
		VectorRegister VecR = VectorTransformVector(VecP, this);
		VectorStoreAligned(VecR, &Result);
		return Result;
	}


	// Transform position

	/** Transform a location - will take into account translation part of the FMatrix. */
	inline FVector4 FMatrix::TransformPosition(const FVector& V) const
	{
		return TransformFVector4(FVector4(V.X, V.Y, V.Z, 1.0f));
	}

	/** Inverts the matrix and then transforms V - correctly handles scaling in this matrix. */
	inline FVector FMatrix::InverseTransformPosition(const FVector& V) const
	{
		FMatrix InvSelf = this->InverseFast();
		return InvSelf.TransformPosition(V);
	}

	// Transform vector

	/**
	 *	Transform a direction vector - will not take into account translation part of the FMatrix.
	 *	If you want to transform a surface normal (or plane) and correctly account for non-uniform scaling you should use TransformByUsingAdjointT.
	 */
	inline FVector4 FMatrix::TransformVector(const FVector& V) const
	{
		return TransformFVector4(FVector4(V.X, V.Y, V.Z, 0.0f));
	}

	/** Faster version of InverseTransformVector that assumes no scaling. WARNING: Will NOT work correctly if there is scaling in the matrix. */
	inline FVector FMatrix::InverseTransformVector(const FVector& V) const
	{
		FMatrix InvSelf = this->InverseFast();
		return InvSelf.TransformVector(V);
	}


	// Transpose.

	inline FMatrix FMatrix::GetTransposed() const
	{
		FMatrix	Result;

		Result.M[0][0] = M[0][0];
		Result.M[0][1] = M[1][0];
		Result.M[0][2] = M[2][0];
		Result.M[0][3] = M[3][0];

		Result.M[1][0] = M[0][1];
		Result.M[1][1] = M[1][1];
		Result.M[1][2] = M[2][1];
		Result.M[1][3] = M[3][1];

		Result.M[2][0] = M[0][2];
		Result.M[2][1] = M[1][2];
		Result.M[2][2] = M[2][2];
		Result.M[2][3] = M[3][2];

		Result.M[3][0] = M[0][3];
		Result.M[3][1] = M[1][3];
		Result.M[3][2] = M[2][3];
		Result.M[3][3] = M[3][3];

		return Result;
	}

	// Determinant.

	inline float FMatrix::Determinant() const
	{
		return	M[0][0] * (
			M[1][1] * (M[2][2] * M[3][3] - M[2][3] * M[3][2]) -
			M[2][1] * (M[1][2] * M[3][3] - M[1][3] * M[3][2]) +
			M[3][1] * (M[1][2] * M[2][3] - M[1][3] * M[2][2])
			) -
			M[1][0] * (
				M[0][1] * (M[2][2] * M[3][3] - M[2][3] * M[3][2]) -
				M[2][1] * (M[0][2] * M[3][3] - M[0][3] * M[3][2]) +
				M[3][1] * (M[0][2] * M[2][3] - M[0][3] * M[2][2])
				) +
			M[2][0] * (
				M[0][1] * (M[1][2] * M[3][3] - M[1][3] * M[3][2]) -
				M[1][1] * (M[0][2] * M[3][3] - M[0][3] * M[3][2]) +
				M[3][1] * (M[0][2] * M[1][3] - M[0][3] * M[1][2])
				) -
			M[3][0] * (
				M[0][1] * (M[1][2] * M[2][3] - M[1][3] * M[2][2]) -
				M[1][1] * (M[0][2] * M[2][3] - M[0][3] * M[2][2]) +
				M[2][1] * (M[0][2] * M[1][3] - M[0][3] * M[1][2])
				);
	}

	/** Calculate determinant of rotation 3x3 matrix */
	inline float FMatrix::RotDeterminant() const
	{
		return
			M[0][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1]) -
			M[1][0] * (M[0][1] * M[2][2] - M[0][2] * M[2][1]) +
			M[2][0] * (M[0][1] * M[1][2] - M[0][2] * M[1][1]);
	}

	// Inverse.
	/** Fast path, doesn't check for nil matrices in final release builds */
	inline FMatrix FMatrix::InverseFast() const
	{
		// If we're in non final release, then make sure we're not creating NaNs
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	// Check for zero scale matrix to invert
		if (GetScaledAxis(EAxis::X).IsNearlyZero(SMALL_NUMBER) &&
			GetScaledAxis(EAxis::Y).IsNearlyZero(SMALL_NUMBER) &&
			GetScaledAxis(EAxis::Z).IsNearlyZero(SMALL_NUMBER))
		{
			ErrorEnsure(("FMatrix::InverseFast(), trying to invert a NIL matrix, this results in NaNs! Use Inverse() instead."));
		}
		else
		{
			const float	Det = Determinant();

			if (Det == 0.0f || !FMath::IsFinite(Det))
			{
				ErrorEnsure(("FMatrix::InverseFast(), trying to invert a non-invertible matrix, this results in NaNs! Use Inverse() instead."));
			}
		}
#endif
		FMatrix Result;
		VectorMatrixInverse(&Result, this);
		return Result;
	}

	// Inverse.
	inline FMatrix FMatrix::Inverse() const
	{
		FMatrix Result;

		// Check for zero scale matrix to invert
		if (GetScaledAxis(EAxis::X).IsNearlyZero(SMALL_NUMBER) &&
			GetScaledAxis(EAxis::Y).IsNearlyZero(SMALL_NUMBER) &&
			GetScaledAxis(EAxis::Z).IsNearlyZero(SMALL_NUMBER))
		{
			// just set to zero - avoids unsafe inverse of zero and duplicates what QNANs were resulting in before (scaling away all children)
			Result = FMatrix::Identity;
		}
		else
		{
			const float	Det = Determinant();

			if (Det == 0.0f)
			{
				Result = FMatrix::Identity;
			}
			else
			{
				VectorMatrixInverse(&Result, this);
			}
		}

		return Result;
	}

	inline FMatrix FMatrix::TransposeAdjoint() const
	{
		FMatrix TA;

		TA.M[0][0] = this->M[1][1] * this->M[2][2] - this->M[1][2] * this->M[2][1];
		TA.M[0][1] = this->M[1][2] * this->M[2][0] - this->M[1][0] * this->M[2][2];
		TA.M[0][2] = this->M[1][0] * this->M[2][1] - this->M[1][1] * this->M[2][0];
		TA.M[0][3] = 0.f;

		TA.M[1][0] = this->M[2][1] * this->M[0][2] - this->M[2][2] * this->M[0][1];
		TA.M[1][1] = this->M[2][2] * this->M[0][0] - this->M[2][0] * this->M[0][2];
		TA.M[1][2] = this->M[2][0] * this->M[0][1] - this->M[2][1] * this->M[0][0];
		TA.M[1][3] = 0.f;

		TA.M[2][0] = this->M[0][1] * this->M[1][2] - this->M[0][2] * this->M[1][1];
		TA.M[2][1] = this->M[0][2] * this->M[1][0] - this->M[0][0] * this->M[1][2];
		TA.M[2][2] = this->M[0][0] * this->M[1][1] - this->M[0][1] * this->M[1][0];
		TA.M[2][3] = 0.f;

		TA.M[3][0] = 0.f;
		TA.M[3][1] = 0.f;
		TA.M[3][2] = 0.f;
		TA.M[3][3] = 1.f;

		return TA;
	}

	// NOTE: There is some compiler optimization issues with WIN64 that cause inline to cause a crash
	// Remove any scaling from this matrix (ie magnitude of each row is 1)
	inline void FMatrix::RemoveScaling(float Tolerance/*=SMALL_NUMBER*/)
	{
		// For each row, find magnitude, and if its non-zero re-scale so its unit length.
		const float SquareSum0 = (M[0][0] * M[0][0]) + (M[0][1] * M[0][1]) + (M[0][2] * M[0][2]);
		const float SquareSum1 = (M[1][0] * M[1][0]) + (M[1][1] * M[1][1]) + (M[1][2] * M[1][2]);
		const float SquareSum2 = (M[2][0] * M[2][0]) + (M[2][1] * M[2][1]) + (M[2][2] * M[2][2]);
		const float Scale0 = FMath::FloatSelect(SquareSum0 - Tolerance, FMath::InvSqrt(SquareSum0), 1.0f);
		const float Scale1 = FMath::FloatSelect(SquareSum1 - Tolerance, FMath::InvSqrt(SquareSum1), 1.0f);
		const float Scale2 = FMath::FloatSelect(SquareSum2 - Tolerance, FMath::InvSqrt(SquareSum2), 1.0f);
		M[0][0] *= Scale0;
		M[0][1] *= Scale0;
		M[0][2] *= Scale0;
		M[1][0] *= Scale1;
		M[1][1] *= Scale1;
		M[1][2] *= Scale1;
		M[2][0] *= Scale2;
		M[2][1] *= Scale2;
		M[2][2] *= Scale2;
	}

	// Returns matrix without scale information
	inline FMatrix FMatrix::GetMatrixWithoutScale(float Tolerance/*=SMALL_NUMBER*/) const
	{
		FMatrix Result = *this;
		Result.RemoveScaling(Tolerance);
		return Result;
	}

	/** Remove any scaling from this matrix (ie magnitude of each row is 1) and return the 3D scale vector that was initially present. */
	inline FVector FMatrix::ExtractScaling(float Tolerance/*=SMALL_NUMBER*/)
	{
		FVector Scale3D(0, 0, 0);

		// For each row, find magnitude, and if its non-zero re-scale so its unit length.
		const float SquareSum0 = (M[0][0] * M[0][0]) + (M[0][1] * M[0][1]) + (M[0][2] * M[0][2]);
		const float SquareSum1 = (M[1][0] * M[1][0]) + (M[1][1] * M[1][1]) + (M[1][2] * M[1][2]);
		const float SquareSum2 = (M[2][0] * M[2][0]) + (M[2][1] * M[2][1]) + (M[2][2] * M[2][2]);

		if (SquareSum0 > Tolerance)
		{
			float Scale0 = FMath::Sqrt(SquareSum0);
			Scale3D[0] = Scale0;
			float InvScale0 = 1.f / Scale0;
			M[0][0] *= InvScale0;
			M[0][1] *= InvScale0;
			M[0][2] *= InvScale0;
		}
		else
		{
			Scale3D[0] = 0;
		}

		if (SquareSum1 > Tolerance)
		{
			float Scale1 = FMath::Sqrt(SquareSum1);
			Scale3D[1] = Scale1;
			float InvScale1 = 1.f / Scale1;
			M[1][0] *= InvScale1;
			M[1][1] *= InvScale1;
			M[1][2] *= InvScale1;
		}
		else
		{
			Scale3D[1] = 0;
		}

		if (SquareSum2 > Tolerance)
		{
			float Scale2 = FMath::Sqrt(SquareSum2);
			Scale3D[2] = Scale2;
			float InvScale2 = 1.f / Scale2;
			M[2][0] *= InvScale2;
			M[2][1] *= InvScale2;
			M[2][2] *= InvScale2;
		}
		else
		{
			Scale3D[2] = 0;
		}

		return Scale3D;
	}

	/** return a 3D scale vector calculated from this matrix (where each component is the magnitude of a row vector). */
	inline FVector FMatrix::GetScaleVector(float Tolerance/*=SMALL_NUMBER*/) const
	{
		FVector Scale3D(1, 1, 1);

		// For each row, find magnitude, and if its non-zero re-scale so its unit length.
		for (int32 i = 0; i < 3; i++)
		{
			const float SquareSum = (M[i][0] * M[i][0]) + (M[i][1] * M[i][1]) + (M[i][2] * M[i][2]);
			if (SquareSum > Tolerance)
			{
				Scale3D[i] = FMath::Sqrt(SquareSum);
			}
			else
			{
				Scale3D[i] = 0.f;
			}
		}

		return Scale3D;
	}
	// Remove any translation from this matrix
	inline FMatrix FMatrix::RemoveTranslation() const
	{
		FMatrix Result = *this;
		Result.M[3][0] = 0.0f;
		Result.M[3][1] = 0.0f;
		Result.M[3][2] = 0.0f;
		return Result;
	}

	inline FMatrix FMatrix::ConcatTranslation(const FVector& Translation) const
	{
		FMatrix Result;

		float* __restrict Dest = &Result.M[0][0];
		const float* __restrict Src = &M[0][0];
		const float* __restrict Trans = &Translation.X;

		Dest[0] = Src[0];
		Dest[1] = Src[1];
		Dest[2] = Src[2];
		Dest[3] = Src[3];
		Dest[4] = Src[4];
		Dest[5] = Src[5];
		Dest[6] = Src[6];
		Dest[7] = Src[7];
		Dest[8] = Src[8];
		Dest[9] = Src[9];
		Dest[10] = Src[10];
		Dest[11] = Src[11];
		Dest[12] = Src[12] + Trans[0];
		Dest[13] = Src[13] + Trans[1];
		Dest[14] = Src[14] + Trans[2];
		Dest[15] = Src[15];

		return Result;
	}

	/** Returns true if any element of this matrix is not finite */
	inline bool FMatrix::ContainsNaN() const
	{
		for (int32 i = 0; i < 4; i++)
		{
			for (int32 j = 0; j < 4; j++)
			{
				if (!FMath::IsFinite(M[i][j]))
				{
					return true;
				}
			}
		}

		return false;
	}

	/** @return the maximum magnitude of any row of the matrix. */
	inline float FMatrix::GetMaximumAxisScale() const
	{
		const float MaxRowScaleSquared = FMath::Max(
			GetScaledAxis(EAxis::X).SizeSquared(),
			FMath::Max(
				GetScaledAxis(EAxis::Y).SizeSquared(),
				GetScaledAxis(EAxis::Z).SizeSquared()
			)
		);
		return FMath::Sqrt(MaxRowScaleSquared);
	}

	inline void FMatrix::ScaleTranslation(const FVector& InScale3D)
	{
		M[3][0] *= InScale3D.X;
		M[3][1] *= InScale3D.Y;
		M[3][2] *= InScale3D.Z;
	}

	// GetOrigin

	inline FVector FMatrix::GetOrigin() const
	{
		return FVector(M[3][0], M[3][1], M[3][2]);
	}

	inline FVector FMatrix::GetScaledAxis(EAxis::Type InAxis) const
	{
		switch (InAxis)
		{
		case EAxis::X:
			return FVector(M[0][0], M[0][1], M[0][2]);

		case EAxis::Y:
			return FVector(M[1][0], M[1][1], M[1][2]);

		case EAxis::Z:
			return FVector(M[2][0], M[2][1], M[2][2]);

		default:
			ensure(0);
			return FVector::ZeroVector;
		}
	}

	inline void FMatrix::GetScaledAxes(FVector& X, FVector& Y, FVector& Z) const
	{
		X.X = M[0][0]; X.Y = M[0][1]; X.Z = M[0][2];
		Y.X = M[1][0]; Y.Y = M[1][1]; Y.Z = M[1][2];
		Z.X = M[2][0]; Z.Y = M[2][1]; Z.Z = M[2][2];
	}

	inline FVector FMatrix::GetUnitAxis(EAxis::Type InAxis) const
	{
		return GetScaledAxis(InAxis).GetSafeNormal();
	}

	inline void FMatrix::GetUnitAxes(FVector& X, FVector& Y, FVector& Z) const
	{
		GetScaledAxes(X, Y, Z);
		X.Normalize();
		Y.Normalize();
		Z.Normalize();
	}

	inline void FMatrix::SetAxis(int32 i, const FVector& Axis)
	{
		//checkSlow(i >= 0 && i <= 2);
		M[i][0] = Axis.X;
		M[i][1] = Axis.Y;
		M[i][2] = Axis.Z;
	}

	inline void FMatrix::SetOrigin(const FVector& NewOrigin)
	{
		M[3][0] = NewOrigin.X;
		M[3][1] = NewOrigin.Y;
		M[3][2] = NewOrigin.Z;
	}

	inline void FMatrix::SetAxes(FVector* Axis0 /*= NULL*/, FVector* Axis1 /*= NULL*/, FVector* Axis2 /*= NULL*/, FVector* Origin /*= NULL*/)
	{
		if (Axis0 != NULL)
		{
			M[0][0] = Axis0->X;
			M[0][1] = Axis0->Y;
			M[0][2] = Axis0->Z;
		}
		if (Axis1 != NULL)
		{
			M[1][0] = Axis1->X;
			M[1][1] = Axis1->Y;
			M[1][2] = Axis1->Z;
		}
		if (Axis2 != NULL)
		{
			M[2][0] = Axis2->X;
			M[2][1] = Axis2->Y;
			M[2][2] = Axis2->Z;
		}
		if (Origin != NULL)
		{
			M[3][0] = Origin->X;
			M[3][1] = Origin->Y;
			M[3][2] = Origin->Z;
		}
	}

	inline FVector FMatrix::GetColumn(int32 i) const
	{
		//checkSlow(i >= 0 && i <= 3);
		return FVector(M[0][i], M[1][i], M[2][i]);
	}

	inline void FMatrix::SetColumn(int32 i, FVector Value)
	{
		//checkSlow(i >= 0 && i <= 3);
		M[0][i] = Value.X;
		M[1][i] = Value.Y;
		M[2][i] = Value.Z;
	}

	inline bool MakeFrustumPlane(float A, float B, float C, float D, FPlane& OutPlane)
	{
		const float	LengthSquared = A * A + B * B + C * C;
		if (LengthSquared > DELTA* DELTA)
		{
			const float	InvLength = FMath::InvSqrt(LengthSquared);
			OutPlane = FPlane(-A * InvLength, -B * InvLength, -C * InvLength, D * InvLength);
			return 1;
		}
		else
			return 0;
	}

	// Frustum plane extraction.
	inline bool FMatrix::GetFrustumNearPlane(FPlane& OutPlane) const
	{
		return MakeFrustumPlane(
			M[0][2],
			M[1][2],
			M[2][2],
			M[3][2],
			OutPlane
		);
	}

	inline bool FMatrix::GetFrustumFarPlane(FPlane& OutPlane) const
	{
		return MakeFrustumPlane(
			M[0][3] - M[0][2],
			M[1][3] - M[1][2],
			M[2][3] - M[2][2],
			M[3][3] - M[3][2],
			OutPlane
		);
	}

	inline bool FMatrix::GetFrustumLeftPlane(FPlane& OutPlane) const
	{
		return MakeFrustumPlane(
			M[0][3] + M[0][0],
			M[1][3] + M[1][0],
			M[2][3] + M[2][0],
			M[3][3] + M[3][0],
			OutPlane
		);
	}

	inline bool FMatrix::GetFrustumRightPlane(FPlane& OutPlane) const
	{
		return MakeFrustumPlane(
			M[0][3] - M[0][0],
			M[1][3] - M[1][0],
			M[2][3] - M[2][0],
			M[3][3] - M[3][0],
			OutPlane
		);
	}

	inline bool FMatrix::GetFrustumTopPlane(FPlane& OutPlane) const
	{
		return MakeFrustumPlane(
			M[0][3] - M[0][1],
			M[1][3] - M[1][1],
			M[2][3] - M[2][1],
			M[3][3] - M[3][1],
			OutPlane
		);
	}

	inline bool FMatrix::GetFrustumBottomPlane(FPlane& OutPlane) const
	{
		return MakeFrustumPlane(
			M[0][3] + M[0][1],
			M[1][3] + M[1][1],
			M[2][3] + M[2][1],
			M[3][3] + M[3][1],
			OutPlane
		);
	}

	/**
	 * Utility for mirroring this transform across a certain plane,
	 * and flipping one of the axis as well.
	 */
	inline void FMatrix::Mirror(EAxis::Type MirrorAxis, EAxis::Type FlipAxis)
	{
		if (MirrorAxis == EAxis::X)
		{
			M[0][0] *= -1.f;
			M[1][0] *= -1.f;
			M[2][0] *= -1.f;

			M[3][0] *= -1.f;
		}
		else if (MirrorAxis == EAxis::Y)
		{
			M[0][1] *= -1.f;
			M[1][1] *= -1.f;
			M[2][1] *= -1.f;

			M[3][1] *= -1.f;
		}
		else if (MirrorAxis == EAxis::Z)
		{
			M[0][2] *= -1.f;
			M[1][2] *= -1.f;
			M[2][2] *= -1.f;

			M[3][2] *= -1.f;
		}

		if (FlipAxis == EAxis::X)
		{
			M[0][0] *= -1.f;
			M[0][1] *= -1.f;
			M[0][2] *= -1.f;
		}
		else if (FlipAxis == EAxis::Y)
		{
			M[1][0] *= -1.f;
			M[1][1] *= -1.f;
			M[1][2] *= -1.f;
		}
		else if (FlipAxis == EAxis::Z)
		{
			M[2][0] *= -1.f;
			M[2][1] *= -1.f;
			M[2][2] *= -1.f;
		}
	}

	/**
	 * Apply Scale to this matrix
	 */
	inline FMatrix FMatrix::ApplyScale(float Scale) const
	{
		FMatrix ScaleMatrix(
			FPlane(Scale, 0.0f, 0.0f, 0.0f),
			FPlane(0.0f, Scale, 0.0f, 0.0f),
			FPlane(0.0f, 0.0f, Scale, 0.0f),
			FPlane(0.0f, 0.0f, 0.0f, 1.0f)
		);
		return ScaleMatrix * (*this);
	}



	/**
	 * FPlane inline functions.
	 */

	inline FPlane FPlane::TransformBy(const FMatrix& M) const
	{
		const FMatrix tmpTA = M.TransposeAdjoint();
		const float DetM = M.Determinant();
		return this->TransformByUsingAdjointT(M, DetM, tmpTA);
	}

	inline FPlane FPlane::TransformByUsingAdjointT(const FMatrix& M, float DetM, const FMatrix& TA) const
	{
		FVector newNorm = TA.TransformVector(*this).GetSafeNormal();

		if (DetM < 0.f)
		{
			newNorm *= -1.0f;
		}

		return FPlane(M.TransformPosition(*this * W), newNorm);
	}


	inline FBasisVectorMatrix::FBasisVectorMatrix(const FVector& XAxis, const FVector& YAxis, const FVector& ZAxis, const FVector& Origin)
	{
		for (uint32 RowIndex = 0; RowIndex < 3; RowIndex++)
		{
			M[RowIndex][0] = (&XAxis.X)[RowIndex];
			M[RowIndex][1] = (&YAxis.X)[RowIndex];
			M[RowIndex][2] = (&ZAxis.X)[RowIndex];
			M[RowIndex][3] = 0.0f;
		}
		M[3][0] = Origin | XAxis;
		M[3][1] = Origin | YAxis;
		M[3][2] = Origin | ZAxis;
		M[3][3] = 1.0f;
	}


	inline FLookAtMatrix::FLookAtMatrix(const FVector& EyePosition, const FVector& LookAtPosition, const FVector& UpVector)
	{
		const FVector ZAxis = (LookAtPosition - EyePosition).GetSafeNormal();
		const FVector XAxis = (UpVector ^ ZAxis).GetSafeNormal();
		const FVector YAxis = ZAxis ^ XAxis;

		for (uint32 RowIndex = 0; RowIndex < 3; RowIndex++)
		{
			M[RowIndex][0] = (&XAxis.X)[RowIndex];
			M[RowIndex][1] = (&YAxis.X)[RowIndex];
			M[RowIndex][2] = (&ZAxis.X)[RowIndex];
			M[RowIndex][3] = 0.0f;
		}
		M[3][0] = -EyePosition | XAxis;
		M[3][1] = -EyePosition | YAxis;
		M[3][2] = -EyePosition | ZAxis;
		M[3][3] = 1.0f;
	}



}
