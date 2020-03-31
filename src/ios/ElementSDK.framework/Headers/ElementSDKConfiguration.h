//
//  ElementSDKConfiguration.h
//  ElementSDK
//
//  Created by Laurent Grandhomme on 1/25/17.
//  Copyright © 2017 Element. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "ElementSDKTheme.h"

/**
 *  Block definition for file upload progress notifications
 */
typedef void(^ELTCloudDataUploadProgressBlock)(NSUInteger);

/**
 *  Enums for anti spoofing method.
 */
typedef NS_ENUM(NSInteger, ELTFaceAntiSpoofingType) {
    /**
     *  Passive anti spoofing
     */
    ELTFaceAntiSpoofingPassive = 0,
    /**
     *  Gaze anti spoofing
     */
    ELTFaceAntiSpoofingGaze,
    /**
     *  Randomized Gaze anti spoofing
     */
    ELTFaceAntiSpoofingRandomizedGaze,
};

/**
 *  Enums for user interface theme
 */
typedef NS_ENUM(NSInteger, ELTUITheme) {
    /**
     *  Default: blue and white
     */
    ELTUIThemeCountdownDefault = 0,
    /**
     *  New theme with flower animation
     */
    ELTUIThemeFlowerPetals,
    /**
     *  yellow theme
     */
    ELTUIThemeCountdownYellow,
    /**
     *  blue theme
     */
    ELTUIThemeCountdownBlue,
    /**
     *  blue green theme
     */
    ELTUIThemeCountdownBlueGreen,
    /**
     * less animation, blue theme
     */
    ELTUIThemeLegacyCountdown
};

/*!
 Singleton that contains the configuration
 */
@interface ElementSDKConfiguration : NSObject

/// Get the singleton
+ (nonnull ElementSDKConfiguration *)shared;

/// User interface theme (ELTUIThemeCountdownDefault by default)
/// Note: add the associated bundle to your project.  view controllers can't be created when themes
/// aren't setup correctly (when the bundle isn't available)
@property (nonatomic)                               ELTUITheme  theme;

/// Main color for the SDK: used for buttons, gaze UI (when applicable), etc
@property (nonatomic, nullable)                     UIColor     *mainColor;

/// Secondary color used for loading animations
@property (nonatomic, nullable)                     UIColor     *secondaryColor;

/// Capture page frame background color
@property (nonatomic, nullable)                     UIColor     *frameBackgroundColor;

/// Flag to specify whether the images should be uploaded to the cloud (YES by default)
@property (nonatomic)                               BOOL        uploadImages;

/// Flag to specify whether one face image should be uploaded for review during enrollment (NO by default)
@property (nonatomic)                               BOOL        uploadOneUserInitImageForReview;

/// Flag to specify whether the user's location at the time of authentication should be
/// uploaded to the cloud (NO by default)
@property (nonatomic)                               BOOL        geolocateUser;

/// Flag to specify which anti spoofing method will be used
/// (ELTFaceAntiSpoofingPassive by default)
@property (nonatomic)                               ELTFaceAntiSpoofingType faceAntiSpoofingType;

/// When anti spoofing is enabled, this flag can be set to NO to accept images where the
/// user doesn't look at the right dot.
/// (YES by default)
@property (nonatomic)                               BOOL        blockOnGazeMismatch;

/// SDK Theme: optional, when provided, using the colors defined in this object to render the UI
/// Default them is ElementSDKTheme's defaultTheme
/// See ElementSDKTheme
@property (nonatomic, nullable)                     ElementSDKTheme *customTheme;

/*!
 Set this block to get notified of the progress of the syncing of files to the cloud server
 (when uploadImages is set to TRUE).
 The NSUInteger passed in represents the number of files left to be sent.
 */
@property (nonatomic, nullable, copy)               ELTCloudDataUploadProgressBlock cloudDataUploadProgressBlock;

/// Flag that can be read to verify that the SDK was successfully configured (same as the result of the
/// initializeWithConfigurationData: method).
@property (nonatomic, readonly)                     BOOL        isConfigured;

/// Sets the timeout interval for the networking calls.
/// The timeout interval specifies the limit on the idle interval allotted to a request in the process of loading.
/// Default is 30 (seconds) - cannot be less than 10
@property (nonatomic)                               NSTimeInterval timeoutInterval;

/// Version of the SDK
@property (nonatomic, readonly, nonnull)            NSString *sdkVersion;

/*!
 Initialize the SDK with the configuration data
 @param configurationData SDK Configuration Data provided by Element
 
 @return A boolean that indicates whether the initialization succeeded (it can fail if the app's
 Bundle Identifier (CFBundleIdentifier) doesn't match the appId contained in configurationData)
 */
- (BOOL)initializeWithConfigurationData:(nonnull NSString *)configurationData;

/*!
 Helper method that can be used by UIApplicationDelegates to determine whether the current view
 controller is an Element view controller to use that result to force the portrait
 (UIInterfaceOrientationMaskPortrait) orientation (UIInterfaceOrientationMask) in
 func application(_ application: UIApplication, supportedInterfaceOrientationsFor window: UIWindow?) -> UIInterfaceOrientationMask
 - (UIInterfaceOrientationMask)application:(UIApplication *)application supportedInterfaceOrientationsForWindow:(nullable UIWindow *)window
 
 @return A boolean that indicates whether current controller is an Element view controller (FaceCaptureViewController subclass)
 */
+ (BOOL)displayingElementViewController;

@end
