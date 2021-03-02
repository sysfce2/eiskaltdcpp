/***************************************************************************
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 3 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
***************************************************************************/

#pragma once

#include <QWidget>
#include <QCloseEvent>

#include "dcpp/stdinc.h"
#include "dcpp/ClientManager.h"
#include "dcpp/Singleton.h"

#include "WulforUtil.h"
#include "ArenaWidget.h"
#include "ui_UISpy.h"

class SpyModel;

class SpyFrame :
        public QWidget,
        public ArenaWidget,
        public dcpp::Singleton<SpyFrame>,
        private dcpp::ClientManagerListener,
        private Ui::UISpy
{
Q_OBJECT
Q_INTERFACES(ArenaWidget)

friend class dcpp::Singleton<SpyFrame>;

public:
    QString getArenaShortTitle() { return tr("Search Spy"); }
    QString getArenaTitle() {return getArenaShortTitle(); }
    QMenu *getMenu() {return nullptr; }
    QWidget *getWidget() { return this; }
    const QPixmap &getPixmap(){ return WICON(WulforUtil::eiSPY); }
    ArenaWidget::Role role() const { return ArenaWidget::SearchSpy; }
    void requestClear() { slotClear(); }

protected:
    virtual void closeEvent(QCloseEvent *);

private Q_SLOTS:
    void slotStartStop();
    void slotClear();
    void contextMenu();
    void slotSettingsChanged(const QString&, const QString&);

Q_SIGNALS:
    void coreIncomingSearch(const QString&, bool);

private:
    explicit SpyFrame(QWidget *parent = nullptr);
    ~SpyFrame();

    SpyModel *model;

    virtual void on(dcpp::ClientManagerListener::IncomingSearch, const std::string& s) noexcept;
};
