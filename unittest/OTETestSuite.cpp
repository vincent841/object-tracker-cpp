//
// NetTestSuite.cpp
//
// Copyright (c) 2005-2012, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "OTETestSuite.h"

CppUnit::Test* OTETestSuite::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("OTETestSuite");

	pSuite->addTest(NetCoreTestSuite::suite());

	return pSuite;
}
