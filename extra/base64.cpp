#include "base64.h"

Base64::Base64() :
	table("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"), 
	safeTable("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_"),
	decodeTableMap(new std::map<char, unsigned char>()), 
	decodeSafeTableMap(new std::map<char, unsigned char>())
{

	for (unsigned char i = 0; i < table.size(); i++)
	{
		decodeTableMap->insert(std::pair<char, unsigned char>(table[i], i));
	}

	for (unsigned char i = 0; i < safeTable.size(); i++)
	{
		decodeSafeTableMap->insert(std::pair<char, unsigned char>(safeTable[i], i));
	}
}

Base64::~Base64()
{
	delete decodeTableMap;
	delete decodeSafeTableMap;
}

std::string Base64::encode(std::string str)
{
	return this->encode_core(str, this->table);
}

std::string Base64::safeEncode(std::string str)
{
	return this->encode_core(str, table);
}

std::string Base64::encode_core(std::string &str, const std::string &table)
{
	std::string ret("");
	
	for (int i = 0; i < str.size() / 3; i++)
	{
		ret += table[str[i * 3] >> 2];
		ret += table[((str[i * 3] << 4) | (str[i * 3 + 1] >> 4)) & 0x3F];
		ret += table[((str[i * 3 + 1] << 2) | (str[i * 3 + 2] >> 6)) & 0x3F];
		ret += table[str[i * 3 + 2] & 0x3F];
	}
	int num = str.size() * 8 % 6;

	if (num == 4)
	{
		int i = str.size() / 3;
		ret += table[str[i * 3] >> 2];
		ret += table[((str[i * 3] << 4) | (str[i * 3 + 1] >> 4)) & 0x3F];
		ret += table[(str[i * 3 + 1] << 2) & 0x3F];
		ret += '=';
	} else if (num == 2) {
		int i = str.size() / 3;
		ret += table[str[i * 3] >> 2];
		ret += table[(str[i * 3] << 4) & 0x3F];
		ret += '=';
		ret += '=';
	}

	return ret;
}

std::string Base64::decode(std::string str)
{
	return decode_core(str, this->decodeTableMap);
}

std::string Base64::safeDecode(std::string str)
{
	return decode_core(str, this->decodeSafeTableMap);
}

std::string Base64::decode_core(std::string str, std::map<char, unsigned char> *decodeTableMap)
{
	int fillBytes = 4 - str.size() % 4;
	if (fillBytes == 3) return "";
	int outSize = str.size() / 4 * 3 + (fillBytes == 0 ? 0 : 3);
	for (int i = 0; i < fillBytes; i++) str = str + '\0';
	std::string ret("", outSize + 1);
	for (int i = 0; i < outSize + 1; i++) ret[i] = '\0';
	for (int i = str.size() / 4 * 4; i < str.size(); i++) str[i] == '=' ? str[i] = 0 : 0;

	for (int i = 0; i < str.size() / 4; i++)
	{
		ret[i * 3] |= (unsigned char)((*decodeTableMap)[str[i * 4]] << 2);
		ret[i * 3] |= (unsigned char)((*decodeTableMap)[str[i * 4 + 1]] >> 4);
		ret[i * 3 + 1] |= (unsigned char)((*decodeTableMap)[str[i * 4 + 1]] << 4);
		ret[i * 3 + 1] |= (unsigned char)((*decodeTableMap)[str[i * 4 + 2]] >> 2);
		ret[i * 3 + 2] |= (unsigned char)((*decodeTableMap)[str[i * 4 + 2]] << 6);
		ret[i * 3 + 2] |= (*decodeTableMap)[str[i * 4 + 3]];
	}

	return ret;
}


