//
//  TWNWalkNavigationData.h
//  TWNNavigationKit
//
//  Created by Zhang Tian on 2019/3/21.
//  Copyright © 2019 Tencent. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "TWNWalkNavigationTypes.h"

/**
 *  @brief 导航面板数据类.包含路名，距离，时间等数据.
 */
@interface TWNWalkNavigationData : NSObject

/**
 * @brief 是否室内
 */
@property (nonatomic) BOOL isIndoor;

#pragma mark Road Name

/**
 * @brief 下一段路名
 */
@property (nonatomic, strong) NSString *nextRoadName;

/**
 * @brief 当前路名
 */
@property (nonatomic, strong) NSString *currentRoadName;


#pragma mark Distance

/**
 * @brief 到下一段的距离 单位:米
 */
@property (nonatomic) int nextDistanceLeft;

/**
 * @brief 到下一段的距离字符串 无单位
 */
@property (nonatomic, strong) NSString *nextDistanceLeftString;

/**
 * @brief 到下一段的距离单位
 */
@property (nonatomic, strong) NSString *nextDistanceLeftUnit;

/**
 * @brief 剩余总距离 单位:米
 */
@property (nonatomic) int totalDistanceLeft;

/**
 * @brief 剩余总距离字符串 无单位
 */
@property (nonatomic, strong) NSString *totalDistanceLeftString;

/**
 * @brief 剩余总距离单位
 */
@property (nonatomic, strong) NSString *totalDistanceLeftUnit;


#pragma mark Time

/**
 * @brief 剩余时间 单位:分钟
 */
@property (nonatomic) int totalTimeLeft;


#pragma mark Intersection Image

/**
 * @brief 路口行为。如右转
 */
@property (nonatomic) TWNWalkNavigationActionType actionType;

/**
 * @brief 路口行为的子项。0为无, 1:上行, 2:下行
 */
@property (nonatomic) int subActionType;

/**
 * @brief 路口行为。如右转
 */
@property (nonatomic, strong) NSString *intersectionActionString;

/**
 * @brief 路口箭头图片
 */
@property (nonatomic, strong) UIImage *intersectionImage;

#pragma mark Current Point
/**
 * @brief 关键点诱导信息。如在XX店铺附近
 */
@property (nonatomic, strong) NSString *keyPointString;

@end
