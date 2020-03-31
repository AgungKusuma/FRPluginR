//
//  RemoteFaceEnrollmentViewController.h
//  FaceMatchingSDK
//
//  Created by Laurent Grandhomme on 6/24/19.
//  Copyright © 2019 Element. All rights reserved.
//

#import "FaceCaptureViewController.h"
#import "FaceEnrollmentViewController.h"

NS_ASSUME_NONNULL_BEGIN

/*!
 View controller that can be used to orchestrate face enrollment by grabbing 4 frames and returning them
 to the caller who can then use them to generate a user model.
 
 If the user taps on the cancel button, onCancel is called.
 
 Subclass of FaceCaptureViewController
 */
@interface RemoteFaceEnrollmentViewController : FaceEnrollmentViewController

/*!
 Create a view controller that can be used to grab 4 frames; the caller is responsible for creating the model.

 @param onSuccess called when 4 frames have been grabbed
 @param onCancel called when the user cancels
 
 @return a valid RemoteFaceEnrollmentViewController or nil if the SDK hasn't been initialized or if the selected
 theme's bundle hasn't been added to the project
 */
- (nullable id)initWithSuccessBlock:(nonnull void(^)(UIViewController * _Nonnull, NSArray <CornerImage *> * _Nonnull cornerImages))onSuccess onCancel:(nonnull void(^)(UIViewController * _Nonnull))onCancel;

/*!
 Create a view controller for user enrollment

 @param firstName : enrollee's first name
 @param lastName : enrollee's last name
 @param userId : enrollee's user ID
 @param onSuccess called when the user model has been created
 @param onCancel called when the user cancels
 
 @return a valid RemoteFaceEnrollmentViewController or nil if the SDK hasn't been initialized or if the selected
 theme's bundle hasn't been added to the project
 */
- (nullable id)initWithFirstName:(NSString *)firstName lastName:(NSString *)lastName userId:(NSString *)userId successBlock:(nonnull void(^)(UIViewController * _Nonnull))onSuccess onCancel:(nonnull void(^)(UIViewController * _Nonnull))onCancel;

/*!
 Can be set to send addional paramaters to the backend along with the enrollment data.
 Note: only applicable when the SDK handles the network call to perform enrollment.
 Default is nil.
 */
@property (nonatomic, nullable) NSDictionary *additionalEnrollmentParameters;

@end

NS_ASSUME_NONNULL_END
