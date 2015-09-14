//
//  SettingEntity.swift
//  TableviewAndWebviewSample
//
//  Created by Osamu Nishiyama on 2015/08/17.
//  Copyright (c) 2015年 ever sense. All rights reserved.
//

import RealmSwift

class SettingEntity: Object {
    dynamic var id = 1
    dynamic var type = 0
    
    override static func primaryKey() -> String? {
        return "id"
    }

}
