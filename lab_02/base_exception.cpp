#include <iostream>

#include "base_exception.h"

BaseException::BaseException(const str &time, const str &fileName,
              const uint line, const str &className,
              const str &methodName, const str &info = "Something went wrong!")
{
    errIfno = "\nTime: " + time +
              "\nFile: " + fileName +
              "\nLine: " + line +
              "\nClass: " + className +
              "\nFunc: " + methodName +
              "\nInfo: " + info + "\n";
}

const char *BaseException::what() const noexcept
{
    return errInfo.c_str();
}
