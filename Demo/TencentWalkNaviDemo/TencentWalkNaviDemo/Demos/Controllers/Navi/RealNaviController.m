//
//  RealNaviController.m
//  QMapKitDemo
//
//  Created by Tencent on 2018/8/7.
//  Copyright © 2018年 tencent. All rights reserved.
//

#import "RealNaviController.h"

@interface RealNaviController ()

@end

@implementation RealNaviController

#pragma mark - Navigation

- (void)startNavigation
{
    TWNWalkRouteSearchNaviPoi *startPoint = [[TWNWalkRouteSearchNaviPoi alloc] init];
    startPoint.coordinate = CLLocationCoordinate2DMake(39.979602, 116.313972);
    startPoint.floorName = @"F3";
    startPoint.buildingID = @"11000023805";
    
    TWNWalkRouteSearchNaviPoi *destinationPoint = [[TWNWalkRouteSearchNaviPoi alloc] init];
    destinationPoint.coordinate = CLLocationCoordinate2DMake(39.958553, 116.288640);
    destinationPoint.floorName = @"F3";
    destinationPoint.buildingID = @"1100005175";
    
    TWNWalkRouteSearchRequest *searchRequest = [[TWNWalkRouteSearchRequest alloc] init];
    
    searchRequest.startPoint = startPoint;
    searchRequest.destinationPoint = destinationPoint;
    
    __weak __typeof(self) weakSelf = self;
    [self.walkNaviManager searchNavigationRoutesWithRequest:searchRequest completion:^(TWNWalkRouteSearchResult * _Nullable result, NSError * _Nullable error)
     {
         if (error != nil)
         {
             return;
         }
         
         // 开始导航
         [weakSelf.walkNaviManager startWithIndex:0];
     }];
}

#pragma mark - Life Cycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [self startNavigation];
}

@end
