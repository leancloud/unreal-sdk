#pragma once
#include "LCObject.h"

class FLCUser;
DECLARE_DELEGATE_TwoParams(FLeanCloudUserDelegate, TSharedPtr<FLCUser> UserPtr, const FLCError& Error);

class LEANCLOUD_API FLCUser : public FLCObject {
public:
	virtual ~FLCUser() override;
	void SetUsername(const FString& InUserName);
	void SetPassword(const FString& InPassword);
	void SetEmail(const FString& InEmail);
	void SetMobilePhoneNumber(const FString& InMobilePhoneNumber);
	FString GetUsername() const;
	FString GetSessionToken() const;
	FString GetEmail() const;
	FString GetMobilePhoneNumber() const;

	// 当前用户
	static TSharedPtr<FLCUser> GetCurrentUser();

	// 登录
	void SignUp(FLeanCloudBoolResultDelegate CallBack = nullptr);
	static void RequestLoginSmsCode(const FString& PhoneNumber, FLeanCloudBoolResultDelegate CallBack);
	static void SignUpOrLoginByMobilePhone(const FString& PhoneNumber, const FString& SmsCode, FLeanCloudUserDelegate CallBack);
	static void Login(const FString& UserName, const FString& Password, FLeanCloudUserDelegate CallBack);
	static void LoginByEmail(const FString& Email, const FString& Password, FLeanCloudUserDelegate CallBack);
	static void LoginByMobilePhone(const FString& PhoneNumber, const FString& Password, FLeanCloudUserDelegate CallBack);
	static void LoginWithSessionToken(const FString& SessionToken, FLeanCloudUserDelegate CallBack);
	static void LoginWithAuthData(TSharedPtr<FJsonObject> AuthData, const FString& Platform, FLeanCloudUserDelegate CallBack);
	static void LoginAnonymously(FLeanCloudUserDelegate CallBack);
	
	// 退出登录
	static void LogOut();

	// 邮箱及手机验证
	static void RequestEmailVerify(const FString& Email, FLeanCloudBoolResultDelegate CallBack);
	static void RequestMobilePhoneVerify(const FString& PhoneNumber, FLeanCloudBoolResultDelegate CallBack);
	static void VerifyMobilePhone(const FString& PhoneNumber, const FString& SmsCode, FLeanCloudBoolResultDelegate CallBack);

	// 绑定、修改手机号
	static void RequestSMSCodeForUpdatingPhoneNumber(const FString& PhoneNumber, FLeanCloudBoolResultDelegate CallBack);
	static void VerifySMSCodeForUpdatingPhoneNumber(const FString& PhoneNumber, const FString& SmsCode, FLeanCloudBoolResultDelegate CallBack);

	// 验证SessionToken是否有效
	static void VerifySessionToken(const FString& SessionToken, FLeanCloudBoolResultDelegate CallBack);
	bool IsAuthenticated();

	// 重置密码
	static void RequestPasswordResetByEmail(const FString& Email, FLeanCloudBoolResultDelegate CallBack);
	static void RequestPasswordResetByMobilePhone(const FString& PhoneNumber, FLeanCloudBoolResultDelegate CallBack);
	static void ResetPasswordBySmsCode(const FString& PhoneNumber, const FString& SmsCode, FLeanCloudBoolResultDelegate CallBack);

	// 用户的查询
	FLCQuery GetQuery();

	// 绑定/解绑第三方账户
	void AssociateWithAuthData(TSharedPtr<FJsonObject> AuthData, const FString& Platform, FLeanCloudUserDelegate CallBack);
	void DisassociateWithPlatform(const FString& Platform, FLeanCloudUserDelegate CallBack);

	// 是否是匿名用户
	bool IsAnonymous();
};
