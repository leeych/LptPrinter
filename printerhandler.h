#ifndef PRINTERHANDLER_H
#define PRINTERHANDLER_H

#include "printerparam.h"

class PrinterHandler
{
public:
    void SetPrinterParam(const PrinterParam& param);
    PrinterParam &GetPrinterParam();

    void EnableBold(bool enable);
    void EnableExtend(bool enable);
    void SetLeftMargin(int high, int low);
    void SetCharSpacing(int dotpitch);
    void SetRowspacing(int dotpitch);
    void SetFeedinches(int dotpitch);

    static PrinterHandler *GetInstance()
    {
        static PrinterHandler instance;
        return &instance;
    }

private:
    PrinterHandler();
    ~PrinterHandler();

private:
    PrinterParam *param_;
};

#endif // PRINTERHANDLER_H
