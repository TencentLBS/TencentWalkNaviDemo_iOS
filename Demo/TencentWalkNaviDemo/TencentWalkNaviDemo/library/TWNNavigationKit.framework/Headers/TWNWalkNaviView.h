//
//  TWNWalkNaviView.h
//  TWNNavigationKit
//
//  Created by fan on 2019/3/26.
//  Copyright © 2019 Tencent. All rights reserved.
//

#import "TWNBaseNaviView.h"
#import "TWNWalkNaviManager.h"
#import "TWNUserLocationPresentation.h"
#import <QMapKit/QMapKit.h>

NS_ASSUME_NONNULL_BEGIN


typedef enum _TWNWalkNaviUIMode
{
    TWNWalkNaviUIModeBounce             = 0,    ///< 回弹模式
    TWNWalkNaviUIMode3DNavigation       = 1,    ///< 3D 导航模式
    TWNWalkNaviUIMode2DNorthUp          = 2,    ///< 2D 北朝上模式
    TWNWalkNaviUIModeOverview           = 3,    ///< 全览模式
    TWNWalkNaviUIModeRemainingOverview  = 4     ///< 剩余全览模式
} TWNWalkNaviUIMode;

@class TWNWalkNaviView;


/**
 *  @brief 驾车导航UI类回调. 用于显示默认导航界面(包括地图和导航面板).
 */
@protocol TWNWalkNaviViewDelegate <NSObject>

@optional

/**
 * @brief  获取导航模式改变回调.
 * @param walkNaviView view
 * @param mode 导航模式
 */
- (void)walkNaviView:(TWNWalkNaviView *)walkNaviView didChangeUIMode:(TWNWalkNaviUIMode)mode;

@end


@interface TWNWalkNaviView : TWNBaseNaviView <TWNWalkNaviUIDelegate>

/**
 *  @brief  TWNWalkNaviView的回调,用于接收导航模式、日夜状态等变化.
 */
@property (nonatomic, weak) id <TWNWalkNaviViewDelegate> delegate;


/**
 *  @brief  是否隐藏默认导航面板, 默认为不隐藏默认导航面板.
 */
@property (nonatomic, assign) BOOL hideNavigationPanel;
/**
 *  @brief  导航模式. 导航模式包括3D导航模式、2D地图朝北、全览和剩余全览4种模式. 默认为3D导航模式.
 *          回弹模式在导航状态下使用手势操作地图时被触发,会在手势操作结束后一段时间切换回之前的导航模式.
 *          该时间可由bounceTime设定,默认回弹时间为5秒.直接设置导航模式为回弹模式将不会被响应.
 */
@property (nonatomic, assign) TWNWalkNaviUIMode mode;

/**
 *  @brief  回弹模式的回弹时间，单位为秒，需大于0. 默认为5秒.
 */
@property (nonatomic, assign) NSUInteger bounceTime;

/**
 *  @brief  3D导航时用户位置位置在地图上位置的比例 默认值为(0.5,0.75).
 *  x取值范围为[0.25,0.75] 表示从屏幕左边起的宽度比例.
 *  y取值范围为[0.25,0.75] 表示从屏幕上边起的高度比例.
 *  若设置值不在区间内则使用默认值.
 */
@property (nonatomic, assign) CGPoint TWNWalkNaviFixUserLocationProportion3D;

/**
 *  @brief  2D导航时用户位置位置在地图上位置的比例 默认值为(0.5,0.75).
 *  x取值范围为[0.25,0.75] 表示从屏幕左边起的宽度比例.
 *  y取值范围为[0.25,0.75] 表示从屏幕上边起的高度比例.
 *  若设置值不在区间内则使用默认值.
 */
@property (nonatomic, assign) CGPoint TWNWalkNaviFixUserLocationProportion2D;

/**
 *  @brief  设置地图绘制路线的线宽. 默认值为10 point.
 */
@property (nonatomic, assign) NSUInteger routeLineWidth;

/**
 *  @brief  设置全览和剩余全览模式下导航路线显示区域距离地图四周的边距.
 *          当在walkNaviView上自定义显示元素时, 为避免与导航路线相互遮挡, 可调用该接口调整导航路线显示区域范围.
 *          默认值为(40,10,20,10), 使得全览和剩余全览模式下导航路线四周有部分留白.
 */
@property (nonatomic, assign) UIEdgeInsets externalEdgeInsets;

/**
 * @brief  panel顶部空隙距离, 单位为px. 默认为全屏状态下避开状态栏. 取值范围为[0,100].
 */
@property (nonatomic, assign) NSUInteger panelTopGap;

/**
 *  @brief  内部持有的地图实例,可以通过该地图实例接收地图事件回调、添加annotation、操作地图视野等.
 *
 * 导航中内部也会使用此地图实例，因此对地图的操作有可能会影响导航效果的显示。
 */
@property (nonatomic, strong, readonly) QMapView *naviMapView;

/**
 *  @brief  清除路线相关UI.该方法用于非导航状态下清除路线相关UI,包括导航路线、用户位置图标、动态添加的限速/指示标识等. 导航过程中调用该方法无效.
 */
- (void)clearAllRouteUI;

/**
 *  @brief  设置显示/隐藏用户位置罗盘.该方法用于导航状态下控制显示/隐藏用户位置罗盘. 非导航过程中调用该方法无效.
 *          用户位置罗盘在3D导航模式模式下会默认显示, 在2D地图朝北、全览模式和剩余全览模式下会默认隐藏.
 */
- (void)setUserLocationCompassEnabled:(BOOL)enabled;

/**
 *  @brief  配置用户位置UI属性. 该方法用于配置导航时用户位置UI属性, 非导航时进行配置会在导航发起后生效, 导航过程中进行配置即时生效.
 */
- (void)configUserLocationPresentation:(TWNUserLocationPresentation *)presentation;

@end

NS_ASSUME_NONNULL_END
