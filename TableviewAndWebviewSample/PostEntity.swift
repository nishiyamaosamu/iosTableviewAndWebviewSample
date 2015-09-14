//
//  PostEntity.swift
//  TableviewAndWebviewSample
//
//  Created by Osamu Nishiyama on 2015/08/17.
//  Copyright (c) 2015年 ever sense. All rights reserved.
//

import RealmSwift

class PostEntity: Object {
    dynamic var id = 0
    dynamic var type = 0
    dynamic var title = ""
    dynamic var url = ""
}
