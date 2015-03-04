//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Wednesday, 14 January 2009 1:06:02 AM
//////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER

#ifndef __RECORD_H_958566FD_FD76_4F38_B4ED_3BBD443CF252_
#define __RECORD_H_958566FD_FD76_4F38_B4ED_3BBD443CF252_

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
	
	/// types that record values can take
	enum value_type
	{
		vt_int,
		vt_uint,
		vt_string,
		vt_bool,
		vt_record,
		vt_float2
	};
	
	enum type_modifier
	{
		vt_array = 1,
	};

	class value
	{
	
	};
	
	/// Abstract interface to raw object data.
    class TYCHO_MIRROR_ABI record
    {	
    public:
		/// destructor
		virtual ~record() {}
		
		/// \returns the number of base classes declared in the record
		virtual int get_num_base_records() const = 0;
		
		/// \returns the i'th base class record
		virtual const record& get_base_record(int i) const = 0;
		
		/// \returns the number of values in the record
		virtual int get_num_values() const = 0;
		
		/// \returns the i'th record value
		virtual const value& get_value(int i) const = 0;
    };

} // end namespace
} // end namespace

#endif // __RECORD_H_958566FD_FD76_4F38_B4ED_3BBD443CF252_
