//
// TaskTest.cpp
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "TaskTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "EchoServer.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/NetException.h"
#include "Poco/Timespan.h"
#include "Poco/Stopwatch.h"
#include "Poco/Buffer.h"
#include "Poco/FIFOBuffer.h"
#include "Poco/Delegate.h"
#include "Poco/File.h"
#include <iostream>


using Poco::Net::Socket;
using Poco::Net::StreamSocket;
using Poco::Net::ServerSocket;
using Poco::Net::SocketAddress;
using Poco::Net::ConnectionRefusedException;
using Poco::Timespan;
using Poco::Stopwatch;
using Poco::TimeoutException;
using Poco::InvalidArgumentException;
using Poco::Buffer;
using Poco::FIFOBuffer;
using Poco::delegate;


TaskTest::TaskTest(const std::string& name): CppUnit::TestCase(name)
{
}


TaskTest::~TaskTest()
{
}


void TaskTest::testEcho()
{

}

void TaskTest::setUp()
{
}


void TaskTest::tearDown()
{
}

CppUnit::Test* TaskTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("TaskTest");

	CppUnit_addTest(pSuite, TaskTest, testEcho);

	return pSuite;
}
