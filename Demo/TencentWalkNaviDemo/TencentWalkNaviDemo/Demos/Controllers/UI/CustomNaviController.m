//
//  CustomNaviController.m
//  QMapKitDemo
//
//  Created by Tencent on 2018/8/8.
//  Copyright © 2018年 tencent. All rights reserved.
//

#import "CustomNaviController.h"

@interface CustomNaviController() <TWNWalkNaviUIDelegate>
{
    UILabel *_guideLabel;
    UIView *_backgroundView;
    UIImageView *_intersectionImageView;
}

@end

@implementation CustomNaviController

#pragma mark - TWNWalkNaviUIDelegate

- (void)walkNavigationManager:(TWNWalkNaviManager *)manager updateNavigationData:(TWNWalkNavigationData *)data
{
    _intersectionImageView.image = data.intersectionImage;
    _guideLabel.text = [NSString stringWithFormat:@"%@%@后    %@", data.nextDistanceLeftString, data.nextDistanceLeftUnit, data.intersectionActionString];
}

#pragma mark - Setup

- (void)setupSelf
{
    self.walkNaviView.hideNavigationPanel = YES;
    [self.walkNaviManager registerUIDelegate:self];
}

- (void)setupViews
{
    _backgroundView = [[UIView alloc] init];
    {
        _backgroundView.backgroundColor = UIColor.lightGrayColor;
        _backgroundView.translatesAutoresizingMaskIntoConstraints = NO;
    }
    [self.view addSubview:_backgroundView];
    
    _guideLabel = [[UILabel alloc] init];
    {
        _guideLabel.textColor = UIColor.whiteColor;
        _guideLabel.font = [UIFont boldSystemFontOfSize:22];
        _guideLabel.translatesAutoresizingMaskIntoConstraints = NO;
    }
    [_backgroundView addSubview:_guideLabel];
    
    _intersectionImageView = [[UIImageView alloc] init];
    {
        _intersectionImageView.contentMode = UIViewContentModeScaleAspectFit;
        _intersectionImageView.translatesAutoresizingMaskIntoConstraints = NO;
    }
    [_backgroundView addSubview:_intersectionImageView];
}

- (void)setupConstraints
{
    [_backgroundView.heightAnchor constraintEqualToConstant:100].active = YES;
    [_backgroundView.topAnchor constraintEqualToAnchor:self.view.topAnchor].active = YES;
    [_backgroundView.leadingAnchor constraintEqualToAnchor:self.view.leadingAnchor].active = YES;
    [_backgroundView.trailingAnchor constraintEqualToAnchor:self.view.trailingAnchor].active = YES;
    
    [_intersectionImageView.heightAnchor constraintEqualToConstant:80].active = YES;
    [_intersectionImageView.widthAnchor constraintEqualToConstant:80].active = YES;
    [_intersectionImageView.centerYAnchor constraintEqualToAnchor:_backgroundView.centerYAnchor].active = YES;
    [_intersectionImageView.leadingAnchor constraintEqualToAnchor:_backgroundView.leadingAnchor constant:10].active = YES;
    
    [_guideLabel.centerYAnchor constraintEqualToAnchor:_backgroundView.centerYAnchor].active = YES;
    [_guideLabel.leadingAnchor constraintEqualToAnchor:_intersectionImageView.trailingAnchor constant:40].active = YES;
}

#pragma mark - Life Cycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [self setupSelf];
    [self setupViews];
    [self setupConstraints];
}

@end
