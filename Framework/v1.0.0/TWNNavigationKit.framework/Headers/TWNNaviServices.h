//
//  TWNNaviServices.h
//  TWNNavigationKit
//
//  Created by Zhang Tian on 2019/3/12.
//  Copyright © 2019 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * @brief 导航服务类, 包含鉴权, 获取版本号等功能
 */
@interface TWNNaviServices : NSObject

/**
 * @brief 获取单例
 */
+ (TWNNaviServices *)sharedServices;

/**
 * @brief apikey 在官网申请的服务授权标识的key
 */
@property (nonatomic, copy) NSString *APIKey;

/**
 * @brief 获取导航SDK的版本号(1.0.0)
 */
- (NSString *)sdkVersion;

@end
