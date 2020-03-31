//
//  LocalFaceIdentificationViewController.h
//  ElementSDK
//
//  Created by Laurent Grandhomme on 3/15/18.
//  Copyright © 2018 Element. All rights reserved.
//

#import "FaceCaptureViewController.h"

@interface LocalFaceIdentificationViewController : FaceCaptureViewController

- (nullable id)initWithIdentificationBlock:(nonnull void(^)(UIViewController * _Nonnull, ELTAccount * _Nonnull))onIdentification
                                  onCancel:(nonnull void(^)(UIViewController * _Nonnull))onCancel NS_DESIGNATED_INITIALIZER;

@end
