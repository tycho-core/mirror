//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Wednesday, 14 January 2009 1:53:44 AM
//////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER

#ifndef __RECORD_REACTOR_H_5FE787B0_D8AE_4A7E_8CD6_D8935DA189A8_
#define __RECORD_REACTOR_H_5FE787B0_D8AE_4A7E_8CD6_D8935DA189A8_

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "mirror/mirror_abi.h"
#include "mirror/forward_decls.h"


//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////

namespace tycho
{
namespace mirror
{

	/// Event interface used during record passing to report declarations encountered. 
    class TYCHO_MIRROR_ABI record_reactor
    {
    public:
		/// destructor
		virtual ~record_reactor() {}
    
		/// assignment declaration
		virtual void start_assignment() = 0;
		
		/// signals the start of an array declaration
		virtual void start_array_assignment() = 0;
				
		/// signals the end of an array declaration
		virtual void end_array_assignment() = 0;
		
		/// signals the beginning of an object
		virtual void start_object() = 0;		
    };

} // end namespace
} // end namespace

#endif // __RECORD_REACTOR_H_5FE787B0_D8AE_4A7E_8CD6_D8935DA189A8_
