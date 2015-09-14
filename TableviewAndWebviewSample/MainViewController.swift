//
//  MainViewController.swift
//  TableviewAndWebviewSample
//
//  Created by Osamu Nishiyama on 2015/08/17.
//  Copyright (c) 2015年 ever sense. All rights reserved.
//

import UIKit
import RealmSwift

class MainViewController: UITableViewController {
    
    var posts : Results<PostEntity>!

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        updatePost()
        
        NSNotificationCenter.defaultCenter().addObserver(self, selector: "updateTable", name: NotificationCenterName.ChangedType.toString(), object: nil)
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    deinit{
        NSNotificationCenter.defaultCenter().removeObserver(self)
    }
        
    func updatePost(){
        let type = SettingModel.getType();
        println(type)
        posts = PostModel.getEntities(SettingModel.getType())
        println(posts)
    }
    
    func updateTable(){
        println("update table")
        updatePost()
        tableView.reloadData()
    }
    
    
    override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
        if segue.identifier == "showWebview" {
            let vc = segue.destinationViewController as! WebViewController
            if let row = self.tableView.indexPathForSelectedRow()?.row {
                vc.url = posts[row].url
            }
        }
    }
    
    
    override func tableView(tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return posts.count
    }
    
    override func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCellWithIdentifier("Cell", forIndexPath: indexPath) as! UITableViewCell
        let post = posts[indexPath.row]
        let title = post.type.description + " - " + post.title
        cell.textLabel?.text = title
        return cell
    }
    
    @IBAction func showSetting(sender: UIBarButtonItem) {
        let sb = UIStoryboard(name: "Setting", bundle: nil)
        let vc = sb.instantiateInitialViewController() as! UIViewController
        self.presentViewController(vc, animated: true, completion: nil)
    }

}

