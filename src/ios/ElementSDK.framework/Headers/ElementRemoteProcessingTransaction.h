//
//  ElementRemoteProcessingTransaction.h
//  ElementSDK
//
//  Created by Laurent Grandhomme on 10/15/19.
//  Copyright © 2019 Element. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FaceMatchingResult.h"

static NSString * _Nonnull const kEnrollmentInvalidDataError = @"kEnrollmentInvalidDataError";

@class CornerImage;

@interface ElementRemoteProcessingTransaction : NSObject

NS_ASSUME_NONNULL_BEGIN

/*
    Synchronous
 */
+ (FaceMatchingResult *)verifyUserId:(NSString *)userId
                          withImages:(NSArray <CornerImage *>* _Nonnull)imagesArray
                            latitude:(NSNumber * _Nullable)latitude
                           longitude:(NSNumber * _Nullable)longitude
                additionalParameters:(NSDictionary * _Nullable)additionalParameters;

/*
    Asynchronous
 */
+ (void)enrollUserWithFirstName:(NSString *)firstName
                       lastName:(NSString *)lastName
                         userId:(NSString *)userId
                         images:(NSArray <CornerImage *>*)imagesArray
           additionalParameters:(NSDictionary * _Nullable)additionalParameters
                   successBlock:(void(^)(NSDictionary *))successBlock
                     errorBlock:(void(^)(NSError *))errorBlock;

NS_ASSUME_NONNULL_END

@end
