#ifndef cooloi_openssl_class
#define cooloi_openssl_class

#include <iostream>
#include <string>
#include <cassert>
#include <openssl/rsa.h>
#include <openssl/err.h>
#include <openssl/pem.h>

namespace cooloi {

class Openssl {
public:
	static Openssl * create();
	std::string ClientEncodeFile(const std::string msg); /* 客户端加密 */
	std::string ClientDecodeFile(const std::string msg); /* 客户端解密 */
	std::string ServerEncodeFile(const std::string msg); /* 服务端加密 */
	std::string ServerDecodeFile(const std::string msg); /* 服务端解密 */
private:
	std::string pubkey();
	std::string prikey();
};

}

#endif
