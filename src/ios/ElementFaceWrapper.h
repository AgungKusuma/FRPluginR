/********* ElementFaceWrapper.m Cordova Plugin Implementation *******/

#import <Cordova/CDV.h>

@interface ElementFaceWrapper : CDVPlugin

- (void)authenticate:(CDVInvokedUrlCommand *)command;
- (void)authenticateWithoutLiveness:(CDVInvokedUrlCommand *)command;
- (void)generateId:(CDVInvokedUrlCommand *)command;
- (void)createAccount:(CDVInvokedUrlCommand*)command;
- (void)configuration:(NSString *)eak;
- (void)config:(CDVInvokedUrlCommand *)command;
- (void)uploadModel:(CDVInvokedUrlCommand *)command;
- (void)authAccount:(CDVInvokedUrlCommand *)command;
- (void)getAccount:(CDVInvokedUrlCommand *)command;
- (void)deleteAccount:(CDVInvokedUrlCommand *)command;
- (void)faceIdentification:(CDVInvokedUrlCommand *)command;

@end
