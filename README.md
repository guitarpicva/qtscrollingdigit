# qtscrollingdigit
A Qt project to implement mouse wheel scrollable "digits" for UI

Read the source for more implementation information, but essentially, this sub-classes QLabel to provide a mouse wheel scrollable "digit" (any item that is incrementally set).

This example implementation is for a Ham Radio frequency display where the left-most scrollable is 10's of Megahertz.  Subsequent scrollables are 100 kHz, 10 kHz, 1 kHz, 100 Hz, 10 Hz and 1 Hz.  Concatenating the textual values of the scrolled digits creates a QString of the frequency value which is used by remote control protocols such as CAT to set the frequency on the radio.  The opposite is also possible by reading the CAT value of the radio frequency and setting the scrollable digits to match.

An example for the Yaesu FT-450D:

````
void FT450D::on_valueChanged(const int newval)
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
