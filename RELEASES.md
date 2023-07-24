# Release Notes

All notable changes to this project will be documented in this file. This project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

<!--
请在每个需要用户关注变化的 MR 中更新 Unreleased 部分。请按以下类型顺序组织变化：
### Breaking changes
### Features
### Bug fixes
### Improvements
### Internal changes

在发布时请为 Unreleased 的变化添加一个合适的版本号标题并附加发布日期，并请务必保留空的 Unreleased section。
不同类型的区别以及版本号的选择请参考： https://xindong.atlassian.net/wiki/spaces/TDS/pages/723709064
-->
## Unreleased


<!--
Content below is genarated by https://codesandbox.io/p/sandbox/condescending-artem-c8wps8
-->
## 3.19.0
Released 2023-07-07

## 3.18.9
Released 2023-06-30

## 3.18.8
Released 2023-06-15


## 3.18.7
Released 2023-05-25

### Improvements
- **DB:** 支持新版 CAID 接口


## 3.18.6
Released 2023-04-27

### Improvements
- **Support:** 打开的客服页面支持多语言适配
- **Moment:** 优化旋转逻辑


## 3.18.5.1
Released 2023-04-18

同步版本信息


## 3.18.5
Released 2023-04-10

### Features
- **DB:** TapDB 添加设备属性


## 3.18.4
Released 2023-03-30

### Features
- **DB:** TapDB 新增接口控制是否使用 Themis
- **DB:** Themis 更新

### Bug fixes
- **DB:** TapDB 版本号改为 TapSDK 版本号


## 3.18.3
Released 2023-03-24

### Bug fixes
- **AntiAddiction:** 修复部分情况下没有回调的问题


## 3.18.2
Released 2023-03-20

### Features
- **AntiAddiction:** 更新防沉迷认证接口
- **Achievement:** UI 适配大屏设备

### Bug fixes
- **AntiAddiction:** 修复提示 UI 错位问题 
- **AntiAddiction:** 修复iOS 部分情况下进入宵禁未弹出提示异常


## 3.18.1
Released 2023-03-06

### Bug fixes
- **Support:** 修复断网重连时点击重试白屏的问题


## 3.18.0
Released 2023-02-20

### Features
- **Support:** 支持自有账户关联登录
- **Support:** 支持 TDS 内建账户登录
- **Support:** 优化客服接口


## 3.17.0
Released 2023-02-17

### Features
- **Billboard:** 添加跑马灯及开屏公告

### Improvements
- **DB:** 优化设备兼容性


## 3.16.5
Released 2022-12-05

### Features
- **DB:** 添加设备时长上报


## 3.16.4
Released 2022-11-17

### Features
- **Login:** 更新网页登录时 UI 显示
- **DB:** 更新上报域名及数据格式


## 3.16.2
Released 2022-10-31

### Features
- **Support:** 新增 SDK 内打开客服页面的能力
- **DB:** 支持 CAID 归因


## 3.16.1
Released 2022-10-17

### Features
- **Billboard:** 新增关闭按钮回调事件
- **Billboard:** 优化网络异常时 UI 显示
- **Friend:** 添加数据埋点支持
- **Friend:** 处理分享链接接口添加延时参数

### Bug fixes
- **Billboard:** 修复 iOS 16 运行异常问题


## 3.16.0
Released 2022-09-30

### Features
- **DB:** 设备型号支持识别运行在 Arm 架构的 Mac 设备


## 3.15.1
Released 2022-09-15

### Bug fixes
- **AntiAddiction:** 防沉迷初始化`showSwitchAccount`设置失效的问题


## 3.15.0
Released 2022-09-13

### Features
- **AntiAddiction:** 防沉迷 `API` 优化
- **AntiAddiction:** 防沉迷`AntiAddictionService`新增动态库，用于避开`Swift`的相关设置


## 3.14.0
Released 2022-08-31

### Features
- **Login:** 支持新的授权 Scope：basic_info、email
- **Login:** 有端登录协议升级


## 3.13.0
Released 2022-08-18

### Features
- **Login:** 支持新的授权 Scope：basic_info、email
- **Login:** 有端登录协议升级


## 3.12.0
Released 2022-08-04

### Features
- **Billboard:** 添加公告模块


## 3.11.1
Released 2022-07-25

### Bug fixes
- **Login:** 修复登录模块对系统 URL 回调的使用方式
- **Common:** 修复授权模块对系统 URL 回调的使用方式

### Improvements
- **Friend:** 更新获取 Tap 互关好友的方式


## 3.11.0
Released 2022-07-12

### Bug fixes
- **AntiAddiction:** userId 包含特殊字符时增加了兼容处理
- **DB:** TapDB 桥接传入参数为null时增加了兼容处理


## 3.10.0
Released 2022-06-30

### Features
- **Achievement:** 支持海外成就服务
- **Bootstrap:** 添加排行榜服务


## 3.9.0
Released 2022-05-25

### Bug fixes
- **Common:** 屏蔽了日志的后台任务，避免出现crash

### Improvements
- **Moment:** 动态SDK本地多语言资源适配


## 3.8.0
Released 2022-05-09

### Features
- **Friend:** 添加好友模式黑名单
- **LeanCloud:** 更新 objc-sdk 至 13.7.1

### Bug fixes
- **AntiAddiction:** 修复iOS本地缓存的配置错误，并且优化了配置缓存逻辑

- **Optimization:** 优化授权请求逻辑


## 3.7.1
Released 2022-04-11

### Features
- **DB:** 增加开机时间的获取和上报

### Bug fixes
- **Moment:** 修复了在动态中键盘打开时页面会自动下滑并出现白色区域的bug，仅在带刘海的手机中出现。
- **Moment:** 支持识别 Unity 中配置的 iOS 特性

### Improvements
- **AntiAddiction:** 优化从主站授权的逻辑


## 3.7.0
Released 2022-03-28

### Bug fixes
- **Friend:** 分享链接支持自定义用户名称及配置额外自定义参数
- **Friend:** 添加解析及处理分享链接接口
- **Friend:** 添加关注模式下黑名单相关接口
- **Friend:** 好友请求数据中添加对方富信息数据
- **Friend:** 支持根据用户 ID 查找用户信息
- **Login:** 添加获取互关好友列表接口


## 3.6.3
Released 2022-03-08

### Features
- **DB:** 当初始化地区为海外时，使用海外上报域名（如果之前已接入数据分析功能，且初始化地区为海外，升级 SDK 至 3.6.3 前需迁移数据，请提交工单联系我们）
- **DB:** 当结束进程时上报游玩时长失败后，再次打开会尝试重新上报时长
- **DB:** 内部版本更新到3.0.9

### Bug fixes
- **Achievement:** 成就面板在稀有度为0时不显示稀有度对应文案
- **Login:** 预埋可供 web 读取语言配置的 js-api
- **Moment:** 提供可供切换到 Controller 模式展示UI的 api
- **AntiAddiction:** 提升防沉迷服务异常情况下的用户体验


## 3.6.1
Released 2022-01-25

源源新生颂光阴，邸安宅暖迎佳期，值此新年之际，TapSDK祝愿幸福与美好一直伴您左右

### Bug fixes
- **RTC:** RTC 接口优化
- **Login:** 登陆 UI 优化
- **Moment:** 内嵌动态支持多语言上报
- **AntiAddiction:** 实名认证接口移除参数TapToken


## 3.6.0
Released 2022-01-07

### Breaking changes
- **LeanCloud:** 更新为同时支持真机和模拟器架构的静态库

### Bug fixes
- **Friend:** 支持获取 Tap 及游戏内单向关注模型好友列表


## 3.5.0
Released 2021-11-30

### Features
- **RTC:** 新增 RTC（实时语音） 模块

### Bug fixes
- **Friend:** 根据好友码查找好友
- **Friend:** 根据好友码添加好友
- **Friend:** 查询第三方好友列表
- **Friend:** 关注 TapTap 好友
- **AntiAddiction:** 防沉迷服务端异常时增加兼容处理
- **AntiAddiction:** 切换账号可隐藏
- **AntiAddiction:** 更新切换账号的回调 code （from 1000 -> 1001）


## 3.3.2
Released 2021-11-11

### Bug fixes
- **AntiAddiction:** Api 增加公用参数


## 3.3.1
Released 2021-10-25

### Features
- **Friend:** 好友新增多语言支持

### Bug fixes
- **Friend:** 从分享页跳转到应用内且发送好友申请时，从提示改为回调。


## 3.3.0
Released 2021-10-15

### Features
- **Support:** 新增客服模块
- **Friend:** 新增好友模块
- **AntiAddiction:** 新增防沉迷模块

### Bug fixes
- **Achievement:** UI 调整
- **Moment:** 统一关闭逻辑，避免出现内存泄漏和音视频无法正常结束的问题
- **Moment:** 优化对 TapDB 版本兼容性
- **Moment:** 优化统计参数


## 3.2.1
Released 2021-09-08

### Bug fixes
- **Bootstrap:** 游客登录默认退出后保留id，非卸载状态下再次登录能获得同一个id
- **LeanCloud:** 支持游客退出登录时保留id


## 3.2.0
Released 2021-09-01

### Features
- **Bootstrap:** 支持云存档
- **LeanCloud:** 支持排行榜

### Bug fixes
- **Moment:** 修复动态内登录后没有回调的问题
- **Moment:** 优化动态多次打开后的内存占用


## 3.1.0
Released 2021-07-28

### Features
- **Bootstrap:** 支持游戏内好友
- **Achievement:** 支持游戏内成就


## 3.0.0
Released 2021-07-16

Tips: 当前版本不支持 v2.x 升级

### Breaking changes
- **Bootstrap:** 账号系统升级为TDSUser
- **Bootstrap:** 登录相关接口修改
- **Bootstrap:** 获取篝火资格接口移动至 TapLogin 模块
- **Bootstrap:** 删除设置语言接口
- **Login:** 开放所有接口，支持获取 TapTap 账号的 openID 和 unionID


## 2.1.7
Released 2021-07-14

### Bug fixes
- **DB:** TapDB 充值接口新增支持传入自定义字段的函数


## 2.1.6
Released 2021-07-01

### Bug fixes
- **Moment:** 修复调用 [TapMoment close] 不生效的 bug


## 2.1.5
Released 2021-06-22

### Features
- **Moment:** 新增场景化入口内的回调 code = TM_RESULT_CODE_MOMENT_SCENE_EVENT


## 2.1.4
Released 2021-06-10

### Features
- **Friend:** 新增设置富信息和查询富信息接口
- **Friend:** TapUserRelationShip 新增 online & time & TapRichPresence 参数

### Bug fixes
- **Bootstrap:** 内部优化
- **Common:** 优化多语言相关


## 2.1.3
Released 2021-05-28

### Features
* 新增繁体中文、日文、韩文、泰语、印度尼西亚语5种新的翻译，并可通过 `TapBootstrap setPreferredLanguage:` 设定
* **Common:** 新增方法 `TapGameUtil isTapTapInstalled` 和 `TapGameUtil isTapGlobalInstalled`，可用来检测设备上是否安装了 TapTap/TapTap 国际版客户端，需要注意，这个能力需要在 info.plist 中 LSApplicationQueriesSchemes 配置里增加 `tapsdk` 和 `tapiosdk`

### Bug fixes
* **DB:** 修复了一个关于版本定义的问题


## 2.1.2
Released 2021-05-14

### Breaking changes
- **Bootstrap:** 删除 `openUserCenter` 接口

### Features
- **Friend:** 新增消息回调的接口
    ``` objectivec
    + (void)registerMessageDelegate:(id<ComponentMessageDelegate>)delegate;
    ```
- **Friend:** 新增获取好友邀请链接的接口
    ``` objectivec
    [TapFriends generateFriendInvitationWithHandler:^(NSString *_Nullable invitationString, NSError *_Nullable error) {
        if (error) {
            NSLog(@"error:%@", error);
        } else {
            NSLog(@"url %@", invitationString);
        }
    }];
    ```
  
- **Friend:** 新增调用系统分享控件分享好友邀请链接的接口
    ``` objectivec
    [TapFriends sendFriendInvitationWithHandler:^(BOOL success, NSError *_Nullable error) {
        if (success) {
            NSLog(@"分享成功");
        } else {
            NSLog(@"分享失败 %@", error);
        }
    }];
    ```
  
- **Friend:** 新增搜索用户的接口（需要登录状态）
    ``` objectivec
    [TapFriends searchUserWithUserId:self.idField.text handler:^(TapUserRelationShip *_Nullable user, NSError *_Nullable error) {
        if (error) {
            NSLog(@"error:%@", error);
        } else {
            NSString *str = @"";
  
            str = [str stringByAppendingString:[self beanToString:user]];
            str = [str stringByAppendingString:@"\n\n"];
  
            NSLog(@"friend list %@ %@ %@ %@", str, user.isBlocked ? @"yes" : @"no", user.isFollowed ? @"yes" : @"no", user.isFollowing ? @"yes" : @"no");
        }
    }];
    ```
- **Friend:** 新增拦截好友邀请链接唤起的接口
    ``` objectivec
    - (BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey, id> *)options {
        return [TapBootstrap handleOpenURL:url] || [TapFriends  handleOpenURL:url];
    }
    ```
- **Friend:** 新增 TapFriendUISDK.framework 和 TapFriendResource.bundle ，需要在收到链接时直接打开预制的好友添加弹窗，请加入这两个文件
- **Common:** 支持性升级


## 2.1.1
Released 2021-05-10

### Breaking changes
- **Bootstrap:** TapConfig 新增 clientSecret 字段，必填
- **Bootstrap:** TapBootstrapLoginType 删除 Apple 和 Guest 类型
- **Bootstrap:** 删除绑定接口
    ``` objectivec
    + (void)bind:(TapBootstrapBindType)type permissions:(NSArray *)permissions;
    ```

### Features
- **Bootstrap:** 新增篝火测试资格校验接口
    ``` objectivec
        [TapBootstrap getTestQualification:^(BOOL isQualified, NSError *_Nullable error) {
        if (error) {
            // 网络异常或未开启篝火测试
        } else {
            if (isQualified) {
                // 有篝火测试资格
            }
        }
    }];
    ```
- **Bootstrap:** 引入TapDB库时，在 `[TapBootstrap initWithConfig:config];` 接口默认初始化 TapDB，可以通过 TapDBConfig 配置 channel、gameVersion、enable 参数
    ``` objectivec
    TapDBConfig * dbConfig = [TapDBConfig new];
    dbConfig.channel = @"channel";// 游戏渠道
    dbConfig.gameVersion = @"x.y.z"; // 游戏版本号
    dbConfig.enable = YES; // 是否开启，默认为YES
    dbConfig.advertiserIDCollectionEnabled = NO; // 是否开启IDFA，默认为NO
    tapConfig.dbConfig = dbConfig;
    ```
- **Moment:** 新增打开特定页面的接口（打开场景化入口等） 
    ``` objectivec
     [TapMoment directlyOpen:mconfig page:TapMomentPageShortcut extras:@{ TapMomentPageShortcutKey: @"sceneid" }];
    ```


## 2.0.0
Released 2021-04-08

TapSDK 开发者中心文档 https://developer.taptap.com/v2-doc/sdk/tap-ios
