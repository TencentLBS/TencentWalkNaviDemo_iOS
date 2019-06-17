//
//  TWNSimulateLocationManager.h
//  TWNNavigationKit
//
//  Created by Zhang Tian on 2019/3/19.
//  Copyright © 2019 Tencent. All rights reserved.
//

#import "TWNLocationEntryProtocol.h"

@interface TWNSimulateLocationManager : NSObject <TWNLocationEntry>

@property(nonatomic, weak) id <TWNLocationEntryDelegate> delegate;

- (id)initWithLocationArray:(NSArray<TWNLocation *> *)array timeInterval:(NSTimeInterval)ti;

- (void)startUpdatingLocation;

- (void)stopUpdatingLocation;

- (void)startUpdatingHeading;

- (void)stopUpdatingHeading;

@end
