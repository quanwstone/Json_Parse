/*
Json解析依赖的库为开源的JsonCpp,需要手动编译生成lib。
Json parsing depends on the open source JsonCpp,
need to be manually compiled to generate lib.
*/
#include<stdio.h>
#include"json.h"

int main(int argc, char*argv[])
{
	Json::Reader reader;
	Json::Value root;

	char json_data[] =
		"[{\"name\" : \"Tocy\", \"salary\" : 100}, {\"name\" : \"Kit\", \"salary\" : 89}, \
        \"a json note\"]";

	// reader将Json字符串解析到root，root将包含Json里所有子元素  
	if (!reader.parse(json_data, json_data + sizeof(json_data), root))
	{
		printf( "json parse failed\n");
		return 0;
	}

	unsigned int count = root.size() - 1;
	
	for (unsigned int i = 0; i < count; ++i)
	{
		std::string name = root[i]["name"].asString();
		int salary = root[i]["salary"].asInt();
		printf("name =%s salary=%d\n",name.c_str(),salary);
	}

	Json::StyledWriter swrite;
	
	FILE *pFile = nullptr;

	errno_t er = fopen_s(&pFile, "Write.json", "wb+");
	if (er != 0)
	{
		printf("fopen faile\n");
	}
	std::string str = swrite.write(root);
	
	size_t sz = fwrite(str.c_str(), 1, str.size(), pFile);
	
	printf("fwrite size= %d\n",sz);
	
	fclose(pFile);
	
	pFile = nullptr;

	for (;;);

	return 0;
}