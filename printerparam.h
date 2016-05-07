#ifndef PRINTERPARAM_H
#define PRINTERPARAM_H


class PrinterParam
{
public:
    PrinterParam();
    PrinterParam(const PrinterParam& rhs);
    PrinterParam& operator=(const PrinterParam &rhs);

public:
    bool is_bold_, is_widen_;
    int high_byte_, low_byte_;
    int char_spacing_;
};

#endif // PRINTERPARAM_H
