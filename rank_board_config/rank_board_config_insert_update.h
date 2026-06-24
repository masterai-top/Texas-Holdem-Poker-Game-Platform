#ifndef __RANK_BOARD_CONFIG_INSERT_UPDATE_H__
#define __RANK_BOARD_CONFIG_INSERT_UPDATE_H__
class RankBoardConfigInsertUpdateRequest
{
public:
    friend class RankBoardConfigInsertUpdateResponse;
    RankBoardConfigInsertUpdateRequest() {}
    RankBoardConfigInsertUpdateRequest(const string &json)
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
        SERIALIZE_MEMBER(writer, coin);
        SERIALIZE_MEMBER(writer, level);
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
        try
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
            SET_DOC_MEMBER(d, coin);
            SET_DOC_MEMBER(d, level);
            SET_DOC_MEMBER(d, type);
        }
        catch (const std::exception &e)
        {
            std::string errInfo = ::toString(__FILE__, ":", __LINE__, ":RankBoardConfigInsertUpdateRequest decode error!");
            throw logic_error(errInfo);
        }
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
    CInteger        _coin           ;  //金币数量
    CInteger        _level          ;  //玩家等级
    CInteger        _type           ;  //操作类型
};

class RankBoardConfigInsertUpdateResponse
{
public:
    RankBoardConfigInsertUpdateResponse() {}
    RankBoardConfigInsertUpdateResponse(const string &json)
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
        SERIALIZE_MEMBER(writer, level);
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

        SET_DOC_MEMBER(d, id);
        SET_DOC_MEMBER(d, area);
        SET_DOC_MEMBER(d, uid);
        SET_DOC_MEMBER(d, nickName);
        SET_DOC_MEMBER(d, coin);
        SET_DOC_MEMBER(d, optUser);
        SET_DOC_MEMBER(d, createDate);
        SET_DOC_MEMBER(d, level);
        SET_DOC_MEMBER(d, type);
    }

    static tars::Int32 handler(const vector<tars::Char> &reqBuf, const map<std::string, std::string> &extraInfo, vector<tars::Char> &rspBuf)
    {
        RankBoardConfigInsertUpdateRequest request;
        decode(reqBuf, request);

        XGame::UpdateRankBoardReq updateRankBoardReq;
        updateRankBoardReq.type = request._type;
        updateRankBoardReq.uid = request._uid;
        updateRankBoardReq.gold = request._coin;
        updateRankBoardReq.level = request._level;
        XGame::UpdateRankBoardResp  updateRankBoardResp;
        int iRet = g_app.getOuterFactoryPtr()->getGlobalServantPrx(request._uid)->updateRankBoard(updateRankBoardReq, updateRankBoardResp);
        if (iRet != 0)
        {
            std::string errInfo = ::toString(__FILE__, ":", __LINE__, ":update rankboard err! uid : ", updateRankBoardReq.uid);
            throw logic_error(errInfo);
        }

        RankBoardConfigInsertUpdateResponse response;
        response._id.assign(request._uid);
        response._area.assign(request._area);
        response._uid.assign(request._uid);
        response._nickName.assign(request._nickName);
        response._coin.assign(request._coin);
        response._optUser.assign("");
        response._createDate.assign(getNow());
        response._level.assign(request._level);
        response._type.assign(request._type);

        std::string json;
        response.toString(json);
        std::string resultData = "[" + json + "]";

        int64_t totalItems = 1;                                 //总条数
        int64_t totalPages = 1;                                 // 总页数
        GMResponse rsp(RESULT_CODE_SUCCESS, "", resultData, totalItems, totalPages);
        std::string resultJson;
        rsp.toString(resultJson);
        rspBuf.assign(resultJson.begin(), resultJson.end());
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
    CInteger        _level          ;  //等级
    CInteger        _type           ;  //操作类型

};
#endif