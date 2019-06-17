//
//  NaviPanelController.m
//  QMapKitDemo
//
//  Created by Tencent on 2018/8/8.
//  Copyright © 2018年 tencent. All rights reserved.
//

#import "NaviPanelController.h"

@interface NaviPanelController ()

@property UISwitch *switcher;

@end

@implementation NaviPanelController

#pragma mark - Slider

- (void)addSwitch
{
    self.switcher = [[UISwitch alloc] init];

    UIBarButtonItem *item = [[UIBarButtonItem alloc] initWithCustomView:self.switcher];
    self.navigationItem.rightBarButtonItem = item;
    
    self.switcher.on = YES;
    [self.switcher addTarget:self action:@selector(changePanelVisibility) forControlEvents:UIControlEventValueChanged];
}

-(void)changePanelVisibility
{
    self.walkNaviView.hideNavigationPanel = !self.switcher.on;
}

#pragma mark - Life Cycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [self addSwitch];
}

@end
