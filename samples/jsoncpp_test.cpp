#include <iostream>
#include <fstream>

#include "/usr/local/include/json/json.h"

//#ifdef _DEBUD
//#pragma comment(lib, "json/lib_json_d.lib")
//#endif

using namespace std;

int main(int args,char **argv)
{
	// 1. Reading
	Json::Value root;			//Json 의 value를 담는 변수
	Json::Reader reader;		//Json 의 스크립트 Parsor. Root table을 채워주고 성공실패여부 리턴
	std::ifstream t;
	t.open("/Users/jinwon/Documents/GitHub/object-tracker-cpp/samples/test.json");
	if (!reader.parse(t, root)) {

		cout << "Parsing Failed!!" << endl;
		return 0;

	}
	
	//전체 key()를 읽어보기
	for (auto it = root.begin(); it != root.end(); it++)
	{
		std::cout << it.key() << ": " << (*it) << std::endl;
	}
	
	//---------------------------

	
	cout << "firstName: "<< root.get("firstName", "firstName_").asString() << endl;
	cout << "lastName: "<<root["lastName"].asCString()<< endl;

	//  "string_array": ["331","23","Hello"],
	const Json::Value string_array = root["string_array"];
	for (int i = 0; i < (int)string_array.size(); ++i)
	{
		std::cout << string_array[i].asString() << std::endl;
	}

	//   "num_array": [3,4,2],
	const Json::Value num_array = root["num_array"]; //  "num_array": ["331","23","44"],
	for (int i = 0; i < (int)num_array.size(); ++i)
	{
		std::cout << num_array[i] << std::endl;
	}

	// "num_arr_array" : [{"num_10" : [10,11,13]}]
	cout << "num_arr_array_1: " << root["num_arr_array"][0][0] << " "<< root["num_arr_array"][0][1] << " "<<root["num_arr_array"][0][2] << endl;
}