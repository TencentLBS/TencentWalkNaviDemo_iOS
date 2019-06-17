//
//  TWNWalkNaviManager.h
//  TWNNavigationKit
//
//  Created by Zhang Tian on 2019/3/5.
//  Copyright © 2019 Tencent. All rights reserved.
//

#import "TWNBaseNaviManager.h"

#import "TWNNaviTTS.h"
#import "TWNHeading.h"
#import "TWNLocation.h"
#import "TWNWalkNavigationData.h"
#import "TWNWalkRouteSearchTypes.h"
#import "TWNLocationEntryProtocol.h"

NS_ASSUME_NONNULL_BEGIN

@class TWNWalkNaviManager;

/**
 * @brief  导航UI事件回调. 用于通知用户导航过程中出现的UI信息改变.
 */
@protocol TWNWalkNaviUIDelegate<NSObject>

@optional

/**
 * @brief  导航数据回调.
 * @param manager manager
 * @param data 导航数据
 */
- (void)walkNavigationManager:(TWNWalkNaviManager *)manager updateNavigationData:(TWNWalkNavigationData *)data;

@end

/**
 * @brief  导航事件回调. 用于通知用户导航过程中出现的状态或信息改变.
 */
@protocol TWNWalkNaviDelegate<NSObject>

@optional

/**
 * @brief  导航开始.
 * @param manager manager
 */
- (void)walkNavigationManagerDidStart:(TWNWalkNaviManager *)manager;

/**
 * @brief  导航结束.
 * @param manager manager
 */
- (void)walkNavigationManagerDidStop:(TWNWalkNaviManager *)manager;

/**
 * @brief  获取TTS回调.
 * @param manager manager
 * @param naviTTS tts信息
 */
- (void)walkNavigationManager:(TWNWalkNaviManager *)manager broadcastTTS:(TWNNaviTTS *)naviTTS;

/**
 * @brief  获取到达终点回调.
 * @param manager manager
 */
- (void)walkNavigationManagerDidArriveDestination:(TWNWalkNaviManager *)manager;

/**
 * @brief  获取偏航回调.
 * @param manager manager
 */
- (void)walkNavigationManagerDidOffRoute:(TWNWalkNaviManager *)manager;

/**
 * @brief  获取导航定位更新回调.
 * @param manager manager
 * @param location 定位信息
 */
- (void)walkNavigationManager:(TWNWalkNaviManager *)manager didUpdateLocation:(TWNLocation *)location;

/**
 * @brief  获取重新算路请求开始回调.
 * @param manager manager
 */
- (void)walkNavigationManagerdidStartRecaculateRoute:(TWNWalkNaviManager *)manager;

/**
 * @brief  获取重新算路请求成功回调.
 * @param manager manager
 * @param result 重新算路成功结果
 */
- (void)walkNavigationManagerdidSuccessRecaculateRoute:(TWNWalkNaviManager *)manager result:(TWNWalkRouteSearchResult *)result;

/**
 * @brief  获取重新算路请求失败回调.
 * @param manager manager
 * @param error 重新算路失败原因
 */
- (void)walkNavigationManagerdidFailRecaculateRoute:(TWNWalkNaviManager *)manager error:(NSError *)error;

@end

/**
 * @brief  步行导航控制类. 用于设置导航状态回调、调用步行路线规划、启动/停止导航等.
 */
@interface TWNWalkNaviManager : TWNBaseNaviManager

/**
 * @brief  注册对象接收导航事件变化.
 *  注册后可通过该协议获取导航过程中出现的状态或信息改变(如已偏航、到达终点等).
 *  导航事件变化采用广播形式,可同时注册多个对象接收事件变化.
 * @param naviDelegate 接收导航事件变化的对象
 */
- (void)registerNaviDelegate:(nullable id <TWNWalkNaviDelegate>)naviDelegate;

/**
 * @brief  注销对象接收导航事件变化.
 * @param naviDelegate naviDelegate
 */
- (void)unregisterNaviDelegate:(nullable id <TWNWalkNaviDelegate>)naviDelegate;

/**
 * @brief  注销所有对象接收导航事件变化.
 */
- (void)unregisterAllNaviDelegates;

/**
 * @brief  注册对象接收导航UI数据更新.
 *  注册后可通过该协议获取导航面板所需数据(如道路名称、剩余距离等).
 *  使用导航SDK提供的默认导航界面TWNWalkNaviView(其中包括地图和导航面板)需要将其通过本方法注册.
 *  若需要自定义导航面板,则可通过本方法注册从而接收导航UI数据更新.
 *  导航UI数据更新采用广播形式,可同时注册多个对象接收数据更新.
 * @param UIDelegate 接收导航UI数据更新的对象
 */
- (void)registerUIDelegate:(nullable id <TWNWalkNaviUIDelegate>)UIDelegate;

/**
 * @brief  注销对象接收导航UI数据更新.
 * @param UIDelegate naviDelegate
 */
- (void)unregisterUIDelegate:(nullable id <TWNWalkNaviUIDelegate>)UIDelegate;

/**
 * @brief  注销所有对象接收导航UI数据更新.
 */
- (void)unregisterAllUIDelegates;

/**
 *  @brief  导航开始前最后的位置信息. 设置该字段可提升真实导航开始时的定位速度及准确性, 需在发起导航前设置. 定位经纬度需为GCJ02类型.
 */
@property (nonatomic, strong, nullable) TWNLocation *lastLocationBeforeNavigation;

/**
 *  @brief  是否开启内置导航语音播报功能. 开启后无法通过TTS回调控制播报状态. 默认关闭.
 */
@property (nonatomic, assign) BOOL enableInternalTTS;

/**
 *  @brief  启动导航, 需要在步行导航路线规划成功后进行.
 *  @param index 路线索引, 与路线规划返回的路线结果顺序一致.
 */
- (void)startWithIndex:(NSUInteger)index;

/**
 *  @brief  根据自定义数据源启动导航. 需要在步行导航路线规划成功后进行.
 *  @param index 路线索引, 与路线规划返回的路线结果顺序一致.
 *  @param locationEntry 用户自定义的定位数据源入口.
 */
- (void)startWithIndex:(NSUInteger)index locationEntry:(id <TWNLocationEntry>)locationEntry;

/**
 *  @brief  结束导航.
 */
- (void)stop;

/**
 * @brief  发起步行导航路线规划. 通过路线规划请求配置起点、终点.
 * @param request 路线规划请求
 * @param callback 路线规划完成回调
 *
 * @return 路线规划任务
 */
- (TWNSearchTask *)searchNavigationRoutesWithRequest:(TWNWalkRouteSearchRequest *)request completion:(void (^)(TWNWalkRouteSearchResult * _Nullable result, NSError * _Nullable error))callback;

@end

NS_ASSUME_NONNULL_END
