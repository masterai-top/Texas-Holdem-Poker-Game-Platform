#ifndef __MALL_LIST_H__
#define __MALL_LIST_H__
#include "../Define.h"
class MallListRequest
{
public:
	friend class MallListResponse;
	MallListRequest(){}
	MallListRequest(const string& json) {
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
			SET_DOC_MEMBER(d, area);
			SET_DOC_MEMBER(d, itemId);
			SET_DOC_MEMBER(d, startDate);
			SET_DOC_MEMBER(d, endDate);
			SET_DOC_MEMBER(d, pageIndex);
			SET_DOC_MEMBER(d, pageSize);
		}
		catch (const std::exception& e)
		{
			std::string errInfo = ::toString(__FILE__, ":", __LINE__, ":MallListRequest decode error!");
			throw logic_error(errInfo);
		}
	}
private:
	CInteger       	_id;  //主键
	CInteger        _area;  //区域
	CInteger        _itemId;  //商品id
	CString        	_startDate;  //开始时间
	CString        	_endDate;  //结束时间
	CInteger        _pageIndex;//当前页数
	CInteger        _pageSize;// 页容数量

};
class MallListResponse
{
public:
	MallListResponse(){}
	MallListResponse(const string& json) {
		this->Deserialize(json);
	}
	template <typename Writer>
	void Serialize(Writer& writer) const {
		try
		{
			writer.StartObject();
			SERIALIZE_MEMBER(writer, id);
			SERIALIZE_MEMBER(writer, area);
			SERIALIZE_MEMBER(writer, itemId);
			SERIALIZE_MEMBER(writer, icon);
			SERIALIZE_MEMBER(writer, itemType);
			SERIALIZE_MEMBER(writer, payPropsType);
			SERIALIZE_MEMBER(writer, label);
			SERIALIZE_MEMBER(writer, platformType);
			SERIALIZE_MEMBER(writer, qrCode);
			SERIALIZE_MEMBER(writer, payValue);
			SERIALIZE_MEMBER(writer, payPropsId);
			SERIALIZE_MEMBER(writer, itemValue);
			SERIALIZE_MEMBER(writer, optUser);
			SERIALIZE_MEMBER(writer, createDate);
			SERIALIZE_MEMBER(writer, exchangeGroup);
			SERIALIZE_MEMBER(writer, product_id);
			SERIALIZE_MEMBER(writer, condition);
			SERIALIZE_MEMBER(writer, discount);
			writer.EndObject();
		}
		catch (const std::exception&)
		{
			std::string errInfo = ::toString(__FILE__, ":", __LINE__, ":MallListResponse encode error!");
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
		if (d.Parse(json.c_str()).HasParseError()) {
			throw logic_error("parse json error. raw data : " + json);
		}
		SET_DOC_MEMBER(d, id);
		SET_DOC_MEMBER(d, area);
		SET_DOC_MEMBER(d, itemId);
		SET_DOC_MEMBER(d, icon);
		SET_DOC_MEMBER(d, itemType);
		SET_DOC_MEMBER(d, payPropsType);
		SET_DOC_MEMBER(d, label);
		SET_DOC_MEMBER(d, platformType);
		SET_DOC_MEMBER(d, qrCode);
		SET_DOC_MEMBER(d, payValue);
		SET_DOC_MEMBER(d, payPropsId);
		SET_DOC_MEMBER(d, itemValue);
		SET_DOC_MEMBER(d, optUser);
		SET_DOC_MEMBER(d, createDate);
		SET_DOC_MEMBER(d, exchangeGroup);
		SET_DOC_MEMBER(d, product_id);
		SET_DOC_MEMBER(d, condition);
		SET_DOC_MEMBER(d, discount);
	}

	static tars::Int32 handler(const vector<tars::Char>& reqBuf, const map<std::string, std::string>& extraInfo, vector<tars::Char>& rspBuf)
	{
		MallListRequest request;
		decode(reqBuf, request);

		// 业务代码
		config::MallConfigQueryReq req;
		if (request._area.isNull() == false) req.data.insert(make_pair("area", request._area.toString()));
		if (request._id.isNull() == false) req.data.insert(make_pair("id", request._id.toString()));
		if (request._itemId.isNull() == false) req.data.insert(make_pair("itemId", request._itemId.toString()));
		req.pageIndex = request._pageIndex;
		req.pageSize = request._pageSize;
		config::MallConfigQueryRsp resp;
		int iRet = g_app.getOuterFactoryPtr()->getConfigServantPrx()->MallConfigQuery(req, resp);
		if (iRet != 0)
		{
			string errInfo = ::toString(__FILE__, ":", __LINE__, ":MallConfigQuery error!");
			ROLLLOG_ERROR << errInfo << endl;
			throw logic_error(errInfo);
		}

		int64_t resultCode = RESULT_CODE_SUCCESS;
		std::string errDesc = "";
		int64_t totalItems = resp.totalItems;									//总条数
		int64_t totalPages = resp.totalPages;
		std::vector<MallListResponse> respVec;
		for(const auto& _map : resp.data){
			MallListResponse response;
			for(const auto& _pair : _map){
				const std::string& key = _pair.first;
				const std::string& value = _pair.second;
				SET_RESPONSE_MEMBER(id);
				SET_RESPONSE_MEMBER(area);
				SET_RESPONSE_MEMBER(itemId);
				SET_RESPONSE_MEMBER(icon);
				SET_RESPONSE_MEMBER(itemType);
				SET_RESPONSE_MEMBER(payPropsType);
				SET_RESPONSE_MEMBER(label);
				SET_RESPONSE_MEMBER(platformType);
				SET_RESPONSE_MEMBER(qrCode);
				SET_RESPONSE_MEMBER(payValue);
				SET_RESPONSE_MEMBER(payPropsId);
				SET_RESPONSE_MEMBER(itemValue);
				SET_RESPONSE_MEMBER(optUser);
				SET_RESPONSE_MEMBER(createDate);
				SET_RESPONSE_MEMBER(exchangeGroup);
				SET_RESPONSE_MEMBER(product_id);
				SET_RESPONSE_MEMBER(condition);
				SET_RESPONSE_MEMBER(discount);
				ROLLLOG_DEBUG << "key:" << key<< ", value: "<< value << endl;
			}
			respVec.push_back(response);
		}
		toClient(resultCode, errDesc, respVec, totalItems, totalPages, rspBuf);
		return 0;
	}
private:
	CInteger       	_id;  //主键
	CInteger       	_area;  //地区
	CInteger       	_itemId;  //商品id
	CString        	_icon;  //商品图标id
	CInteger       	_itemType;  //商品类型 1:金币 2:钻石 3:储蓄罐
	CInteger       	_payPropsType;  //消耗类型 1:现金 2:钻石 3:金币
	CInteger       	_label;  //购买标签 1:金币充值 2:钻石充值 3:钻石购买 4:金币购买
	CInteger       	_platformType;  //平台类型 0:本地测试 1:台湾 2:东南亚 3:香港 4:澳门
	CInteger       	_qrCode;  //商品二维码
	CDouble       	_payValue;  //充值档位
	CInteger       	_payPropsId;  //道具id:数值(多个道具用英文字符,隔开)
	CInteger       	_itemValue;  //获得道具数量(金币)
	CString        	_optUser;  //操作者
	CString        	_createDate;  //创建时间
	CString			_exchangeGroup;
	CString         _product_id;//产品id
	CInteger        _condition;//条件
	CString         _discount; //优惠百分比
};
#endif