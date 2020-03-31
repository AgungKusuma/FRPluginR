//
//  ElementSDKTransaction.h
//  ElementSDK
//
//  Created by Laurent Grandhomme on 3/1/17.
//  Copyright © 2017 Element. All rights reserved.
//

#import "ELTAccount.h"

/*!
 Enum for the results of the sign in endpoints
 */
typedef enum ELTTransactionResult {
    ELTTransactionSuccess,
    ELTTransactionErrorNoApiKey,
    ELTTransactionErrorInvalidApiKey,
    ELTTransactionErrorNoSuchUser,
    ELTTransactionErrorInvalidPin,
    ELTTransactionErrorInvalidResponse,
    ELTTransactionErrorNetwork,
    ELTTransactionErrorUnspecified
} ELTTransactionResult;

/*!
 Collection of static methods used to communicate with the Element backend.
 */
@interface ElementSDKTransaction : NSObject

NS_ASSUME_NONNULL_BEGIN

/*!
 Endpoint to get a user account based on their email and 4-digit pin (if present, the face and palm
 models will be downloaded).  See [ELTAccount]
 @param email User's email
 @param pin User's 4-Digit pin
 @param successBlock Called when the user exists and the pin is valid
 @param errorBlock Called when an error occurred (unknown email, invalid pin, network error, etc)
 */
+ (void)userSignInWithEmail:(NSString *)email
                        pin:(NSString *)pin
               successBlock:(void(^)(ELTAccount * _Nonnull ))successBlock
                 errorBlock:(void(^)(ELTTransactionResult, NSError *, NSString * __nullable ))errorBlock;

/*!
 Endpoint to get a user account based on their userId (if present, the face and palm
 models will be downloaded).  See [ELTAccount]
 @param userId User's userId
 @param downloadMetaData if TRUE, the ELTAccount's metadata (first name, last name, etc) will be
 downloaded as well as the biometric information.  if FALSE, only the biometrics information will be
 downloaded.
 @param successBlock Called when the user exists
 @param errorBlock Called when an error occurred (unknown userId, network error, etc)
 */
+ (void)userSignInWithUserId:(NSString *)userId
            downloadMetaData:(BOOL)downloadMetaData
                successBlock:(void(^)(ELTAccount * _Nonnull ))successBlock
                  errorBlock:(void(^)(ELTTransactionResult, NSError *, NSString * __nullable ))errorBlock;

/*!
 Endpoint to get a user account based on their email (if present, the face and palm
 models will be downloaded).  See [ELTAccount]
 @param email User's email
 @param successBlock Called when the user exists
 @param errorBlock Called when an error occurred (unknown email, network error, etc)
 
 Note: this endpoint is only enabled with private deployment of the Element webservices
 */
+ (void)userSignInWithEmail:(NSString *)email
               successBlock:(void(^)(ELTAccount * _Nonnull ))successBlock
                 errorBlock:(void(^)(ELTTransactionResult, NSError *, NSString * __nullable ))errorBlock;

/*!
 Endpoint to synchronize the SDK data and the user data with the backend
 @param account User account to synchronize
 @param successBlock Called when the call succeeds
 @param errorBlock Called when an error occurred (invalid api key, network error, etc)
 */
+ (void)synchronizeWithBackendForAccount:(ELTAccount *)account
                            successBlock:(void(^)(void))successBlock
                              errorBlock:(void(^)(void))errorBlock;

/*!
 Get the list of users for the current company
 @param successBlock Called when the call succeeds
 @param errorBlock Called when an error occurred (invalid api key, network error, etc)
 */
+ (void)getUserListSuccessBlock:(void(^)(NSArray <ELTAccount *>* _Nonnull ))successBlock
                     errorBlock:(void(^)(NSError *, NSString * __nullable ))errorBlock;

/*!
 Call the endpoint (backend described in your EAK)
 @param successBlock Called when the call succeeds
 @param errorBlock Called when an error occurred (invalid api key, network error, etc)
 */
+ (void)genericGetWithEndpoint:(NSString *)endpoint
                 successBlock:(void(^)(id))successBlock
                   errorBlock:(void(^)(NSError *, NSDictionary * ))errorBlock;
/*!
 Call the endpoint (backend described in your EAK)
 @param successBlock Called when the call succeeds
 @param errorBlock Called when an error occurred (invalid api key, network error, etc)
 */
+ (void)genericPostWithEndpoint:(NSString *)endpoint
                     parameters:(NSDictionary *)parameters
                   successBlock:(void(^)(id))successBlock
                     errorBlock:(void(^)(NSError *, NSString * __nullable ))errorBlock;

NS_ASSUME_NONNULL_END

@end
