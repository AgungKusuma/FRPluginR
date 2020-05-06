/********* ElementFaceWrapper.m Cordova Plugin Implementation *******/

#import "ElementFaceWrapper.h"

#import <Cordova/CDV.h>

#import <ElementSDK/ElementSDK.h>

@implementation ElementFaceWrapper

- (void)getSdkVersion:(CDVInvokedUrlCommand *)command {
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:[ElementSDKConfiguration shared].sdkVersion];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}
  
// private method
- (BOOL)configureSDK {
    // TODO: update with your EAK
    NSString *eak = @"EREREcEnyXza3yorVUnQmDHKC81Ekw2ksqjdfR2xhCkBU0hTqIBE5d4jfA1Q6YOJX2WNMxEpL81T91QbZ3Zoa6KRMGt2tPendqMbpoej2Abey21hjmmwP+ZW8vf0yEAzry8SBFmbjH350jNHBtEbvv2HpuqaTTWczomEZiO45SB75/bQtNphTdldYlmucDQgShQGQAskhq2qhb7ruhV4bPFC1WHg87R8wfO1RxgnD0WUGlNr75FoayQkOpHkKE4e26DODi+DmB8txsczQdOaV1fvRM2QJiMDkRIZuRJxxmU0eIxyqo3lUL3q+7kMHan0N9xWDrRUZB1BucMR6FvGqcpF9pLdcKRQtksCBvBG/42jCO6rfeZqersRiQFIIxu3oidw3WRZAKmRsXVx1+TbGqduSoGtmvkTp1TWWFvo3Blc0OCqLKyjOENlhgUl4Mq9iSyB6T7SK6YVJ5fNcrDABo3KvkkupaZfbGSde5swRzPa2bNkC83bLqaWoDAfIONRAcEhbNkTBzzJNLd6/pF58mjBqytSHuk6L2HwN8syT8rVjLOJEpvNhwD7jdlvyzQ9z08isZlL8Z04vO2k2qHZuKm8hhJeh1CYQ4xZHKT3JW2ep21yR08XfqtIASaCSs+HggylYyWrJ5boSupRXnwg7L7lOsEF2nMlHzFzRNECbuccfJXqVrjmz0hqa3D2tSDKtOaEGtmdw9VZBEyWAKIo503hsTQC9t9JSnb2n46SumME2Sk/s//IY3WmRllMiJSbb9cHfB1JdKXmeEAr81D8xauRlTKhJ3p7k5/TmMlISXjpASjmuZG6UKRlk9iAE9nMR4lMr3zSeK9LMUJuB/xNRviA+GLEV/++hhgCDFatyRZHi/4aQVBFIiDw30h5JJCAjctZV1fTbpCInWMMkWvLck+IYDaxRNFv4vA2atcDPdg2DmRIPpVCdi9Dkq9SbvC0KEQfXXSU0Wo4/WSR7xVc4zz9ohEBYmCIlclMXsv9RXX3qVzrXFBAFV3igWFjnw9f4Xp3c/dirr+d4A==";
    BOOL result = [[ElementSDKConfiguration shared] initializeWithConfigurationData:eak];
    if (!result) {
        NSLog(@"Error: ElementSDK configuration failed");
        return NO;
    }
    [ElementSDKConfiguration shared].uploadImages = NO;
    [ElementSDKConfiguration shared].geolocateUser = NO;
    [ElementSDKConfiguration shared].theme = ELTUIThemeFlowerPetals;
    [ElementSDKConfiguration shared].customTheme.backgroundColor = [UIColor colorWithRed:0.949 green:0.502 blue:0.094 alpha:1.0];
    return YES;
}

- (void)enroll:(CDVInvokedUrlCommand *)command {
    NSLog(@"enroll");
    if (![ElementSDKConfiguration shared].isConfigured) {
        NSLog(@"configuration needed");
        BOOL configureResult = [self configureSDK];
        if (!configureResult) {
            NSLog(@"SDK configuration error (CDVCommandStatus_ERROR)");
            CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Element SDK configuration failed (see logs)"];
            [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
            return;
        }
    }
    [ElementSDKConfiguration shared].faceAntiSpoofingType = ELTFaceAntiSpoofingGaze;
    RemoteFaceAuthenticationViewController *vc = [[RemoteFaceAuthenticationViewController alloc] initWithAsyncVerifyBlock:^(NSArray<CornerImage *> *  images, NSNumber *  latitude, NSNumber *  longitude, FaceMatchingResultBlock   resultCallBack) {
        NSLog(@"got the images");
        NSString *singleImage = @"";
        for (CornerImage *img in images) {
            singleImage = [img.data base64EncodedStringWithOptions:0];
            NSLog(@"return the 1st image");
            break;
        }
        FaceMatchingResult *res = [FaceMatchingResult new];
        res.verified = YES;
        resultCallBack(res);
        NSLog(@"returning the image CDVCommandStatus_OK");
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:singleImage];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    } onAuthentication:^(UIViewController * viewController, CGFloat confidenceScore) {
        NSLog(@"enrolled, dismiss the view controller");
        [viewController dismissViewControllerAnimated:YES completion:nil];
    } onCancel:^(UIViewController * viewController) {
        NSLog(@"user cancelled, dismiss the view controller (CDVCommandStatus_ERROR)");
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"User cancelled"];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
        [viewController dismissViewControllerAnimated:YES completion:nil];
    }];
    vc.showAuthenticationSuccessScreen = NO;
    [[self viewController] presentViewController:vc animated:YES completion:nil];
}

- (void)match:(CDVInvokedUrlCommand *)command {
    NSLog(@"match (auth)");
    if (![ElementSDKConfiguration shared].isConfigured) {
        NSLog(@"configuration needed");
        BOOL configureResult = [self configureSDK];
        if (!configureResult) {
            NSLog(@"SDK configuration error (CDVCommandStatus_ERROR)");
            CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Element SDK configuration failed (see logs)"];
            [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
            return;
        }
    }
    [ElementSDKConfiguration shared].faceAntiSpoofingType = ELTFaceAntiSpoofingPassive;
    RemoteFaceAuthenticationViewController *vc = [[RemoteFaceAuthenticationViewController alloc] initWithAsyncVerifyBlock:^(NSArray<CornerImage *> *  images, NSNumber *  latitude, NSNumber *  longitude, FaceMatchingResultBlock   resultCallBack) {
        NSString *singleImage = @"";
        for (CornerImage *img in images) {
            NSLog(@"return the 1st image");
            singleImage = [img.data base64EncodedStringWithOptions:0];
            break;
        }
        FaceMatchingResult *res = [FaceMatchingResult new];
        res.verified = YES;
        resultCallBack(res);
        NSLog(@"returning the image CDVCommandStatus_OK");
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:singleImage];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    } onAuthentication:^(UIViewController * viewController, CGFloat confidenceScore) {
        NSLog(@"matched, dismiss the view controller");
        [viewController dismissViewControllerAnimated:YES completion:nil];
    } onCancel:^(UIViewController * viewController) {
        NSLog(@"user cancelled, dismiss the view controller (CDVCommandStatus_ERROR)");
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"User cancelled"];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
        [viewController dismissViewControllerAnimated:YES completion:nil];
    }];
    vc.showAuthenticationSuccessScreen = NO;
    [[self viewController] presentViewController:vc animated:YES completion:nil];
}

// Below is old code
#if 0
- (void)authenticate:(CDVInvokedUrlCommand *)command {
    NSLog(@"authenticate");
    [ElementSDKConfiguration shared].faceAntiSpoofingType = ELTFaceAntiSpoofingGaze;
    RemoteFaceAuthenticationViewController *vc = [[RemoteFaceAuthenticationViewController alloc] initWithAsyncVerifyBlock:^(NSArray<CornerImage *> *  images, NSNumber *  latitude, NSNumber *  longitude, FaceMatchingResultBlock   resultCallBack) {
        NSLog(@"got the images");
        NSMutableArray *arr = [NSMutableArray new];
        for (CornerImage *img in images) {
            NSString *singleImage = [img.data base64EncodedStringWithOptions:0];
            [arr addObject:singleImage];
        }
        FaceMatchingResult *res = [FaceMatchingResult new];
        res.verified = YES;
        resultCallBack(res);
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsArray:arr];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    } onAuthentication:^(UIViewController * viewController, CGFloat confidenceScore) {
        NSLog(@"authenticated, dismiss the view controller");
        [viewController dismissViewControllerAnimated:YES completion:nil];
    } onCancel:^(UIViewController * viewController) {
        NSLog(@"user cancelled, dismiss the view controller");
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"User cancelled"];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
        [viewController dismissViewControllerAnimated:YES completion:nil];
    }];
    vc.showAuthenticationSuccessScreen = NO;
    [[self viewController] presentViewController:vc animated:YES completion:nil];
}

- (void)authenticateWithoutLiveness:(CDVInvokedUrlCommand *)command {
    NSLog(@"authenticateWithoutLiveness");
    [ElementSDKConfiguration shared].faceAntiSpoofingType = ELTFaceAntiSpoofingPassive;
    RemoteFaceAuthenticationViewController *vc = [[RemoteFaceAuthenticationViewController alloc] initWithAsyncVerifyBlock:^(NSArray<CornerImage *> *  images, NSNumber *  latitude, NSNumber *  longitude, FaceMatchingResultBlock   resultCallBack) {
        NSString *singleImage = @"";
        for (CornerImage *img in images) {
            singleImage = [img.data base64EncodedStringWithOptions:0];
            break;
        }
        FaceMatchingResult *res = [FaceMatchingResult new];
        res.verified = YES;
        resultCallBack(res);
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:singleImage];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    } onAuthentication:^(UIViewController * viewController, CGFloat confidenceScore) {
        [viewController dismissViewControllerAnimated:YES completion:nil];
    } onCancel:^(UIViewController * viewController) {
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"User cancelled"];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
        [viewController dismissViewControllerAnimated:YES completion:nil];
    }];
    vc.showAuthenticationSuccessScreen = NO;
    [[self viewController] presentViewController:vc animated:YES completion:nil];
}

- (void)generateId:(CDVInvokedUrlCommand *)command {
  NSString *userid = [[NSUUID UUID] UUIDString];
  CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:userid];
  [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)configuration:(NSString *)eak {
    [[ElementSDKConfiguration shared] initializeWithConfigurationData:eak];
    [ElementSDKConfiguration shared].uploadImages = YES;
    [ElementSDKConfiguration shared].geolocateUser = YES;
}

- (void)config:(CDVInvokedUrlCommand *)command {
    NSDictionary *data = [command.arguments objectAtIndex:0];
    NSString *eak = data[@"eak"];
    bool image = [data[@"image"] boolValue];
    bool location = [data[@"location"] boolValue];
    bool landscape = [data[@"landscape"] boolValue];
    NSInteger themeId = [data[@"theme"] integerValue];
    ELTUITheme theme;
    switch (themeId) {
        case 1:
            theme = ELTUIThemeFlowerPetals;
            break;
        case 2:
            theme = ELTUIThemeCountdownYellow;
            break;
        case 3:
            theme = ELTUIThemeCountdownBlue;
            break;
        case 4:
            theme = ELTUIThemeCountdownBlueGreen;
            break;
        case 5:
            theme = ELTUIThemeLegacyCountdown;
            break;
        default:
            theme = ELTUIThemeCountdownDefault;
            break;
    }

    BOOL result = [[ElementSDKConfiguration shared] initializeWithConfigurationData:eak];
    if (!result) {
        NSLog(@"Error: ElementSDK configuration failed");
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"configuration failed"];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
        return;
    }
    [ElementSDKConfiguration shared].uploadImages =image;
    [ElementSDKConfiguration shared].geolocateUser = location;
    [ElementSDKConfiguration shared].theme = theme;
    [ElementSDKConfiguration shared].customTheme.backgroundColor = [UIColor colorWithRed:0.949 green:0.502 blue:0.094 alpha:1.0];
    /*
     -- somehow the gazeFlowerUIColor method disappears
     [ElementSDKConfiguration shared].gazeFlowerUIColor = [UIColor colorWithRed:0.949 green:0.502 blue:0.094 alpha:1.0];*/
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"config successfully"];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)createAccount:(CDVInvokedUrlCommand *)command {
    NSDictionary *data = [command.arguments objectAtIndex:0];
    NSString *firstname = data[@"firstname"];
    NSString *lastname = data[@"lastname"];
    NSString *email = data[@"email"];
    NSString *cleartextpin = data[@"cleartextpin"];
    NSString *extrainfo = data[@"extrainfo"];
    NSString *userid = data[@"id"];
    NSString *eak = data[@"eak"];
    bool gaze = [data[@"gaze"] boolValue];
    bool delayupload = [data[@"delayupload"] boolValue];

    if ([userid length] == 0) {
        userid = [[NSUUID UUID] UUIDString];
    }

    if ([eak length] == 0 ||[firstname length] == 0 || [lastname length] == 0) {
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"EAK, FirstName or LastName is empty."];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    } else {
        ELTAccount *accounts = [ELTAccount createNewAccountWithFirstName:firstname lastName:lastname email:email clearTextPin:cleartextpin extraInfo:extrainfo userId:userid ];
        LocalFaceEnrollmentViewController *faceUserInitViewController =
        [[LocalFaceEnrollmentViewController alloc]
         initWithAccount:accounts
         completionHandler:^(UIViewController *vc) {
             NSLog(@"#PluginResult: SUCCESS");
             CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:userid];
             [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
             [vc dismissViewControllerAnimated:YES completion:nil];
         }
         onCancel:^(UIViewController *vc) {
             NSLog(@"#PluginResult: ERROR");
             CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Account enrollment cancelled"];
             [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
             [vc dismissViewControllerAnimated:YES completion:nil];
         }];
        faceUserInitViewController.showGazeInstructions = gaze;
        faceUserInitViewController.uploadAccountUponEnrollmentCompletion = delayupload;
        [[self viewController] presentViewController:faceUserInitViewController animated:YES completion:nil];
    }
}

- (void)uploadModel: (CDVInvokedUrlCommand *)command {
    NSString *userid = [command.arguments objectAtIndex:0];

    if ([userid length] == 0) {
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"userId is empty."];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }
    else {
        ELTAccount *model = [ELTAccount getAccountByUserId:userid];
        NSString *acc = nil;
        if([model faceAccountState] == ELTAccountStateReady) {
            acc = @"Ready";
        }  else if ([model faceAccountState] == ELTAccountStateUserInitNeeded) {
            acc = @"User Init Needed";
        } else if ([model faceAccountState] == ELTAccountStateUnknown) {
            acc = @"State Unknown";
        }  else if ([model faceAccountState] == ELTAccountStateAvailableButNotDownloaded) {
            acc = @"Available but not downloaded";
        } else {
            acc = @"Not Ready";
        }
        if ([model faceAccountState] == ELTAccountStateReady) {
            [model uploadWithSuccessBlock:^{
                NSLog(@"account was successfully uploaded! (it stays on the device)");
                CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"account was successfully uploaded!"];
                [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
            } failureBlock:^{
                NSLog(@"account couldn't be sent, try again later");
                CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"account couldn't be sent, try again later"];
                [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
            }];
        }
        else {
            CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:userid];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
        }
    }
}

- (void)authAccount:(CDVInvokedUrlCommand *)command {
    NSDictionary *data = [command.arguments objectAtIndex:0];
    NSString *userid = data[@"uid"];
    NSString *eak = data[@"eak"];
    CGFloat score = [data[@"cs"] floatValue];

    /* [self configuration:eak]; */
    if ([eak length] == 0 || [userid length] == 0) {
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"EAK or userId is empty."];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    } else {
        ELTAccount *model = [ELTAccount getAccountByUserId:userid];

        if ([model faceAccountState] == ELTAccountStateReady) {
            LocalFaceAuthenticationViewController *authViewController =
            [[LocalFaceAuthenticationViewController alloc] initWithAccount:model onAuthentication:^(UIViewController * vc, CGFloat cs) {
                NSMutableArray *models = [[NSMutableArray alloc] init];
                NSMutableDictionary *array = [[NSMutableDictionary alloc] init];
                NSString *fn = [NSString stringWithFormat:@"%@", model.firstName];
                NSString *ln = [NSString stringWithFormat:@"%@", model.lastName];
                NSString *em = [NSString stringWithFormat:@"%@", model.email];
                NSString *ei = [NSString stringWithFormat:@"%@", model.extraInfo];
                NSString *uid = [NSString stringWithFormat:@"%@", model.userId];
                NSString *acc = nil;
                CGFloat score = cs;
                if([model faceAccountState] == ELTAccountStateReady) {
                    acc = @"Ready";
                }  else if ([model faceAccountState] == ELTAccountStateUserInitNeeded) {
                    acc = @"User Init Needed";
                } else if ([model faceAccountState] == ELTAccountStateUnknown) {
                    acc = @"State Unknown";
                }  else if ([model faceAccountState] == ELTAccountStateAvailableButNotDownloaded) {
                    acc = @"Available but not downloaded";
                } else {
                    acc = @"Not Ready";
                }
                [array setObject:fn forKey:@"firstName"];
                [array setObject:ln forKey:@"lastName"];
                [array setObject:em forKey:@"email"];
                [array setObject:ei forKey:@"extraInfo"];
                [array setObject:uid forKey:@"userId"];
                [array setObject:acc forKey:@"faceAccountState"];
                [array setObject:[NSNumber numberWithFloat:score] forKey:@"confidenceScore"];
                [models addObject:array];
                NSData *jsonData = [NSJSONSerialization dataWithJSONObject:models options:NSJSONWritingPrettyPrinted error:nil];
                NSString *jsonString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
                NSLog(@"JSONString:\n%@\n---", jsonString);
                CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:jsonString];
                [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
                [vc dismissViewControllerAnimated:YES completion:nil];
            } onCancel:^(UIViewController * vc) {
                CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Account authentication cancelled"];
                [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
                [vc dismissViewControllerAnimated:YES completion:nil];
            }];

            authViewController.authenticationConfidenceScoreThreshold = score;

            [[self viewController] presentViewController:authViewController animated:YES completion:nil];
            //Quickfix: refresh the view; change DISPATCH_TIME_NOW > 0.5 if the view doesn't refresh
            //dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 0.2 * NSEC_PER_SEC), dispatch_get_main_queue(), ^{
            //    [[[self viewController] presentedViewController] viewWillAppear:YES];
            //});

        } else if ([model faceAccountState] == ELTAccountStateUserInitNeeded) {
            //complete account creation
            LocalFaceEnrollmentViewController *faceUserInitViewController =
            [[LocalFaceEnrollmentViewController alloc]
             initWithAccount:model
             completionHandler:^(UIViewController *vc) {
                 CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:userid];
                 [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
                 [vc dismissViewControllerAnimated:YES completion:nil];
             }
             onCancel:^(UIViewController *vc) {
                 CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Account enrollment cancelled"];
                 [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
                 [vc dismissViewControllerAnimated:YES completion:nil];
             }];

            [[self viewController] presentViewController:faceUserInitViewController animated:YES completion:nil];
        }
        else if([model faceAccountState] == ELTAccountStateUnknown) {

            [ElementSDKTransaction userSignInWithUserId:userid downloadMetaData:false successBlock:^(ELTAccount * account) {
                [self authAccount:command];
                /*CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"NEED_REAUTHENTICATION"];
                [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];*/

            } errorBlock:^(ELTTransactionResult errCode, NSError * err, NSString * msg) {
                NSString *res = [NSString stringWithFormat:@"ErrorCode:%u, Error:%@, Message:%@", errCode, err, msg];
                NSLog(@"%@", res);
                //[self authenticate:command withUserId:userid Eak:eak];
                CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:res];
                 [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
            }];
        }
        else if ([model faceAccountState] == ELTAccountStateAvailableButNotDownloaded) {
            //CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Download feature not available yet"];
            //[self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
            dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0), ^{
                ELTModelDownloadResult res = [model downloadFaceModel];
                if (res == ELTModelDownloadResultModelDownloaded) {
                    [self authAccount:command];
                    //[self authenticate:command withUserId:userid Eak:eak];
                }
                else {
                    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Download feature not available yet"];
                    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
                }
            });
        } else {
            CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Account not ready"];
            [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
        }
    }

}

- (void)getAccount:(CDVInvokedUrlCommand *)command {
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Get account failed"];
    NSString *userid = [command.arguments objectAtIndex:0];

    if ([userid length] == 0) {
        NSArray<ELTAccount *> *accounts = [ELTAccount allAccounts];
        NSMutableArray *models = [[NSMutableArray alloc] init];

        for (ELTAccount *model in accounts) {
            NSMutableDictionary *array = [[NSMutableDictionary alloc] init];
            NSString *fn = [NSString stringWithFormat:@"%@", model.firstName];
            NSString *ln = [NSString stringWithFormat:@"%@", model.lastName];
            NSString *em = [NSString stringWithFormat:@"%@", model.email];
            NSString *ei = [NSString stringWithFormat:@"%@", model.extraInfo];
            NSString *uid = [NSString stringWithFormat:@"%@", model.userId];
            NSString *acc = nil;
            if([model faceAccountState] == ELTAccountStateReady) {
              acc = @"Ready";
            }  else if ([model faceAccountState] == ELTAccountStateUserInitNeeded) {
              acc = @"User Init Needed";
            } else if ([model faceAccountState] == ELTAccountStateUnknown) {
              acc = @"State Unknown";
            }  else if ([model faceAccountState] == ELTAccountStateAvailableButNotDownloaded) {
              acc = @"Available but not downloaded";
            } else {
              acc = @"Not Ready";
            }
            [array setObject:fn forKey:@"firstName"];
            [array setObject:ln forKey:@"lastName"];
            [array setObject:em forKey:@"email"];
            [array setObject:ei forKey:@"extraInfo"];
            [array setObject:uid forKey:@"userId"];
            [array setObject:acc forKey:@"faceAccountState"];
            [models addObject:array];
        }
        NSData *jsonData = [NSJSONSerialization dataWithJSONObject:models options:NSJSONWritingPrettyPrinted error:nil];
        NSString *jsonString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
        NSLog(@"JSONString:\n%@\n---", jsonString);
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:jsonString];
    } else {
        ELTAccount *model = [ELTAccount getAccountByUserId:userid];
        NSMutableArray *models = [[NSMutableArray alloc] init];
        NSMutableDictionary *array = [[NSMutableDictionary alloc] init];
        NSString *fn = [NSString stringWithFormat:@"%@", model.firstName];
        NSString *ln = [NSString stringWithFormat:@"%@", model.lastName];
        NSString *em = [NSString stringWithFormat:@"%@", model.email];
        NSString *ei = [NSString stringWithFormat:@"%@", model.extraInfo];
        NSString *uid = [NSString stringWithFormat:@"%@", model.userId];
        NSString *acc = nil;
          if([model faceAccountState] == ELTAccountStateReady) {
            acc = @"Ready";
          }  else if ([model faceAccountState] == ELTAccountStateUserInitNeeded) {
            acc = @"User Init Needed";
          } else if ([model faceAccountState] == ELTAccountStateUnknown) {
            acc = @"State Unknown";
          }  else if ([model faceAccountState] == ELTAccountStateAvailableButNotDownloaded) {
            acc = @"Available but not downloaded";
          } else {
            acc = @"Not Ready";
          }
        [array setObject:fn forKey:@"firstName"];
        [array setObject:ln forKey:@"lastName"];
        [array setObject:em forKey:@"email"];
        [array setObject:ei forKey:@"extraInfo"];
        [array setObject:uid forKey:@"userId"];
        [array setObject:acc forKey:@"faceAccountState"];
        [models addObject:array];
        NSData *jsonData = [NSJSONSerialization dataWithJSONObject:models options:NSJSONWritingPrettyPrinted error:nil];
        NSString *jsonString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
        NSLog(@"JSONString:\n%@\n---", jsonString);
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:jsonString];
    }

    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];

}

- (void)deleteAccount:(CDVInvokedUrlCommand *)command {

    NSString *userid = [command.arguments objectAtIndex:0];

    //check if userid is not empty
    if([userid length] > 0) {
        if([userid  isEqual: @"DELETE_ALL"]) {
            [ELTAccount deleteAll];
            CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"All accounts deleted"];
            [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
        } else {
            //get account
            ELTAccount *account = [ELTAccount getAccountByUserId:userid];
            //delete from device
            [account deleteFromDevice];
            CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"Account deleted"];
            [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
        }
    }
    else {
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Error: Account not deleted"];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }
}

- (void)faceIdentification:(CDVInvokedUrlCommand *)command {
    NSString *eak = [command.arguments objectAtIndex:0];

    /* [self configuration:eak]; */
    //show face identification
    if([eak length] == 0) {
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"EAK is empty"];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }else {
        //face identification
        LocalFaceIdentificationViewController *faceId = [[LocalFaceIdentificationViewController alloc]  initWithIdentificationBlock:^(UIViewController * vc, ELTAccount * model) {
            NSMutableArray *models = [[NSMutableArray alloc] init];
            NSMutableDictionary *array = [[NSMutableDictionary alloc] init];
            NSString *fn = [NSString stringWithFormat:@"%@", model.firstName];
            NSString *ln = [NSString stringWithFormat:@"%@", model.lastName];
            NSString *em = [NSString stringWithFormat:@"%@", model.email];
            NSString *ei = [NSString stringWithFormat:@"%@", model.extraInfo];
            NSString *uid = [NSString stringWithFormat:@"%@", model.userId];
            NSString *acc = nil;
            if([model faceAccountState] == ELTAccountStateReady) {
                acc = @"Ready";
            }  else if ([model faceAccountState] == ELTAccountStateUserInitNeeded) {
                acc = @"User Init Needed";
            } else if ([model faceAccountState] == ELTAccountStateUnknown) {
                acc = @"State Unknown";
            }  else if ([model faceAccountState] == ELTAccountStateAvailableButNotDownloaded) {
                acc = @"Available but not downloaded";
            } else {
                acc = @"Not Ready";
            }
            [array setObject:fn forKey:@"firstName"];
            [array setObject:ln forKey:@"lastName"];
            [array setObject:em forKey:@"email"];
            [array setObject:ei forKey:@"extraInfo"];
            [array setObject:uid forKey:@"userId"];
            [array setObject:acc forKey:@"faceAccountState"];
            [models addObject:array];
            NSData *jsonData = [NSJSONSerialization dataWithJSONObject:models options:NSJSONWritingPrettyPrinted error:nil];
            NSString *jsonString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
            NSLog(@"JSONString:\n%@\n---", jsonString);
            CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:jsonString];
            [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
            [vc dismissViewControllerAnimated:YES completion:nil];
        } onCancel:^(UIViewController * vc) {
            CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Face Id cancelled"];
            [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
            [vc dismissViewControllerAnimated:YES completion:nil];
        }];
        [[self viewController] presentViewController:faceId animated:YES completion:nil];
    }
}
#endif

@end
