
#include "RoboticsConnection.h"

using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPMessage;
using Poco::StreamCopier;
using Poco::Path;
using Poco::URI;
using Poco::Exception;
using Poco::JSON::Object;

namespace AIDoop
{
    namespace ObjectTracker
    {
        RoboticsConnection::RoboticsConnection(const std::string& host, const std::string& port)
            : _signpath("/signin"), _scheme("http"), _username("admin@hatiolab.com"), _password("admin")
        {
            // make uri for authentication
            _uriSign.setScheme(_scheme);
            _uriSign.setAuthority(host + std::string(":") + port);
            _uriSign.setPath(_signpath);
        }

        RoboticsConnection::~RoboticsConnection()
        {

        }

        // TODO: split the codes by some functions
        bool RoboticsConnection::signin()
        {
            bool result = false;
            HTTPResponse::HTTPStatus httpStatus;

            try
            {
                //Poco::URI uriSign("http://127.0.0.1:3000/signin");
                std::string uriPath(_uriSign.getPathAndQuery());

                // create a session
                _pSession = new HTTPClientSession(_uriSign.getHost(), _uriSign.getPort());

                std::cout << _uriSign.getHost() << std::endl;
                std::cout << _uriSign.getPort() << std::endl;
                std::cout << _uriSign.getScheme()+"://"+_uriSign.getAuthority() << std::endl;

                _pSession->setKeepAlive(true);

                ///////////////////////////////////////////////////////////////
                // start to authorize
                ////////////////////////////////////////////////////////////////
                HTTPRequest request(HTTPRequest::HTTP_POST, uriPath, HTTPMessage::HTTP_1_1);
                request.set("origin", _uriSign.getScheme()+"://"+_uriSign.getAuthority());  // TODO: for what??

                // this line is where you get your response
                request.setContentType("application/json");
                request.add("x-only-token", "true");

                // make the information for signging
                Poco::JSON::Object jsonObj;
                jsonObj.set("email", _username);
                jsonObj.set("password", _password);
                std::stringstream jsonString;
                jsonObj.stringify(jsonString);

                // TODO: change to poco log functions
                std::cout << jsonString.str().size() << std::endl;
                std::cout << jsonString.str() << std::endl;

                // set content length
                request.setContentLength(jsonString.str().size());

                std::ostream& myOStream = _pSession->sendRequest(request);
                jsonObj.stringify(myOStream);

                HTTPResponse response;
                std::istream& rs = _pSession->receiveResponse(response);

                httpStatus = response.getStatus();
                std::cout << httpStatus << " " << response.getReason() << std::endl;

                std::string access_token;
                StreamCopier::copyToString(rs, access_token);

                std::cout << access_token << std::endl;
            }
            catch (std::exception &e)
            {
                    std::cout << "Exception " << e.what();
            }

            result = ((httpStatus >= HTTPResponse::HTTPStatus::HTTP_OK) &&  (httpStatus <= HTTPResponse::HTTPStatus::HTTP_ACCEPTED)) ? true : false;

            return result;
        }

        void RoboticsConnection::closeSession()
        {
            try
            {
                _pSession->abort();
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
    }
}