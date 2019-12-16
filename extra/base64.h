#ifndef BASE64_H
#define BASE64_H

#include <string>
#include <map>

class Base64 {
public:
	Base64();
	~Base64();
	std::string encode(std::string str);
	std::string decode(std::string str);
	std::string safeDecode(std::string str);
	std::string safeEncode(std::string str);

protected:
	std::string encode_core(std::string &str, const std::string &table);
	std::string decode_core(std::string str, std::map<char, unsigned char> *decodeTableMap);

private:
	std::string table;
	std::string safeTable;
	std::map<char, unsigned char> *decodeTableMap;
	std::map<char, unsigned char> *decodeSafeTableMap;

};


#endif
