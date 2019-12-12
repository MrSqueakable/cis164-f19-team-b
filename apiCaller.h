#include <iostream>
#include <string>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <Poco/Exception.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include "Poco/Dynamic/Var.h"
#include "Poco/JSON/Object.h"
#include <Poco/JSON/PrintHandler.h>
#include <Poco/Dynamic/Var.h>
#include <sstream>
//#include <json.h>
//#include <value.h>

#include <Poco/StreamCopier.h>
#include <Poco/SharedPtr.h>
#include <Poco/JSON/ParserImpl.h>
#pragma comment(lib, "ws2_32.lib") // for Visual Studio, pulls in a Windows library
#pragma comment(lib, "IPHLPAPI.lib") // for Visual Studio, pulls in a Windows library
//using namespace std;
using namespace Poco;
using namespace Poco::Dynamic;
using namespace Net;
using namespace Poco::JSON;
using namespace Poco::Net;
using namespace Poco::JSON;
using namespace Poco;
using namespace Dynamic;
using namespace std;
Poco::JSON::Object obj;
using Poco::JSON::Parser;
//using Poco::JSON::Object;




class getIt {
public:
	std::string parseJson(std::istream& is) {
		Parser parser;
		Var result = parser.parse(is);

		

		Object::Ptr object = result.extract<Object::Ptr>();
		stringstream ss;
		object->stringify(ss);
		cout << ss.str();

		string temp[1];
		Var value = object->get("main");
		//std::cout << value.toString() << std::endl;
		Object::Ptr subObject = value.extract<Object::Ptr>();
		value = subObject->get("temp");
		
		value.toString(temp[0]);
		cout << temp[0];
		//std::unique_ptr<Post> post = std::unique_ptr<Post>(new Post(userId, id, title, body));
		return temp[0];
	}
		std::string parseJson1(std::istream & is) {
			Parser parser;
			Var result = parser.parse(is);
			string uv[4];
			Object::Ptr object = result.extract<Object::Ptr>();
			stringstream ss;
			object->stringify(ss);
			cout << ss.str();

			Var value = object->get("value");
			value.toString(uv[0]);

			//std::unique_ptr<Post> post = std::unique_ptr<Post>(new Post(userId, id, title, body));
			return value[0,1,2,3,4];
		}
		std::string parseJson2(std::istream& is) {
			Parser parser;
			Var result = parser.parse(is);
			string day[4];

			Object::Ptr object = result.extract<Object::Ptr>();
			stringstream ss;
			object->stringify(ss);
			cout << ss.str();

			Var value = object->getArray("list");
			
			Object::Ptr subObject = value.extract<Object::Ptr>();
			value = subObject->get("main");
			 subObject = value.extract<Object::Ptr>();
			value = subObject->get("temp");
			value.toString(day[0]);
			value.toString(day[1]);
			value.toString(day[2]);
			value.toString(day[3]);
			value.toString(day[4]);


			//std::unique_ptr<Post> post = std::unique_ptr<Post>(new Post(userId, id, title, body));
			return day[0,1,2,3,4];
		}
		std::string getApi(std::string input, std::string para, std::string para1) {
			std::string WebSiteURL = "";
			/*
			tile Tile;
			Weatherview weatherview;
			tile.setWeatherview(input)
			Dashboard.setCity(para)
			*/



			

			URI uri("http://openweathermap.org");

			HTTPClientSession session(uri.getHost(), uri.getPort());

			// specify the location of the resource we want from the server
			std::string path(uri.getPathAndQuery());
			if (input == "current") { //fc874eefd38cdc309674836731fb62cc
				if (path.empty()) path = "/data/2.5/weather?q=" + para + "," + para1 + "&appid=071148d52929efe36be9d67518b09d8e";
				// send the HTTP request

				HTTPRequest req(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
				req.setContentType("application/json");
				
				session.sendRequest(req);
				HTTPResponse res;
				
				
				//http://api.openweathermap.org



				std::cout << res.getStatus() << " " << res.getReason() << std::endl << std::endl;

				// print the response

				istream &is = session.receiveResponse(res);


				StreamCopier::copyStream(is, cout);

				std::string post = parseJson(is);
				return post;
			}
			if (input == "UV") {
				if (path.empty()) path = "/data/2.5/uvi/forecest?lat=" + para + "&lon=" + para1 + "&appid=b5546bdb7575f9ed8ffacdfdcdd259a3";
				// send the HTTP request
				HTTPRequest req(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
				session.sendRequest(req);

				HTTPResponse res;
				std::cout << res.getStatus() << " " << res.getReason() << std::endl << std::endl;

				// print the response
				std::istream& is = session.receiveResponse(res);
				//	StreamCopier::CopyStream(is, cout);
				std::string post = parseJson1(is);
				return post;
			}
			if (input == "5")
			{
				if (path.empty()) path = "/data/2.5/forecast?id=" + para + "&appid=b5546bdb7575f9ed8ffacdfdcdd259a3";
				// send the HTTP request
				HTTPRequest req(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
				session.sendRequest(req);

				HTTPResponse res;
				std::cout << res.getStatus() << " " << res.getReason() << std::endl << std::endl;

				// print the response
				std::istream& is = session.receiveResponse(res);
				//StreamCopier::CopyStream(is, cout);

				std::string post = parseJson2(is);
				return post;
			}



		

		}
	};
