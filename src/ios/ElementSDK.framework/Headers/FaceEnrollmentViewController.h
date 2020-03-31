//
//  FaceEnrollmentViewController.h
//  ElementSDK
//
//  Created by Laurent Grandhomme on 2/26/20.
//  Copyright © 2020 Element. All rights reserved.
//

#import "FaceCaptureViewController.h"

/*!
 Optional block to specify the message that will be shown to the user after enrollment.
 
 @return The message that will be shown
 */
typedef NSString *_Nonnull(^EnrollmentMessageBlock)(void);

NS_ASSUME_NONNULL_BEGIN

@interface FaceEnrollmentViewController : FaceCaptureViewController

/// if TRUE, the Remote or Local FaceEnrollmentViewController will show a success screen after a successful enrollment (default is TRUE)
@property (nonatomic) BOOL showEnrollmentSuccessScreen;

/*!
 Can be set to modify the message that's shown to the user on enrollment.
 Default is nil (in that case, "Account Created" will be shown).
 */
@property (nonatomic, copy, nullable) EnrollmentMessageBlock enrollmentMessageForAccountBlock;

@end

NS_ASSUME_NONNULL_END
