//
//  LocalFaceAuthenticationViewController.h
//  ElementSDK
//
//  Created by Laurent Grandhomme on 10/17/17.
//  Copyright © 2017 Element. All rights reserved.
//

#import "FaceCaptureViewController.h"

/*!
 Optional block to specify additional authentication parameters to send to the backend.
 
 @param ELTAccount account that just authenticated
 @return A dictionary containing additional information to send to the backend
 */
typedef NSDictionary *_Nonnull(^AdditionalAuthenticationParametersBlock)(ELTAccount *_Nonnull);

/*!
 Optional block to specify the message that will be shown to the user when authenticating.
 
 @param ELTAccount account that just authenticated
 @return The message that will be shown
 */
typedef NSString *_Nonnull(^AuthenticationMessageBlock)(ELTAccount *_Nonnull);

/*!
 View controller that can be used to authenticate a user using the Face modality.  
 Subclass of [FaceCaptureViewController]
 */
@interface LocalFaceAuthenticationViewController : FaceCaptureViewController

/*!
 Create the view controller to authenticate the user represented by the account.  If the user
 authenticate the authenticatedBlock is called.  If the user cancels, the cancelBlock is called.
 @param account User to authenticate
 @param onAuthentication called when the user is authenticated
 @param onCancel called when the user cancels the authentication process
 
 @return a valid LocalFaceAuthenticationViewController or nil if the SDK hasn't been initialized or if the selected
 theme's bundle hasn't been added to the project
 */
- (nullable id)initWithAccount:(ELTAccount * _Nonnull)account
              onAuthentication:(nonnull void(^)(UIViewController * _Nonnull, CGFloat confidenceScore))onAuthentication
                      onCancel:(nonnull void(^)(UIViewController * _Nonnull))onCancel NS_DESIGNATED_INITIALIZER;

/*!
 Create the view controller to authenticate the user represented by its userId.  If the user
 authenticate the authenticatedBlock is called.  If the user cancels, the cancelBlock is called.
 @param userId userId of the ELTAccount to authenticate
 @param onAuthentication called when the user is authenticated
 @param onCancel called when the user cancels the authentication process
 @return The initialized view controller or nil of the ELTAccount with userId isn't found on the device or if the SDK hasn't been initialized or if the selected theme's bundle hasn't been added to the project
 */
- (nullable id)initWithUserId:(NSString * _Nonnull)userId
             onAuthentication:(nonnull void(^)(UIViewController * _Nonnull, CGFloat confidenceScore))onAuthentication
                     onCancel:(nonnull void(^)(UIViewController * _Nonnull))onCancel NS_DESIGNATED_INITIALIZER;


/// Authentication confidence score threshold (between 0 and 1) - default is 0.95
@property (nonatomic) CGFloat authenticationConfidenceScoreThreshold;

/// if TRUE, the LocalFaceAuthenticationViewController will show a success screen after an authentication
@property (nonatomic) BOOL showAuthenticationSuccessScreen;

/// only applicable if showAuthenticationSuccessScreen is TRUE
/// if warnOnAuthenticationReportingFailure TRUE, the authentication success screen shows whether the authentication
/// was reported or not
@property (nonatomic) BOOL warnOnAuthenticationReportingFailure;

/*!
 Can be set to add addional paramaters to the data that's sent to the backend
 to report authentications.  Default is nil.
 */
@property (nonatomic, nullable) NSDictionary *additionalAuthenticationParameters;

/*!
 Can be set to add addional paramaters to the data that's sent to the backend to report authentications.
 Default is nil.
 */
@property (nonatomic, copy, nullable) AdditionalAuthenticationParametersBlock additionalAuthenticationParametersForAccountBlock;

/*!
 Can be overriden by subclasses to add addional paramaters to the data that's sent to the backend
 to report authentications.  Default is nil.
 @param account Account that just authenticated
 */
- (nullable NSDictionary *)additionalAuthenticationParametersForAccount:(ELTAccount * _Nonnull)account;

/*!
 Can be set to modify the message that's shown to the user on authentication.
 Default is nil.
 
 Note: similar to the authenticationMessageForAccount: method that should be used when subclassing
 this view controller.
 */
@property (nonatomic, copy, nullable) AuthenticationMessageBlock authenticationMessageForAccountBlock;

/*!
 Can be overriden by subclasses to show a custom message when the user authenticate.  Default is "Hello <first name>!".
 @param account Account that just authenticated
 */
- (nonnull NSString *)authenticationMessageForAccount:(ELTAccount * _Nonnull)account;

@end
