//
//  NotificationCenterName.swift
//  TableviewAndWebviewSample
//
//  Created by Osamu Nishiyama on 2015/08/17.
//  Copyright (c) 2015年 ever sense. All rights reserved.
//

import Foundation

enum NotificationCenterName {
    case ChangedType
    
    func toString() -> String {
        switch self {
        case .ChangedType:
            return "ChangedType"
        }
    }
}