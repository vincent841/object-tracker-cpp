#ifndef __ROBOTICSCONNECTION__H_
#define __ROBOTICSCONNECTION__H_

#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPMessage.h"
#include "Poco/Net/WebSocket.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/StreamCopier.h"
#include "Poco/NullStream.h"
#include "Poco/Path.h"
#include "Poco/URI.h"
#include "Poco/Exception.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/ParseHandler.h"
#include "Poco/JSON/JSONException.h"
#include <iostream>
#include <string>

using Poco::Net::HTTPClientSession;
using Poco::URI;


namespace AIDoop
{
    namespace ObjectTracker
    {
        class RoboticsConnection
        {
            public:
                    RoboticsConnection(const std::string& host, const std::string& port);
                    virtual ~RoboticsConnection();

                    virtual bool signin();
                    virtual void closeSession();
                    virtual HTTPClientSession& getSession() { return *_pSession; }
                    

            private:
                    const std::string _signpath;
                    const std::string _scheme;
                    const std::string _username;
                    const std::string _password;

                    URI _uriSign;
                    HTTPClientSession* _pSession;
                    std::string _accesstoken;
        };
    }
}

#endif // __ROBOTICSCONNECTION__H_
