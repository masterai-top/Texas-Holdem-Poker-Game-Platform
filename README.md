[简体中文](README.md) | [繁體中文](README.zh-TW.md) | [English](README.en.md)
# 德州扑克游戏平台源码｜俱乐部、联盟、私人局与好友局
一套多人实时德州扑克平台，基于线上 README 的产品范围整理，包含 **Unity/C# 客户端、C++ 服务端、MySQL、Redis**，覆盖大厅、俱乐部、联盟、私人局/好友局、代理、锦标赛、多种玩法和运营后台。

## 产品模块
| 模块 | 功能 |
|---|---|
| 游戏大厅 | 登录、大厅、房间列表、快速游戏和多人牌桌 |
| 德州俱乐部 | 创建/加入、成员、详情、管理和内部牌局 |
| 德州联盟 | 多俱乐部组织、大联盟和运营场景 |
| 私人局/好友局 | 创建私人房、好友约局、邀请、2-6与2-9人桌 |
| 锦标赛 | MTT多桌锦标赛、SNG坐满即玩 |
| 对局工具 | 战绩、牌谱、玩家信息、保险、礼物、机器人 |
| 社交运营 | 语音视频、代理、多语言和后台管理 |

## 游戏玩法
经典德州、AOF、6+短牌、奥马哈、大菠萝、MTT、SNG、德州牛仔。实际运行范围请按源码、数据库和部署资料验收。

## 技术架构
- Unity/C#：iOS、Android 客户端。
- C++：游戏服务、房间管理、客户端/房间消息处理。
- MySQL + Redis：持久化数据与状态数据。
- 典型模块：`gameserver`、`gameroot`、`onclientmessage`、`onroommessage`、`sendclientmessage`、`sendroommessage`。

## 产品截图
### 私人局、好友局与俱乐部
![私人房](https://github.com/user-attachments/assets/3c062e17-fe61-4138-adb2-f3843d51b29d)
![创建牌局](https://github.com/user-attachments/assets/66951932-7973-4405-880d-70ebc5877a4c)
![俱乐部详情](https://github.com/user-attachments/assets/24bf8082-c9d3-47ad-bcb6-4ba370533fca)
![管理俱乐部](https://github.com/user-attachments/assets/e1c947a7-833c-4881-863e-b2aea3c81f23)
![联盟管理](https://github.com/user-attachments/assets/54c9bb2f-11bd-4eee-81c4-fbba6ccfb943)
### 牌桌、玩家与牌谱
![胜利界面](https://github.com/user-attachments/assets/407ae870-510a-4fd0-bce7-2b996a6777a7)
![玩家信息](https://github.com/user-attachments/assets/eff22cd9-9c78-465d-9c84-8eee238d28d7)
![牌谱](https://github.com/user-attachments/assets/8f41f3c8-a273-416b-b144-427c766599a1)
![六人桌](https://github.com/user-attachments/assets/34ea9b1a-09bd-4424-b50b-a04000c14254)
![玩家头像](https://github.com/user-attachments/assets/8673b6d6-7579-4d66-b60e-a29556ade3b6)
![九人桌](https://github.com/user-attachments/assets/b4fa375c-2de7-4d26-90e1-6e045900657d)

## 专题与联系
[完整产品页](https://masterai-top.github.io/Texas-Holdem-Poker-Game-Platform/) · [俱乐部联盟](https://masterai-top.github.io/Texas-Holdem-Poker-Game-Platform/zh-cn/poker-club-league.html) · [私人局好友局](https://masterai-top.github.io/Texas-Holdem-Poker-Game-Platform/zh-cn/private-friend-game.html)

Telegram：[@xuzongbin001](https://t.me/xuzongbin001) · Email：masterai918@gmail.com
