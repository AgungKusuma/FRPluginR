/*global cordova, module*/
var exec = require('cordova/exec');

var ElementSDK = {
    getSdkVersion: function (successCallback, errorCallback) {
        // TODO: you can change this string to match your needs
        /*
            usage:
            element.getSdkVersion(function(msg) { console.log('version is ' + msg); }, function(error) { console.log('error not supposed to be here'); });
        */
        successCallback("1.2.1");
    },
    match: function (id, successCallback, errorCallback) {
        cordova.exec(successCallback, errorCallback, "ElementFaceMatchingSDK", "match", [id]);
    },
    enroll: function(userId, name, successCallback, errorCallback) {
        cordova.exec(successCallback, errorCallback, "ElementFaceMatchingSDK", "enroll", [userId, name]);
    }
};

module.exports = ElementSDK;
