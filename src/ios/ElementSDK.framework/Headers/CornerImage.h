//
//  CornerImage.h
//  ElementSDK
//
//  Created by Laurent Grandhomme on 12/2/19.
//  Copyright © 2019 Element. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// holds image data and corner id of the image
@interface CornerImage : NSObject

/// image data : UIImageJPEGRepresentation(image, 0.95)
@property (nonatomic) NSData    *data;
/// corner: tl = top left, tr = top right, bl = bottom left, br = bottom right, na = gaze not used
@property (nonatomic) NSString  *cornerId;

- (instancetype)initWithData:(NSData *)data cornerId:(NSString *)cornerId;

@end

NS_ASSUME_NONNULL_END
