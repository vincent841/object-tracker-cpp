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
#include "Poco/JSON/Query.h"
#include <iostream>

using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPMessage;
using Poco::Net::WebSocket;
using Poco::StreamCopier;
using Poco::Path;
using Poco::URI;
using Poco::Exception;
using Poco::JSON::Object;
using Poco::JSON::Query;


bool doRequest(Poco::Net::HTTPClientSession& session, Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response)
{
	session.sendRequest(request);
	std::istream& rs = session.receiveResponse(response);
	std::cout << response.getStatus() << " " << response.getReason() << std::endl;
	if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED)
	{
		StreamCopier::copyStream(rs, std::cout);
		return true;
	}
	else
	{
		Poco::NullOutputStream null;
		StreamCopier::copyStream(rs, null);
		return false;
	}
}

void objPrint(Object& obj, const std::string& name = "")
{
    for (Object::ConstIterator it = obj.begin(),
        end = obj.end(); it != end;   it)
    {
        if (!name.empty()) std::cout << name << ':';
        std::cout << it->first << ':';
        if (it->second.type() == typeid(Object::Ptr))
        {
            Object::Ptr p = it->second.extract<Object::Ptr>();
            objPrint(*p, it->first);
        }
        else
             std::cout << it->second.toString() << std::endl;
    }
}

int operato_connect_main(int args,char **argv)
{
    try
    {
        Poco::URI uriSign("http://127.0.0.1:3000/signin");
        std::string uriPath(uriSign.getPathAndQuery());

        HTTPClientSession session(uriSign.getHost(), uriSign.getPort());    
        session.setKeepAlive(true);

        ///////////////////////////////////////////////////////////////
        // start to authorize 
        ////////////////////////////////////////////////////////////////
        HTTPRequest request(HTTPRequest::HTTP_POST, uriPath, HTTPMessage::HTTP_1_1);
        request.set("origin", "http://127.0.0.1:3000");     // for what??
        HTTPResponse response;

        std::string username = "admin@hatiolab.com";
        std::string password = "admin";
        //Poco::Net::HTTPCredentials::extractCredentials("127.0.0.1:3000/signin", username, password);
        //Poco::Net::HTTPCredentials credentials(username, password);    

        request.setContentType("application/json");
        request.add("x-only-token", "true");
        //request.add("email")

        Poco::JSON::Object jsonObj;
        jsonObj.set("email", "admin@hatiolab.com");
        jsonObj.set("password", "admin");

        std::stringstream jsonString;
        jsonObj.stringify(jsonString);

        // check json data
        std::cout << jsonString.str().size() << std::endl;
        std::cout << jsonString.str() << std::endl;

        request.setContentLength(jsonString.str().size());

        std::ostream& myOStream = session.sendRequest(request);
        jsonObj.stringify(myOStream);
        
        // this line is where you get your response
        std::istream& rs = session.receiveResponse(response);
        std::cout << response.getStatus() << " " << response.getReason() << std::endl;
        
        std::string access_token;
        StreamCopier::copyToString(rs, access_token);
        
        std::cout << access_token << std::endl;



        ///////////////////////////////////////////////////////////////
        // start to get data formed by graphql
        ////////////////////////////////////////////////////////////////
        Poco::URI uriGql("http://127.0.0.1:3000/graphql");
        std::string uriGplPath(uriGql.getPathAndQuery());

        HTTPRequest request2(HTTPRequest::HTTP_POST, uriGplPath, HTTPMessage::HTTP_1_1);
        request2.set("origin", "http://127.0.0.1:3000");     // for what??

        HTTPResponse response2;

        request2.setContentType("application/json");
        request2.add("Accept", "*/*");
        request2.add("Accept-Encoding","gzip,deflate");        
        request2.add("authorization", access_token);
        request2.add("x-things-factory-domain", "system");

        Poco::JSON::Object jsonGqlObj;
        jsonGqlObj.set("query", "{\n  trackingCameras {\n    items {\n      id\n      name\n      domain {\n        name\n      }\n      description\n      type\n      endpoint\n      active\n      config\n      baseRobotArm {\n        id\n        name\n      }\n      cameraMatrix {\n        rows\n        columns\n        data\n      }\n      handEyeMatrix {\n        rows\n        columns\n        data\n      }\n      rois {\n        id\n        region {\n          lt {\n            x\n            y\n          }\n          rb {\n            x\n            y\n          }\n        }\n      }\n      updater {\n        email\n      }\n      creator {\n        email\n      }\n      updatedAt\n      createdAt\n    }\n    total\n  }\n}\n");

        std::stringstream jsonString2;
        jsonGqlObj.stringify(jsonString2);        

        request2.setContentLength(jsonString2.str().size());

        std::ostream& myOStream2 = session.sendRequest(request2);
        jsonGqlObj.stringify(myOStream2);

        std::istream& rs2 = session.receiveResponse(response2);
        std::cout << response2.getStatus() << " " << response2.getReason() << std::endl;
        //StreamCopier::copyStream(rs2, std::cout);
        std::cout << std::endl;


    
        // HOW TO HANDLE JSON OBJECT 
        Poco::JSON::Parser parser;
        Poco::JSON::Object::Ptr ret = parser.parse(rs2).extract<Poco::JSON::Object::Ptr>();
        //std::cout << (*ret).getValue<std::string>("data") << std::endl;

        Poco::JSON::Object::Ptr jsonData = ret->getObject("data");
        Poco::JSON::Object::Ptr jsonTrackingCameras = jsonData->getObject("trackingCameras");
        Poco::JSON::Object::Ptr jsonItems = jsonTrackingCameras->getObject("items");

        // Poco::JSON::Object::Iterator it;
        // for (it = jsonItems->begin(); it != jsonItems->end(); it++) // how to iterate here?
        // {
        //     std::cout << "children:" << it->first << "\n";
        // }

        objPrint(*jsonTrackingCameras);


        // Poco::Dynamic::Var test = jsonTrackingCameras->get("items");
        // Poco::JSON::Array::Ptr subObject = test.extract<Poco::JSON::Array::Ptr>();
        // for (Poco::JSON::Array::ConstIterator it= subObject->begin(); it != subObject->end(); ++it)
        // {
        //     std::cout << "Children:" << it->convert<std::string>() << "\n";
        // }








        

       

        std::string dataResult = (*ret).getValue<std::string>("data");
        

        // Poco::Dynamic::Var vdata = (*ret).getObject("data");
        // vdata.extract<Object::Ptr>();


        




        Poco::JSON::Parser parser2;
        Poco::Dynamic::Var result2 = parser2.parse(dataResult);

        Query query(result2);

        std::string firstChild = query.findValue("items", "trackingCameras");
        std::cout << firstChild << std::endl;


        



          // (*ret) will contain all the members in a json structure returned
        if ((*ret).get("data") != true) {
            std::cout << "Failed to upload: " << (*ret).get("message").toString();
        }
        else
        {
            std::cout << "Success!!" << std::endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    // doRequest(session, request, response);
    //credentials.authenticate(request, response);
    //doRequest(session, request, response);



    // try {

    //     WebSocket* m_psock = new WebSocket(cs, request, response);
    //     char const *testStr="Hello echo websocket!";
    //     char receiveBuff[256];

    //     int len=m_psock->sendFrame(testStr,strlen(testStr),WebSocket::FRAME_TEXT);
    //     std::cout << "Sent bytes " << len << std::endl;
    //     int flags=0;

    //     int rlen=m_psock->receiveFrame(receiveBuff,256,flags);
    //     std::cout << "Received bytes " << rlen << std::endl;
    //     std::cout << receiveBuff << std::endl;

    //     m_psock->close();

    // } catch (std::exception &e) {
    //     std::cout << "Exception " << e.what();
    // }

}
