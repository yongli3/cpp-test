#include <iostream>
#include <vector>
#include "json.hpp"
#include <fstream>
using namespace std;
//#include <experimental/filesystem>

typedef struct
{
	int busId;
	int slaveAddr;
	std::vector<unsigned char> data;
} filter_t;

vector<filter_t> filter_list;

int vector_test()
{
	int i = 0;
	nlohmann::json data = nullptr;

	char text[] = R"(
     {
"filters":[
{"busId": "0x07", "slaveAddr" : "0x58", "data" : "0x06 0x00"},
{"busId": "0x08",  "slaveAddr" : "0x59", "data" : "0x07 0x00"},
{"busId": "0x09",  "slaveAddr" : "0x60", "data" : "0x08 0x00"}
]
}
     )";

	// parse and serialize JSON
	try
	{
		data = nlohmann::json::parse(text);
	}
	catch (nlohmann::json::parse_error &e)
	{
		cout << e.what() << endl;
	}

	std::cout << data << endl;

	nlohmann::json filters = data["filters"].get<nlohmann::json>();

	std::cout << filters << endl;

	std::cout << filters.size() << endl;

	filter_list.resize(filters.size());

	i = 0;
	for (nlohmann::json::iterator it = filters.begin(); it != filters.end(); ++it)
	{
		nlohmann::json filter = it.value();
		cout << filter << endl;
		//cout << it[string("busId")].get<string>() << endl;

		unsigned int busId =
			std::stoul(filter["busId"].get<string>(), nullptr, 16);

		unsigned int slaveAddr =
			std::stoul(filter["slaveAddr"].get<string>(), nullptr, 16);

		std::string command = filter["data"].get<string>();

		filter_list[i].busId = busId;
		filter_list[i].slaveAddr = slaveAddr;
		filter_list[i].data.resize(command.length());
		std::copy(command.begin(), command.end(), filter_list[i].data.begin());
		i++;

		//std::vector<uint8_t> inBuf(readCount);

		cout << busId << endl;
		cout << slaveAddr << endl;

		cout << command << endl;
		//cout << it.key() << endl;
		//std::cout << *it << endl;
	}

	for (i = 0; i < filter_list.size(); i++)
	{
		char str[] = "0x06 0x00";
		std::vector<unsigned char> outBuf(filter_list[i].data.size());

		std::copy(str, str + strlen(str), outBuf.begin());

		if (filter_list[i].data == outBuf)
			//if ("0x06 0x00" == string(filter_list[i].data.begin(), filter_list[i].data.end()))
		{
			cout << "1" << endl;
		}
		else
		{
			cout << "0" << endl;
		}
	}
	return 0;
}

int main()
{
	unsigned int i = 0;
	int inLen = 10;
	int outLen = 10;
	unsigned char buf[256] = { 'a', 'b' };
	nlohmann::json data = nullptr;

	vector_test();

	cout << filter_list.size() << endl;

	std::ifstream dev_id_file(std::string("C:\\j.json"));
	if (dev_id_file.is_open())
	{
		try
		{
			data = nlohmann::json::parse(dev_id_file, nullptr, false);
		}
		catch (nlohmann::json::parse_error &e)
		{
			cout << "err" << endl;
		}

		std::cout << data.dump() << endl;
	}

	std::vector<unsigned char> inBuf(inLen);
	std::vector<unsigned char> outBuf;
	std::copy(buf, buf + 2, outBuf.begin());

	std::cout << "start " << std::endl;

	return 0;
}