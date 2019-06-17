//
//  SimuNaviController.m
//  QMapKitDemo
//
//  Created by Tencent on 2018/8/7.
//  Copyright © 2018年 tencent. All rights reserved.
//

#import "SimuNaviController.h"

@interface SimuNaviController ()

@property (nonatomic, strong) TWNSimulateLocationManager *simulateLocationManager;

@end

@implementation SimuNaviController

#pragma mark - Simulate Navigation

- (void)setupSimulateNavigationWithRouteSearchResult:(TWNWalkRouteSearchResult *)result
{
    NSArray<TWNLocation *> *locationArray = [self locationArrayForNaviResult:result];
    
    self.simulateLocationManager = [[TWNSimulateLocationManager alloc] initWithLocationArray:locationArray timeInterval:0];
}

- (NSArray<TWNLocation *> *)locationArrayForNaviResult:(TWNWalkRouteSearchResult *)result
{
    NSMutableArray *array = [NSMutableArray array];
    NSArray<TWNCoordinatePoint *> *pointsArray = result.routes.firstObject.pointsArray;
    NSArray<TWNWalkRouteSearchLine *> *renderArray = result.routes.firstObject.renderArray;
    
    for (TWNWalkRouteSearchLine *line in renderArray)
    {
        for (int i = line.fromIndex; i <= line.toIndex; i++)
        {
            TWNLocation *naviLocation = [[TWNLocation alloc] init];
            CLLocationCoordinate2D coordinate = [pointsArray objectAtIndex:i].coordinate;
            
            naviLocation.location = [[CLLocation alloc] initWithLatitude:coordinate.latitude longitude:coordinate.longitude];
            
            if ([line isMemberOfClass:[TWNWalkRouteSearchIndoorLine class]])
            {
                TWNWalkRouteSearchIndoorLine *indoorLine = (TWNWalkRouteSearchIndoorLine *)line;
                
                naviLocation.buildingId = indoorLine.buildingID;
                naviLocation.floorName  = indoorLine.floorName;
            }
            else if ([line isMemberOfClass:[TWNWalkRouteSearchElevatorLine class]])
            {
                TWNWalkRouteSearchElevatorLine *elevatorLine = (TWNWalkRouteSearchElevatorLine *)line;
                
                naviLocation.buildingId = elevatorLine.buildingID;
                
                if (i == elevatorLine.fromIndex)
                {
                    naviLocation.floorName = elevatorLine.startFloorName;
                }
                else
                {
                    naviLocation.floorName = elevatorLine.endFloorName;
                }
            }
            
            [array addObject:naviLocation];
        }
    }
    
    return [[NSArray<TWNLocation *> alloc] initWithArray:array];
}

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
         
         // 模拟位置
         [weakSelf setupSimulateNavigationWithRouteSearchResult:result];
         
         // 开始模拟导航
         [weakSelf.walkNaviManager startWithIndex:0 locationEntry:weakSelf.simulateLocationManager];
     }];
}

#pragma mark - Life Cycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [self startNavigation];
}

@end
