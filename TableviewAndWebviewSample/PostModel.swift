//
//  PostModel.swift
//  TableviewAndWebviewSample
//
//  Created by Osamu Nishiyama on 2015/08/17.
//  Copyright (c) 2015年 ever sense. All rights reserved.
//

import Foundation
import RealmSwift

class PostModel : NSObject {
    
    static func getEntities(type : Int)-> Results<PostEntity> {
        let realm = Realm()
        if type == 0 {
            return realm.objects(PostEntity)
        }else{            
            return realm.objects(PostEntity).filter("type == " + type.description)
        }
    }
    
    static func initData(){
        let realm = Realm()
        let objects = realm.objects(PostEntity)
        
        if objects.count == 0{
            var postData : [[AnyObject]] = [
                [1,1,"妊娠2週目！妊婦の症状は？体の変化や兆候はあるの？","http://192abc.com/28010"],
                [2,1,"【妊活】受精から着床までの流れや仕組み、時期を解説！","http://192abc.com/13374"],
                [3,2,"【妊娠超初期症状】受精から着床までの症状まとめ。もしかして妊娠？","http://192abc.com/13381"],
                [4,2,"インプランテーションディップとは？着床時に基礎体温が下がる？","http://192abc.com/30783"],
                [5,1,"【妊婦、妊活中の方必見】保険の基本！生命保険には３タイプしかない！（終身、定期、養老）","http://192abc.com/14449"],
                [6,1,"【妊娠超初期症状】妊娠兆候の基礎体温とは？時期と体温を知ろう！","http://192abc.com/11711"],
                [7,2,"妊娠初期症状まとめ。妊娠兆候はいつから？","http://192abc.com/archives/pregnancy-childbirth20140529"]
            ]
            
            for post in postData {
                let ent = PostEntity(value: post)
                realm.write{
                    realm.add(ent)
                }
            }
        }
        
    }
}
