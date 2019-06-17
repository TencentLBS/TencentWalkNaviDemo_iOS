//
//  TWNHeading.h
//  TWNNavigationKit
//
//  Created by fan on 2019/4/16.
//  Copyright © 2019 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

NS_ASSUME_NONNULL_BEGIN

@interface TWNHeading : NSObject

/**
 * @brief  导航的原始定位的 CLHeading 信息.
 */
@property (nonatomic, strong) CLHeading *heading;

@end

NS_ASSUME_NONNULL_END
