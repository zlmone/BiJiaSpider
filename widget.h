﻿#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>
#include <QWebFrame>
#include <QWebElement>
#include <QWebView>
#include <QUrl>
#include <QSqlDatabase>
#include <QSqlQuery>

#include <QtGlobal>
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#include <QUrlQuery>
#else
#include <QtGui>
#endif

#include "bijiaarkthread.h"
#include "bijiabehthread.h"
#include "bijiacombthread.h"

#define ARKPHARM_URL   "http://www.arkpharminc.com/web/search.html?s=1&keyword="
#define BEPHARM_URL     "http://www.bepharm.com/en/Search.html?searchValue="
#define COMBLOCKS_URL "http://www.combi-blocks.com/cgi-bin/find.cgi"

#define ARKFINAL_URL "http://www.arkpharminc.com/default.ashx?xmls=lib/stockprice.xmls&method=getstock&GoodsCode="
#define DEFAULT "http://www.arkpharminc.com/default.ashx?xmls=lib/stockprice.xmls&method=getstock&GoodsCode="
namespace Ui {
class Widget;
}
typedef struct {
    QString id;
    QString price;
    QString value;
    QUrl url;
}DATA_M;

class Widget : public QWidget
{
    Q_OBJECT
    enum WEBSITE_TYPE{
        BEPHARM = 0,
        ARKPHARM,
        COMBLOCKS
    };
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    QWebView* m_View;
    void initThreeThreads();
    void setUrl(const QUrl &url);
    void setWebSiteType(WEBSITE_TYPE type);
    void startLoad(const QUrl & url);
    void startPost(const QUrl & url);

    BiJiaARKThread* m_ARK;
    BiJiaBehThread* m_BEH;
    BiJiaCOMBThread* m_COMB;

    bool arkIsOK;
    bool behIsOk;
public slots:
    void examineChildElements(const QWebElement &parentElement);
    void parseArk(const QByteArray& arr);
    void parseBeh(const QByteArray& arr,bool isFirst);
    void parseComBlock(const QByteArray& arr,bool isFirst);

    void appendStatus(QString);
    void operatorData(DATA_M stu);
private slots:
    void on_pushButton_clicked();
//    void replyFinished(QNetworkReply*);
    void setCurrentCas(QString);
private:
    Ui::Widget *ui;
    WEBSITE_TYPE iType;
    QList<DATA_M> dataStuList;
    bool isFirstBe;
};

#endif // WIDGET_H