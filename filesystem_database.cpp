//////////////////////////////////////////////////////////////////////////////	
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Tuesday, 13 January 2009 1:01:14 AM
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "filesystem_database.h"
#include "glass/glass.h"
#include "glass/utils.h"
#include "glass/base_type.h"
#include "glass/class_type.h"
#include "glass/enum_type.h"
#include "glass/bitfield_type.h"
#include "glass/pointer_type.h"
#include "io/interface.h"
#include "io/stream.h"
#include "core/globals.h"

//////////////////////////////////////////////////////////////////////////////
// LOCAL MACROS
//////////////////////////////////////////////////////////////////////////////

#define CHECKED_WRITE(_str) if(!str->printf(_str)) return false;
#define CHECKED_WRITE_A(_str, ...) if(!str->printf(_str, __VA_ARGS__)) return false;
#define INDENT(str, depth) { for(int i = 0; i < (depth); ++i) CHECKED_WRITE("    ") }

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////
namespace tycho
{
namespace mirror
{

    //--------------------------------------------------------------------

	filesystem_database::filesystem_database(io::interface* io, const io::path& root_path) :
		m_root_path(root_path)
	{
		m_transaction_path = m_root_path;
		m_transaction_path.append("/trx");
		m_db_path = m_root_path;
		m_db_path.append("/db");

		// ensure all the paths exist
		TYCHO_VERIFY(m_io->create_directories(m_transaction_path));
		TYCHO_VERIFY(m_io->create_directories(m_db_path));
	}
	
    //--------------------------------------------------------------------

	filesystem_database::~filesystem_database()
	{
	
	}

    //--------------------------------------------------------------------

	int filesystem_database::start_transaction()
	{
		// create a scratch area to store this transaction
		return false;
	}

    //--------------------------------------------------------------------

	bool filesystem_database::commit_transaction(int trx_id)
	{
		return false;
	}
 
    //--------------------------------------------------------------------

	bool filesystem_database::abort_transaction(int trx_id)
	{
		return false;
	}

    //--------------------------------------------------------------------

	void* filesystem_database::load_object(int trx_id, const char* name)
	{
		return 0;
	}

    //--------------------------------------------------------------------

	bool filesystem_database::store_object(int trx_id, const void* ptr, const glass::base_type* type, const glass::name& name)
	{
		// make full filesystem path for this object exits
		char obj_path[glass::MaxNameLength];
		if(!name.get_name_as_path(obj_path, glass::MaxNameLength))
			return false;
		io::path full_path = m_db_path;
		full_path.append(obj_path);
		io::path dir_path = full_path.get_directory();
		if(!m_io->create_directories(dir_path))
			return false;

		// create file output stream to write to
		io::stream_ptr str = m_io->open_stream(full_path, io::open_flag_create | io::open_flag_write);
		if(!str)
			return false;
	
		// write root assignment
		CHECKED_WRITE_A("%s = (%s)", name.get_name(), type->get_name().c_str());

		// dispatch based on type we are pointing
		return dispatch(str, 0, ptr, type);
	}

    //--------------------------------------------------------------------

	bool filesystem_database::dispatch(io::stream_ptr str, int depth, const void* ptr, const glass::base_type* type)
	{
		switch(type->get_type_t())
		{
			case glass::base_type::t_int32		: if(!write_int32(str, depth, ptr, type)) return false; break;
			case glass::base_type::t_uint32		: if(!write_uint32(str, depth, ptr, type)) return false; break;
			case glass::base_type::t_float32	: if(!write_float32(str, depth, ptr, type)) return false; break;
			case glass::base_type::t_string		: if(!write_string(str, depth, ptr, type)) return false; break;
			case glass::base_type::t_class		: if(!write_class(str, depth, ptr, type)) return false; break;
			case glass::base_type::t_enum		: if(!write_enum(str, depth, ptr, type)) return false; break;
			case glass::base_type::t_bitfield	: if(!write_bitfield(str, depth, ptr, type)) return false; break;
			case glass::base_type::t_pointer	: if(!write_pointer(str, depth, ptr, type)) return false; break;

			default: TYCHO_PANIC("Type not supported"); break;
		};
		return true;
	}

    //--------------------------------------------------------------------

	bool filesystem_database::write_int32(io::stream_ptr str, int /*depth*/, const void* obj_ptr, const glass::base_type* type)
	{
		TYCHO_ASSERT(obj_ptr);
		TYCHO_ASSERT(type);
		TYCHO_ASSERT(!str->fail());
		const core::int32& v = *((const core::int32*)obj_ptr);
		CHECKED_WRITE_A("%d", (v));
		return true;
	}

    //-------------------------------------------------------------------

		
	bool filesystem_database::write_uint32(io::stream_ptr str, int /*depth*/, const void* obj_ptr, const glass::base_type* type)
	{
		TYCHO_ASSERT(obj_ptr);
		TYCHO_ASSERT(type);
		TYCHO_ASSERT(!str->fail());
		const core::uint32& v = *((const core::uint32*)obj_ptr);
		CHECKED_WRITE_A("%u", (v));
		return true;
	}

    //-------------------------------------------------------------------

		
	bool filesystem_database::write_float32(io::stream_ptr str, int /*depth*/, const void* obj_ptr, const glass::base_type* type)
	{
		TYCHO_ASSERT(obj_ptr);
		TYCHO_ASSERT(type);
		TYCHO_ASSERT(!str->fail());
		const core::float32& v = *((const core::float32*)obj_ptr);
		CHECKED_WRITE_A("%f", (v));
		return true;
	}

    //-------------------------------------------------------------------


	bool filesystem_database::write_string(io::stream_ptr str, int /*depth*/, const void* obj_ptr, const glass::base_type* type)
	{
		return true;
	}

    //-------------------------------------------------------------------


	bool filesystem_database::write_class(io::stream_ptr str, int depth, const void* obj_ptr, const glass::base_type* type)
	{
		CHECKED_WRITE("{\n");
		for(int i = 0; i < type->get_num_child_symbols(); ++i)
		{
			const glass::symbol* s = type->get_child_symbol(i);
			TYCHO_ASSERT(s);

			// write out member variables
			if(s->get_type() == glass::symbol::t_member_variable)
			{
				const glass::member_variable* mem_var = (glass::member_variable*)s;
				const void* mem_ptr = mem_var->get_raw_ptr(obj_ptr);
				const char* type_name = mem_var->get_type()->get_name().c_str();
				const char* var_name = mem_var->get_name().c_str();
				INDENT(str, depth+1);
				CHECKED_WRITE_A("%s = (%s)", var_name, type_name);
				if(!dispatch(str, depth+1, mem_ptr, mem_var->get_type()))
					return false;
				CHECKED_WRITE(";\n");
			}
		}		
		INDENT(str, depth);
		CHECKED_WRITE("}");
		return true;
	}

    //-------------------------------------------------------------------

	bool filesystem_database::write_enum(io::stream_ptr str, int /*depth*/, const void* obj_ptr, const glass::base_type* type)
	{
		TYCHO_ASSERT(obj_ptr);
		TYCHO_ASSERT(type);
		TYCHO_ASSERT(!str->fail());
		const core::int32& v = *((const core::int32*)obj_ptr);
		const glass::enum_type* enum_type = (const glass::enum_type*)type;
		const char* enum_str = 0;
		if(!enum_type->find(v, enum_str))
			return false;
		TYCHO_ASSERT(enum_str);
		CHECKED_WRITE(enum_str);
		return true;	
	}

    //-------------------------------------------------------------------

	bool filesystem_database::write_bitfield(io::stream_ptr str, int /*depth*/, const void* obj_ptr, const glass::base_type* type)
	{
		TYCHO_ASSERT(obj_ptr);
		TYCHO_ASSERT(type);
		TYCHO_ASSERT(!str->fail());
		const core::int32& v = *((const core::int32*)obj_ptr);
		const glass::bitfield_type* bitfield_type = (const glass::bitfield_type*)type;

		// iterate over bits 
		bool first = true;
		for(int bit = 0; bit < 32; ++bit)
		{
			int tv = v & (1 << bit);
			if(v & tv)
			{
				const char* field_str = 0;
				if(!bitfield_type->find(tv, field_str))
					return false;
				TYCHO_ASSERT(field_str);
				if(!first)
					CHECKED_WRITE(" | ");
				CHECKED_WRITE(field_str);
				first = false;
			}
		}
		return true;	
	}
	
	//-------------------------------------------------------------------

	bool filesystem_database::write_pointer(io::stream_ptr str, int /*depth*/, const void* obj_ptr, const glass::base_type* type)
	{
		TYCHO_ASSERT(obj_ptr);
		TYCHO_ASSERT(type);
		TYCHO_ASSERT(!str->fail());
		const void* value = *((const void**)obj_ptr);
		if(value == 0)
		{
			CHECKED_WRITE("0");
			return true;
		}
		const char* pointee_name = glass::get_object_name(value).get_name();
		TYCHO_ASSERT(pointee_name);
		CHECKED_WRITE(pointee_name);
		return true;	
	}

    //-------------------------------------------------------------------

	int filesystem_database::resolve_label(const char*)
	{
		return -1;//revision::invalid;
	}

    //--------------------------------------------------------------------

#undef CHECKED_WRITE
#undef CHECKED_WRITE_A
#undef INDENT

} // end namespace
} // end namespace
