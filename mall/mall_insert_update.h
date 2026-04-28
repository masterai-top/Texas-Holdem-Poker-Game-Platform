#ifndef __MALL_INSERT_UPDATE_H__
#define __MALL_INSERT_UPDATE_H__
#include "../utilityFunction.h"
class MallInsertUpdateRequest
{
public:
	friend class MallInsertUpdateResponse;
	MallInsertUpdateRequest(){}
	MallInsertUpdateRequest(const string& json) {
		this->Deserialize(json);
	}
	template <typename Writer>
	void Serialize(Writer& writer) const {
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

		writer.EndObject();
	}

	void toString(std::string& json) {
		StringBuffer sb;
		Writer<StringBuffer> writer(sb);
		Serialize(writer);
		json = sb.GetString();
	}

	// 请求只用到反序列化的函数
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
		}
		catch (const std::exception& e)
		{
			std::string errInfo = std::string(__FILE__) + ":" + std::to_string(__LINE__) + ":MallInsertUpdateRequest decode error!";
			throw logic_error(errInfo);
		}
	}

private:
	CInteger       	_id;	//主键
	CInteger        _area;  //地区
	CInteger       	_itemId;  //商品id
	CString        	_icon;  //商品图标id
	CInteger        _itemType;  //商品类型 1:金币 2:钻石 3:储蓄罐
	CInteger       	_payPropsType;  //消耗类型 1:现金 2:钻石 3:金币
	CInteger       	_label;  //购买标签 1:金币充值 2:钻石充值 3:钻石购买 4:金币购买
	CInteger       	_platformType;  //平台类型 0:本地测试 1:台湾 2:东南亚 3:香港 4:澳门
	CInteger       	_qrCode;  //商品二维码
	CDouble       	_payValue;  //充值档位
	CInteger        _payPropsId;  //道具id:数值(多个道具用英文字符,隔开)
	CInteger       	_itemValue;  //获得道具数量(金币)
	CString        	_optUser;  //操作者
	CString        	_createDate;  //创建时间
	CString        	_exchangeGroup;  

};
class MallInsertUpdateResponse
{
public:
	MallInsertUpdateResponse(){}
	MallInsertUpdateResponse(const string& json) {
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
			writer.EndObject();
		}
		catch (const std::exception& e)
		{
			std::string errInfo = std::string(__FILE__) + ":" + std::to_string(__LINE__) + ":MallInsertUpdateResponse encode error!";
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

	}

	static void sendToClient(const std::map<std::string, std::string>& m, vector<tars::Char>& rspBuf)
	{
		int64_t resultCode = RESULT_CODE_SUCCESS;
		std::string errDesc = "";
		std::vector<MallInsertUpdateResponse> respVec;
		MallInsertUpdateResponse response;
		for (const auto& _pair : m) {
				const std::string& key = _pair.first;
				const std::string& value = _pair.second;
				// Usage: 改这部分的代码即可 -- 不会抛出异常
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
			}
		respVec.push_back(response);
		toClientInsertUpdate(resultCode, errDesc, respVec, rspBuf);
	}
	static tars::Int32 handler(const vector<tars::Char>& reqBuf, const map<std::string, std::string>& extraInfo, vector<tars::Char>& rspBuf)
	{
		MallInsertUpdateRequest request;
		decode(reqBuf, request);

		if (request._id.isNull()){
			// 插入数据 == 这里可能抛出异常
			config::MallConfigInsertReq req;
			try
			{
				INSERT_ASSIGN_STATEMENT(area);
				INSERT_ASSIGN_STATEMENT(itemId);
				INSERT_ASSIGN_STATEMENT(icon);
				INSERT_ASSIGN_STATEMENT(itemType);
				INSERT_ASSIGN_STATEMENT(payPropsType);
				INSERT_ASSIGN_STATEMENT(label);
				INSERT_ASSIGN_STATEMENT(platformType);
				INSERT_ASSIGN_STATEMENT(qrCode);
				INSERT_ASSIGN_STATEMENT(payValue);
				INSERT_ASSIGN_STATEMENT(payPropsId);
				INSERT_ASSIGN_STATEMENT(itemValue);
				INSERT_ASSIGN_STATEMENT(optUser);
				INSERT_ASSIGN_STATEMENT(exchangeGroup);
				//INSERT_ASSIGN_STATEMENT(createDate); // TODO  插入的时候createDate为null 删除为客户段传入的数据
			}
			catch (const std::exception&)
			{
				string errInfo = ::toString(__FILE__, ":", __LINE__, ":", "插入的部分数据字段为NULL!");
				ROLLLOG_ERROR << errInfo << endl;
				throw logic_error(errInfo);
			}
			config::MallConfigInsertRsp resp;
			int iRet = g_app.getOuterFactoryPtr()->getConfigServantPrx()->MallConfigInsert(req, resp);
			if (iRet != 0)
			{
				string errInfo = ::toString(__FILE__, ":", __LINE__, ":", "MallConfigInsert err!");
				ROLLLOG_ERROR << errInfo << endl;
				throw logic_error(errInfo);
			}

			// 响应给客户端
			MallInsertUpdateResponse::sendToClient(resp.data.at(0), rspBuf);
		}
		else{
			// UPDATE == TODO 这里好像可以和上面的合并
			config::MallConfigUpdateReq req;
			UPDATE_ASSIGN_STATEMENT(id);
			UPDATE_ASSIGN_STATEMENT(area);
			UPDATE_ASSIGN_STATEMENT(itemId);
			UPDATE_ASSIGN_STATEMENT(icon);
			UPDATE_ASSIGN_STATEMENT(itemType);
			UPDATE_ASSIGN_STATEMENT(payPropsType);
			UPDATE_ASSIGN_STATEMENT(label);
			UPDATE_ASSIGN_STATEMENT(platformType);
			UPDATE_ASSIGN_STATEMENT(qrCode);
			UPDATE_ASSIGN_STATEMENT(payValue);
			UPDATE_ASSIGN_STATEMENT(payPropsId);
			UPDATE_ASSIGN_STATEMENT(itemValue);
			UPDATE_ASSIGN_STATEMENT(optUser);
			UPDATE_ASSIGN_STATEMENT(createDate);
			UPDATE_ASSIGN_STATEMENT(exchangeGroup);
			config::MallConfigUpdateRsp resp;
			int iRet = g_app.getOuterFactoryPtr()->getConfigServantPrx()->MallConfigUpdate(req, resp);
			if (iRet != 0)
			{
				string errInfo = ::toString(__FILE__, ":", __LINE__, ":", "MallConfigUpdate err!");
				ROLLLOG_ERROR << errInfo << endl;
				throw logic_error(errInfo);
			}

			// 响应给客户端
			MallInsertUpdateResponse::sendToClient(resp.data.at(0), rspBuf);
		}
		return 0;
	}
private:
	CInteger       	_id;  //主键
	CInteger        _area;  //地区
	CInteger       	_itemId;  //商品id
	CString        	_icon;  //商品图标id
	CInteger        _itemType;  //商品类型 1:金币 2:钻石 3:储蓄罐
	CInteger       	_payPropsType;  //消耗类型 1:现金 2:钻石 3:金币
	CInteger       	_label;  //购买标签 1:金币充值 2:钻石充值 3:钻石购买 4:金币购买
	CInteger       	_platformType;  //平台类型 0:本地测试 1:台湾 2:东南亚 3:香港 4:澳门
	CInteger       	_qrCode;  //商品二维码
	CDouble       	_payValue;  //充值档位
	CInteger        _payPropsId;  
	CInteger       	_itemValue;  //获得道具数量(金币)
	CString        	_optUser;  //操作者
	CString        	_createDate;  //创建时间
	CString			_exchangeGroup;

};
#endif