//
//  SettingViewController.swift
//  TableviewAndWebviewSample
//
//  Created by Osamu Nishiyama on 2015/08/17.
//  Copyright (c) 2015年 ever sense. All rights reserved.
//

import UIKit

class SettingViewController: UIViewController {
    
    @IBOutlet weak var segmentedControl: UISegmentedControl!
    override func viewDidLoad() {
        segmentedControl.selectedSegmentIndex = SettingModel.getType()
    }
    
    @IBAction func selectType(sender: UISegmentedControl) {
        var selectedType = sender.selectedSegmentIndex
        SettingModel.setType(selectedType)
    }
    
    @IBAction func close(sender: UIBarButtonItem) {
        dismissViewControllerAnimated(true, completion: nil)
    }
}
