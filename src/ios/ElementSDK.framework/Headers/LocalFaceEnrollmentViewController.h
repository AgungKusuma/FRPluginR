//
//  LocalFaceEnrollmentViewController.h
//  ElementSDK
//
//  Created by Laurent Grandhomme on 10/17/17.
//  Copyright © 2017 Element. All rights reserved.
//

#import "FaceEnrollmentViewController.h"

/*!
 Class to use for account enrollment
 */
@interface LocalFaceEnrollmentViewController : FaceEnrollmentViewController

/*!
 Initialize the user enrollment view controller for the specified account.
 @param account User to enroll.
 @param completionHandler Handler called when the account is ready / enrolled
 @param onCancel Handler called when the user cancels
 
 @return The initialized view controller or nil if the SDK hasn't been initialized or if the selected
 theme's bundle hasn't been added to the project
 */
- (nullable id)initWithAccount:(ELTAccount * _Nonnull)account
             completionHandler:(nonnull void(^)(UIViewController * _Nonnull))completionHandler
                      onCancel:(nonnull void(^)(UIViewController * _Nonnull))onCancel NS_DESIGNATED_INITIALIZER;

/*!
Initialize the user init view controller for the specified account.
@param userId User Id to enroll.
@param completionHandler Handler called when the account is ready / enrolled
@param onCancel Handler called when the user cancels

@return The initialized view controller or nil if the SDK hasn't been initialized or if the selected
theme's bundle hasn't been added to the project or if no account is found for this userId
*/
- (nullable id)initWithUserId:(NSString * _Nonnull)userId
             completionHandler:(nonnull void(^)(UIViewController * _Nonnull))completionHandler
                      onCancel:(nonnull void(^)(UIViewController * _Nonnull))onCancel NS_DESIGNATED_INITIALIZER;

/// Flag to control whether the view controller should upload the user/account data to the backend
/// when the enrollment process is completed (default is YES)
@property (nonatomic) BOOL  uploadAccountUponEnrollmentCompletion;

@end
