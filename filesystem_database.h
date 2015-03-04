//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Tuesday, 13 January 2009 1:01:13 AM
//////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER

#ifndef __FILESYSTEM_DATABASE_H_E627B599_ED09_45DB_B020_9B34E4933E62_
#define __FILESYSTEM_DATABASE_H_E627B599_ED09_45DB_B020_9B34E4933E62_

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "mirror/mirror_abi.h"
#include "mirror/forward_decls.h"
#include "mirror/database.h"
#include "glass/forward_decls.h"
#include "io/path.h"
#include "io/forward_decls.h"

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////

namespace tycho
{
namespace mirror
{

	/// This manages the object databases on the filesystem using a structure
	/// layout that mimics the object namespace layout. Each individual object 
	/// is stored in its own file and contains its data and that of any 
	/// base classes it has.
    class TYCHO_MIRROR_ABI filesystem_database : public database
    {
    public:
		/// constructor
		/// \param root_path Filesystem path of the database root directory
		/// \param revision  Database revision to use. 
		filesystem_database(io::interface* io, const io::path& root_path);
		
		/// destructor
		~filesystem_database();
		
		/// \name database interface
		//@{
		int start_transaction();
		bool commit_transaction(int trx_id);
		bool abort_transaction(int trx_id);
		void* load_object(int trx_id, const char* name);
		bool store_object(int trx_id, const void* ptr, const glass::base_type* type, const glass::name&);
		int resolve_label(const char*);
		//@}

	private:
		bool dispatch(io::stream_ptr str, int depth, const void* obj_ptr, const glass::base_type* type);
		bool write_int32(io::stream_ptr str, int depth, const void* obj_ptr, const glass::base_type* type);
		bool write_uint32(io::stream_ptr str, int depth, const void* obj_ptr, const glass::base_type* type);
		bool write_float32(io::stream_ptr str, int depth, const void* obj_ptr, const glass::base_type* type);
		bool write_string(io::stream_ptr str, int depth, const void* obj_ptr, const glass::base_type* type);
		bool write_class(io::stream_ptr str, int depth, const void* obj_ptr, const glass::base_type* type);
		bool write_enum(io::stream_ptr str, int depth, const void* obj_ptr, const glass::base_type* type);
		bool write_bitfield(io::stream_ptr str, int depth, const void* obj_ptr, const glass::base_type* type);
		bool write_pointer(io::stream_ptr str, int depth, const void* obj_ptr, const glass::base_type* type);

    private:
		const static int FileVersion = 1;
        io::interface* m_io;
		io::path m_root_path;
		io::path m_transaction_path;
		io::path m_db_path;
    };

} // end namespace
} // end namespace

#endif // __FILESYSTEM_DATABASE_H_E627B599_ED09_45DB_B020_9B34E4933E62_
