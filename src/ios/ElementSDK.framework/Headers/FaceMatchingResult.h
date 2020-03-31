//
//  FaceMatchingResult.h
//  FaceMatchingLightSDK
//
//  Created by Laurent Grandhomme on 10/9/18.
//  Copyright © 2018 Element. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 Object that holds the face matching result as well as some information to pass back to the [RemoteFaceAuthenticationViewController] controller.
 */
@interface FaceMatchingResult : NSObject

/// flag to indicate whether the 2 frames passed in match the identity of the user
@property (nonatomic, readwrite) BOOL               verified;
/// display message to show to the user (if verified, it's the message shown on the success screen, otherwise it's a message shown before the user tries again
@property (nonatomic, readwrite, nullable) NSString *displayMessage;
/// confidence of the result
@property (nonatomic, readwrite, nullable) NSNumber *confidenceScore;
/// when an error happens (typically a network error, pass it to the view controller)
@property (nonatomic, readwrite, nullable) NSError  *error;
/// when set, the view controller will abort the authentication
@property (nonatomic, readwrite) BOOL               abort;

@end

