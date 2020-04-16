/********* ElementFaceWrapper.m Cordova Plugin Implementation *******/

#import <Cordova/CDV.h>

@interface ElementFaceWrapper : CDVPlugin

- (void)getSdkVersion:(CDVInvokedUrlCommand *)command;
- (void)enroll:(CDVInvokedUrlCommand *)command;
- (void)match:(CDVInvokedUrlCommand *)command;

@end
