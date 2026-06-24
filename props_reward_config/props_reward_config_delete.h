#ifndef __PROPS_REWARD_CONFIG_DELETE_H__
#define __PROPS_REWARD_CONFIG_DELETE_H__
class PropsRewardConfigDeleteRequest
{
public:
	friend class PropsRewardConfigDeleteResponse;
	PropsRewardConfigDeleteRequest(){}
	PropsRewardConfigDeleteRequest(const string& json) {
		this->Deserialize(json);
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
			std::string errInfo = ::toString(__FILE__, ":", __LINE__, ":PropsRewardConfigDeleteRequest decode error!");
			throw logic_error(errInfo);
		}

	}

private:
	CInteger       	_id             ;  //主键

};
class PropsRewardConfigDeleteResponse
{
public:
	template <typename Writer>
	void Serialize(Writer& writer) const {
		writer.StartObject();
		SERIALIZE_MEMBER(writer,result);

		writer.EndObject();
	}

	void toString(std::string& json) {
		StringBuffer sb;
		Writer<StringBuffer> writer(sb);
		Serialize(writer);
		json = sb.GetString();
	}

	static tars::Int32 handler(const vector<tars::Char>& reqBuf, const map<std::string, std::string>& extraInfo, vector<tars::Char>& rspBuf)
	{
		PropsRewardConfigDeleteRequest request;
		decode(reqBuf, request);


		config::PropsConfigDeleteReq req;
		req.id = request._id;
		int iRet = g_app.getOuterFactoryPtr()->getConfigServantPrx()->ConfigPropsRewardDelete(req);
		if (iRet != 0)
		{
			string errInfo = ::toString(__FILE__, ":", __LINE__, ":", "ConfigPropsRewardDelete err! id : ", req.id);
		}

		int64_t resultCode = RESULT_CODE_SUCCESS;
		std::string errDesc = "";
		toClientDelete(resultCode, errDesc, rspBuf);
		return 0;
	}
private:
	CInteger       	_result         ;  //状态码

};
#endif