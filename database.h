//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Monday, 12 January 2009 12:59:34 AM
//////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER

#ifndef __DATABASE_H_1FEEBABC_E7D7_428E_8B06_7FABCAA707B9_
#define __DATABASE_H_1FEEBABC_E7D7_428E_8B06_7FABCAA707B9_

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "mirror/mirror_abi.h"
#include "mirror/forward_decls.h"
#include "glass/forward_decls.h"


//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////

namespace tycho
{
namespace mirror
{

	///	Abstract interface to write and read objects to and from backing storage.
    class TYCHO_MIRROR_ABI database
    {
    public:
		//TODO: 
		//		versioning
		//		single identifying integer for each specific version of the db (perforce CL number)
		//		querying
		/// constructor
		
   		/// destructor
		virtual ~database() {}
				
		/// start a transaction
		/// \returns id for the transaction
		virtual int start_transaction() = 0;
		
		/// commit a transaction
		virtual bool commit_transaction(int id) = 0;
		
		/// abort a transaction
		virtual bool abort_transaction(int id) = 0;
		
		/// load an object
		virtual void* load_object(int trx_id, const char* name) = 0;
		
		/// save an object
		virtual bool store_object(int trx_id, const void* ptr, const glass::base_type* type, const glass::name& name) = 0;
		
		/// resolve a label to a revision number
		virtual int resolve_label(const char*) = 0;
    };

} // end namespace
} // end namespace

#endif // __DATABASE_H_1FEEBABC_E7D7_428E_8B06_7FABCAA707B9_
