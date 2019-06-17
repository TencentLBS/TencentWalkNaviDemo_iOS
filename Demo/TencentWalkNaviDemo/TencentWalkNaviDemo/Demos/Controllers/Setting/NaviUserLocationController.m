//
//  NaviUserLocationController.m
//  QMapKitDemo
//
//  Created by Tencent on 2018/8/8.
//  Copyright © 2018年 tencent. All rights reserved.
//

#import "NaviUserLocationController.h"

@implementation NaviUserLocationController

#pragma mark - Setup

- (void)setupUserLocationProportion
{
    self.walkNaviView.TWNWalkNaviFixUserLocationProportion3D = CGPointMake(0.5, 0.5);
    self.walkNaviView.TWNWalkNaviFixUserLocationProportion2D = CGPointMake(0.5, 0.5);
}

#pragma mark - Life Cycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [self setupUserLocationProportion];
}

@end
