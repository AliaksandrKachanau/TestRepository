#include <string>
using namespace std;
#pragma once

#pragma warning (push, 4)


class CMTPumpingManagerEx
{

public:
	CMTPumpingManagerEx();
protected:
	virtual void OnStart();
	virtual void OnUpdateSymbols();
	virtual void OnUpdateSymbols(const ConSymbol& symbol);
	virtual void OnUpdateGroups();
	virtual void OnUpdateGroups(const int type, const ConGroup& group);
	virtual void OnUpdateUsers();
	virtual void OnUpdateUsers(const int type, const UserRecord& record);
	virtual void OnUpdateOnline();
	virtual void OnUpdateOnline(const int type, const int login);
	virtual void OnUpdateBidAsk();
	virtual void OnUpdateNews();
	virtual void OnUpdateNews(const NewsTopic& topic);
	virtual void OnUpdateNewsBody();
	virtual void OnUpdateMail();
	virtual void OnUpdateMail(const MailBox& mail);
	virtual void OnUpdateTrades();
	virtual void OnUpdateTrades(const int type, const TradeRecord& record);
	virtual void OnUpdateRequests();
	virtual void OnUpdateRequests(const int type, const RequestInfo& info);
	virtual void OnUpdatePlugins();
	virtual void OnUpdateActivation();
	virtual void OnUpdateMargincall();
	virtual void OnStop();
	virtual void OnPing();
	virtual void OnUpdateNewsNew();
	virtual void OnUpdateNewsNew(const NewsTopicNew& topicNew);
public:
	void OnStartInternal(int type, void* data);
	void OnUpdateSymbolsInternal(int type, void* data);
	void OnUpdateGroupsInternal(int type, void* data);
	void OnUpdateUsersInternal(int type, void* data);
	void OnUpdateOnlineInternal(int type, void* data);
	void OnUpdateBidAskInternal(int type, void* data);
	void OnUpdateNewsInternal(int type, void* data);
	void OnUpdateNewsBodyInternal(int type, void* data);
	void OnUpdateMailInternal(int type, void* data);
	void OnUpdateTradesInternal(int type, void* data);
	void OnUpdateRequestsInternal(int type, void* data);
	void OnUpdatePluginsInternal(int type, void* data);
	void OnUpdateActivationInternal(int type, void* data);
	void OnUpdateMargincallInternal(int type, void* data);
	void OnStopInternal(int type, void* data);
	void OnPingInternal(int type, void* data);
	void OnUpdateNewsNewInternal(int type, void* data);

public:
	static void __stdcall PumpingFunction(int code, int type, void* data, void* param);
	void PumpingMethod(int code, int type, void* data);
	static ofstream fout;
};



#pragma warning (pop)