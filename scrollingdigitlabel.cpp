// ----------------------------------------------------------------------------
// Copyright (C) 2019 GrizzWorks, LLC
// ALL RIGHTS RESERVED
// ----------------------------------------------------------------------------
#include "scrollingdigitlabel.h"
#include <QDebug>

void ScrollingDigitLabel::mouseDoubleClickEvent(QMouseEvent *event) {
    qDebug()<<"double-click!";
    emit goToZero(); // tell others listening to set to zero, usually to the right
    emit valueChanged(0);
    event->accept();
}

void ScrollingDigitLabel::wheelEvent(QWheelEvent *event)
{    // test the transform of a digit label by mouse wheel
    QPoint numPixels = event->pixelDelta();
    QPoint numDegrees = event->angleDelta() / 8;
    bool b_dir = 0;
    if (!numPixels.isNull()) {
        b_dir = (numPixels.ry() > 0);
    }
    else if (!numDegrees.isNull()) {
        QPoint numSteps = numDegrees / 15;
        b_dir = (numSteps.ry() > 0);
    }
    int next;
    if(b_dir) // rolled upward
    {
        next = this->text().toInt() + 1;
        if(!b_roll && (next >= i_max))
        {
            //qDebug()<<"goToZero"<<next;
            emit goToZero();
            next = i_max;
        }
        else if(next > i_max)
        {
            //qDebug()<<"b_roll:"<<b_roll;
            if(b_roll)
            {
                next = i_min;
                emit rolledUp();
            }
        }
        if(i_max > 9) {
            if(next < 10)
                this->setText("0" + QString::number(next));
            else
                this->setNum(next);
        }
        else
            this->setNum(next);
        emit valueChanged(next);
    }
    else // rolled downward
    {
        b_hitMax = false;
        next = this->text().toInt() - 1;
        //qDebug()<<"i_min:"<<i_min;
        if(next < i_min)
        {
            if(b_roll)
            {
                next = i_max;
                emit rolledDown();
            }
            else {
                return;// don't change it
            }
        }
        if(i_max > 9) {
            if(next < 10)
                this->setText("0" + QString::number(next));
            else
                this->setNum(next);
        }
        else
            this->setNum(next);
        emit valueChanged(next);
    }
    event->accept();
}

void ScrollingDigitLabel::on_rolledUp()
{
    //qDebug()<<"on_rolledUp:"<<this->text().toInt();
    int next = this->text().toInt() + 1;
    if(!b_roll && (next >= i_max))
    {
        //qDebug()<<"goToZero";
        if(b_markMax)
            emit hitMax();
        emit goToZero();
        this->setNum(i_max);
        return;
    }
    if(next > i_max)
    {
        if(b_roll)
        {
            next = i_min;
            emit rolledUp();  // this digit needs to talk to the one on it's left also
            this->setNum(next);
        }
    }
    else {
        this->setNum(next);
    }
    //emit valueChanged(next);
}

void ScrollingDigitLabel::on_rolledDown()
{
    //qDebug()<<"on_rolledDown:"<<this->text();
    int prev = this->text().toInt() - 1;
    if(!b_roll && (prev == i_min))
    {
        // qDebug()<<"goToZero";
        //
        emit goToZero();
        this->setNum(prev);
        return;
    }
    if(prev < i_min)
    {
        if(b_roll)
        {
            prev = i_max;
            emit rolledDown();  // this digit needs to talk to the one on it's left also
            this->setNum(prev);
        }
    }
    else {
        this->setNum(prev);
    }
    //emit valueChanged(prev);
}

void ScrollingDigitLabel::on_goToZero()
{
    this->setNum(0);
    //emit valueChanged(0);
}

