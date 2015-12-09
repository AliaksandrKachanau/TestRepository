#pragma once
#include "MT4ManagerAPI.h"
#include "MTPumpingManagerEx.h"
#include <string>
using namespace std;

class CMetaConnect
{
public:
	CMetaConnect(string address = "", int login = 0, string password = "");
	~CMetaConnect(void);

	bool CheckConnection();
	static CManagerInterface *m_pManager;
	static CManagerFactory *m_pFactory;
	CMTPumpingManagerEx m_pumping;
protected:
	bool Connect();

private:
	const string m_address;
	const int m_login;
	const string m_password;
};

