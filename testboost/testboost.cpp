// testboost.cpp: определяет точку входа для приложения.
//

#include "testboost.h"
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <iostream>
#include "req.h"
using namespace std;

string getFieldJson(string json, string field);

int main()
{
	cout << "Hello CMake." << endl;
	string js = "{\"a\": \"123\"}";
	cout << getFieldJson(js, "a") << endl;

	Client client;
	boost::property_tree::ptree root;
	root.put("hwid", "testhwid");
	root.put("key", "123123123");
	std::ostringstream buf;
	boost::property_tree::write_json(buf, root, false);
	cout << getFieldJson(client.postResponse("httpbin.org", "/anything", buf.str()), "data") << endl;


	return 0;
}


string getFieldJson(string json, string field) {
	stringstream jsonEncoded(json);
	boost::property_tree::ptree root;
	boost::property_tree::read_json(jsonEncoded, root);

	if (root.empty())
		return "";

	return root.get <string> (field);

}