//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Wednesday, 14 January 2009 12:18:18 AM
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "object_file.h"
#include "mirror/record.h"
#include "core/flexint.h"
#include <stdio.h>

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////
namespace tycho
{
namespace mirror
{

	namespace detail
	{
	namespace parser
	{
		struct token_def
		{	
			int token;
			char str[128];
		};
		
        enum tokens
        {
		    #include "object_file_grammar.h"
        };

		#include "object_file_grammar.inl"	
	}
	}

    //--------------------------------------------------------------------

	object_file::object_file(const io::path&) :
		m_record(0)
	{
	
	}

    //--------------------------------------------------------------------
	
	object_file::object_file(const io::path&, record_reactor*) :
		m_record(0)
	{
		TYCHO_NOT_IMPLEMENTED;
	}
	

    //--------------------------------------------------------------------

	object_file::~object_file()
	{
		core::safe_delete(m_record);
	}

    //--------------------------------------------------------------------
	
	const record& object_file::get_record() const
	{
		return *m_record;
	}

    //--------------------------------------------------------------------


} // end namespace
} // end namespace
