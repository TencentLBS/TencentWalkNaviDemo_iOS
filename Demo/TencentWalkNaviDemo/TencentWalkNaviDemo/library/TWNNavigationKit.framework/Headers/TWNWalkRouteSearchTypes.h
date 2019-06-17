//
//  TWNWalkRouteSearchTypes.h
//  TWNNavigationKit
//
//  Created by Zhang Tian on 2019/3/4.
//  Copyright © 2019 Tencent. All rights reserved.
//

#import "TWNSearchTypes.h"
#import "TWNSearchTask.h"
#import "TWNGeometry.h"
#import "TWNWalkNavigationTypes.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * @brief 路线规划的错误
 */
extern NSString *const TWNWalkRouteSearchErrorDomain;

typedef NS_ENUM(NSUInteger, TWNWalkRouteSearchErrorCode)
{
    TWNWalkRouteSearchErrorCode_NetworkError                = 1001,     // 网络错误
    TWNWalkRouteSearchErrorCode_SameStartDest               = 2001,     // 起终点相同
    TWNWalkRouteSearchErrorCode_SameStartDestAdsorption     = 2002,     // 起终点吸附相同
    TWNWalkRouteSearchErrorCode_StartDestTooClose           = 2003,     // 起终点距离太短
    TWNWalkRouteSearchErrorCode_StartDestTooFar             = 2004,     // 起终点距离太长
    TWNWalkRouteSearchErrorCode_StartDestIllegal            = 2005,     // 起终点不合法
    TWNWalkRouteSearchErrorCode_Unreachable                 = 2006,     // 不连通
    TWNWalkRouteSearchErrorCode_AdsorptionFailed            = 2007,     // 无效吸附
    TWNWalkRouteSearchErrorCode_SearchTimeout               = 2008,     // 算路超时
    TWNWalkRouteSearchErrorCode_InvalidKeyError             = 2009,     // 鉴权失败
    TWNWalkRouteSearchErrorCode_ServerError                 = 2999,     // 服务器内部错误
};

typedef NS_ENUM(NSUInteger, TWNWalkRouteSearchElevatorType)
{
    TWNWalkRouteSearchElevatorType_UNKNOWN              = 0,    // 未知
    TWNWalkRouteSearchElevatorType_ELEVATOR             = 1,    // 电梯
    TWNWalkRouteSearchElevatorType_ESCALATOR            = 2,    // 扶梯
    TWNWalkRouteSearchElevatorType_PASSENGER_ELEVATOR   = 3,    // 客梯
    TWNWalkRouteSearchElevatorType_FREIGHT_ELEVATOR     = 4,    // 货梯
    TWNWalkRouteSearchElevatorType_STAIRS               = 5,    // 楼梯
};

typedef NS_ENUM(NSUInteger, TWNWalkRouteSearchDoorType)
{
    TWNWalkRouteSearchDoorType_EXIT                     = 0,    // 出口
    TWNWalkRouteSearchDoorType_ENTER                    = 1,    // 入口
};

#pragma mark - TWNWalkRouteSearchRequest

@class TWNWalkRouteSearchNaviPoi;

/**
 * @brief 步行路线规划请求.
 */
@interface TWNWalkRouteSearchRequest : NSObject

/**
 * @brief 步行路线规划的起点.
 */
@property (nonatomic, strong) TWNWalkRouteSearchNaviPoi *startPoint;

/**
 * @brief 步行路线规划的终点.
 */
@property (nonatomic, strong) TWNWalkRouteSearchNaviPoi *destinationPoint;

@end


#pragma mark - TWNWalkRouteSearchNaviPoi

/**
 * @brief 步行路线规划的起终点类型.
 */
@interface TWNWalkRouteSearchNaviPoi : NSObject

/**
 * @brief 地点的坐标.
 *
 * @note 必须不为空.
 */
@property (nonatomic, assign) CLLocationCoordinate2D coordinate;

/**
 * @brief 室内 poi 的楼层名称.
 *
 * @note 为室内 poi 请求时不可为空.
 */
@property (nonatomic, copy, nullable) NSString *floorName;

/**
 * @brief 室内 poi 对应的建筑物 ID.
 *
 * @note 为室内 poi 请求时不可为空.
 */
@property (nonatomic, copy, nullable) NSString *buildingID;

/**
 * @brief 室内 poi 对应的检索词.
 *
 * @note 可以为空.
 */
@property (nonatomic, copy, nullable) NSString *word;

@end


#pragma mark - TWNWalkRouteSearchResult

@class TWNWalkRouteSearchPlan;

/**
 * @brief 步行路线规划的所有路线结果集合.
 */
@interface TWNWalkRouteSearchResult : TWNRouteSearchResult

/**
 * @brief 步行路线结果集合.
 */
@property (readonly, nonatomic, strong) NSArray<TWNWalkRouteSearchPlan *> *routes;

@end


#pragma mark - TWNWalkRouteSearchPlan

@class TWNWalkRouteSearchStep;
@class TWNWalkRouteSearchLine;

/**
 * @brief 步行路线规划的一条可选路线.
 */
@interface TWNWalkRouteSearchPlan : TWNSearchPlan

/**
 * @brief 总距离 单位: 分钟
 */
@property (readonly, nonatomic) int distance;

/**
 * @brief 总时间 单位: 米
 */
@property (readonly, nonatomic) int time;

/**
 * @brief 路线规划的起点
 */
@property (readonly, nonatomic, strong) TWNWalkRouteSearchNaviPoi *startPoint;

/**
 * @brief 路线规划的终点
 */
@property (readonly, nonatomic, strong) TWNWalkRouteSearchNaviPoi *destinationPoint;

/**
 * @brief 步行路线规划的路线点串.
 */
@property (readonly, nonatomic, strong) NSArray<TWNCoordinatePoint *> *pointsArray;

/**
 * @brief 步行路线规划的路线分段.
 */
@property (readonly, nonatomic, strong) NSArray<TWNWalkRouteSearchStep *> *stepsArray;

/**
 * @brief 步行路线规划用于画线的分段.
 */
@property (readonly, nonatomic, strong) NSArray<TWNWalkRouteSearchLine *> *renderArray;

@end


#pragma mark - TWNWalkRouteSearchStep

/**
 * @brief 步行路线规划的一条路线中的路线分段.
 */
@interface TWNWalkRouteSearchStep : TWNSearchStep

/**
 * @brief 该分段的起点索引.
 */
@property (readonly, nonatomic) int fromIndex;

/**
 * @brief 该分段的终点索引.
 */
@property (readonly, nonatomic) int toIndex;

/**
 * @brief 该分段的路线末尾动作.
 */
@property (readonly, nonatomic) TWNWalkNavigationActionType action;

/**
 * @brief 该分段的路名.
 */
@property (readonly, nonatomic, copy) NSString *roadName;

/**
 * @brief 该分段的路长.
 */
@property (readonly, nonatomic) int roadLength;

@end


/**
 * @brief 步行路线规划的一条路线中的室外路线分段.
 */
@interface TWNWalkRouteSearchOutdoorStep : TWNWalkRouteSearchStep

@end


/**
 * @brief 步行路线规划的一条路线中门的信息.
 */
@interface TWNWalkRouteSearchDoorInfo : NSObject

/**
 * @brief 该门的类型.
 */
@property (nonatomic, readonly) TWNWalkRouteSearchDoorType type;

/**
 * @brief 该门的索引.
 */
@property (nonatomic, readonly) int index;

/**
 * @brief 该门的名称.
 */
@property (readonly, nonatomic, copy) NSString *name;

/**
 * @brief 该门的楼层名称.
 */
@property (readonly, nonatomic, copy) NSString *floorName;

/**
 * @brief 该门对应的建筑物 ID.
 */
@property (readonly, nonatomic, copy) NSString *buildingID;

/**
 * @brief 该门对应的建筑物名称.
 */
@property (readonly, nonatomic, copy) NSString *buildingName;

@end


/**
 * @brief 步行路线规划的一条路线中的室内外连接处路线分段.
 */
@interface TWNWalkRouteSearchDoorStep : TWNWalkRouteSearchOutdoorStep

/**
 * @brief 该分段中门的信息.
 */
@property (readonly, nonatomic, strong) TWNWalkRouteSearchDoorInfo *doorInfo;

@end


/**
 * @brief 步行路线规划的一条路线中的电梯类路线分段.
 */
@interface TWNWalkRouteSearchElevatorStep : TWNWalkRouteSearchStep

/**
 * @brief 该分段的具体类型.
 */
@property (readonly, nonatomic) TWNWalkRouteSearchElevatorType type;

/**
 * @brief 该分段对应的建筑物 ID.
 */
@property (readonly, nonatomic, copy) NSString *buildingID;

/**
 * @brief 该分段的起始楼层.
 */
@property (readonly, nonatomic) int startFloor;

/**
 * @brief 该分段的起始楼层名称.
 */
@property (readonly, nonatomic, copy) NSString *startFloorName;

/**
 * @brief 该分段的终点楼层.
 */
@property (readonly, nonatomic) int endFloor;

/**
 * @brief 该分段的终点楼层名称.
 */
@property (readonly, nonatomic, copy) NSString *endFloorName;

@end


/**
 * @brief 步行路线规划的一条路线中的室内路线分段.
 */
@interface TWNWalkRouteSearchIndoorStep : TWNWalkRouteSearchStep

/**
 * @brief 该分段对应的建筑物 ID.
 */
@property (readonly, nonatomic, copy) NSString *buildingID;

/**
 * @brief 该分段的楼层.
 */
@property (readonly, nonatomic) int floor;

/**
 * @brief 该分段的楼层名称.
 */
@property (readonly, nonatomic, copy) NSString *floorName;

@end


#pragma mark - TWNWalkRouteSearchLine

/**
 * @brief 步行路线规划用于画线的分段.
 */
@interface TWNWalkRouteSearchLine : NSObject

/**
 * @brief 该分段的起点索引.
 */
@property (readonly, nonatomic) int fromIndex;

/**
 * @brief 该分段的终点索引.
 */
@property (readonly, nonatomic) int toIndex;

@end


/**
 * @brief 步行路线规划用于室外画线的分段.
 */
@interface TWNWalkRouteSearchOutdoorLine : TWNWalkRouteSearchLine

@end

/**
 * @brief 步行路线规划用于室内画线的分段.
 */
@interface TWNWalkRouteSearchIndoorLine : TWNWalkRouteSearchLine

/**
 * @brief 该分段对应的建筑物 ID.
 */
@property (readonly, nonatomic, copy) NSString *buildingID;

/**
 * @brief 该分段的楼层.
 */
@property (readonly, nonatomic) int floor;

/**
 * @brief 该分段的楼层名称.
 */
@property (readonly, nonatomic, copy) NSString *floorName;

@end


/**
 * @brief 步行路线规划用于电梯画线的分段.
 */
@interface TWNWalkRouteSearchElevatorLine : TWNWalkRouteSearchLine

/**
 * @brief 该分段的具体类型.
 */
@property (readonly, nonatomic) TWNWalkRouteSearchElevatorType type;

/**
 * @brief 该分段对应的建筑物 ID.
 */
@property (readonly, nonatomic, copy) NSString *buildingID;

/**
 * @brief 该分段的起始楼层.
 */
@property (readonly, nonatomic) int startFloor;

/**
 * @brief 该分段的起始楼层名称.
 */
@property (readonly, nonatomic, copy) NSString *startFloorName;

/**
 * @brief 该分段的终点楼层.
 */
@property (readonly, nonatomic) int endFloor;

/**
 * @brief 该分段的终点楼层名称.
 */
@property (readonly, nonatomic, copy) NSString *endFloorName;

@end

NS_ASSUME_NONNULL_END
