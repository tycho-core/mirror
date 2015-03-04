//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Thursday, 15 January 2009 11:42:58 PM
//////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER

#ifndef __REVISION_H_A6F1255E_941A_4FC8_BB53_9CC2BE3CDCA0_
#define __REVISION_H_A6F1255E_941A_4FC8_BB53_9CC2BE3CDCA0_

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "mirror/mirror_abi.h"
#include "mirror/forward_decls.h"
#include <string>


//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////

namespace tycho
{
namespace mirror
{

	/// Identifies a particular change in the database.
    class TYCHO_MIRROR_ABI revision
	{
	public:
		/// construct from an integer revision number
		revision(int num);
		
		/// construct from a string label name
		revision(const char* label);
		
		/// If the revision is already a revision number this returns 
		/// that otherwise it resolves the label to a revision number
		/// and returns it.
		int resolve(database* db);
		
	private:
		int			m_num;
		std::string m_label;
	};
	
} // end namespace
} // end namespace

#endif // __REVISION_H_A6F1255E_941A_4FC8_BB53_9CC2BE3CDCA0_
