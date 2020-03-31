//
//  FaceCaptureViewController.h
//
//  Created by Fengjun (Felix) Lv on 5/1/17.
//  Copyright © 2017 Element Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ELTAccount.h"

/*!
 Base class for LocalFaceAuthenticationViewController, LocalFaceEnrollmentViewController, RemoteFaceAuthenticationViewController and RemoteFaceEnrollmentViewController..
 Shouldn't be used directly.
 */
@interface FaceCaptureViewController : UIViewController

/*!
 Method to add UI element to the capture view.  Can be called multiple times.
 View(s) will be added in viewWillAppear: in the order they were added.
 @param view UIView to add above the default UI
 */
- (void)addAdditionalView:(UIView * _Nonnull)view;

/// Read only account: during enrollment, it's the account that's being created, during authentication it is the
/// account of the user trying to verify themselves.  Can be nil.
@property (nonatomic, nullable, readonly) ELTAccount *userAccount;

/// Flag to control whether the pre-capture instructions should be shown.
@property (nonatomic) BOOL showGazeInstructions;

@end
