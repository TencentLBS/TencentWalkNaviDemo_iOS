//
//  NaviRouteWidthController.m
//  QMapKitDemo
//
//  Created by Tencent on 2018/8/8.
//  Copyright © 2018年 tencent. All rights reserved.
//

#import "NaviRouteWidthController.h"

@interface NaviRouteWidthController()

@property UISlider *slider;

@end

@implementation NaviRouteWidthController

#pragma mark - Slider

- (void)addSlider
{
    self.slider = [[UISlider alloc] init];
    self.slider.minimumValue = 5;
    self.slider.maximumValue = 20;
    self.slider.value = 10;
    [self.slider addTarget:self action:@selector(changeWidth) forControlEvents:UIControlEventValueChanged];

    UIBarButtonItem *item = [[UIBarButtonItem alloc] initWithCustomView:self.slider];
    self.navigationItem.rightBarButtonItem = item;
}

-(void)changeWidth
{
    self.walkNaviView.routeLineWidth = self.slider.value;
}

#pragma mark - Life Cycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [self addSlider];
}

@end
