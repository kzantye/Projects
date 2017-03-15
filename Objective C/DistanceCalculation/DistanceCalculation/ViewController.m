//
//  ViewController.m
//  DistanceCalculation
//
//  Created by Kunal Zantye on 7/17/16.
//  Copyright © 2016 Kunal Zantye. All rights reserved.
//

#import "ViewController.h"
#import "DistanceGetter/DGDistanceRequest.h"

@interface ViewController ()

@property (nonatomic) DGDistanceRequest *req;
@property (weak, nonatomic) IBOutlet UITextField *startLocation;

@property (weak, nonatomic) IBOutlet UITextField *endLocationA;
@property (weak, nonatomic) IBOutlet UILabel *distanceA;

@property (weak, nonatomic) IBOutlet UITextField *endLocationB;
@property (weak, nonatomic) IBOutlet UILabel *distanceB;

@property (weak, nonatomic) IBOutlet UITextField *endLocationC;
@property (weak, nonatomic) IBOutlet UILabel *distanceC;
@property (weak, nonatomic) IBOutlet UITextField *endLocationD;
@property (weak, nonatomic) IBOutlet UILabel *distanceD;

@property (weak, nonatomic) IBOutlet UIButton *calculateButton;
@property (weak, nonatomic) IBOutlet UISegmentedControl *unitController;
@end

@implementation ViewController

- (IBAction)calculateButtonTapped:(id)sender {
    
    self.calculateButton.enabled=NO;

    
    self.req=[DGDistanceRequest alloc];
    NSString *start= self.startLocation.text;
    NSString *destA = self.endLocationA.text;
    NSString *destB = self.endLocationB.text;
    NSString *destC = self.endLocationC.text;
    NSString *destD = self.endLocationD.text;
    NSArray *dests= @[destA,destB,destC,destD];
    self.req=[self.req initWithLocationDescriptions:dests sourceDescription: start];
    __weak ViewController *weakSelf= self;
    self.req.callback =^(NSArray *responses){
        ViewController *strongSelf= weakSelf;
        if (!strongSelf) {
            return;
        }
        
        NSNull *badrequest =[NSNull null];
        
        if (responses[0]!= badrequest) {
            double num;
            NSString *x;
            if (self.unitController.selectedSegmentIndex==0) {
                num=[responses[0] floatValue];
                x=[NSString stringWithFormat:@"%.2f Meter",num];
            }
            else if(self.unitController.selectedSegmentIndex==1) {
                num= ([responses[0] floatValue]/1000.0);
                 x=[NSString stringWithFormat:@"%.2f KM",num];
            }
            else if(self.unitController.selectedSegmentIndex==2) {
                num= ([responses[0] floatValue]/1609.34);
                 x=[NSString stringWithFormat:@"%.2f Miles",num];
            }
            
            strongSelf.distanceA.text=x;
        }
        else{
            strongSelf.distanceA.text=@"Error";
        }
        
        
        
        if (responses[1]!= badrequest) {
          
                double num;
                NSString *x;
                if (self.unitController.selectedSegmentIndex==0) {
                    num=[responses[1] floatValue];
                    x=[NSString stringWithFormat:@"%.2f Meter",num];
                }
                else if(self.unitController.selectedSegmentIndex==1) {
                    num= ([responses[1] floatValue]/1000.0);
                    x=[NSString stringWithFormat:@"%.2f KM",num];
                }
                else if(self.unitController.selectedSegmentIndex==2) {
                    num= ([responses[1] floatValue]/1609.34);
                    x=[NSString stringWithFormat:@"%.2f Miles",num];
                }

            strongSelf.distanceB.text=x;
        }
        else{
            strongSelf.distanceB.text=@"Error";
        }
        
        if(responses[2]!= badrequest) {
            double num;
            NSString *x;
            if (self.unitController.selectedSegmentIndex==0) {
                num=[responses[2] floatValue];
                x=[NSString stringWithFormat:@"%.2f Meter",num];
            }
            else if(self.unitController.selectedSegmentIndex==1) {
                num= ([responses[2] floatValue]/1000.0);
                x=[NSString stringWithFormat:@"%.2f KM",num];
            }
            else if(self.unitController.selectedSegmentIndex==2) {
                num= ([responses[2] floatValue]/1609.34);
                x=[NSString stringWithFormat:@"%.2f Miles",num];
            }
            strongSelf.distanceC.text=x;
        }
        else{
            strongSelf.distanceC.text=@"Error";
        }
        
        
        if(responses[3]!= badrequest) {
            double num;
            NSString *x;
            if (self.unitController.selectedSegmentIndex==0) {
                num=[responses[3] floatValue];
                x=[NSString stringWithFormat:@"%.2f Meter",num];
            }
            else if(self.unitController.selectedSegmentIndex==1) {
                num= ([responses[3] floatValue]/1000.0);
                x=[NSString stringWithFormat:@"%.2f KM",num];
            }
            else if(self.unitController.selectedSegmentIndex==2) {
                num= ([responses[3] floatValue]/1609.34);
                x=[NSString stringWithFormat:@"%.2f Miles",num];
            }
            strongSelf.distanceD.text=x;
        }
        else{
            strongSelf.distanceD.text=@"Error";
        }

        strongSelf.req=nil;
        strongSelf .calculateButton.enabled=YES;
        
        
    };
    
    [self.req start];
    
}

@end
