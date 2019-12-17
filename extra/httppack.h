#ifndef HTTPPACK_H
#define HTTPPACK_H

#include <iostream>

typedef enum method{
	OPTIONS, 
	GET, 
	POST, 
	HEAD, 
	PUT, 
	DELETE, 
	TRACE, 
	CONNECT, 
	extension_method, 
};

typedef struct HEADER_LINE {
	std::string method;
	std::string uri;
	std::string version;
}HeaderLine;

typedef struct GENERAL_HEADER {
	std::string cacheControl;
	std::string connection;
	std::string data;
	std::string pragma;
	std::string trailer;
	std::string upgrade;
	std::string via;
	std::string warning;
}GeneralHeader;

typedef struct REQUEST_HEADER {
	std::string accept;
	std::string acceptCharset;
	std::string acceptEncoding;
	std::string acceptLanguage;
	std::string authorization;
	std::string expect;
	std::string from;
	std::string host;
	std::string ifMatch;
}RequestHeader;

typedef struct RESPONSE_HEADER {
	std::string acceptRanges;
	std::string age;
	std::string etag;
	std::string location;
	std::string proxyAuthenticate;
}ResponseHeader;

#endif

