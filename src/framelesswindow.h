// FramelessWindow Demo for Qt Applications
// Copyright (c) 2022, Pedro López-Cabanillas <plcl@users.sf.net>. All rights reserved.
// Copyright (c) 2023 CM0use

#ifndef FRAMELESSWINDOW_H
#define FRAMELESSWINDOW_H

#include <QMainWindow>

class FramelessWindow: public QMainWindow
{
public:
    explicit FramelessWindow(QWidget *const parent = nullptr);
    virtual ~FramelessWindow() = default;

protected:
    virtual bool event(QEvent *const event) override;

    void setTitleBar(QWidget *const widget);
    QWidget* getTitleBar() const;

private:
    void updateCursor(const Qt::Edges &edges);
    QWidget *m_titleBar;
};

#endif
