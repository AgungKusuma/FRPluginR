//
//  RemoteFaceAuthenticationViewController.h
//  ElementSDK
//
//  Created by Laurent Grandhomme on 10/17/17.
//  Copyright © 2017 Element. All rights reserved.
//

#import "FaceCaptureViewController.h"
#import "FaceMatchingResult.h"

@interface ELTDebugSettings : NSObject
@property (nonatomic, nonnull) NSString *userId;
- (instancetype _Nullable)initWithUserId:(NSString * _Nonnull)userId;
@end

/*!
 Block to call to give back the FaceMatchingResult to the RemoteFaceAuthenticationViewController
 */
typedef void(^FaceMatchingResultBlock)(FaceMatchingResult * _Nonnull);

/*!
 Process the images (asynchronously) and call the FaceMatchingResultBlock callback when done
 
 @param images : images captured (data and corner: tl = top left, tr = top right, bl = bottom left, br = bottom right, na = gaze not used)
 @param latitude optional user latitude
 @param longitude optional user longitude
 @param resultCallBack called when the user has been verified, see FaceMatchingResultBlock
 */
typedef void (^VerifyImagesAsyncBlock)(NSArray <CornerImage *> * _Nonnull images,
                                       NSNumber * _Nullable latitude, NSNumber *_Nullable longitude,
                                       FaceMatchingResultBlock _Nonnull resultCallBack);


/*!
 View controller that can be used to orchestrate face matching by grabbing 2 frames and returning them
 to the caller who then analyzes the frames and give the verification result to the view controller
 via the FaceMatchingResultBlock callback.
 
 If the user is authenticated, the view controller finishes the session and onAuthentication; otherwise
 the capture continues and VerifyImagesAsyncBlock is called when the next set of 2 frames is available.
 
 If the user taps on the cancel button, onCancel is called.
 
 Subclass of FaceCaptureViewController
 */
@interface RemoteFaceAuthenticationViewController : FaceCaptureViewController

/*!
 Create a view controller for account authentication.  Calling the matching endpoint is done by the caller.

 @param verifyAsyncBlock the view controller will call this handler when both images have been captured,
 the handler should verify these pictures and then call back the FaceMatchingResultBlock with a FaceMatchingResult
 as a parameter to give back the face matching result to the controller.
 See FaceMatchingResult for more information.
 @param onAuthentication called when the user has been verified
 @param onCancel called when the user cancels
 
 @return a valid RemoteFaceAuthenticationViewController or nil if the SDK hasn't been initialized or if the selected
 theme's bundle hasn't been added to the project
 */
- (nullable id)initWithAsyncVerifyBlock:(VerifyImagesAsyncBlock _Nonnull)verifyAsyncBlock
                       onAuthentication:(nonnull void(^)(UIViewController * _Nonnull, CGFloat confidenceScore))onAuthentication
                               onCancel:(nonnull void(^)(UIViewController * _Nonnull))onCancel;

/*!
 Create a view controller for account authentication.  The view controller calls the matching endpoint described in the provided EAK.

 @param userId User to authenticate
 @param onAuthentication called when the user has been verified
 @param onCancel called when the user cancels
 
 @return a valid RemoteFaceAuthenticationViewController or nil if the SDK hasn't been initialized or if the selected
 theme's bundle hasn't been added to the project
 */
- (nullable id)initWithUserId:(NSString * _Nonnull)userId
             onAuthentication:(nonnull void(^)(UIViewController * _Nonnull, NSNumber * _Nonnull, NSString * _Nonnull))onAuthentication
                     onCancel:(nonnull void(^)(UIViewController * _Nonnull))onCancel;

/*!
 Can be set to add addional paramaters to the data that's sent to the backend
 to perform the authentication.  Default is nil.
 */
@property (nonatomic, nullable) NSDictionary *additionalAuthenticationRequestParameters;

/// if TRUE, user can retry after an authentication failure (default is TRUE)
@property (nonatomic) BOOL addRetryButtonOnFailure;

/// if TRUE, the RemoteFaceAuthenticationViewController will show a success screen after an authentication
@property (nonatomic) BOOL showAuthenticationSuccessScreen;

/// if set, the RemoteFaceAuthenticationViewController will use the data provided in this object to upload
/// images to the cloud for debugging purposes
@property (nonatomic, nullable) ELTDebugSettings *debugSettings;

@end
