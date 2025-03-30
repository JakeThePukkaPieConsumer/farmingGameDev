#ifndef ERROR_HANDLING_HPP
#define ERROR_HANDLING_HPP

#include <stdexcept>
#include <string>
#include <sstream>

enum class ErrorCategory
{
    TextRendering,
    ResourceLoading,
    GameLogic
};

class CustomException : public std::runtime_error
{
public:
    CustomException(
        ErrorCategory category,
        const std::string& message,
        const char* file,
        int line
    );

    ErrorCategory getCategory() const;
    const char* getFile() const;
    int getLine() const;

private:
    static std::string buildErrorMessage(
        ErrorCategory category,
        const std::string& message,
        const char* file,
        int line
    );

    ErrorCategory m_category;
    const char* m_file;
    int m_line;
};

#define THROW_CUSTOM_EXCEPTION(category, message) \
    throw CustomException(category, message, __FILE__, __LINE__)

#endif // ERROR_HANDLING_HPP