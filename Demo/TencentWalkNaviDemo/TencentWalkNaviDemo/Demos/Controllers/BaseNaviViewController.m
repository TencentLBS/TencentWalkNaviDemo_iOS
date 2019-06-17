//
//  BaseNaviViewController.m
//  QMapKitDemo
//
//  Created by Tencent on 2018/8/6.
//  Copyright © 2018年 tencent. All rights reserved.
//

#import "BaseNaviViewController.h"

@interface BaseNaviViewController()

@property (nonatomic, strong, readwrite) TWNWalkNaviView *walkNaviView;
@property (nonatomic, strong, readwrite) TWNWalkNaviManager *walkNaviManager;

@end

@implementation BaseNaviViewController

#pragma mark - Setup

- (void)setupWalkNaviManager
{
    self.walkNaviManager = [[TWNWalkNaviManager alloc] init];
    [self.walkNaviManager registerNaviDelegate:self];
    self.walkNaviManager.enableInternalTTS = YES;
}

- (void)setupWalkNaviView
{
    CGRect frame = CGRectMake(0,
                              0,
                              self.view.bounds.size.width,
                              self.view.bounds.size.height);
    
    self.walkNaviView = [[TWNWalkNaviView alloc] initWithFrame:frame];
    self.walkNaviView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    
    self.walkNaviView.delegate = self;
    self.walkNaviView.naviMapView.delegate = self;
    self.walkNaviView.mode = TWNWalkNaviUIMode3DNavigation;
    [self.walkNaviManager registerUIDelegate:self.walkNaviView];
    
    [self.view addSubview:self.walkNaviView];
}

- (void)setupConstraints
{
    [self.walkNaviView.leadingAnchor constraintEqualToAnchor:self.view.leadingAnchor].active = YES;
    [self.walkNaviView.trailingAnchor constraintEqualToAnchor:self.view.trailingAnchor].active = YES;
    [self.walkNaviView.topAnchor constraintEqualToAnchor:self.view.safeAreaLayoutGuide.topAnchor].active = YES;
    [self.walkNaviView.bottomAnchor constraintEqualToAnchor:self.view.safeAreaLayoutGuide.bottomAnchor].active = YES;
}

#pragma mark - Life Cycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [self setupWalkNaviManager];
    [self setupWalkNaviView];
    [self setupConstraints];
}

@end
