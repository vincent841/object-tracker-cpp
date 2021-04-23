#ifndef __CONNECTION_H__
#define __CONNECTION_H__

#include "Poco/Net/HTTPClientSession.h"

using Poco::Net::HTTPClientSession;

namespace AIDoop
{
    namespace ObjectTracker
    {
        class Connection
        {
            public:
                Connection() {}
                virtual ~Connection() {}

            public:
                virtual bool connect() = 0;
                virtual void disconnect() = 0;
                virtual HTTPClientSession& getSession() = 0;
        };
    }
}

#endif // __CONNECTION_H__
