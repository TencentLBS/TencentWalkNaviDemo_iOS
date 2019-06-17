//
//  EntryData.m
//  QMapKitDemoNew
//
//  Created by Tencent on 17/5/11.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "EntryData.h"
#import <QMapKit/QMapKit.h>

@implementation Cell

@end

@implementation Section

@end

@implementation EntryData

+ (instancetype)constructDefaultEntryData
{
    EntryData *entry = [[EntryData alloc] init];
    entry.title = @"Navigation Demo";
    NSMutableArray<Section *> *sectionArray = [NSMutableArray array];
    entry.sections = sectionArray;
    
    // Navi Section.
    {
        Section *section = [[Section alloc] init];
        section.title = @"基础导航";
        NSMutableArray<Cell *> *cellArray = [NSMutableArray array];
        section.cells = cellArray;
    
        [sectionArray addObject:section];
        
        // 基础导航
        {
            Cell *cell = [[Cell alloc] init];
            cell.title = @"导航算路";
            cell.controllerClassName = @"NaviSearchRoutes";
            [cellArray addObject:cell];
            
            cell = [[Cell alloc] init];
            cell.title = @"实时导航";
            cell.controllerClassName = @"RealNaviController";
            [cellArray addObject:cell];
            
            cell = [[Cell alloc] init];
            cell.title = @"模拟导航";
            cell.controllerClassName = @"SimuNaviController";
            [cellArray addObject:cell];
        }
    }
    
    {
        Section *section = [[Section alloc] init];
        section.title = @"导航配置设置";
        NSMutableArray<Cell *> *cellArray = [NSMutableArray array];
        section.cells = cellArray;
        
        [sectionArray addObject:section];
        
        {
            Cell *cell = [[Cell alloc] init];
            cell.title = @"设置导航模式";
            cell.controllerClassName = @"NaviModeController";
            [cellArray addObject:cell];
            
            cell = [[Cell alloc] init];
            cell.title = @"设置车标位置";
            cell.controllerClassName = @"NaviUserLocationController";
            [cellArray addObject:cell];
            
            cell = [[Cell alloc] init];
            cell.title = @"设置路线宽度";
            cell.controllerClassName = @"NaviRouteWidthController";
            [cellArray addObject:cell];
        }
    }
    
    {
        Section *section = [[Section alloc] init];
        section.title = @"导航 UI";
        NSMutableArray<Cell *> *cellArray = [NSMutableArray array];
        section.cells = cellArray;
        
        [sectionArray addObject:section];
        

        {
            Cell *cell = [[Cell alloc] init];
            cell.title = @"隐藏导航面板";
            cell.controllerClassName = @"NaviPanelController";
            [cellArray addObject:cell];

            
            cell = [[Cell alloc] init];
            cell.title = @"自定义导航面板";
            cell.controllerClassName = @"CustomNaviController";
            [cellArray addObject:cell];
        }
    }
    
    return entry;
}

@end
