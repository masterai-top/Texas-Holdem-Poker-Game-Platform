#ifndef __PROPS_REWARD_CONFIG_LIST_H__
#define __PROPS_REWARD_CONFIG_LIST_H__
class PropsRewardConfigListRequest
{
public:
	friend class PropsRewardConfigListResponse;
	PropsRewardConfigListRequest(){}
	PropsRewardConfigListRequest(const string& json) {
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
			SET_DOC_MEMBER(d, startDate);
			SET_DOC_MEMBER(d, endDate);
			SET_DOC_MEMBER(d, pageIndex);
			SET_DOC_MEMBER(d, pageSize);
		}
		catch (const std::exception& e)
		{
			std::string errInfo = ::toString(__FILE__, ":", __LINE__, ":PropsRewardConfigListRequest decode error!");
			throw logic_error(errInfo);
		}
	}
private:
	CInteger		_id;  //主键ID
	CString        	_startDate;  //开始时间
	CString        	_endDate;  //结束时间
	CInteger        _pageIndex;//当前页数
	CInteger        _pageSize;// 页容数量

};
class PropsRewardConfigListResponse
{
public:
	PropsRewardConfigListResponse(){}
	PropsRewardConfigListResponse(const string& json) {
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

	// TODO 这里有时间可以传入查询条件,比如ID,目前时间比较紧,查出全部数据
	static tars::Int32 handler(const vector<tars::Char>& reqBuf, const map<std::string, std::string>& extraInfo, vector<tars::Char>& rspBuf)
	{
		PropsRewardConfigListRequest request;
		decode(reqBuf, request);

		config::PropsConfigQueryReq req;
		if (request._id.isNull() == false) req.data.insert(make_pair("id", request._id.toString()));
		req.pageIndex = request._pageIndex;
		req.pageSize = request._pageSize;
		config::PropsConfigQueryRsp resp;
		int iRet = g_app.getOuterFactoryPtr()->getConfigServantPrx()->ConfigPropsRewardQuery(req, resp);
		if (iRet != 0)
		{
			ROLLLOG_ERROR << "ConfigPropsRewardQuery ERROR!" << endl;
			throw logic_error("ConfigPropsRewardQuery ERROR! RPC invoke failed!");
		}

		int64_t resultCode = RESULT_CODE_SUCCESS;
		std::string errDesc = "";
		int64_t totalItems = resp.totalItems;									//总条数
		int64_t totalPages = resp.totalPages;
		std::vector<PropsRewardConfigListResponse> respVec;
		for (const auto& _map : resp.data) {
			PropsRewardConfigListResponse response;
			for (const auto& _pair : _map) {
				const std::string& key = _pair.first;
				const std::string& value = _pair.second;
				if (key == "id")			response._id.assign(value); 
				if (key == "reward_id")		response._rewardId.assign(value);
				if (key == "rank_start")	response._rankStart.assign(value);
				if (key == "rank_end")		response._rankEnd.assign(value);
				if (key == "ratio")			response._ratio.assign(value);
				if (key == "status")		response._status.assign(value);
				if (key == "propsIds")		response._propsIds.assign(value);
				if (key == "modify_man")	response._optUser.assign(value);
				if (key == "modify_time")	response._createDate.assign(value);
			}
			respVec.push_back(response);
		}
		toClient(resultCode, errDesc, respVec, totalItems, totalPages, rspBuf);
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