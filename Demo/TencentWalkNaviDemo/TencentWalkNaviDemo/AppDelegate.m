//
//  AppDelegate.m
//  TencentWalkNaviDemo
//
//  Created by Zhang Tian on 2019/5/10.
//  Copyright © 2019 Tencent. All rights reserved.
//

#import "AppDelegate.h"
#import "EntryViewController.h"

#import <QMapKit/QMapKit.h>
#import <TWNNavigationKit/TWNNavigationKit.h>

@interface AppDelegate ()

@end

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    
    // Configure API Key.
    [QMapServices sharedServices].APIKey = @"您的 Key";
    [TWNNaviServices sharedServices].APIKey = @"您的 Key";
    NSAssert([QMapServices sharedServices].APIKey.length != 0, @"Please configure API key before using QMapKit.framework");
    NSAssert([TWNNaviServices sharedServices].APIKey.length != 0, @"Please configure API key before using TWNNavigationKit.framework");
    
    EntryViewController *entry = [[EntryViewController alloc] init];
    
    UINavigationController* navigationController = [[UINavigationController alloc] initWithRootViewController:entry];
    self.window.rootViewController = navigationController;
    
    self.window.backgroundColor = [UIColor whiteColor];
    [self.window makeKeyAndVisible];
    
    return YES;
}

@end
