//
//  TWNLocationEntryProtocol.h
//  TWNNavigationKit
//
//  Created by Zhang Tian on 2019/3/19.
//  Copyright © 2019 Tencent. All rights reserved.
//

#import "TWNHeading.h"
#import "TWNLocation.h"

@protocol TWNLocationEntryDelegate;

/**
 * @brief  定位协议. 定义定位入口需要实现的属性及方法.
 */
@protocol TWNLocationEntry <NSObject>

@required

/**
 *  @brief  回调
 */
@property(nonatomic, weak) id<TWNLocationEntryDelegate> delegate;

/**
 *  @brief  启动定位更新.
 */
- (void)startUpdatingLocation;

/**
 *  @brief  结束定位更新.
 */
- (void)stopUpdatingLocation;

/**
 *  @brief  启动Heading更新.
 */
- (void)startUpdatingHeading;

/**
 *  @brief  停止Heading更新.
 */
- (void)stopUpdatingHeading;

@end

/**
 * @brief  定位协议. 用于通知导航manager导航过程中出现的定位信息改变.
 */
@protocol TWNLocationEntryDelegate <NSObject>

@optional

/**
 * @brief  定位位置回调.
 * @param entry entry
 * @param location 定位数据.
 */
- (void)locationEntry:(id<TWNLocationEntry>)entry didUpdateLocation:(TWNLocation *)location;

/**
 * @brief  定位发生错误.
 * @param entry entry
 * @param error 错误
 */
- (void)locationEntry:(id<TWNLocationEntry>)entry didFailWithError:(NSError *)error;

/**
 * @brief  定位Heading回调.
 * @param entry entry
 * @param heading Heading数据.
 */
- (void)locationEntry:(id<TWNLocationEntry>)entry didUpdateHeading:(TWNHeading *)heading;

@end
