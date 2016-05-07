#include "printerparam.h"

PrinterParam::PrinterParam():
    is_bold_(false),
    is_widen_(false),
    high_byte_(0),
    low_byte_(0),
    char_spacing_(0)
{
}

PrinterParam::PrinterParam(const PrinterParam &rhs)
{
    this->is_bold_ = rhs.is_bold_;
    this->is_widen_ = rhs.is_widen_;
    this->high_byte_ = rhs.high_byte_;
    this->low_byte_ = rhs.low_byte_;
    this->char_spacing_ = rhs.char_spacing_;
}

PrinterParam &PrinterParam::operator=(const PrinterParam &rhs)
{
    this->is_bold_ = rhs.is_bold_;
    this->is_widen_ = rhs.is_widen_;
    this->high_byte_ = rhs.high_byte_;
    this->low_byte_ = rhs.low_byte_;
    this->char_spacing_ = rhs.char_spacing_;
    return *this;
}
