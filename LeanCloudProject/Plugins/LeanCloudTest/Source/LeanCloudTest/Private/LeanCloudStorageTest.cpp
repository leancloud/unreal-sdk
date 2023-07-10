#include "LCObject.h"
#include "LCSMS.h"
#include "LCUser.h"
#include "LCValue.h"
#include "LCLeaderboard.h"

#if WITH_DEV_AUTOMATION_TESTS

static FString TestClassName = "UETest";

// DEFINE_LATENT_AUTOMATION_COMMAND(FWaitRequest);
DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FWaitRequest, bool&, HasCallBack);

bool FWaitRequest::Update() {
	return HasCallBack;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(LeanCloudStorageClearObjects, "LeanCloud.Storage.0 Clear Objects",
                                 EAutomationTestFlags::ApplicationContextMask |
                                 EAutomationTestFlags::ProductFilter)

bool LeanCloudStorageClearObjects::RunTest(const FString& Parameters) {
	static bool HasCallBack = false;
	HasCallBack = false;
	FLCQuery Query = FLCQuery("UETest");
	Query.Find(FLeanCloudQueryObjectsDelegate::CreateLambda([=](TArray<TSharedPtr<FLCObject>> ObjectPtrs,
	                                                            const FLCError& _Error) {
		FLCObject::Delete(ObjectPtrs, FLeanCloudBoolResultDelegate::CreateLambda(
			                  [](bool bIsSuccess, const FLCError& Error) {
				                  HasCallBack = true;
			                  }));
	}));

	AddCommand(new FWaitRequest(HasCallBack));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(LeanCloudStorageSaveTest, "LeanCloud.Storage.01 Object Save",
                                 EAutomationTestFlags::ApplicationContextMask |
                                 EAutomationTestFlags::ProductFilter)

bool LeanCloudStorageSaveTest::RunTest(const FString& Parameters) {
	TSharedPtr<FLCObject> ObjectPtrO = MakeShared<FLCObject>(TestClassName);
	ObjectPtrO->Set("name", TEXT("小红"));
	TSharedPtr<FLCObject> ObjectPtr = MakeShared<FLCObject>(TestClassName);
	ObjectPtr->Set("name", TEXT("小明"));
	ObjectPtr->Set("age", 18);
	ObjectPtr->Set("like", ObjectPtrO);
	ObjectPtr->Set("flag", {"66", 17});
	ObjectPtr->Set("birth", FDateTime());
	ObjectPtr->Set("location", FLCGeoPoint(23.3, 45.6));
	TLCMap TestMap;
	TestMap.Add("name", TEXT("小明"));
	TestMap.Add("age", 18);
	ObjectPtr->Set("map", TestMap);

	static bool HasCallBack = false;
	HasCallBack = false;
	ObjectPtr->Save(FLeanCloudBoolResultDelegate::CreateLambda(
		[this, ObjectPtr](bool bIsSuccess, const FLCError& Error) {
			TestTrue("Request Error: " + Error.Reason, bIsSuccess);
			TestTrue("Object should has Object Id", !ObjectPtr->GetObjectId().IsEmpty());
			HasCallBack = true;
		}));
	AddCommand(new FWaitRequest(HasCallBack));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(LeanCloudStorageCircularReferenceTest, "LeanCloud.Storage.02 Circular Reference",
                                 EAutomationTestFlags::ApplicationContextMask |
                                 EAutomationTestFlags::ProductFilter)

bool LeanCloudStorageCircularReferenceTest::RunTest(const FString& Parameters) {
	TSharedPtr<FLCObject> ObjectPtrO = MakeShared<FLCObject>(TestClassName);
	ObjectPtrO->Set("name", TEXT("小红"));
	TSharedPtr<FLCObject> ObjectPtr = MakeShared<FLCObject>(TestClassName);
	ObjectPtr->Set("name", TEXT("小明"));
	ObjectPtr->Set("like", ObjectPtrO);
	ObjectPtrO->Set("like", ObjectPtr);

	static bool HasCallBack = false;
	HasCallBack = false;
	ObjectPtr->Save(FLeanCloudBoolResultDelegate::CreateLambda([this](bool bIsSuccess, const FLCError& Error) {
		TestTrue("Request should error", !bIsSuccess);
		TestTrue("Error code should be CircularReference", int(ELCErrorCode::CircularReference) == Error.Code);
		HasCallBack = true;
	}));
	AddCommand(new FWaitRequest(HasCallBack));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(LeanCloudStorageRemoveTest, "LeanCloud.Storage.03 Remove",
                                 EAutomationTestFlags::ApplicationContextMask |
                                 EAutomationTestFlags::ProductFilter)

bool LeanCloudStorageRemoveTest::RunTest(const FString& Parameters) {
	TSharedPtr<FLCObject> ObjectPtr = MakeShared<FLCObject>(FString("UETest888"), "172387564");
	ObjectPtr->Set("name", TEXT("小红"));
	static bool HasCallBack = false;
	ObjectPtr->Delete(FLeanCloudBoolResultDelegate::CreateLambda([this](bool bIsSuccess, const FLCError& Error) {
		TestTrue("Delete should be error", !bIsSuccess);
		TSharedPtr<FLCObject> ObjectPtrO = MakeShared<FLCObject>(TestClassName);
		ObjectPtrO->Set("name", TEXT("小红"));
		ObjectPtrO->Save(FLeanCloudBoolResultDelegate::CreateLambda(
			[this, ObjectPtrO](bool bIsSuccess, const FLCError& Error) {
				TestTrue("Save Before Delete", bIsSuccess);
				ObjectPtrO->Delete(FLeanCloudBoolResultDelegate::CreateLambda(
					[this](bool bIsSuccess, const FLCError& Error) {
						TestTrue("Delete", bIsSuccess);
						HasCallBack = true;
					}));
			}));
	}));

	AddCommand(new FWaitRequest(HasCallBack));
	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(LeanCloudStorageFetchTest, "LeanCloud.Storage.04 Fetch",
                                 EAutomationTestFlags::ApplicationContextMask |
                                 EAutomationTestFlags::ProductFilter)

bool LeanCloudStorageFetchTest::RunTest(const FString& Parameters) {
	TSharedPtr<FLCObject> ObjectPtr = MakeShared<FLCObject>(TestClassName);
	ObjectPtr->Set("name", TEXT("小红"));
	ObjectPtr->Set("age", 18);
	static bool HasCallBack = false;
	ObjectPtr->Save(FLeanCloudBoolResultDelegate::CreateLambda(
		[this, ObjectPtr](bool bIsSuccess, const FLCError& Error) {
			TestTrue("Save Before Fetch", bIsSuccess);
			TSharedPtr<FLCObject> NewObjectPtr = MakeShared<FLCObject>(TestClassName, ObjectPtr->GetObjectId());
			TArray<FString> Keys = {"name"};
			NewObjectPtr->Fetch(Keys, FLeanCloudBoolResultDelegate::CreateLambda(
				                    [this, NewObjectPtr](bool bIsSuccess, const FLCError& Error) {
					                    TestTrue("Fetch", bIsSuccess);
					                    NewObjectPtr->Get("name");
					                    TestEqual("Fetch Name", NewObjectPtr->Get("name").AsString(), TEXT("小红"));
					                    TestTrue("Fetch age is null", NewObjectPtr->Get("age").IsNoneType());
					                    HasCallBack = true;
				                    }));
		}));

	AddCommand(new FWaitRequest(HasCallBack));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(LeanCloudStorageSaveOptionTest, "LeanCloud.Storage.05 Save Option",
                                 EAutomationTestFlags::ApplicationContextMask |
                                 EAutomationTestFlags::ProductFilter)

bool LeanCloudStorageSaveOptionTest::RunTest(const FString& Parameters) {
	TSharedPtr<FLCObject> ObjectPtr = MakeShared<FLCObject>(TestClassName);
	ObjectPtr->Set("name", TEXT("小红"));
	ObjectPtr->Set("age", 18);
	static bool HasCallBack = false;
	ObjectPtr->Save(FLeanCloudBoolResultDelegate::CreateLambda(
		[this, ObjectPtr](bool bIsSuccess, const FLCError& Error) {
			TestTrue("Save before test save option", bIsSuccess);
			TSharedPtr<FLCObject> NewObjectPtr = MakeShared<FLCObject>(TestClassName, ObjectPtr->GetObjectId());
			FLCQuery Query(NewObjectPtr->GetClassName(), NewObjectPtr->GetApplicationPtr());
			Query.WhereEqualTo("age", 19);
			NewObjectPtr->Set("score", 100);
			FLCSaveOption Option(Query, true);
			static int RequestCount = 0;
			NewObjectPtr->Save(Option, FLeanCloudBoolResultDelegate::CreateLambda(
				                   [this, ObjectPtr](bool bIsSuccess, const FLCError& Error) {
					                   TestTrue("Save should be false", !bIsSuccess);
					                   RequestCount++;
					                   HasCallBack = RequestCount == 2;
				                   }));
			Option.GetMatchQuery()->WhereEqualTo("age", 18);
			NewObjectPtr->Save(Option, FLeanCloudBoolResultDelegate::CreateLambda(
				                   [this, ObjectPtr](bool bIsSuccess, const FLCError& Error) {
					                   TestTrue("Save should be success", bIsSuccess);
					                   RequestCount++;
					                   HasCallBack = RequestCount == 2;
				                   }));
		}));

	AddCommand(new FWaitRequest(HasCallBack));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(LeanCloudStorageQueryTest, "LeanCloud.Storage.06 Query-Find",
                                 EAutomationTestFlags::ApplicationContextMask |
                                 EAutomationTestFlags::ProductFilter)

bool LeanCloudStorageQueryTest::RunTest(const FString& Parameters) {
	TSharedPtr<FLCObject> ObjectPtr = MakeShared<FLCObject>(FString("UETest"));
	ObjectPtr->Set("name", TEXT("小红"));
	ObjectPtr->Set("age", 38);
	FDateTime Birth = FDateTime::Now();
	ObjectPtr->Set("brith", Birth);

	static bool HasCallBack = false;
	ObjectPtr->Save(FLeanCloudBoolResultDelegate::CreateLambda(
		[this, Birth](bool bIsSuccess, const FLCError& Error) {
			TestTrue("Save success before query", bIsSuccess);
			FLCQuery Query = FLCQuery(TestClassName);
			Query.WhereEqualTo("brith", Birth);
			Query.Find(FLeanCloudQueryObjectsDelegate::CreateLambda([=](TArray<TSharedPtr<FLCObject>> ObjectPtrs,
			                                                            const FLCError& _Error) {
				TestTrue("ObjectPtrs should has object", ObjectPtrs.Num() > 0);
				HasCallBack = true;
			}));
		}));

	AddCommand(new FWaitRequest(HasCallBack));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(LeanCloudStorageUserSignUpTest,
                                 "LeanCloud.Storage.07 User SignUp Test And Update Passwork Test",
                                 EAutomationTestFlags::ApplicationContextMask |
                                 EAutomationTestFlags::ProductFilter)

bool LeanCloudStorageUserSignUpTest::RunTest(const FString& Parameters) {
	TSharedPtr<FLCUser> UserPtr = MakeShared<FLCUser>();
	FString NameAndPassword = FGuid::NewGuid().ToString();
	FString Email = NameAndPassword + "@qq.com";
	UserPtr->SetUsername(NameAndPassword);
	UserPtr->SetEmail(Email);
	UserPtr->SetPassword(NameAndPassword);
	UserPtr->Set("age", 38);

	static bool HasCallBack = false;
	UserPtr->SignUp(FLeanCloudBoolResultDelegate::CreateLambda(
		[=](bool bIsSuccess, const FLCError& Error) {
			TestTrue("SignUp should be success", bIsSuccess);
			TestTrue("User's session token has content", !UserPtr->GetSessionToken().IsEmpty());
			static int RequestCount = 0;
			FLCUser::Login(NameAndPassword, NameAndPassword, FLeanCloudUserDelegate::CreateLambda(
				               [=](TSharedPtr<FLCUser> ResultUserPtr, const FLCError& ResultError) {
					               TestTrue("Login should be success", ResultUserPtr.IsValid());
					               TestTrue("Username should be same", ResultUserPtr->GetEmail() == Email);
					               TestTrue("age should be same",
					                        ResultUserPtr->Get("age").AsInteger() == UserPtr->Get("age").AsInteger());
					               ResultUserPtr->UpdatePassword(NameAndPassword, "123456",
					                                             FLeanCloudBoolResultDelegate::CreateLambda(
						                                             [=](bool bIsSuccess, const FLCError& Error1) {
							                                             TestTrue("Update Password be success",
								                                             bIsSuccess);
						                                             }));
				               }));
			FLCUser::LoginByEmail(Email, NameAndPassword, FLeanCloudUserDelegate::CreateLambda(
				                      [=](TSharedPtr<FLCUser> ResultUserPtr, const FLCError& ResultError) {
					                      TestTrue("Login should be success", ResultUserPtr.IsValid());
					                      TestTrue("Username should be same",
					                               ResultUserPtr->GetUsername() == NameAndPassword);
					                      TestTrue("age should be same",
					                               ResultUserPtr->Get("age").AsInteger() == UserPtr->Get("age").
					                               AsInteger());
				                      }));
		}));

	AddCommand(new FWaitRequest(HasCallBack));
	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(LeanCloudStorageUserSignUpOrLoginByMobilePhoneTest,
                                 "LeanCloud.Storage.08 User Sign Up Or Login By MobilePhone Test",
                                 EAutomationTestFlags::ApplicationContextMask |
                                 EAutomationTestFlags::ProductFilter)

bool LeanCloudStorageUserSignUpOrLoginByMobilePhoneTest::RunTest(const FString& Parameters) {
	static bool HasCallBack = false;
	auto Ptr = FLCUser::GetCurrentUser();

	FLCUser::SignUpOrLoginByMobilePhone("+8618622223333", "143922", FLeanCloudUserDelegate::CreateLambda(
		                                    [=](TSharedPtr<FLCUser> ResultUserPtr, const FLCError& ResultError) {
			                                    TestTrue("Login should be success", ResultUserPtr.IsValid());
			                                    static int RequestCount = 0;
			                                    RequestCount = 0;
			                                    TLCMap AuthData;
			                                    AuthData.Add("access_token", FGuid::NewGuid().ToString());
			                                    AuthData.Add("openid", FGuid::NewGuid().ToString());
			                                    ResultUserPtr->AssociateWithAuthData(
				                                    AuthData, "weixin", FLeanCloudBoolResultDelegate::CreateLambda(
					                                    [=](bool bIsSuccess, const FLCError& Error) {
						                                    TestTrue("AssociateWithAuthData should be success",
						                                             bIsSuccess);
						                                    ResultUserPtr->DisassociateWithPlatform(
							                                    "weixin", FLeanCloudBoolResultDelegate::CreateLambda(
								                                    [=](bool bIsSuccess1, const FLCError& Error1) {
									                                    TestTrue(
										                                    "DisassociateWithPlatform should be success",
										                                    bIsSuccess1);
									                                    RequestCount--;
									                                    HasCallBack = RequestCount == 0;
								                                    }));
					                                    })
			                                    );
			                                    RequestCount++;

			                                    ResultUserPtr->RetrieveShortToken(
				                                    FStringSignature::CreateLambda([=](const FString& Signature) {
				                                    	TestTrue("RetrieveShortToken has Value",!Signature.IsEmpty());
					                                    RequestCount--;
					                                    HasCallBack = RequestCount == 0;
				                                    }), FLCError::FDelegate::CreateLambda([=](const FLCError& Error) {
				                                    	TestTrue("RetrieveShortToken request fail",true);
					                                    RequestCount--;
					                                    HasCallBack = RequestCount == 0;
				                                    }));
			                                    RequestCount++;
		                                    }));
	AddCommand(new FWaitRequest(HasCallBack));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(LeanCloudStorageUserLoginAnonymouslyAndLoginWithSessionTokenTest,
                                 "LeanCloud.Storage.09 User Login Anonymously Test And Login With Session Token Test",
                                 EAutomationTestFlags::ApplicationContextMask |
                                 EAutomationTestFlags::ProductFilter)

bool LeanCloudStorageUserLoginAnonymouslyAndLoginWithSessionTokenTest::RunTest(const FString& Parameters) {
	static bool HasCallBack = false;
	FLCUser::LoginAnonymously(FLeanCloudUserDelegate::CreateLambda(
		[=](TSharedPtr<FLCUser> ResultUserPtr, const FLCError& ResultError) {
			TestTrue("Login should be success", ResultUserPtr.IsValid());
			TestTrue("SessionToken should not be empty",
			         !ResultUserPtr->GetSessionToken().IsEmpty());
			FLCUser::LoginWithSessionToken(
				ResultUserPtr->GetSessionToken(),
				FLeanCloudUserDelegate::CreateLambda(
					[=](TSharedPtr<FLCUser> ResultUserPtr1,
					    const FLCError& ResultError1) {
						TestTrue("Login should be success",
						         ResultUserPtr1.IsValid());
						TestTrue("User is anonymous",
						         FLCUser::GetCurrentUser()->IsAnonymous());
						TestTrue("Current User is valid", FLCUser::GetCurrentUser().IsValid());
						FLCUser::LogOut();
						TestTrue("Current User is invalid",
						         !FLCUser::GetCurrentUser().IsValid());
						HasCallBack = true;
						HasCallBack = true;
					}));
		}));

	AddCommand(new FWaitRequest(HasCallBack));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(LeanCloudStorageUserOtherTest, "LeanCloud.Storage.10 User Other API Test",
                                 EAutomationTestFlags::ApplicationContextMask |
                                 EAutomationTestFlags::ProductFilter)

bool LeanCloudStorageUserOtherTest::RunTest(const FString& Parameters) {
	static bool HasCallBack = false;
	FLCSMSOption Option;
	static int RequestCount = 0;
	RequestCount = 0;
	HasCallBack = false;
	FLeanCloudBoolResultDelegate FailDelegate = FLeanCloudBoolResultDelegate::CreateLambda(
		[=](bool bIsSuccess, const FLCError& Error) {
			TestTrue("RequestLoginSmsCode should be Fail", !bIsSuccess);
			RequestCount--;
			HasCallBack = RequestCount == 0;
		});
	FLCSMS::RequestSMSCode("+8618622223333", Option, FailDelegate);
	RequestCount++;

	FLCUser::RequestEmailVerify("haha@163.com", FailDelegate);
	RequestCount++;

	FLCUser::RequestSMSCodeForUpdatingPhoneNumber("+8618622223333", FailDelegate, Option);
	RequestCount++;

	FLCUser::RequestPasswordResetByEmail("haha@163.com", FailDelegate);
	RequestCount++;

	FLCUser::RequestPasswordResetBySmsCode("+8618622223333", FailDelegate);
	RequestCount++;

	FLCUser::ResetPasswordBySmsCode("+143922", "123456", FailDelegate);
	RequestCount++;

	FLeanCloudBoolResultDelegate SuccessDelegate = FLeanCloudBoolResultDelegate::CreateLambda(
		[=](bool bIsSuccess, const FLCError& Error) {
			TestTrue("RequestLoginSmsCode should be Success", bIsSuccess);
			RequestCount--;
			HasCallBack = RequestCount == 0;
		});

	FLCUser::VerifySMSCodeForUpdatingPhoneNumber("+8618622223333", "143922", SuccessDelegate);
	RequestCount++;

	FLCUser::RequestMobilePhoneVerify("+8618622223333", SuccessDelegate);
	RequestCount++;

	FLCUser::VerifyMobilePhone("+8618622223333", "143922", SuccessDelegate);
	RequestCount++;

	AddCommand(new FWaitRequest(HasCallBack));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(LeanCloudLeaderboardTest, "LeanCloud.Storage.11 Leaderboard API Test",
                                 EAutomationTestFlags::ApplicationContextMask |
                                 EAutomationTestFlags::ProductFilter)

bool LeanCloudLeaderboardTest::RunTest(const FString& Parameters) {
	static bool HasCallBack = false;
	HasCallBack = false;
	TMap<FString, double> Values;
	FString WorldName = "World";
	double WorldValue = FMath::RandRange(0, 200);
	FString ChinaName = "China";
	double ChinaValue = FMath::RandRange(0, 200);

	Values.Add(WorldName, WorldValue);
	Values.Add(ChinaName, ChinaValue);
	FLCUser::LoginAnonymously(FLeanCloudUserDelegate::CreateLambda(
		[=](TSharedPtr<FLCUser> ResultUserPtr, const FLCError& ResultError) {
			if (!ResultUserPtr.IsValid()) {
				TestTrue("Login should be success", ResultUserPtr.IsValid());
				HasCallBack = true;
				return;
			}
			FLCLeaderboard::UpdateCurrentUserStatistics(Values, FLCLeaderboard::FStatisticsDelegate::CreateLambda(
				                                            [=](const TArray<FLCLeaderboardStatistic>&
				                                            TempStatistics) {
					                                            static int RequestCount = 0;

					                                            FLCLeaderboard Leaderboard(WorldName);
					                                            Leaderboard.WithCount = true;

					                                            Leaderboard.GetResults(
						                                            FLCLeaderboard::FRankingsDelegate::CreateLambda(
							                                            [=](const TArray<FLCLeaderboardRanking>&
							                                                Rankings, int64 Count) {
								                                            TestTrue(
									                                            "Ranking's count should larger than 0",
									                                            Count > 0);
								                                            TestTrue(
									                                            "Ranking's Num should larger than 0",
									                                            Rankings.Num() > 0);
								                                            RequestCount--;
								                                            HasCallBack = RequestCount == 0;
							                                            }), FLCError::FDelegate::CreateLambda(
							                                            [=](const FLCError& Error) {
								                                            TestTrue("Request Error", false);
								                                            RequestCount--;
								                                            HasCallBack = RequestCount == 0;
							                                            }));
					                                            RequestCount++;

					                                            Leaderboard.GetAroundResults(
						                                            FLCUser::GetCurrentUser()->GetObjectId(),
						                                            FLCLeaderboard::FRankingsDelegate::CreateLambda(
							                                            [=](const TArray<FLCLeaderboardRanking>&
							                                                Rankings, int64 Count) {
								                                            TestTrue(
									                                            "Ranking's count should larger than 0",
									                                            Count > 0);
								                                            TestTrue(
									                                            "Ranking's Num should larger than 0",
									                                            Rankings.Num() > 0);
								                                            RequestCount--;
								                                            HasCallBack = RequestCount == 0;
							                                            }), FLCError::FDelegate::CreateLambda(
							                                            [=](const FLCError& Error) {
								                                            TestTrue("Request Error", false);
								                                            RequestCount--;
								                                            HasCallBack = RequestCount == 0;
							                                            }));
					                                            RequestCount++;

					                                            TArray<FString> StatisticNames;
					                                            StatisticNames.Add(WorldName);
					                                            StatisticNames.Add(ChinaName);
					                                            FLCLeaderboard::GetStatistics(
						                                            FLCUser::GetCurrentUser()->GetObjectId(),
						                                            FLCLeaderboard::FStatisticsDelegate::CreateLambda(
							                                            [=](const TArray<FLCLeaderboardStatistic>&
							                                            Statistics) {
								                                            for (auto Statistic : Statistics) {
									                                            if (Statistic.Name == WorldName) {
										                                            TestTrue(
											                                            "World should be " +
											                                            LexToString(WorldValue),
											                                            Statistic.Value ==
											                                            WorldValue);
									                                            }
									                                            if (Statistic.Name == ChinaName) {
										                                            TestTrue(
											                                            "China should be " +
											                                            LexToString(ChinaValue),
											                                            Statistic.Value ==
											                                            ChinaValue);
									                                            }
								                                            }
								                                            RequestCount--;
								                                            HasCallBack = RequestCount == 0;
							                                            }), FLCError::FDelegate::CreateLambda(
							                                            [=](const FLCError& Error) {
								                                            TestTrue("Request Error", false);
								                                            RequestCount--;
								                                            HasCallBack = RequestCount == 0;
							                                            }), StatisticNames);
					                                            RequestCount++;
				                                            }), FLCError::FDelegate::CreateLambda(
				                                            [=](const FLCError& Error) {
					                                            TestTrue("Request Error", false);
					                                            HasCallBack = true;
				                                            }));
		}));

	AddCommand(new FWaitRequest(HasCallBack));
	return true;
}


#endif
