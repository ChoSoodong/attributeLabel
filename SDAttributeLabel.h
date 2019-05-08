







#import <UIKit/UIKit.h>

typedef NS_ENUM(NSUInteger , SDAttributeLabelStyle){
    SDAttributeLabelStyleNone = 0,
    SDAttributeLabelStyleUser = 1,
    SDAttributeLabelStyleTopic = 2,
    SDAttributeLabelStyleLink = 3,
    SDAttributeLabelStyleAgreement = 4,
    SDAttributeLabelStyleUserDefine = 5,
    SDAttributeLabelStylePhoneNumber = 6
};

@class  SDAttributeLabel;

@protocol SDAttributeLabelDelegate <NSObject>

@optional

// 代理
-(void)attributeLabel:(SDAttributeLabel *)label didSelectedString:(NSString *)selectedString forStyle:(SDAttributeLabelStyle)style onRange:(NSRange)range;

@end

//Block
typedef void(^TapLabel)(UILabel *label,SDAttributeLabelStyle style, NSString * selectString, NSRange selectRange);

@interface SDAttributeLabel : UILabel

/* 普通文字颜色 */
@property(nonatomic , strong)UIColor *normalColor ;

/* 选中时高亮背景色 */
@property(nonatomic , strong)UIColor *hightLightBackgroundColor ;

/* 字符串+显示颜色 字典数组, */
@property(nonatomic, strong)NSArray<NSDictionary *> *matchArr;

/* 高亮文字设置颜色*/
-(void)setHightLightLabelColor:(UIColor *)hightLightColor forStyle:(SDAttributeLabelStyle)style;

/* delegate */
@property(nonatomic, weak)id<SDAttributeLabelDelegate> delegate;


/* 点击事件block */
@property(nonatomic, strong)TapLabel tapOperation;


@end


/**
 使用示例:
 
 -(void)setupUI{
 
 _label = [[SDAttributeLabel alloc]initWithFrame:CGRectMake(50, 100, self.view.bounds.size.width - 100, 200)];
 [self.view addSubview:_label];
 
 self.label.text = @"#GZLabel# 用于各种字符串的内容显示, 用户:@轻斟浅醉17, 包括话题:#怎么成为行业大神?#, 链接:http://www.jianshu.com/u/ab83189244d9, 使用说明:《使用说明》, 还有自定义要高亮显示的字符串,电话:13468651651.";
 
 // 非匹配内容文字颜色
 self.label.normalColor = [UIColor colorWithRed:112.0/255 green:93.0/255 blue:77.0/255 alpha:1];
 
 // 点选高亮文字颜色
 self.label.hightLightBackgroundColor = [UIColor colorWithRed:237.0/255 green:213.0/255 blue:177.0/255 alpha:1];
 
 // 匹配文字颜色
 [self.label setHightLightLabelColor:[UIColor colorWithRed:132.0/255 green:77.0/255 blue:255.0/255 alpha:1] forStyle:SDAttributeLabelStyleUser];
 [self.label setHightLightLabelColor:[UIColor colorWithRed:1.0/255 green:16.0/255 blue:213.0/255 alpha:1] forStyle:SDAttributeLabelStyleLink];
 [self.label setHightLightLabelColor:[UIColor colorWithRed:254.0/255 green:156.0/255 blue:59.0/255 alpha:1] forStyle:SDAttributeLabelStyleTopic];
 [self.label setHightLightLabelColor:[UIColor colorWithRed:255.0/255 green:69.0/255 blue:0.0/255 alpha:1] forStyle:SDAttributeLabelStyleAgreement];
 
 [self.label setHightLightLabelColor:[UIColor colorWithRed:9.0/255 green:160.0/255 blue:213.0/255 alpha:1] forStyle:SDAttributeLabelStylePhoneNumber];
 
 // 自定义匹配的文字和颜色#8FDF5C
 self.label.matchArr = @[
 @{
 @"string" : @"高亮显示",
 @"color" : [UIColor colorWithRed:0.55 green:0.86 blue:0.74 alpha:1]
 }
 ];
 
 // 匹配到合适内容的回调
 self.label.tapOperation = ^(UILabel *label, SDAttributeLabelStyle style, NSString *selectedString, NSRange range){
 
 // 你想要做的事
 NSLog(@"block打印 %@", selectedString);
 
 if (style == SDAttributeLabelStyleLink) {
 
 GZWebViewController *web = [GZWebViewController new];
 web.URL = selectedString;
 [weakSelf.navigationController pushViewController:web animated:YES];
 }
 if (style == SDAttributeLabelStylePhoneNumber) {
 UIAlertController *alertControler = [UIAlertController alertControllerWithTitle:@"拨号" message:selectedString preferredStyle:UIAlertControllerStyleAlert];
 UIAlertAction *noAction = [UIAlertAction actionWithTitle:@"取消" style:UIAlertActionStyleCancel handler:^(UIAlertAction *action){
 return ;
 }];
 UIAlertAction *yesAction = [UIAlertAction actionWithTitle:@"确定" style:UIAlertActionStyleDefault handler:^(UIAlertAction *action){
 [[UIApplication sharedApplication] openURL:[NSURL URLWithString:[NSString stringWithFormat:@"tel:%@",selectedString]] options:@{ NSDocumentTypeDocumentAttribute: NSPlainTextDocumentType } completionHandler:^(BOOL success) {
 }];
 }];
 [alertControler addAction:noAction];
 [alertControler addAction:yesAction];
 [weakSelf presentViewController:alertControler animated:YES completion:nil];
 
 }
 };
 
 
 self.label.delegate = self;
 
 }
 
 //代理
 -(void)attributeLabel:(SDAttributeLabel *)label didSelectedString:(NSString *)selectedString forStyle:(SDAttributeLabelStyle)style onRange:(NSRange)range{
 
 // 你想要做的事
 NSLog(@"代理打印 %@", selectedString);
 }
 
 
 
 
 */
