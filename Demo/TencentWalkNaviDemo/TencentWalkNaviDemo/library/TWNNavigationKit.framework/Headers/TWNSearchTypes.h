//
//  TWNSearchTypes.h
//  TWNNavigation
//
//  Created by 薛程 on 2018/3/5.
//  Copyright © 2018年 Tencent. All rights reserved.
//

#import <CoreLocation/CoreLocation.h>
#import <UIKit/UIKit.h>


#pragma mark - TWNSearchRequest

@class TWNSearchNaviPoi;

/**
 * @brief 路线规划的起终点类型
 */
@interface TWNSearchRequest : NSObject

/**
 * @brief 路线规划的起点
 */
@property (nonatomic, strong) TWNSearchNaviPoi   *startPoint;

/**
 * @brief 路线规划的终点
 */
@property (nonatomic, strong) TWNSearchNaviPoi   *destinationPoint;

@end


#pragma mark - TWNSearchNaviPoi

/**
 * @brief 路线规划的起终点类型
 */
@interface TWNSearchNaviPoi : NSObject

/**
 * @brief 地点的坐标.
 *
 * @note 途经点只支持coordinate
 */
@property (nonatomic, assign) CLLocationCoordinate2D coordinate;

/**
 * @brief 该地点的唯一标识. 有uid时优先使用uid
 */
@property (nonatomic,strong) NSString        *uid;

@end


#pragma mark - TWNRouteSearchResult

/**
 * @brief 路线规划的所有路线结果集合
 */
@interface TWNRouteSearchResult : NSObject

@end


#pragma mark - TWNSearchPlan

@class TWNSearchStep;

/**
 * @brief 路线规划的一条可选路线
 */
@interface TWNSearchPlan : NSObject

@end


#pragma mark - TWNSearchStep

/**
 * @brief 路线规划的一条可选路线的子线段
 */
@interface TWNSearchStep : NSObject

@end


