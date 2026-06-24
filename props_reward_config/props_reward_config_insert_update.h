 #ifndef __PROPS_REWARD_CONFIG_INSERT_UPDATE_H__
#define __PROPS_REWARD_CONFIG_INSERT_UPDATE_H__
class PropsRewardConfigInsertUpdateRequest
{
public:
	friend class PropsRewardConfigInsertUpdateResponse;
	PropsRewardConfigInsertUpdateRequest(){}
	PropsRewardConfigInsertUpdateRequest(const string& json) {
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
			SET_DOC_MEMBER(d, rewardId);
			SET_DOC_MEMBER(d, rankStart);
			SET_DOC_MEMBER(d, rankEnd);
			SET_DOC_MEMBER(d, ratio);
			SET_DOC_MEMBER(d, status);
			SET_DOC_MEMBER(d, propsIds);
			SET_DOC_MEMBER(d, optUser);
			SET_DOC_MEMBER(d, createDate);
		}
		catch (const std::exception&)
		{
			std::string errInfo = ::toString(__FILE__, ":", __LINE__, ":PropsRewardConfigInsertUpdateRequest decode error!");
			throw logic_error(errInfo);
		}
	}
private:
	CInteger       	_id;  //主键
	CInteger       	_rewardId;  //奖励Id
	CInteger       	_rankStart;  //开始排名
	CInteger       	_rankEnd;  //结束排名
	CInteger       	_ratio;  //奖池百分比
	CInteger       	_status;  //是否可用 0:否 1:是
	CString        	_propsIds;  //奖励道具：(例如: 10010001:100｜100010002:200)
	CString        	_optUser;  //操作者
	CString        	_createDate;  //创建时间

};
class PropsRewardConfigInsertUpdateResponse
{
public:
	PropsRewardConfigInsertUpdateResponse(){}
	PropsRewardConfigInsertUpdateResponse(const string& json) {
		this->Deserialize(json);
	}
	template <typename Writer>
	void Serialize(Writer& writer) const {
		writer.StartObject();
		SERIALIZE_MEMBER(writer, id);
		SERIALIZE_MEMBER(writer, rewardId);
		SERIALIZE_MEMBER(writer, rankStart);
		SERIALIZE_MEMBER(writer, rankEnd);
		SERIALIZE_MEMBER(writer, ratio);
		SERIALIZE_MEMBER(writer, status);
		SERIALIZE_MEMBER(writer, propsIds);
		SERIALIZE_MEMBER(writer, optUser);
		SERIALIZE_MEMBER(writer, createDate);

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
		Document d;
		if (d.Parse(json.c_str()).HasParseError()) {
			throw logic_error("parse json error. raw data : " + json);
		}
		SET_DOC_MEMBER(d, id);
		SET_DOC_MEMBER(d, rewardId);
		SET_DOC_MEMBER(d, rankStart);
		SET_DOC_MEMBER(d, rankEnd);
		SET_DOC_MEMBER(d, ratio);
		SET_DOC_MEMBER(d, status);
		SET_DOC_MEMBER(d, propsIds);
		SET_DOC_MEMBER(d, optUser);
		SET_DOC_MEMBER(d, createDate);

	}

	static void sendToClient(const std::map<std::string, std::string>& m, vector<tars::Char>& rspBuf)
	{
		int64_t resultCode = RESULT_CODE_SUCCESS;
		std::string errDesc = "";
		std::vector<PropsRewardConfigInsertUpdateResponse> respVec;
		PropsRewardConfigInsertUpdateResponse response;
		for (const auto& _pair : m) {
			const std::string& key = _pair.first;
			const std::string& value = _pair.second;
			if (key == "id") response._id.assign(value); 
			if (key == "reward_id") response._rewardId.assign(value);
			if (key == "rank_start") response._rankStart.assign(value);
			if (key == "rank_end") response._rankEnd.assign(value);
			if (key == "ratio") response._ratio.assign(value);
			if (key == "status") response._status.assign(value);
			if (key == "propsIds") response._propsIds.assign(value);
			if (key == "modify_man") response._optUser.assign(value);
			if (key == "modify_time") response._createDate.assign(value);
		}
		respVec.push_back(response);
		toClientInsertUpdate(resultCode, errDesc, respVec, rspBuf);
	}

	static tars::Int32 handler(const vector<tars::Char>& reqBuf, const map<std::string, std::string>& extraInfo, vector<tars::Char>& rspBuf)
	{
		PropsRewardConfigInsertUpdateRequest request;
		decode(reqBuf, request);

		if (request._id.isNull()) {
			// 插入数据 == 这里可能抛出异常
			config::PropsConfigInsertReq req;
			try
			{
				req.data["reward_id"]	= request._rewardId.toString();
				req.data["rank_start"]	= request._rankStart.toString();
				req.data["rank_end"]	= request._rankEnd.toString();
				req.data["ratio"]		= request._ratio.toString();
				req.data["status"]		= request._status.toString();
				req.data["modify_man"]	= request._optUser.toString();
				req.data["props_id"]	= request._propsIds.toString();
			}
			catch (const std::exception&)
			{
				string errInfo = ::toString(__FILE__, ":", __LINE__, ":", "插入的部分数据字段为NULL!");
				ROLLLOG_ERROR << errInfo << endl;
				throw logic_error(errInfo);
			}
			config::PropsConfigInsertRsp resp;
			int iRet = g_app.getOuterFactoryPtr()->getConfigServantPrx()->ConfigPropsRewardInsert(req, resp);
			if (iRet != 0)
			{
				string errInfo = ::toString(__FILE__, ":", __LINE__, ":", "ConfigPropsRewardInsert err!");
				ROLLLOG_ERROR << errInfo << endl;
				throw logic_error(errInfo);
			}

			// 响应给客户端
			PropsRewardConfigInsertUpdateResponse::sendToClient(resp.data.at(0), rspBuf);
		}
		else {
			config::PropsConfigUpdateReq req;
			if (request._id.isNull() == false)			req.data["id"] = request._id.toString();
			if (request._rewardId.isNull() == false)	req.data["reward_id"] = request._rewardId.toString();
			if (request._rankStart.isNull() == false)	req.data["rank_start"] = request._rankStart.toString();
			if (request._rankEnd.isNull() == false)		req.data["rank_end"] = request._rankEnd.toString();
			if (request._ratio.isNull() == false)		req.data["ratio"] = request._ratio.toString();
			if (request._status.isNull() == false)		req.data["status"] = request._status.toString();
			if (request._propsIds.isNull() == false)	req.data["props_id"] = request._propsIds.toString();
			if (request._optUser.isNull() == false)		req.data["modify_man"] = request._optUser.toString();
			config::PropsConfigUpdateRsp resp;
			int iRet = g_app.getOuterFactoryPtr()->getConfigServantPrx()->ConfigPropsRewardUpdate(req, resp);
			if (iRet != 0){
				string errInfo = ::toString(__FILE__, ":", __LINE__, ":", "ConfigPropsRewardUpdate err!");
				ROLLLOG_ERROR << errInfo << endl;
				throw logic_error(errInfo); 
			}

			// 响应给客户端
			PropsRewardConfigInsertUpdateResponse::sendToClient(resp.data.at(0), rspBuf);
		}
		return 0;
	}
private:
	CInteger       	_id;  //主键
	CInteger       	_rewardId;  //奖励Id
	CInteger       	_rankStart;  //开始排名
	CInteger       	_rankEnd;  //结束排名
	CInteger       	_ratio;  //奖池百分比
	CInteger       	_status;  //是否可用 0:否 1:是
	CString        	_propsIds;  //奖励道具：(例如: 10010001:100｜100010002:200)
	CString        	_optUser;  //操作者
	CString        	_createDate;  //创建时间

};
#endif