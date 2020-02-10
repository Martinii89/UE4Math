// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

namespace UE4Math
{
	/**
	 * Traits class which tests if a type is POD.
	 */
	template <typename T>
	struct TIsPODType
	{
		enum { Value = __is_pod(T) };
	};
}


