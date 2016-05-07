#include "printerhandler.h"

PrinterHandler::PrinterHandler()
{
    param_ = new PrinterParam();
}

PrinterHandler::~PrinterHandler()
{
    if (param_ != nullptr)
    {
        delete param_;
    }
}

void PrinterHandler::SetPrinterParam(const PrinterParam &param)
{
    param_->is_bold_ = param.is_bold_;
    param_->is_widen_ = param.is_widen_;
    param_->high_byte_ = param.high_byte_;
    param_->low_byte_ = param.low_byte_;
    param_->char_spacing_ = param.char_spacing_;
}

PrinterParam &PrinterHandler::GetPrinterParam()
{
    return *param_;
}

void PrinterHandler::EnableBold(bool enable)
{
    param_->is_bold_ = enable;
}

void PrinterHandler::EnableExtend(bool enable)
{
    param_->is_widen_ = enable;
}

void PrinterHandler::SetLeftMargin(int high, int low)
{
    param_->high_byte_ = high;
    param_->low_byte_ = low;
}

void PrinterHandler::SetCharSpacing(int dotpitch)
{
    param_->char_spacing_ = dotpitch;
}
