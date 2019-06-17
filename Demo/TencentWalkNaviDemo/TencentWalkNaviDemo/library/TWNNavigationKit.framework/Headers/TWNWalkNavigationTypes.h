//
//  TWNWalkNavigationTypes.h
//  TWNNavigationKit
//
//  Created by fan on 2019/4/6.
//  Copyright © 2019 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN


typedef NS_ENUM(NSUInteger, TWNWalkNavigationActionType)
{
    TWNWalkNavigationActionType_UNKNOWN                = 0,    // 未知
    TWNWalkNavigationActionType_AHEAD                  = 1,    // 直行
    TWNWalkNavigationActionType_LEFT_AHEAD             = 2,    // 左前方转弯
    TWNWalkNavigationActionType_LEFT                   = 3,    // 左转
    TWNWalkNavigationActionType_LEFT_BACK              = 4,    // 左后方转弯
    TWNWalkNavigationActionType_UTURN                  = 5,    // 调头
    TWNWalkNavigationActionType_RIGHT_BACK             = 6,    // 右后方转弯
    TWNWalkNavigationActionType_RIGHT                  = 7,    // 右转
    TWNWalkNavigationActionType_RIGHT_AHEAD            = 8,    // 右前方转弯
    TWNWalkNavigationActionType_ELEVATOR               = 9,    // 电梯
    TWNWalkNavigationActionType_ESCALATOR              = 10,   // 扶梯
    TWNWalkNavigationActionType_PASSENGER_ELEVATOR     = 11,   // 客梯
    TWNWalkNavigationActionType_FREIGHT_ELEVATOR       = 12,   // 货梯
    TWNWalkNavigationActionType_STAIRS                 = 13,   // 楼梯
    TWNWalkNavigationActionType_EXIT_BUILDING          = 16,   //出建筑物
    TWNWalkNavigationActionType_ENTER_BUILDING         = 17,    //进建筑物
    TWNWalkNavigationActionType_ARRIVED                = 1000    // 到达
};

NS_ASSUME_NONNULL_END
