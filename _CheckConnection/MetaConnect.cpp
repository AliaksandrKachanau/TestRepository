#include "StdAfx.h"
#include "MetaConnect.h"

CManagerInterface* CMetaConnect::m_pManager = NULL;
CManagerFactory* CMetaConnect::m_pFactory = NULL;
CMetaConnect::CMetaConnect(string address, int login, string password): m_address(address), m_login(login), m_password(password)
{
	m_pFactory = new CManagerFactory("mtmanapi");
	m_pFactory->WinsockStartup();
	if( m_pFactory->IsValid() == FALSE || 
				(m_pManager = m_pFactory->Create( ManAPIVersion ))==NULL)
			{
				string ss;
				cout<<"Create Error";
			}
	Connect();
}


CMetaConnect::~CMetaConnect(void)
{
	m_pManager->Disconnect();
	m_pManager->Release();
	delete m_pFactory;
}

bool CMetaConnect::CheckConnection()
{
	if (0 == m_login)
	{
		return true;
	}
	bool isConnected = m_pManager->IsConnected();
	if (isConnected || Connect())
	{
		return true;
	}
	else
	{
		cout<<"pumping disconnected "<<'\n';
		m_pumping.fout<<"pumping disconnected "<<'\n';

		return false;
	}
}

bool CMetaConnect::Connect()
{
	int code = m_pManager->Connect(m_address.c_str());
	if (RET_OK != code)
	{
		cout<<"unable to connect to meta server; address = "<<m_address<<"; code = "<<code<<'\n';
		m_pumping.fout<<"unable to connect to meta server; address = "<<m_address<<"; code = "<<code<<'\n';

		return false;
	}
	code = m_pManager->Login(m_login, m_password.c_str());
	if (RET_OK != code)
	{
		cout<<"unable to login to meta server; login = "<<m_login<<"; password = "<<m_password<<"; code = "<<code<<'\n';
		m_pumping.fout<<"unable to login to meta server; login = "<<m_login<<"; password = "<<m_password<<"; code = "<<code<<'\n';
		return false;
	}
			
	cout<<"pumping connected "<<'\n';
	m_pumping.fout<<"pumping connected "<<'\n';
		
	m_pManager->PumpingSwitchEx(m_pumping.PumpingFunction, 0, this);
	cout<<"pumping PumpingSwitchEx ON"<<'\n';
	m_pumping.fout<<"pumping PumpingSwitchEx ON"<<'\n';
	return true;
}