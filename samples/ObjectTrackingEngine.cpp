
#include "Poco/Util/Application.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Util/AbstractConfiguration.h"
#include "Poco/Net/IPAddress.h"
#include "Poco/AutoPtr.h"
#include "Poco/NumberParser.h"
#include <iostream>
#include <sstream>


using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;
using Poco::Util::AbstractConfiguration;
using Poco::Net::IPAddress;
using Poco::AutoPtr;
using Poco::NumberParser;


class ObjectTrackingEngine: public Application
{
public:
	ObjectTrackingEngine(): 
		_helpRequested(false), 
		_target("localhost")
	{
	}

protected:	
	void initialize(Application& self)
	{
		loadConfiguration(); // load default configuration files, if present
		Application::initialize(self);

		// TODO: initialize this module

	}
	
	void uninitialize()
	{
		// TODO: unintialize this module
		

		Application::uninitialize();
	}

	void defineOptions(OptionSet& options)
	{
		Application::defineOptions(options);


		// TODO: set options here..
		// options.addOption(
		// 	Option("help", "h", "display help information on command line arguments")
		// 		.required(false)
		// 		.repeatable(false));

		// options.addOption(
		// 	Option("repetitions", "r", "define the number of repetitions")
		// 		.required(false)
		// 		.repeatable(false)
		// 		.argument("repetitions"));
				
		// options.addOption(
		// 	Option("target", "t", "define the target address")
		// 		.required(false)
		// 		.repeatable(false)
		// 		.argument("target"));
	}
	
	void handleOption(const std::string& name, const std::string& value)
	{
		Application::handleOption(name, value);

		if (name == "help")
			_helpRequested = true;
		else if (name == "repetitions")
			_repetitions = NumberParser::parse(value);
		else if (name == "target")
			_target = value;
	}
	
	void displayHelp()
	{
		HelpFormatter helpFormatter(options());
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage("OPTIONS");
		helpFormatter.setHeader(
			"Object Tracking Engine with arm robots"
			"released by AIDoop Co.");
		helpFormatter.format(std::cout);
	}


	int main(const std::vector<std::string>& args)
	{
		if (_helpRequested) 
			displayHelp();
		else 
			;	// TODO: process main jobs 
		
		return Application::EXIT_OK;
	}

private:
	bool        _helpRequested;
	int         _repetitions;
	std::string _target;
};


int objtrackingMain(int argc, char** argv)
{
	AutoPtr<ObjectTrackingEngine> pApp = new ObjectTrackingEngine;
	try
	{
		pApp->init(argc, argv);
	}
	catch (Poco::Exception& exc)
	{
		pApp->logger().log(exc);
		return Application::EXIT_CONFIG;
	}
	return pApp->run();
}
