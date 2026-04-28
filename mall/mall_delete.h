#ifndef __MALL_DELETE_H__
#define __MALL_DELETE_H__
#include "utilityFunction.h"
class MallDeleteRequest
{
public:
	friend class MallDeleteResponse;
	MallDeleteRequest(){}
	MallDeleteRequest(const string& json) {
		this->Deserialize(json);
	}
	template <typename Writer>
	void Serialize(Writer& writer) const {
		writer.StartObject();
		SERIALIZE_MEMBER(writer,id);

		writer.EndObject();
	}

	void toString(std::string& json) {
		StringBuffer sb;
		Writer<StringBuffer> writer(sb);
		Serialize(writer);
		json = sb.GetString();
	}

	void Deserialize(const string& json)
	{
		try
		{
			Document d;
			if (d.Parse(json.c_str()).HasParseError()) {
				throw logic_error("parse json error. raw data : " + json);
			}
			SET_DOC_MEMBER(d, id);
		}
		catch (const std::exception& e)
		{
			std::string errInfo = std::string(__FILE__) + ":" + std::to_string(__LINE__) + ":MallDeleteRequest decode error!";
			throw logic_error(errInfo);
		}
	}

	static tars::Int32 handler(const vector<tars::Char>& reqBuf, const map<std::string, std::string>& extraInfo, vector<tars::Char>& rspBuf)
	{
	    return 0;
	}
private:
	CInteger       	_id             ;  //主键

};
class MallDeleteResponse
{
public:
	MallDeleteResponse(const string& json) {
		this->Deserialize(json);
	}
	template <typename Writer>
	void Serialize(Writer& writer) const {
		try
		{
			writer.StartObject();
			SERIALIZE_MEMBER(writer, resultCode);

			writer.EndObject();
		}
		catch (const std::exception& e)
		{
			std::string errInfo = std::string(__FILE__) + ":" + std::to_string(__LINE__) + ":MallDeleteResponse encode error!";
			throw logic_error(errInfo);
		}

	}

	void toString(std::string& json) {
		StringBuffer sb;
		Writer<StringBuffer> writer(sb);
		Serialize(writer);
		json = sb.GetString();
	}

	void Deserialize(const string& json)
	{
		Document d;
		if (d.Parse(json.c_str()).HasParseError()){
			throw logic_error("parse json error. raw data : " + json);
		}
		SET_DOC_MEMBER(d,resultCode);

	}

	static tars::Int32 handler(const vector<tars::Char>& reqBuf, const map<std::string, std::string>& extraInfo, vector<tars::Char>& rspBuf)
	{
		MallDeleteRequest request;
		decode(reqBuf, request);


		config::MallConfigDeleteReq req;
		req.id = request._id;
		int iRet = g_app.getOuterFactoryPtr()->getConfigServantPrx()->MallConfigDelete(req);
		if (iRet != 0)
		{
			string errInfo = ::toString(__FILE__, ":", __LINE__, ":", "MallConfigDelete err! id : ", req.id);
		}

		int64_t resultCode = RESULT_CODE_SUCCESS;
		std::string errDesc = "";
		toClientDelete(resultCode, errDesc, rspBuf);
	    return 0;
	}
private:
	CInteger       	_resultCode     ;  //状态码

};
#endif
