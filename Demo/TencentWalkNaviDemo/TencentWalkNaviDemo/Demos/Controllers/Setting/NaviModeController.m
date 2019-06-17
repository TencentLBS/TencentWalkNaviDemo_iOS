//
//  NaviModeController.m
//  QMapKitDemo
//
//  Created by Tencent on 2018/8/8.
//  Copyright © 2018年 tencent. All rights reserved.
//

#import "NaviModeController.h"

@interface NaviModeController ()

@property UISegmentedControl *modeSegment;

@end

@implementation NaviModeController

#pragma mark - Segment

- (void)addModeSegment
{
    NSArray *modeArray = @[@"3D", @"2D", @"全览", @"剩余全览"];
    self.modeSegment = [[UISegmentedControl alloc] initWithItems:modeArray];
    self.modeSegment.selectedSegmentIndex = 0;
    [self.modeSegment addTarget:self action:@selector(changeMode) forControlEvents:UIControlEventValueChanged];
    
    self.navigationItem.titleView = self.modeSegment;
}

-(void)changeMode
{
    switch (self.modeSegment.selectedSegmentIndex)
    {
        case 0:
            self.walkNaviView.mode = TWNWalkNaviUIMode3DNavigation;
            break;
        case 1:
            self.walkNaviView.mode = TWNWalkNaviUIMode2DNorthUp;
            break;
        case 2:
            self.walkNaviView.mode = TWNWalkNaviUIModeOverview;
            break;
        case 3:
            self.walkNaviView.mode = TWNWalkNaviUIModeRemainingOverview;
            break;
        default:
            break;
    }
}

#pragma mark - Life Cycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [self addModeSegment];
}

@end
