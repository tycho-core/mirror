//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Sunday, 7 December 2008 9:46:31 PM
//////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER

#ifndef __MIRROR_ABI_H_7E4378BB_2BB0_48A4_B9C1_CD6917E2AF54_
#define __MIRROR_ABI_H_7E4378BB_2BB0_48A4_B9C1_CD6917E2AF54_

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "core/core_abi.h"

#if TYCHO_PC

// DLL interface
#ifdef TYCHO_MIRROR_EXPORTS
#define TYCHO_MIRROR_ABI __declspec(dllexport)
#else
#define TYCHO_MIRROR_ABI __declspec(dllimport)
#endif 

// disable a few warnings globally. should move these into specific cpp's to avoid polluting
// user header files
#pragma warning(disable : 4251) // class needs to have dll-interface to be used by clients of class ''
#pragma warning(disable : 4355) // 'this' : used in base member initializer list

#else // TYCHO_PC

#define TYCHO_MIRROR_ABI

#endif // TYCHO_GC

#ifdef __cplusplus
#include "core/memory/new.h"
#include "core/memory.h"
#include "core/debug/assert.h"
#endif 

#endif // __MIRROR_ABI_H_7E4378BB_2BB0_48A4_B9C1_CD6917E2AF54_
