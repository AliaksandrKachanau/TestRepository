#include "stdafx.h"
#include "MTPumpingManagerEx.h"


#pragma warning (push, 4)


namespace
{
	typedef void (CMTPumpingManagerEx::*PumpingHandler)(int type, void* data);
	struct PumpingEntry
	{
		int Code;
		PumpingHandler Handler;
	};
	PumpingEntry cHandlers[] =
	{
		{ PUMP_START_PUMPING,		&CMTPumpingManagerEx::OnStartInternal },
		{ PUMP_UPDATE_SYMBOLS,		&CMTPumpingManagerEx::OnUpdateSymbolsInternal },
		{ PUMP_UPDATE_GROUPS,		&CMTPumpingManagerEx::OnUpdateGroupsInternal },
		{ PUMP_UPDATE_USERS,			&CMTPumpingManagerEx::OnUpdateUsersInternal },
		{ PUMP_UPDATE_ONLINE,		&CMTPumpingManagerEx::OnUpdateOnlineInternal },
		{ PUMP_UPDATE_BIDASK,		&CMTPumpingManagerEx::OnUpdateBidAskInternal },
		{ PUMP_UPDATE_NEWS,			&CMTPumpingManagerEx::OnUpdateNewsInternal },
		{ PUMP_UPDATE_NEWS_BODY,	&CMTPumpingManagerEx::OnUpdateNewsBodyInternal },
		{ PUMP_UPDATE_MAIL,			&CMTPumpingManagerEx::OnUpdateMailInternal },
		{ PUMP_UPDATE_TRADES,		&CMTPumpingManagerEx::OnUpdateTradesInternal },
		{ PUMP_UPDATE_REQUESTS,		&CMTPumpingManagerEx::OnUpdateRequestsInternal },
		{ PUMP_UPDATE_PLUGINS,		&CMTPumpingManagerEx::OnUpdatePluginsInternal },
		{ PUMP_UPDATE_ACTIVATION,	&CMTPumpingManagerEx::OnUpdateActivationInternal },
		{ PUMP_UPDATE_MARGINCALL,	&CMTPumpingManagerEx::OnUpdateMargincallInternal },
		{ PUMP_STOP_PUMPING,			&CMTPumpingManagerEx::OnStopInternal },
		{ PUMP_PING,					&CMTPumpingManagerEx::OnPingInternal },
		{ PUMP_UPDATE_NEWS_NEW,			&CMTPumpingManagerEx::OnUpdateNewsNewInternal },
	};
}

CMTPumpingManagerEx::CMTPumpingManagerEx()
{
	time_t rawtime;
	time ( &rawtime );
	struct tm *timeinfo = localtime( &rawtime );
	std::stringstream ssFile;
	ssFile << asctime (timeinfo);
	string sFile = ssFile.str().substr(0, ssFile.str().length() - 1);
	sFile += ".txt";
	std::replace(sFile.begin(), sFile.end(), ':', '_');
	std::replace(sFile.begin(), sFile.end(), ' ', '_');
	fout.open(sFile, ios_base::app);
	if(!fout.is_open())
		cout<<"file "<<sFile<<" isn't opened"<<'\n';
}

ofstream CMTPumpingManagerEx::fout;
void CALLBACK CMTPumpingManagerEx::PumpingFunction(int code, int type, void* data, void* param)
{

	CMTPumpingManagerEx* pThis = reinterpret_cast<CMTPumpingManagerEx*>(param);


	if ((code < 0) || (code >= lengthof(cHandlers)))
	{
		assert(!"unknown pumping code");
		return;
	}

	cout<<"PumpingMethod code = "<<code<<'\n';
	fout<<"PumpingMethod code = "<<code<<'\n';
			
	time_t rawtime;
	time ( &rawtime );
	struct tm *timeinfo = localtime( &rawtime );
	fout << asctime (timeinfo);
	fout.flush();
	pThis->PumpingMethod(code, type, data);
}
void CMTPumpingManagerEx::PumpingMethod(int code, int type, void* data)
{
	assert(cHandlers[code].Code == code);
	PumpingHandler pMethod = cHandlers[code].Handler;
	(this->*pMethod)(type, data);
}

// begin of internal handlers

void CMTPumpingManagerEx::OnStartInternal(int type, void* data)
{
	assert(0 == type); UNREFERENCED_PARAMETER(type);
	assert(0 == data); UNREFERENCED_PARAMETER(data);
	OnStart();
}

void CMTPumpingManagerEx::OnUpdateSymbolsInternal(int type, void* data)
{	
	UNREFERENCED_PARAMETER(type);
	const ConSymbol* pSymbol = reinterpret_cast<const ConSymbol*>(data);
	cout<<"OnUpdateSymbolsInternal pSymbol = "<<pSymbol<< '\n';
	fout<<"OnUpdateSymbolsInternal pSymbol = "<<pSymbol<< '\n';
	if (0 == pSymbol)
	{
		OnUpdateSymbols();
	}
	else
	{
		OnUpdateSymbols(*pSymbol);
	}
}

void CMTPumpingManagerEx::OnUpdateGroupsInternal(int type, void* data)
{	
	const ConGroup* pGroup = reinterpret_cast<const ConGroup*>(data);
	cout<<"OnUpdateGroupsInternal pGroup = "<<pGroup<< '\n';
	fout<<"OnUpdateGroupsInternal pGroup = "<<pGroup<< '\n';
	if (0 == pGroup)
	{
		OnUpdateGroups();
	}
	else
	{
		OnUpdateGroups(type, *pGroup);
	}
}

void CMTPumpingManagerEx::OnUpdateUsersInternal(int type, void* data)
{
	const UserRecord* pRecord = reinterpret_cast<const UserRecord*>(data);
	cout<<"OnUpdateUsersInternal pRecord = "<<pRecord<< '\n';
	fout<<"OnUpdateUsersInternal pRecord = "<<pRecord<< '\n';
	if (0 == pRecord)
	{
		OnUpdateUsers();
	}
	else
	{
		OnUpdateUsers(type, *pRecord);
	}
}

void CMTPumpingManagerEx::OnUpdateOnlineInternal(int type, void* data)
{
	const int* pLogin = reinterpret_cast<const int*>(data);
	cout<<"OnUpdateOnlineInternal pLogin = "<<pLogin<< '\n';
	fout<<"OnUpdateOnlineInternal pLogin = "<<pLogin<< '\n';
	if (0 == pLogin)
	{
		assert(0 == type);
		OnUpdateOnline();
	}
	else
	{
		OnUpdateOnline(type, *pLogin);
	}
}

void CMTPumpingManagerEx::OnUpdateBidAskInternal(int type, void* data)
{
	assert(0 == type); UNREFERENCED_PARAMETER(type);
	assert(0 == data); UNREFERENCED_PARAMETER(data);
	OnUpdateBidAsk();
}

void CMTPumpingManagerEx::OnUpdateNewsInternal(int type, void* data)
{
	assert(0 == type); UNREFERENCED_PARAMETER(type);
	const NewsTopic* pTopic = reinterpret_cast<const NewsTopic*>(data);
	cout<<"OnUpdateNewsInternal pTopic = "<<pTopic<< '\n';
	fout<<"OnUpdateNewsInternal pTopic = "<<pTopic<< '\n';
	if (0 == pTopic)
	{
		OnUpdateNews();
	}
	else
	{
		OnUpdateNews(*pTopic);
	}
}

void CMTPumpingManagerEx::OnUpdateNewsBodyInternal(int type, void* data)
{
	assert(0 == type); UNREFERENCED_PARAMETER(type);
	assert(0 == data); UNREFERENCED_PARAMETER(data);
	OnUpdateNewsBody();
}

void CMTPumpingManagerEx::OnUpdateMailInternal(int type, void* data)
{
	assert(0 == type); UNREFERENCED_PARAMETER(type);
	const MailBox* pMail = reinterpret_cast<const MailBox*>(data);
	cout<<"OnUpdateMailInternal pMail = "<<pMail<< '\n';
	fout<<"OnUpdateMailInternal pMail = "<<pMail<< '\n';
	if (0 == pMail)
	{
		OnUpdateMail();
	}
	else
	{
		OnUpdateMail(*pMail);
	}
}

void CMTPumpingManagerEx::OnUpdateTradesInternal(int type, void* data)
{
	const TradeRecord* pRecord = reinterpret_cast<const TradeRecord*>(data);
	cout<<"OnUpdateTradesInternal pRecord = "<<pRecord<< '\n';
	fout<<"OnUpdateTradesInternal pRecord = "<<pRecord<< '\n';
	if (0 == pRecord)
	{
		OnUpdateTrades();
	}
	else
	{
		OnUpdateTrades(type, *pRecord);
	}
}

void CMTPumpingManagerEx::OnUpdateRequestsInternal(int type, void* data)
{
	const RequestInfo* pInfo = reinterpret_cast<const RequestInfo*>(data);
	cout<<"OnUpdateRequestsInternal pInfo = "<<pInfo<< '\n';
	fout<<"OnUpdateRequestsInternal pInfo = "<<pInfo<< '\n';
	if (0 == pInfo)
	{
		OnUpdateRequests();
	}
	else
	{
		OnUpdateRequests(type, *pInfo);
	}
}

void CMTPumpingManagerEx::OnUpdatePluginsInternal(int type, void* data)
{
	assert(0 == type); UNREFERENCED_PARAMETER(type);
	assert(0 == data); UNREFERENCED_PARAMETER(data);
	OnUpdatePlugins();
}

void CMTPumpingManagerEx::OnUpdateActivationInternal(int type, void* data)
{
	assert(0 == type); UNREFERENCED_PARAMETER(type);
	assert(0 == data); UNREFERENCED_PARAMETER(data);
	OnUpdateActivation();
}

void CMTPumpingManagerEx::OnUpdateMargincallInternal(int type, void* data)
{
	assert(0 == type); UNREFERENCED_PARAMETER(type);
	assert(0 == data); UNREFERENCED_PARAMETER(data);
	OnUpdateMargincall();
}

void CMTPumpingManagerEx::OnStopInternal(int type, void* data)
{
//	(m_isInHouse ? g_bIsPumping2ExtInitialized : g_bIsPumpingExtInitialized) = false;
	assert(0 == type); UNREFERENCED_PARAMETER(type);
	assert(0 == data); UNREFERENCED_PARAMETER(data);
	OnStop();
}

void CMTPumpingManagerEx::OnPingInternal(int type, void* data)
{
	assert(0 == type); UNREFERENCED_PARAMETER(type);
	assert(0 == data); UNREFERENCED_PARAMETER(data);
	OnPing();
}

void CMTPumpingManagerEx::OnUpdateNewsNewInternal(int type, void* data)
{
	assert(0 == type); UNREFERENCED_PARAMETER(type);
	const NewsTopicNew* pTopicNew = reinterpret_cast<const NewsTopicNew*>(data);
	cout<<"OnUpdateNewsNewInternal pTopicNew = "<<pTopicNew<< '\n';
	fout<<"OnUpdateNewsNewInternal pTopicNew = "<<pTopicNew<< '\n';
	if (0 == pTopicNew)
	{
		OnUpdateNewsNew();
	}
	else
	{
		OnUpdateNewsNew(*pTopicNew);
	}
}
// end of internal handlers

// begin of overriding methods

void CMTPumpingManagerEx::OnStart()
{
}

void CMTPumpingManagerEx::OnUpdateSymbols()
{
}

void CMTPumpingManagerEx::OnUpdateSymbols(const ConSymbol& symbol)
{
	UNREFERENCED_PARAMETER(symbol);
}

void CMTPumpingManagerEx::OnUpdateGroups()
{
}

void CMTPumpingManagerEx::OnUpdateGroups(const int type, const ConGroup& group)
{
	UNREFERENCED_PARAMETER(type);
	UNREFERENCED_PARAMETER(group);
}

void CMTPumpingManagerEx::OnUpdateUsers()
{
}

void CMTPumpingManagerEx::OnUpdateUsers(const int type, const UserRecord& record)
{
	UNREFERENCED_PARAMETER(type);
	UNREFERENCED_PARAMETER(record);
}

void CMTPumpingManagerEx::OnUpdateOnline()
{
}
void CMTPumpingManagerEx::OnUpdateOnline(const int type, const int login)
{
	UNREFERENCED_PARAMETER(type);
	UNREFERENCED_PARAMETER(login);
}

void CMTPumpingManagerEx::OnUpdateBidAsk()
{
}

void CMTPumpingManagerEx::OnUpdateNews()
{
}

void CMTPumpingManagerEx::OnUpdateNews(const NewsTopic& topic)
{
	UNREFERENCED_PARAMETER(topic);
}

void CMTPumpingManagerEx::OnUpdateNewsBody()
{
}

void CMTPumpingManagerEx::OnUpdateMail()
{
}

void CMTPumpingManagerEx::OnUpdateMail(const MailBox& mail)
{
	UNREFERENCED_PARAMETER(mail);
}

void CMTPumpingManagerEx::OnUpdateTrades()
{
}

void CMTPumpingManagerEx::OnUpdateTrades(const int type, const TradeRecord& record)
{
	UNREFERENCED_PARAMETER(type);
	UNREFERENCED_PARAMETER(record);
}

void CMTPumpingManagerEx::OnUpdateRequests()
{
}

void CMTPumpingManagerEx::OnUpdateRequests(const int type, const RequestInfo& info)
{
	UNREFERENCED_PARAMETER(type);
	UNREFERENCED_PARAMETER(info);
}

void CMTPumpingManagerEx::OnUpdatePlugins()
{
}

void CMTPumpingManagerEx::OnUpdateActivation()
{
}

void CMTPumpingManagerEx::OnUpdateMargincall()
{
}

void CMTPumpingManagerEx::OnStop()
{
}

void CMTPumpingManagerEx::OnPing()
{
}

void CMTPumpingManagerEx::OnUpdateNewsNew()
{
}

void CMTPumpingManagerEx::OnUpdateNewsNew(const NewsTopicNew& topicNew)
{
	UNREFERENCED_PARAMETER(topicNew);
}
// end of overriding methods

