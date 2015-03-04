//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Wednesday, 14 January 2009 12:18:18 AM
//////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER

#ifndef __OBJECT_FILE_H_6DD59E03_6E04_4399_9F7C_DD0E0B3DA9E3_
#define __OBJECT_FILE_H_6DD59E03_6E04_4399_9F7C_DD0E0B3DA9E3_

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "mirror/mirror_abi.h"
#include "mirror/forward_decls.h"
#include "mirror/record_reactor.h"
#include "io/path.h"
#include "core/noncopyable.h"

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////

namespace tycho
{
namespace mirror
{
	/// Retrieve the record for the passed object name.
//	record* load_object(const char* object_name);

	/// 
//	bool load_object(const char* object_name, record_reactor*);
	
	/// File system based object record
    class TYCHO_MIRROR_ABI object_file : core::noncopyable
    {
    public:
		/// Construct from the object file at the specified path. This constructs
		/// a queryable representation of the object file retrievable by calling
		/// get_record.
		object_file(const io::path&);
		
		/// Construct from the object file at the specified path. This takes a reactor
		/// interface to call back during passing to handle declarations as they are 
		/// encountered and as such is faster than using the record interface as it 
		/// does not need to build an intermediate data structure. This can also work 
		/// from a fixed sized buffer rather than need the whole file loaded in memory.
		object_file(const io::path&, record_reactor*);
		
		/// destructor
		~object_file();
		
		/// \returns the record for this object. 
		/// \warning This is only valid if the non-reactor constructor was used
		const record& get_record() const;
    
    private:
		record* m_record;
    };

} // end namespace
} // end namespace

#endif // __OBJECT_FILE_H_6DD59E03_6E04_4399_9F7C_DD0E0B3DA9E3_
