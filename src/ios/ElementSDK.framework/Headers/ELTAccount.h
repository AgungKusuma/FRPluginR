//
//  ELTAccount.h
//  ElementSDK
//
//  Created by Laurent Grandhomme on 9/16/16.
//  Copyright © 2016 Element. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 Result of an account model download or update call.
 */
typedef NS_ENUM(NSInteger, ELTModelModality) {
    /// FACE
    ELTModelModalityFace,
    /// PALM
    ELTModelModalityPalm
};

/*!
 Result of an account model download or update call.
 */
typedef NS_ENUM(NSInteger, ELTModelDownloadResult) {
    /// No model
    ELTModelDownloadResultNoModel,
    /// User Init has been done but more pictures are needed in order to finalize the Account
    ELTModelDownloadResultMorePicturesNeeded,
    /// The user model has been download and is ready to use
    ELTModelDownloadResultModelDownloaded,
    /// Model stored in the cloud isn't valid
    ELTModelDownloadResultIncompatibleModelVersion
};

/*!
 State of the Element User Account
 */
typedef NS_ENUM(NSInteger, ELTAccountState) {
    /// Unknown
    ELTAccountStateUnknown,
    /// User needs to perform User Init to create their Account
    ELTAccountStateUserInitNeeded,
    /// More pictures are needed in order to finalize the Account
    ELTAccountStateMorePicturesNeeded,
    /// User Init has been done - waiting for the model to be created
    ELTAccountStateWaitingForModel,
    /// User Init has been done - it's on S3 but not on disk (should be downloaded)
    ELTAccountStateAvailableButNotDownloaded,
    /// The Account is ready to use for the associated product
    ELTAccountStateReady
};

/*!
 Called when the account was successfully sent to the backend / cloud
 */
typedef void(^ELTAccountUploadSuccess)(void);

/*!
 Called when the account couldn't be sent to the backend / cloud
 */
typedef void(^ELTAccountUploadFailure)(void);

/*!
 Object representing an Element Account
 */
@interface ELTAccount : NSObject <NSCoding>

- (nonnull instancetype) init __attribute__((unavailable("init not available")));

/*!
 Create a new account object (not saved to disk)
 */
+ (ELTAccount * _Nonnull)createNewAccountWithFirstName:(NSString * _Nonnull)fn lastName:(NSString * _Nonnull)ln email:(NSString * _Nullable)email clearTextPin:(NSString * _Nullable)pin extraInfo:(NSString * _Nullable)extraInfo userId:(NSString * _Nonnull)userId;

/*!
 Create a new account object (not saved to disk), the userId will be generated
 */
+ (ELTAccount * _Nonnull)createNewAccountWithFirstName:(NSString * _Nonnull)fn lastName:(NSString * _Nonnull)ln;

/*!
 Create a new account object (not saved to disk)
 */
+ (ELTAccount * _Nonnull)createNewAccountWithUserId:(NSString * _Nonnull)userId;

/// User Id
@property (nonnull, nonatomic) NSString              *userId;
/// Email
@property (nullable, nonatomic) NSString             *email;
/// Mr/Mrs/Ms
@property (nullable, nonatomic, readonly) NSString   *title;
/// First name
@property (nonnull, nonatomic) NSString              *firstName;
/// Last name
@property (nonnull, nonatomic) NSString              *lastName;
/// Company name
@property (nonnull, nonatomic) NSString              *companyName;
/// Info
@property (nullable, nonatomic) NSString             *extraInfo;
/// Date when the palm model was last modified
@property (nullable, nonatomic) NSDate               *palmModelLastModified;
/// Date when the face model was last modified
@property (nullable, nonatomic) NSDate               *faceModelLastModified;
/// State of the account for palm authentication (is it ready to use or not)
@property (nonatomic) ELTAccountState                palmAccountState;
/// State of the account for face authentication (is it ready to use or not)
@property (nonatomic) ELTAccountState                faceAccountState;

/// State indicating whether the account (user information & model) has been all sent to the backend / cloud
@property (nonatomic, readonly) BOOL                 hasUnsentAccountData;

/// Available Tags (if this feature is enabled)
@property (nonatomic, nullable) NSArray<NSDictionary *>        *availableTags;

/// Time of the clockin (if applicable)
@property (nullable, nonatomic) NSString             *clockInAlertTime;
/// Time of the clockout (if applicable)
@property (nullable, nonatomic) NSString             *clockOutAlertTime;

/// Number of clear pictures needed to create an account
@property (nonatomic, readonly) NSUInteger           numberOfUserInitPicturesNeeded;

/// Date (as a string) of the last verification of the user
@property (nullable, nonatomic) NSString             *lastActionTimeStr;
/// Timestamp of the last verification of the user
@property (nullable, nonatomic) NSNumber             *lastActionTimestamp;
/// Type of the last verification of the user (can be nil, "A" for authentication, "I" for clockin, "O" for clockout)
@property (nullable, nonatomic) NSString             *lastActionType;

/// Flag used in time & attendance mode: number of minutes between each clock in
@property (nonatomic, nullable) NSNumber             *doubleClockInInterval;

/// Timestamp of the last clock in of the user
@property (nullable, nonatomic) NSNumber             *lastClockInTimestamp;
/// Timestamp of the last clock out of the user
@property (nullable, nonatomic) NSNumber             *lastClockOutTimestamp;

/// Where the user can authenticate
@property (nonatomic, readonly, nullable) NSString   *authorizedLocation;

- (void)updateLastAction:(NSDate * _Nonnull)date type:(NSString * _Nonnull)type;

/// Save to disk
- (void)save;

/// Delete this account from the device
- (void)deleteFromDevice;

/*!
 Asynchronous method to upload the account (account data and/or user model) to the backend
 @param success called when the account was successfully sent
 @param failure called when the account couldn't be sent
 */
- (void)uploadWithSuccessBlock:(_Nonnull ELTAccountUploadSuccess)success
                  failureBlock:(_Nonnull ELTAccountUploadFailure)failure;

/// Whether the Account has a user model
@property (nonatomic, readonly) BOOL hasPalmUserModelOnDisk;

/// Whether the Account has a user model
@property (nonatomic, readonly) BOOL hasFaceUserModelOnDisk;

/// Signed out
@property (nonatomic, readonly) BOOL signedOut;

/// Sign out the user
- (void)signOut;

/// In case there are some devices restriction entered on the dashboard
- (BOOL)canAuthenticateOnThisDevice;

/*!
 Synchronous function to download the user model from S3
 @return Whether the user model was downloaded or not
 */
- (ELTModelDownloadResult)downloadPalmModel;

/*!
 Synchronous function to download the user model from S3
 @return Whether the user model was downloaded or not
 */
- (ELTModelDownloadResult)downloadFaceModel;

/*
 * Class methods
 */

/*!
 Create an account out of its json representation
 @param dic json representation of the Account
 */
+ (nullable ELTAccount *)fromDictionary:(nonnull NSDictionary *)dic;

/// Returns all the accounts stored on the device for the current company
+ (nonnull NSArray<ELTAccount *> *)currentAccounts;

/// Returns all the accounts stored on the device that aren't signed out
+ (nonnull NSArray<ELTAccount *> *)activeAccounts;

/// Returns all the accounts stored on the device
+ (nonnull NSArray<ELTAccount *> *)allAccounts;

/// Get an account by user id
/// @param userId Account's userId
+ (nullable ELTAccount *)getAccountByUserId:(nonnull NSString *)userId;

/// Get an account by extra info and company code
/// @param extraInfo Account's extraInfo
/// @param companyCode Account's companyCode
+ (nullable ELTAccount *)getAccountByExtraInfo:(nonnull NSString *)extraInfo companyCode:(nonnull NSString *)companyCode;

/// Delete all the accounts stored on the device
+ (void)deleteAll;

@end
