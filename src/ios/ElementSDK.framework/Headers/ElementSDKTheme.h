//
//  ElementSDKTheme.h
//  FaceMatchingSDK
//
//  Created by Laurent Grandhomme on 8/2/19.
//  Copyright © 2019 Element. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 Object holding colors to use in the Element Face Matching SDK
 */
@interface ElementSDKTheme : NSObject

/*!
 Default theme used in the SDK.
 @return The default theme.
 */
+ (ElementSDKTheme *)defaultTheme;

/// Main color used for navigation bar, buttons and some other UI elements (such as a loading spinner)
@property (nonatomic, nullable) UIColor *primaryColor;

/// Text color (when used over the backgroundColor color)
@property (nonatomic, nullable) UIColor *textColor;

/// Background color used in a few screens and cards
@property (nonatomic, nullable) UIColor *backgroundColor;

/// Background color of disabled primary buttons (the button's text color remains white).
@property (nonatomic, nullable) UIColor *primaryButtonDisabledColor;

/// Background color of disabled primary reversed buttons.
@property (nonatomic, nullable) UIColor *primaryReversedDisabledBackgroundColor;
/// Text color of disabled primary reversed buttons.
@property (nonatomic, nullable) UIColor *primaryReversedDisabledTextColor;

/// Text color of navigation bar text.
@property (nonatomic, nullable) UIColor *navigationBarTextColor;

/// Text color of presented navigation barWhen a view controller is presented within the SDK, the navigation bar is white and the text is.
@property (nonatomic, nullable) UIColor *presentedNavigationBarTextColor;

/// Helper method: returns the color provided by the user or the default one
+ (UIColor *)primaryColor;
/// Helper method: returns the color provided by the user or the default one
+ (UIColor *)textColor;
/// Helper method: returns the color provided by the user or the default one
+ (UIColor *)backgroundColor;
/// Helper method: returns the color provided by the user or the default one
+ (UIColor *)primaryReversedDisabledBackgroundColor;
/// Helper method: returns the color provided by the user or the default one
+ (UIColor *)primaryReversedDisabledTextColor;
/// Helper method: returns the color provided by the user or the default one
+ (UIColor *)primaryButtonDisabledColor;
/// Helper method: returns the color provided by the user or the default one
+ (UIColor *)navigationBarTextColor;
/// Helper method: returns the color provided by the user or the default one
+ (UIColor *)presentedNavigationBarTextColor;
/// Helper method: returns the color provided by the user or the default one

@end

NS_ASSUME_NONNULL_END
