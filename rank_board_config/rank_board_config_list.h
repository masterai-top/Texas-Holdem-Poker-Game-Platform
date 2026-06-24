#ifndef __RANK_BOARD_CONFIG_LIST_H__
#define __RANK_BOARD_CONFIG_LIST_H__
class RankBoardConfigListRequest
{
public:
    friend class RankBoardConfigListResponse;
    RankBoardConfigListRequest() {}
    RankBoardConfigListRequest(const string &json)
    {
        this->Deserialize(json);
    }
    template <typename Writer>
    void Serialize(Writer &writer) const
    {
        writer.StartObject();
        SERIALIZE_MEMBER(writer, uid);
        SERIALIZE_MEMBER(writer, nickName);
        SERIALIZE_MEMBER(writer, area);
        SERIALIZE_MEMBER(writer, startDate);
        SERIALIZE_MEMBER(writer, endDate);
        SERIALIZE_MEMBER(writer, pageIndex);
        SERIALIZE_MEMBER(writer, pageSize);
        SERIALIZE_MEMBER(writer, type);
        writer.EndObject();
    }

    void toString(std::string &json)
    {
        StringBuffer sb;
        Writer<StringBuffer> writer(sb);
        Serialize(writer);
        json = sb.GetString();
    }

    void Deserialize(const string &json)
    {
        Document d;
        if (d.Parse(json.c_str()).HasParseError())
        {
            throw logic_error("parse json error. raw data : " + json);
        }
        SET_DOC_MEMBER(d, uid);
        SET_DOC_MEMBER(d, nickName);
        SET_DOC_MEMBER(d, area);
        SET_DOC_MEMBER(d, startDate);
        SET_DOC_MEMBER(d, endDate);
        SET_DOC_MEMBER(d, pageIndex);
        SET_DOC_MEMBER(d, pageSize);
        SET_DOC_MEMBER(d, type);

    }

    static tars::Int32 handler(const vector<tars::Char> &reqBuf, const map<std::string, std::string> &extraInfo, vector<tars::Char> &rspBuf)
    {
        return 0;
    }
private:
    CInteger        _uid            ;  //玩家id
    CString         _nickName       ;  //玩家昵称
    CString         _area           ;  //区域：台湾、东南亚、欧洲、大陆等
    CString         _startDate      ;  //开始时间
    CString         _endDate        ;  //结束时间
    CInteger        _pageIndex;         //当前页数
    CInteger        _pageSize;          // 页容数量
    CInteger        _type;

};
class RankBoardConfigListResponse
{
public:
    RankBoardConfigListResponse() {}
    RankBoardConfigListResponse(const string &json)
    {
        this->Deserialize(json);
    }
    template <typename Writer>
    void Serialize(Writer &writer) const
    {
        writer.StartObject();
        SERIALIZE_MEMBER(writer, id);
        SERIALIZE_MEMBER(writer, area);
        SERIALIZE_MEMBER(writer, uid);
        SERIALIZE_MEMBER(writer, nickName);
        SERIALIZE_MEMBER(writer, coin);
        SERIALIZE_MEMBER(writer, optUser);
        SERIALIZE_MEMBER(writer, createDate);

        writer.EndObject();
    }

    void toString(std::string &json)
    {
        StringBuffer sb;
        Writer<StringBuffer> writer(sb);
        Serialize(writer);
        json = sb.GetString();
    }

    void Deserialize(const string &json)
    {
        Document d;
        if (d.Parse(json.c_str()).HasParseError())
        {
            throw logic_error("parse json error. raw data : " + json);
        }
        SET_DOC_MEMBER(d, id);
        SET_DOC_MEMBER(d, area);
        SET_DOC_MEMBER(d, uid);
        SET_DOC_MEMBER(d, nickName);
        SET_DOC_MEMBER(d, coin);
        SET_DOC_MEMBER(d, optUser);
        SET_DOC_MEMBER(d, createDate);
    }

    static tars::Int32 handler(const vector<tars::Char> &reqBuf, const map<std::string, std::string> &extraInfo, vector<tars::Char> &rspBuf)
    {
        RankBoardConfigListRequest request;
        decode(reqBuf, request);

        if (request._pageSize == 0)
        {
            throw logic_error("divide zero!");
        }

        // 业务代码
        XGame::QueryRankInfoReq req;
        req.type = request._type;

        XGame::QueryRankInfoResp resp;
        int iRet = g_app.getOuterFactoryPtr()->getGlobalServantPrx(request._type)->queryRankInfo(req, resp);
        if (iRet != 0)
        {
            std::string errInfo = ::toString(__FILE__, ":", __LINE__, ":queryRankInfo err! uid : ");
            throw logic_error(errInfo);
        }

        int64_t resultCode = RESULT_CODE_SUCCESS;
        std::string errDesc = "";
        int64_t totalItems = resp.list.size();                                  //总条数
        int64_t totalPages = resp.list.size() / request._pageSize + 1;
        std::vector<RankBoardConfigListResponse> respVec;
        for (const auto &item : resp.list)
        {
            RankBoardConfigListResponse response;
            response._uid.assign(item.uid);
            response._coin.assign(item.gold);
            respVec.push_back(response);
        }
        toClient(resultCode, errDesc, respVec, totalItems, totalPages, rspBuf);
        return 0;
    }
private:
    CInteger        _id             ;  //主键
    CString         _area           ;  //区域：台湾、东南亚、欧洲、大陆等
    CInteger        _uid            ;  //玩家id
    CString         _nickName       ;  //玩家昵称
    CInteger        _coin           ;  //金币数量
    CString         _optUser        ;  //操作者
    CString         _createDate     ;  //创建时间

};
#endif