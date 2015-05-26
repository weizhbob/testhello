#include "cooloi_openssl.h"

namespace cooloi {

Openssl *Openssl::create() {
	Openssl * ret = new Openssl;
	return ret;
}

std::string Openssl::pubkey() {
	std::string pubkey =
			"MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQC5IRIUFSEEW0Y+2IwEcOmrVCSX5AZcFIrOHZILkHYEIqK2cFOfFUI/hOiSJ0m3VroyB8mNMkXCY/BrK1fh+3zIGsAlrAiXVhslvLPXlmNubyYpoox5/NtBg/sHLYQSd4Xf4iPzFIUWmdir/2yhquKm/Ow3o82UdFK6ERN5q2mEuQIDAQAB";
	int npubkey = pubkey.size();
	for (int i = 64; i < npubkey; i += 64) {
		if (pubkey[i] != '\n') {
			pubkey.insert(i, "\n");
		}
		i++;
	}
	pubkey.insert(0, "-----BEGIN PUBLIC KEY-----\n");
	pubkey.append("\n-----END PUBLIC KEY-----\n");
	return pubkey;
}

std::string Openssl::prikey() {
	std::string prikey =
			"MIICWwIBAAKBgQC5IRIUFSEEW0Y+2IwEcOmrVCSX5AZcFIrOHZILkHYEIqK2cFOfFUI/hOiSJ0m3VroyB8mNMkXCY/BrK1fh+3zIGsAlrAiXVhslvLPXlmNubyYpoox5/NtBg/sHLYQSd4Xf4iPzFIUWmdir/2yhquKm/Ow3o82UdFK6ERN5q2mEuQIDAQABAoGAXsWtSZafdml7hoS4+TUMimbi7NcQ4mapwGam80CbCfbpMVhDlrb9WSMjJF70f+ToIOCXr67Cw4cB9vsTXF6wO6lCgBhR9s844E6o8Ck+eiEOygBJUFpfgFkIdpApzrcxVx+/Xd5/LGXPI29PfgX/ib8nWj70L3vUP8JjOCnu+/kCQQDkIlKiSa2S11gEZGZtYfgYWxamXHN8Z9K89uhGMiCUxfqesRoXokjyyuG07F49hGmZk5zNtyrCFKtYgVOMtxyzAkEAz73/wt/Guutqpn3QN+U4I7k90GEJyQRjvWFeCGMu0IMzb6+aknrLS34ZqLbTarNpjCz2qIAPYfj9gH7HW1Wm4wJAfH6OgambYyrJCXyQuNhhv0jWD2scSqONyTkkgEoSpZ10qu0SxBr3nCdDDKyAsSl1Ry3awBhY6RjGeMH6iivTKQJAArQxYQLynjo0MCiRDjkwit59XHn226Pv/GYJCEjqMhKTF9AMTf3FKZ1hjh2bENd29zkamMTZ7meEPSjpRVoPCwJAc+fENNd8/J0sgd+Ptqo485uvTSofKFTeH6D4/W+0ZIfnSDZ1IZ/I7ocAeC7wEkGY6mkJJarWJb0nJoG5lBIkmg==";
	int nprikey = prikey.size();
	for (int i = 64; i < nprikey; i += 64) {
		if (prikey[i] != '\n') {
			prikey.insert(i, "\n");
		}
		i++;
	}
	prikey.insert(0, "-----BEGIN RSA PRIVATE KEY-----\n");
	prikey.append("\n-----END RSA PRIVATE KEY-----\n");
	return prikey;
}

//　客户端公钥加密
std::string Openssl::ClientEncodeFile(const std::string msg) {
	std::string pubkey = Openssl::pubkey();
	BIO *bio = NULL;
	RSA *rsa = NULL;
	char * chpubkey = const_cast<char*>(pubkey.c_str());
	if ((bio = BIO_new_mem_buf(chpubkey, -1)) == NULL) {
		std::cout << "BIO_new_mem_buf faild!" << std::endl;
	}
	rsa = PEM_read_bio_RSA_PUBKEY(bio, NULL, NULL, NULL);

	if (msg.empty()) {
		assert(false);
		return "ce1";
	}
	std::string strRet;
	int nlen = RSA_size(rsa);
	char* pEncode = new char[nlen + 1];
	int ret = RSA_public_encrypt(msg.length(),
			(const unsigned char*) msg.c_str(), (unsigned char*) pEncode, rsa,
			RSA_PKCS1_PADDING);
	if (ret >= 0) {
		strRet = std::string(pEncode, ret);
	}
	delete[] pEncode;
	RSA_free(rsa);
	CRYPTO_cleanup_all_ex_data();
	return strRet;
}

//　客户端公钥解密
std::string Openssl::ClientDecodeFile(const std::string msg) {
	std::string pubkey = Openssl::pubkey();
	BIO *bio = NULL;
	RSA *rsa = NULL;
	char * chpubkey = const_cast<char*>(pubkey.c_str());
	if ((bio = BIO_new_mem_buf(chpubkey, -1)) == NULL) {
		std::cout << "BIO_new_mem_buf faild!" << std::endl;
	}
	rsa = PEM_read_bio_RSA_PUBKEY(bio, NULL, NULL, NULL);
	if (msg.empty()) {
		assert(false);
		return "";
	}
	std::string strRet;
	int nlen = RSA_size(rsa);
	char* pDecode = new char[nlen + 1];
	int ret = RSA_public_decrypt(msg.length(),
			(const unsigned char*) msg.c_str(), (unsigned char*) pDecode, rsa,
			RSA_PKCS1_PADDING);
	if (ret >= 0) {
		strRet = std::string((char*) pDecode, ret);
	}
	delete[] pDecode;
	RSA_free(rsa);
	CRYPTO_cleanup_all_ex_data();
	return strRet;
}

//　服务器私钥加密
std::string Openssl::ServerEncodeFile(const std::string msg) {
	std::string prikey = Openssl::prikey();
	BIO *bio = NULL;
	RSA *rsa = NULL;
	char * chprikey = const_cast<char*>(prikey.c_str());
	if ((bio = BIO_new_mem_buf(chprikey, -1)) == NULL) {
		std::cout << "BIO_new_mem_buf faild!" << std::endl;
	}
	rsa = PEM_read_bio_RSAPrivateKey(bio, NULL, NULL, NULL);
	if (msg.empty()) {
		assert(false);
		return "se1";
	}
	std::string strRet;
	int nlen = RSA_size(rsa);
	char* pEncode = new char[nlen + 1];
	int ret = RSA_private_encrypt(msg.length(),
			(const unsigned char*) msg.c_str(), (unsigned char*) pEncode, rsa,
			RSA_PKCS1_PADDING);
	if (ret >= 0) {
		strRet = std::string(pEncode, ret);
	}
	delete[] pEncode;
	RSA_free(rsa);
	CRYPTO_cleanup_all_ex_data();
	return strRet;
}

//　服务器私钥解密
std::string Openssl::ServerDecodeFile(const std::string msg) {
	std::string prikey = Openssl::prikey();
	BIO *bio = NULL;
	RSA *rsa = NULL;
	char * chprikey = const_cast<char*>(prikey.c_str());
	if ((bio = BIO_new_mem_buf(chprikey, -1)) == NULL) {
		std::cout << "BIO_new_mem_buf faild!" << std::endl;
	}
	rsa = PEM_read_bio_RSAPrivateKey(bio, NULL, NULL, NULL);
	if (msg.empty()) {
		assert(false);
		return "sd1";
	}
	std::string strRet;
	int nlen = RSA_size(rsa);
	char* pDecode = new char[nlen + 1];
	int ret = RSA_private_decrypt(msg.length(),
			(const unsigned char*) msg.c_str(), (unsigned char*) pDecode, rsa,
			RSA_PKCS1_PADDING);
	if (ret >= 0) {
		strRet = std::string((char*) pDecode, ret);
	}
	delete[] pDecode;
	RSA_free(rsa);
	CRYPTO_cleanup_all_ex_data();
	return strRet;
}

}
