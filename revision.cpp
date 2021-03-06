//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Thursday, 15 January 2009 11:42:58 PM
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "revision.h"
#include "database.h"

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////
namespace tycho
{
namespace mirror
{

    //--------------------------------------------------------------------

	revision::revision(int num) :
		m_num(num),
		m_label(0)
	{}
		
    //--------------------------------------------------------------------

	revision::revision(const char* label) :
		m_num(0),
		m_label(label)
	{}
		
    //--------------------------------------------------------------------

	int revision::resolve(database* db)
	{
		if(m_num > 0)
			return m_num;
		m_num = db->resolve_label(m_label.c_str());
		return m_num;
	}

    //--------------------------------------------------------------------

} // end namespace
} // end namespace
