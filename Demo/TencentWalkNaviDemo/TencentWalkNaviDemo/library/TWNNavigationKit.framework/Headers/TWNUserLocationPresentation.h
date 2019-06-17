//
//  TWNUserLocationPresentation.h
//  TWNNavigationKit
//
//  Created by 薛程 on 2019/2/28.
//  Copyright © 2019年 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/**
 *  @brief  用户位置UI属性.
 */
@interface TWNUserLocationPresentation : NSObject

/**
 *  @brief  设置用户位置罗盘图标. 设置为nil则使用默认资源. 默认值为nil.
 */
@property (nonatomic, strong, nullable) UIImage *compassIcon;

/**
 *  @brief  设置用户位置图标. 设置为nil则使用默认资源. 默认值为nil.
 */
@property (nonatomic, strong, nullable) UIImage *userIcon;

@end
