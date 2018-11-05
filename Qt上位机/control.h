#include <QString>
#include <QDesktopWidget>
#include <QRect>
#include <QLineEdit>
#include <QPushButton>

class Util :QObject
{
public:
     Util();
     int getWidth() const;
     void setWidth(int value);
     int getHeight() const;
     void setHeight(int value);
     void setBtnQss(QPushButton *btn,
                    QString normalColor, QString normalTextColor,
                    QString hoverColor, QString hoverTextColor,
                    QString pressedColor, QString pressedTextColor);
     void setTxtQss(QLineEdit *txt, QString normalColor, QString focusColor);
     QString getQssContent();
private:
     int width;
     int height;
};


/*************************************************
系统所需常量的声明及定义
**************************************************/
/*
#ifndef CONTROL_H
#define CONTROL_H

#define SHADOW_WIDTH            5
#define WINDOW_WIDTH            680
#define WINDOW_HEIGHT           372
#define WINDOW_START_X          0
#define WINDOW_START_Y          0
#define WINDOW_PAGE_COUNT       4
#define WINDOW_BUTTON_COUNT     4
#define WINDOW_PAGE_MOVE        20
#define WINDOW_ONEBUTTON_WIDTH  170
#define DEFALUT_SKIN    "images/login/skin"

#define _ARM_        0

//调试信息输出控制，1：输出信息，0：不输出信息
#define QDEBUG  1

//保存数据时间间隔 （单位：秒）(5秒测试可以用)
#define SAVE_DATA_INTERVAL  60

//是否显示图例(1：显示，0：不显示;默认显示)
#define SHOW_LEGEND     1

//设备名称,用于插入数据时使用
#define DEVICE_TEMP         "01"    //温度
#define DEVICE_HUM          "02"    //湿度
#define DEVICE_SMOKE        "03"    //烟雾

#define LED_ON      1
#define LED_OFF     0


extern bool gIsSendMessage;

//预设温度值
extern int set_parlour_tempture;
extern int set_bedroom_tempture;
extern int set_parlour_humidity;        //预设湿度值
extern int set_smoke_density;           //预设烟雾浓度

//各个传感器实时值
extern QString cur_parlour_tempture;    //只统计客厅温度(DS18B20温度值)
extern QString cur_parlour_humidity;    //(DHT11值)
extern QString cur_smoke_density;       //(MQ_2值)

extern bool gIsOpenPort;                //串口打开标志位
extern bool gIsOpenCurtain;             //窗帘是否打开

//灯的名称枚举
enum enum_light_name{
    E_BED_ROOM = 0,             //卧室
    E_PARLOUR,                  //客厅
    E_KITCHEN                   //厨房
};
//灯的数量枚举
enum enum_ligt_num{
    ENUM_ONE = 1,
    ENUM_TWO ,
    ENUM_THREE
};
//统计界面标题
enum enum_statistic_title
{
    ENUM_TEMPTURE,                  //温度统计
    ENUM_HUMIDITY_DENSITY,          //湿度浓度统计
    ENUM_SMOKE_DENSITY              //烟雾浓度统计
};
*/


/*#ifndef COMMON_H
#define COMMON_H
//宏定义各个重要参数
#define SHADOW_WIDTH               5    //定义阴影宽度为5
#define WINDOW_WIDTH               680  //定义窗口宽度为680
#define WINDOW_HEIGHT              372  //定义窗口高度为372
#define WINDOW_SATRT_X             0    //定义窗口左上横坐标为0
#define WINDOW_ATART_Y             0    //定义窗口左上纵坐标为0
#define WINDOW_PAGE_COUNT          4    //定义窗口页面个数为4
#define WINDOW_BUTTON_COUNT        4    //定义窗口按钮个数为4
#define WINDOW_PAGE_MOVE           20   //定义页面移动距离为40
#define WINDOW_ONEBUTTON_WIDTH     170  //定义按钮宽度为170
#define DEFAULT_SKIN               ":/skin/17_big"  //定义默认皮肤位置

typedef enum{                      //定义语言枚举
    UI_EN,
    UI_ZH
} LANGUAGE;

typedef enum{                      //定义登录类型枚举
    SAFE,
    SINA,
    RENREN
}  LOGIN;

typedef enum{
    HELP_ONLINE,
    PLATFORM_HELP,
    LOGIN_HOME,
    PROTECT
}ACTION;
typedef enum{                      //定义按钮状态类型枚举
    NORMAL,
    ENTER,
    PRESS,
    NOSTATUS
} ButtonStatus;
#endif // COMMON_H
*/


/*
#define SHADOW_WIDTH            5
#define WINDOW_WIDTH            680
#define WINDOW_HEIGHT           372
#define WINDOW_START_X          0
#define WINDOW_START_Y          0
#define WINDOW_PAGE_COUNT       4
#define WINDOW_BUTTON_COUNT     4
#define WINDOW_PAGE_MOVE        20
#define WINDOW_ONEBUTTON_WIDTH  170
#define DEFAULT_SKIN            ":/skin/17_big"

typedef enum{
    UI_EN,
    UI_ZH
}LANGUAGE;

typedef enum{
    SAFE,
    SINA,
    RENREN
}LOGIN;

typedef enum{
    HELP_ONLINE,
    PLATFORM_HELP,
    LOGIN_HOME,
    PROTECT
}ACTION;

//枚举按钮的几种状态
typedef enum{
    NORMAL,
    ENTER,
    PRESS,
    NOSTATUS
}ButtonStatus;

#endif // CONTROL_H
*/
