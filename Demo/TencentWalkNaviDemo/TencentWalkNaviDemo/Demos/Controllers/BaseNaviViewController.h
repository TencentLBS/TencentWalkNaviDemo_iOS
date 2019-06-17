//
//  BaseNaviViewController.h
//  QMapKitDemo
//
//  Created by Tencent on 2018/8/6.
//  Copyright © 2018年 tencent. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <QMapKit/QMapKit.h>
#import <TencentLBS/TencentLBS.h>
#import <TWNNavigationKit/TWNNavigationKit.h>

@interface BaseNaviViewController : UIViewController
<TWNWalkNaviDelegate,
QMapViewDelegate,
TWNWalkNaviViewDelegate>

@property (nonatomic, strong, readonly) TWNWalkNaviView *walkNaviView;
@property (nonatomic, strong, readonly) TWNWalkNaviManager *walkNaviManager;

@end
