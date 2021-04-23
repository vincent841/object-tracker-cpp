#ifndef __T
#define SocketTest_INCLUDED


#include "Poco/Net/Net.h"
#include "CppUnit/TestCase.h"


class TaskTest: public CppUnit::TestCase
{
public:
	TaskTest(const std::string& name);
	~TaskTest();

	void testEcho();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

private:
	void onReadable(bool& b);
	void onWritable(bool& b);

	int _readableToNot;
	int _notToReadable;
	int _writableToNot;
	int _notToWritable;
};


#endif // SocketTest_INCLUDED
