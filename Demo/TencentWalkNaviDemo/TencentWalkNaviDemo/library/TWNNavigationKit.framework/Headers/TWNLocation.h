//
//  TWNLocation.h
//  TWNNavigationKit
//
//  Created by Zhang Tian on 2019/3/18.
//  Copyright © 2019 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

/**
 * @brief  导航的定位信息.
 */
@interface TWNLocation : NSObject <NSCopying, NSSecureCoding>

/**
 * @brief  导航的原始定位的 CLLocation 信息.
 */
@property (nonatomic, strong) CLLocation *location;

/**
 * @brief  导航的原始定位的建筑物 Id.
 */
@property (nonatomic, copy) NSString *buildingId;

/**
 * @brief  导航的原始定位的楼层名称.
 */
@property (nonatomic, copy) NSString *floorName;

/**
 * @brief  吸附到导航路线上的经纬度信息. 若未成功吸附到路线上会返回 kCLLocationCoordinate2DInvalid.
 */
@property (nonatomic, readonly) CLLocationCoordinate2D matchedCoordinate;

/**
 * @brief  吸附到导航路线上的角度信息. 若未成功吸附到路线上会返回-1.
 */
@property (nonatomic, readonly) CLLocationDirection matchedCourse;

/**
 * @brief  吸附到导航路线上的位置索引. 若未成功吸附到路线上会返回-1.
 */
@property (nonatomic, readonly) NSInteger matchedIndex;

@end
