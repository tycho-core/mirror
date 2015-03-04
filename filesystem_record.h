//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Friday, 16 January 2009 12:09:36 AM
//////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER

#ifndef __FILESYSTEM_RECORD_H_6F1DDFD4_CF2F_4937_ACD6_B394727A71F0_
#define __FILESYSTEM_RECORD_H_6F1DDFD4_CF2F_4937_ACD6_B394727A71F0_

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "mirror/mirror_abi.h"
#include "mirror/forward_decls.h"
#include "mirror/record.h"

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////

namespace tycho
{
namespace mirror
{

	/// Filesystem DB record
    class TYCHO_MIRROR_ABI filesystem_record : public record
    {
    public:
		/// \name record interface
		//@{
		int get_num_base_records() const
			{ return 0; }
			
		const record& get_base_record(int i) const
			{ return *this; }
			
		int get_num_values() const
			{ return 0; }
			
//		const value& get_value(int i) const
//			{ return value(); }
		//@}
		
    private:
    
    };

} // end namespace
} // end namespace

#endif // __FILESYSTEM_RECORD_H_6F1DDFD4_CF2F_4937_ACD6_B394727A71F0_
