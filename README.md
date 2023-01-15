# qtscrollingdigit
A Qt project to implement mouse wheel scrollable "digits" for UI


![image](https://user-images.githubusercontent.com/16414991/206474498-c63a0f11-d27e-4744-b326-4d5bd6b40f63.png)


Read the source for more implementation information, but essentially, this sub-classes QLabel to provide a mouse wheel scrollable "digit" (any item that is incrementally set).

This example implementation is for a Ham Radio frequency display where the left-most scrollable is 10's of Megahertz.  Subsequent scrollables are 100 kHz, 10 kHz, 1 kHz, 100 Hz, 10 Hz and 1 Hz.  Concatenating the textual values of the scrolled digits creates a QString of the frequency value which is used by remote control protocols such as CAT to set the frequency on the radio.  The opposite is also possible by reading the CAT value of the radio frequency and setting the scrollable digits to match.

An example for the Yaesu FT-450D where mhz10, khz100, khz10, khz1, hz100, hz10 and hz1 are ScrollableDigits objects.

````
void YOURPROGRAM::setupScrollingLabels()
{
    // scrolling labels for control of active VFO
    mhz10 = new ScrollingDigitLabel();
    mhz10->setAlignment(Qt::AlignRight);
    mhz10->setMin(0);
    mhz10->setMax(29);
    mhz10->b_roll = false; // stop when min/max reached
    mhz10->setMarkMax(true); // signal when max value reached
    mhz10->setStyleSheet(FREQ_STYLE);
    mhz10->setNum(14);
    mhz10->setMaximumWidth(37);
    mhz10->setMinimumWidth(37);
//    ScrollingDigitLabel * mhz1 = new ScrollingDigitLabel();
//    mhz1.setNum(9);
//    mhz1->setStyleSheet(FREQ_STYLE);
    khz100 = new ScrollingDigitLabel();
    khz100->setStyleSheet(FREQ_STYLE);
    khz100->setNum(9);
    khz100->setMaximumWidth(19);
    khz10 = new ScrollingDigitLabel();
    khz10->setStyleSheet(FREQ_STYLE);
    khz10->setNum(2);
    khz10->setMaximumWidth(19);
    khz1 = new ScrollingDigitLabel();
    khz1->setStyleSheet(FREQ_STYLE);
    khz1->setNum(8);
    khz1->setMaximumWidth(19);
    QLabel * dot = new QLabel(".");
    dot->setStyleSheet(FREQ_STYLE);
    dot->setMaximumWidth(12);
    dot->setAlignment(Qt::AlignHCenter);
    hz100 = new ScrollingDigitLabel();
    hz100->setStyleSheet(FREQ_STYLE);
    hz100->setNum(5);
    hz100->setMaximumWidth(19);
    hz10 = new ScrollingDigitLabel();
    hz10->setStyleSheet(FREQ_STYLE);
    hz10->setNum(0);
    hz10->setMaximumWidth(19);
    hz1 = new ScrollingDigitLabel();
    hz1->setStyleSheet(FREQ_STYLE);
    hz1->setNum(0);
    hz1->setMaximumWidth(19);
    connect(mhz10, &ScrollingDigitLabel::valueChanged, this, &FldigiModem::on_valueChanged);
    connect(khz100, &ScrollingDigitLabel::valueChanged, this, &FldigiModem::on_valueChanged);
    connect(khz10, &ScrollingDigitLabel::valueChanged, this, &FldigiModem::on_valueChanged);
    connect(khz1, &ScrollingDigitLabel::valueChanged, this, &FldigiModem::on_valueChanged);
    connect(hz100, &ScrollingDigitLabel::valueChanged, this, &FldigiModem::on_valueChanged);
    connect(hz10, &ScrollingDigitLabel::valueChanged, this, &FldigiModem::on_valueChanged);
    connect(hz1, &ScrollingDigitLabel::valueChanged, this, &FldigiModem::on_valueChanged);
    // digit hit max so go to zero on all to the right
    //connect(mhz10, &ScrollingDigitLabel::goToZero, mhz1, &ScrollingDigitLabel::on_goToZero);
    //connect(mhz1, &ScrollingDigitLabel::goToZero, khz100, &ScrollingDigitLabel::on_goToZero);
    connect(mhz10, &ScrollingDigitLabel::goToZero, khz100, &ScrollingDigitLabel::on_goToZero);
    connect(mhz10, &ScrollingDigitLabel::goToZero, khz10, &ScrollingDigitLabel::on_goToZero);
    connect(mhz10, &ScrollingDigitLabel::goToZero, khz1, &ScrollingDigitLabel::on_goToZero);
    connect(mhz10, &ScrollingDigitLabel::goToZero, hz100, &ScrollingDigitLabel::on_goToZero);
    connect(mhz10, &ScrollingDigitLabel::goToZero, hz10, &ScrollingDigitLabel::on_goToZero);
    connect(mhz10, &ScrollingDigitLabel::goToZero, hz1, &ScrollingDigitLabel::on_goToZero);
    // when max is hit, send all right side digits to zero
    connect(mhz10, &ScrollingDigitLabel::hitMax, khz100, &ScrollingDigitLabel::on_goToZero);
    connect(mhz10, &ScrollingDigitLabel::hitMax, khz10, &ScrollingDigitLabel::on_goToZero);
    connect(mhz10, &ScrollingDigitLabel::hitMax, khz1, &ScrollingDigitLabel::on_goToZero);
    connect(mhz10, &ScrollingDigitLabel::hitMax, hz100, &ScrollingDigitLabel::on_goToZero);
    connect(mhz10, &ScrollingDigitLabel::hitMax, hz10, &ScrollingDigitLabel::on_goToZero);
    connect(mhz10, &ScrollingDigitLabel::hitMax, hz1, &ScrollingDigitLabel::on_goToZero);
    // from khz100 down
    connect(khz100, &ScrollingDigitLabel::goToZero, khz10, &ScrollingDigitLabel::on_goToZero);
    connect(khz100, &ScrollingDigitLabel::goToZero, khz1, &ScrollingDigitLabel::on_goToZero);
    connect(khz100, &ScrollingDigitLabel::goToZero, hz100, &ScrollingDigitLabel::on_goToZero);
    connect(khz100, &ScrollingDigitLabel::goToZero, hz10, &ScrollingDigitLabel::on_goToZero);
    connect(khz100, &ScrollingDigitLabel::goToZero, hz1, &ScrollingDigitLabel::on_goToZero);
    // from khz10 down
    connect(khz10, &ScrollingDigitLabel::goToZero, khz1, &ScrollingDigitLabel::on_goToZero);
    connect(khz10, &ScrollingDigitLabel::goToZero, hz100, &ScrollingDigitLabel::on_goToZero);
    connect(khz10, &ScrollingDigitLabel::goToZero, hz10, &ScrollingDigitLabel::on_goToZero);
    connect(khz10, &ScrollingDigitLabel::goToZero, hz1, &ScrollingDigitLabel::on_goToZero);
    // from khz1 down
    connect(khz1, &ScrollingDigitLabel::goToZero, hz100, &ScrollingDigitLabel::on_goToZero);
    connect(khz1, &ScrollingDigitLabel::goToZero, hz10, &ScrollingDigitLabel::on_goToZero);
    connect(khz1, &ScrollingDigitLabel::goToZero, hz1, &ScrollingDigitLabel::on_goToZero);
    // from hz100 down
    connect(hz100, &ScrollingDigitLabel::goToZero, hz10, &ScrollingDigitLabel::on_goToZero);
    connect(hz100, &ScrollingDigitLabel::goToZero, hz1, &ScrollingDigitLabel::on_goToZero);
    // finally hz10 down
    connect(hz10, &ScrollingDigitLabel::goToZero, hz1, &ScrollingDigitLabel::on_goToZero);
    // digit rolled up so inform the digit to the left
    //connect(mhz1, &ScrollingDigitLabel::rolledUp, mhz10, &ScrollingDigitLabel::on_rolledUp);
    //connect(khz100, &ScrollingDigitLabel::rolledUp, mhz1, &ScrollingDigitLabel::on_rolledUp);
    connect(khz100, &ScrollingDigitLabel::rolledUp, mhz10, &ScrollingDigitLabel::on_rolledUp);
    connect(khz10, &ScrollingDigitLabel::rolledUp, khz100, &ScrollingDigitLabel::on_rolledUp);
    connect(khz1, &ScrollingDigitLabel::rolledUp, khz10, &ScrollingDigitLabel::on_rolledUp);
    connect(hz100, &ScrollingDigitLabel::rolledUp, khz1, &ScrollingDigitLabel::on_rolledUp);
    connect(hz10, &ScrollingDigitLabel::rolledUp, hz100, &ScrollingDigitLabel::on_rolledUp);
    connect(hz1, &ScrollingDigitLabel::rolledUp, hz10, &ScrollingDigitLabel::on_rolledUp);
    // digit rolled down so inform the digit to the left
    //connect(mhz1, &ScrollingDigitLabel::rolledDown, mhz10, &ScrollingDigitLabel::on_rolledDown);
    //connect(khz100, &ScrollingDigitLabel::rolledDown, mhz1, &ScrollingDigitLabel::on_rolledDown);
    connect(khz100, &ScrollingDigitLabel::rolledDown, mhz10, &ScrollingDigitLabel::on_rolledDown);
    connect(khz10, &ScrollingDigitLabel::rolledDown, khz100, &ScrollingDigitLabel::on_rolledDown);
    connect(khz1, &ScrollingDigitLabel::rolledDown, khz10, &ScrollingDigitLabel::on_rolledDown);
    connect(hz100, &ScrollingDigitLabel::rolledDown, khz1, &ScrollingDigitLabel::on_rolledDown);
    connect(hz10, &ScrollingDigitLabel::rolledDown, hz100, &ScrollingDigitLabel::on_rolledDown);
    connect(hz1, &ScrollingDigitLabel::rolledDown, hz10, &ScrollingDigitLabel::on_rolledDown);
   /* // to add the digits to a QGroupBox perhaps...
    ui->scrollBox->layout()->addWidget(mhz10);
    ui->scrollBox->layout()->addWidget(khz100);
    ui->scrollBox->layout()->addWidget(khz10);
    ui->scrollBox->layout()->addWidget(khz1);
    ui->scrollBox->layout()->addWidget(dot);
    ui->scrollBox->layout()->addWidget(hz100);
    ui->scrollBox->layout()->addWidget(hz10);
    ui->scrollBox->layout()->addWidget(hz1);
    */
}
````
on_rolledUp, on_rolledDown, and goToZero are left here as application dependent slot implementations.  Essentially, goToZero just resets the digit to zero.  on_rolledUp and on_rolledDown are dependent on how the application and it's potential hardware may need to react to these events.

````
void YOURPROGRAM::on_valueChanged(const int newval)
{
    Q_UNUSED (newval)
    if (ui->dialLockCheckbox->isChecked())
        return;
    //qDebug()<<"parent"<<QObject::sender()<<" val:"<<newval;
    const QString newFreq = mhz10->text().append(khz100->text()).append(khz10->text()).append(khz1->text()).append(hz100->text()).append(hz10->text()).append(hz1->text());
    qDebug()<<"new Value:"<<newFreq;
    const QString freq = QString("%1").arg(newFreq, 8, PADCHAR);
    // set the frequency of the current VFO to the value in
    // the set of scrolling labels, after doing the CI-V frequency gymnastics
    //00 17 44 30 00 =  17443000 Hz --> 00 30 44 17 00
    QString cmd;
    if(b_currVFO)
        cmd = "FA" % freq.mid(0, 2) % freq.mid(2, 2) % freq.mid(4, 2) % freq.mid(6, 2) % ";";
    else
        cmd = "FB" % freq.mid(0, 2) % freq.mid(2, 2) % freq.mid(4, 2) % freq.mid(6, 2) % ";";
    qDebug()<<"Freq:"<<cmd;
    radioCommand(cmd);
    updateFreqDisplay();
}
````
