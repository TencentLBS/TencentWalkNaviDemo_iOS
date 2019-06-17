//
//  TWNGeometry.h
//  TWNNavigationKit
//
//  Created by Zhang Tian on 2019/3/5.
//  Copyright © 2019 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  @brief 位置坐标
 */
@interface TWNCoordinatePoint : NSObject

/**
 * @brief 经纬度坐标
 */
@property (nonatomic, assign) CLLocationCoordinate2D coordinate;

@end

NS_ASSUME_NONNULL_END
