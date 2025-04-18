#ifndef __LS_ERROR_CPP__
#define __LS_ERROR_CPP__

#include <string>
#include <mutex>

namespace LSError {

static std::string errorMessage;
static std::mutex errorMutex;

// Set error (printf-style variant can be added too)
void SetError(const std::string& error) {
    std::lock_guard<std::mutex> lock(errorMutex);
    errorMessage = error;
}

// Get last error
const char* GetError() {
    std::lock_guard<std::mutex> lock(errorMutex);
    return errorMessage.c_str();
}

// Clear error (optional)
void ClearError() {
    std::lock_guard<std::mutex> lock(errorMutex);
    errorMessage.clear();
}

} // namespace mylib


#endif // __LS_ERROR_CPP__
