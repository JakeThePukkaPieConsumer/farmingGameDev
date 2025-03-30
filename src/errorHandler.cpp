#include "errorHandling.hpp"

CustomException::CustomException(
    ErrorCategory category,
    const std::string& message,
    const char* file,
    int line
) : std::runtime_error(buildErrorMessage(category, message, file, line)),
    m_category(category),
    m_file(file),
    m_line(line) {}

std::string CustomException::buildErrorMessage(
    ErrorCategory category,
    const std::string& message,
    const char* file,
    int line
)
{
    std::ostringstream errorMsg;
    errorMsg << "Error in "
        << [](ErrorCategory cat)
        {
            switch(cat)
            {
                case ErrorCategory::TextRendering: return "Text Rendering";
                case ErrorCategory::ResourceLoading: return "Resource Loading";
                case ErrorCategory::GameLogic: return "Game Logic";
                default: return "Unknown";
            }
        }(category)
        << ": " << message
        << " (FILE: " << file
        << ", LINE: " << line << ")";
    return errorMsg.str();
}

ErrorCategory CustomException::getCategory() const 
{
    return m_category;
}

const char* CustomException::getFile() const 
{
    return m_file;
}

int CustomException::getLine() const 
{
    return m_line;
}