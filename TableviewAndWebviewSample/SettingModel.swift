//
//  SettingModel.swift
//  TableviewAndWebviewSample
//
//  Created by Osamu Nishiyama on 2015/08/17.
//  Copyright (c) 2015年 ever sense. All rights reserved.
//

import Foundation
import RealmSwift

class SettingModel {
    
    static func getType() -> Int {
        let realm = Realm()
        if let ent = realm.objectForPrimaryKey(SettingEntity.self, key: 1) {
            return ent.type
        }
        return 0
    }
    
    static func setType(type : Int){
        let realm = Realm()
        let ent = SettingEntity()
        ent.type = type
        realm.write{
            realm.add(ent, update: true)
        }
        
        NSNotificationCenter.defaultCenter().postNotificationName(NotificationCenterName.ChangedType.toString(), object: nil)
    }
}
