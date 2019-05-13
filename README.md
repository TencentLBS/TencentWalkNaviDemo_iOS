# 一体化导航SDK

# 目录
- [工程配置](#ProjectConfig)
- [步行路径规划](#NaviPlan)
- [导航](#Navi)
- [导航设置](#NaviConfig)
- [获取导航数据](#NaviData)

### 介绍

腾讯步行导航 SDK 是一款针对步行在线导航的产品。该产品能够提供路径规划、模拟导航、实时导航、导航设置、自定义导航界面等功能，力求为用户提供更加人性化的导航服务。

一体化导航 SDK 下载请联系腾讯位置服务：[https://lbs.qq.com/contractus.html](https://lbs.qq.com/contractus.html)

<div id="ProjectConfig"></div>

### 工程配置

#### 1. 权限申请

(1) 若使用实时导航，则需要在` info.list` 中添加 NSLocationWhenInUseUsageDescription 和 NSLocationAlwaysUsageDescription 字段。

(2) 如果需要后台定位，需在 iOS 9.0及以后设置 allowBackgroundLocationUpdates 为 YES，此时必须保证 `TARGETS->Capabilities->Background Modes->Location updates` 处于选中状态。

#### 2. 引入 SDK

在 `TARGETS->Build Phases->Link Binary Libraries` 中添加步行导航 SDK `TWNNavigationKit.framework`，在 `TARGETS->Build Phases->Copy Bundle Resources` 中添加资源文件 `TencentNavigationKit.bundle`。
由于步行导航 SDK 依赖地图 SDK，还需要依照 [http://lbs.qq.com/ios_v1/guide-project-setup.html](http://lbs.qq.com/ios_v1/guide-project-setup.html) 添加地图 SDK。

#### 3. 申请和设置开发密钥

前往 [http://lbs.qq.com/console/mykey.html](http://lbs.qq.com/console/mykey.html) 申请开发密钥，在 QMapServices 的 APIKey 属性上设置。

```objc
[QMapServices sharedServices].APIKey = @"您的key";
```

<div id="NaviPlan"></div>

### 步行路径规划

#### 基本介绍

`TWNWalkNaviManager` 根据起点、终点为用户提供出行路线。方法：

```objc
- (TWNSearchTask *)searchNavigationRoutesWithRequest:(TWNWalkRouteSearchRequest *)request completion:(void (^)(TWNWalkRouteSearchResult * _Nullable result, NSError * _Nullable error))callback;
```

参数：

- request：路线规划请求，包括起点、终点
- callback：路线规划完成回调

`TWNWalkRouteSearchRequest` 包含下列属性：

- startPoint：起点
- destinationPoint：终点

路线规划的起终点类型为 `TWNWalkRouteSearchNaviPoi`，包含下列属性：

- coordinate：起终点的坐标
- floorName：起终点所在的楼层名称
- buildingID：起终点所在的建筑物 ID

**算路失败回调错误说明**

回调 NSError 的错误码：

- 1001：网络错误
- 2001：起终点相同
- 2002：起终点吸附相同
- 2003：起终点距离太短
- 2004：起终点距离太长
- 2005：起终点不合法
- 2006：不连通
- 2007：无效吸附
- 2008：算路超时
- 2999：服务器内部错误

#### 示例

```objc
// 初始化
self.walkManager = [[TWNWalkNaviManager alloc] init];

// 起点
TWNWalkRouteSearchNaviPoi *start = [[TWNWalkRouteSearchNaviPoi alloc] init];
{
	start.floorName  = @"F4";
	start.buildingID = @"1100005175";
	start.coordinate = CLLocationCoordinate2DMake(39.958548,116.288687);
}

// 终点    
TWNWalkRouteSearchNaviPoi *destination = [[TWNWalkRouteSearchNaviPoi alloc] init];
{
	destination.coordinate = CLLocationCoordinate2DMake(39.958348,116.282312);
}

// 请求
TWNWalkRouteSearchRequest *request = [[TWNWalkRouteSearchRequest alloc] init];
request.startPoint = start;
request.destinationPoint = destination;

[self.walkManager searchNavigationRoutesWithRequest:request completion:^(TWNWalkRouteSearchResult *result, NSError *error)
{
// 获取路线数据 result，包含多条线路。
// ...
}];
```

**步行路线**

路线规划获取的 `TWNWalkRouteSearchResult` 包含属性：

```
NSArray<TWNWalkRouteSearchPlan *> *routes
```


可以通过 `TWNWalkRouteSearchPlan` 获取各条线路的信息，TWNWalkRouteSearchPlan 包含以下属性：

- distance：总距离
- time：总预计时间
- startPoint：起点
- destinationPoint：终点
- pointsArray：路线点串
- stepsArray：路线分段
- renderArray：用于画线的分段


`TWNWalkRouteSearchStep` 是一条线路的分段信息，根据分段的类型可分为室外分段、室内分段、室内外连接处分段以及电梯分段，每一种分段都包含以下属性：

- fromIndex：起点索引
- toIndex：终点索引
- action：路线末尾动作
- roadName：路名
- roadLength：路长

路线末尾动作的类型为 `TWNWalkNavigationActionType`，可能的取值：

- TWNWalkNavigationActionType_UNKNOWN：未知
- TWNWalkNavigationActionType_AHEAD：直行
- TWNWalkNavigationActionType_LEFT_AHEAD：左前方转弯
- TWNWalkNavigationActionType_LEFT：左转
- TWNWalkNavigationActionType_LEFT_BACK：左后方转弯
- TWNWalkNavigationActionType_UTURN：调头
- TWNWalkNavigationActionType_RIGHT_BACK：右后方转弯
- TWNWalkNavigationActionType_RIGHT：右转
- TWNWalkNavigationActionType_RIGHT_AHEAD：右前方转弯
- TWNWalkNavigationActionType_ELEVATOR：电梯
- TWNWalkNavigationActionType_ESCALATOR：扶梯
- TWNWalkNavigationActionType_PASSENGER_ELEVATOR：客梯
- TWNWalkNavigationActionType_FREIGHT_ELEVATOR：货梯
- TWNWalkNavigationActionType_STAIRS：楼梯
- TWNWalkNavigationActionType_EXIT_BUILDING：出建筑物
- TWNWalkNavigationActionType_ENTER_BUILDING：进建筑物
- TWNWalkNavigationActionType_ARRIVED：到达

室外分段的类型为 `TWNWalkRouteSearchOutdoorStep`。

室内外连接处分段的类型为 `TWNWalkRouteSearchDoorStep`，还包含属性：

- doorInfo：门的信息

门的信息类型为 `TWNWalkRouteSearchDoorInfo`，包含以下属性：

- type：类型
- index：索引
- name：名称
- floorName：楼层名称
- buildingID：建筑物 ID
- buildingName：建筑物名称

`TWNWalkRouteSearchDoorType` 代表门的类型，可能的取值：

- TWNWalkRouteSearchDoorType_EXIT：出口
- TWNWalkRouteSearchDoorType_ENTER：入口

电梯分段的类型为 `TWNWalkRouteSearchElevatorStep`，还包含以下属性：

- type：类型
- buildingID：建筑物 ID
- startFloor：起始楼层
- startFloorName：起始楼层名称
- endFloor：终点楼层
- endFloorName：终点楼层名称

`TWNWalkRouteSearchElevatorType` 代表电梯的类型，可能的取值：

- TWNWalkRouteSearchElevatorType_UNKNOWN：未知
- TWNWalkRouteSearchElevatorType_ELEVATOR：电梯
- TWNWalkRouteSearchElevatorType_ESCALATOR：扶梯
- TWNWalkRouteSearchElevatorType_PASSENGER_ELEVATOR：客梯
- TWNWalkRouteSearchElevatorType_FREIGHT_ELEVATOR：货梯
- TWNWalkRouteSearchElevatorType_STAIRS：楼梯

室内分段的类型为 `TWNWalkRouteSearchIndoorStep`，还包含以下属性：

- buildingID：建筑物 ID
- floor：楼层
- floorName：楼层名称

`TWNWalkRouteSearchLine` 是一条线路用于画线的分段，它对室外分段和位于同一楼层的室内分段进行了拼接。根据类型可分为室外画线分段、室内画线分段以及电梯画线分段，每一种分段都包含以下属性：

- fromIndex：起点索引
- toIndex：终点索引

室外画线分段的类型为 `TWNWalkRouteSearchOutdoorLine`。

室内画线分段的类型为 `TWNWalkRouteSearchIndoorLine`，还包含以下属性：

- buildingID：建筑物 ID
- floor：楼层
- floorName：楼层名称

电梯画线分段的类型为 `TWNWalkRouteSearchElevatorLine`，还包含以下属性：

- type：类型
- buildingID：建筑物 ID
- startFloor：起始楼层
- startFloorName：起始楼层名称
- endFloor：终点楼层
- endFloorName：终点楼层名称

电梯画线分段的类型为 `TWNWalkRouteSearchElevatorType`，可能的取值见上。

<div id="Navi"></div>

### 导航

#### 基本介绍

腾讯步行导航 SDK 提供了实时导航的功能，实时导航是基于用户真实的定位信息来驱动的导航过程，路线规划完成后就可以开始导航。
方法：

- 开启实时导航：startWithIndex:(NSUInteger)index，路线规划成功后，根据索引 index 选择路线。
- 停止实时导航：stop。

**导航界面**

腾讯步行导航 SDK 提供了默认的导航界面 `TWNWalkNaviView`，包括导航面板，导航地图：

导航面板：

- 导航 Title：转向箭头、距离下一转弯时间的距离、下一条道路名称

导航地图：

- 地图
- 线路：蚯蚓线、当前道路名称、道路指示箭头
- 起点、终点 Marker
- 用户位置
- 罗盘

导航地图可以通过 `self.walkNaviView.naviMapView` 获取。

#### 使用说明

**1. 初始化**

导航过程中，步行导航 SDK 提供类 TWNWalkNaviView 用于显示导航界面，由步行导航控制类 TWNWalkNaviManager 设置导航状态回调，调用步行路线规划，启动/停止导航。

初始化过程如下：

```objc
self.walkManager = [[TWNWalkNaviManager alloc] init];
// self 需采用 TWNWalkNaviDelegate 协议，通过该协议获取导航过程中出现的状态或信息改变（如已偏航、到达等）
[self.walkManager registerNaviDelegate:self];

self.walkNaviView = [[TWNWalkNaviView alloc] initWithFrame:self.view.bounds];
// self 需采用 TWNWalkNaviViewDelegate 协议，通过该协议接收导航模式的变化
self.walkNaviView.delegate = self;

//注册采用 TWNWalkNaviUIDelegate 协议的对象，通过该协议获取导航面板所需数据，可注册多个对象接收数据更新
[self.walkManager registerUIDelegate: self.walkNaviView];
```

**2. 发起路线规划**

具体参考[步行路径规划](#NaviPlan)。

**3. 开始导航**

路线规划成功后，在回调中获取用于导航的线路。

```objc
[self.walkManager searchNavigationRoutesWithRequest:request completion:^(TWNWalkRouteSearchResult *result, NSError *error)
{
	if(error == nil)
	{
		// 获取线路数据后使用第一条线路进行导航
		[self.walkManager startWithIndex:0];
	}
}];
```

**4. 结束导航**

到达终点后会自动结束导航，导航过程中可以手动结束导航：

```objc
[self.walkManager stop];
```

非导航状态下，用户可以清除导航线路相关 UI，包括导航路线、用户位置等标注：（非导航状态下调用无效）

```objc
[self.walkNaviView clearAllRouteUI];
```

<div id="NaviConfig"></div>

### 导航设置

腾讯步行导航 SDK 提供导航模式等界面的动态设置，这些设置都是即时生效的。

#### 设施导航模式

通过 `TWNWalkNaviView` 的属性 mode 进行设置:

- TWNWalkNaviUIModeBounce：默认值，回弹模式，导航态中，用户使用手势操作地图后进入该模式，手势结束5秒后切换回之前的导航模式，直接设置为该模式不会被响应。
- TWNWalkNaviUIMode3DNavigation：3D 导航模式，该模式下，路线方向始终保持朝向屏幕上方，地图进入倒伏状态，进行旋转并动态调整缩放级别；
- TWNWalkNaviUIMode2DNorthUp：2D 地图朝北模式，该模式下，地图始终保持上北下南并动态调整缩放级别；
- TWNWalkNaviUIModeOverview：全览模式，地图保持上北下南，同时会始终展示整条导航路线；
- TWNWalkNaviUIModeRemainingOverview：剩余全览模式，地图保持上北下南，同时会始终展示剩余的导航路线。

设置过程：

```objc
self.walkNaviView.mode = TWNWalkNaviUIMode3DNavigation;
```

**设置导航面板**

用户可以设定默认导航面板是否显示。

```objc
// 设置是否隐藏默认导航面板
self.walkNaviView.hideNavigationPanel = NO;
```

**设置导航线路**

```objc
// 设置导航路线宽度，默认值为 10 point
self.walkNaviView.routeLineWidth = 12;
```

**设置用户位置**

```objc
// 设置 3D 导航模式下用户位置位于地图宽高的比例，默认 x 为 0.5，y 为 0.75，取值范围为 [0.25, 0.75]，超过则取默认值
self.walkNaviView.TWNWalkNaviFixUserLocationProportion3D = CGPointMake(0.5, 0.75);
// 设置 2D 导航模式下用户位置位于地图宽高的比例，默认 x 为 0.5，y 为 0.75，取值范围为 [0.25, 0.75]，超过则取默认值
self.walkNaviView.TWNWalkNaviFixUserLocationProportion2D = CGPointMake(0.5, 0.75);
```

<div id="NaviData"></div>

### 获取导航数据

#### 面板数据

用户若需要自定义导航面板，可以通过采用 `TWNWalkNaviUIDelegate` 协议获取面板数据，TWNWalkNaviManager 可同时注册多个对象接收更新：

```objc
// 获取导航数据，包括当前道路名称、当前道路剩余距离、当前速度、总剩余距离、总剩余时间、下一条道路名称等
- (void)walkNavigationManager:(TWNWalkNaviManager *)manager updateNavigationData:(TWNWalkNavigationData *)data;
```

注册过程为：

```objc
[self.walkManager registerUIDelegate:self.walkNaviView];
```

导航面板数据为 `TWNWalkNavigationData` 类型，包含以下属性：

- isIndoor：是否室内
- nextRoadName：下一段路名
- currentRoadName：当前路名
- nextDistanceLeft：到下一段的距离
- nextDistanceLeftString：到下一段的距离字符串
- nextDistanceLeftUnit：到下一段的距离单位
- totalDistanceLeft：剩余总距离
- totalDistanceLeftString：剩余总距离字符串
- totalDistanceLeftUnit：剩余总距离单位
- totalTimeLeft：剩余时间
- actionType：路口行为
- subActionType：路口行为的子项。0为无，1为上，2为下行
- intersectionActionString：路口行为字符串
- intersectionImage：路口箭头图片

路口行为的类型为 `TWNWalkNavigationActionType`，可能的取值见步行路径规划部分。

#### 导航模式

用户可以采用 `TWNWalkNaviViewDelegate` 协议获取导航模式改变信息：

```objc
// 获取导航模式改变回调
- (void)walkNaviView:(TWNWalkNaviView *)walkNaviView didChangeUIMode:(TWNWalkNaviUIMode)mode;
```

注册过程为：

```objc
self.walkNaviView.naviMapView.delegate = self;
```

#### 导航状态数据

用户可以采用 `TWNWalkNaviDelegate` 协议获取导航过程中出现的状态信息：

```objc
// 导航开始回调
- (void)walkNavigationManagerDidStart:(TWNWalkNaviManager *)manager;
// 导航结束回调
- (void)walkNavigationManagerDidStop:(TWNWalkNaviManager *)manager;

// 到达终点回调
- (void)walkNavigationManagerDidArriveDestination:(TWNWalkNaviManager *)manager;
// 偏航回调
- (void)walkNavigationManagerDidOffRoute:(TWNWalkNaviManager *)manager;

// 导航定位更新回调
- (void)walkNavigationManager:(TWNWalkNaviManager *)manager didUpdateLocation:(TWNLocation *)location;

// 重新算路请求开始回调
- (void)walkNavigationManagerdidStartRecaculateRoute:(TWNWalkNaviManager *)manager;
// 重新算路请求成功回调
- (void)walkNavigationManagerdidSuccessRecaculateRoute:(TWNWalkNaviManager *)manager result:(TWNWalkRouteSearchResult *)result;
// 重新算路请求失败回调
- (void)walkNavigationManagerdidFailRecaculateRoute:(TWNWalkNaviManager *)manager error:(NSError *)error;
```

注册过程为：

```objc
[self.walkManager registerNaviDelegate: self.walkNaviView];
```
