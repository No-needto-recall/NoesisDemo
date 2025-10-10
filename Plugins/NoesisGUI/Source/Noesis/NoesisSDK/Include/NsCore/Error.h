////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_ERROR_H__
#define __CORE_ERROR_H__


#include <NsCore/Noesis.h>
#include <NsCore/KernelApi.h>


///  ----------------------------------------------------------------------------------------
///  |                     Debug    Profile    Release                                      |
///  ----------------------------------------------------------------------------------------
///  | NS_ASSERT            [x]       [ ]        [ ]         Internal Debug checks          |
///  | NS_CHECK             [x]       [x]        [ ]         Development checks             |
///  | NS_ERROR             [x]       [x]        [x]         Recoverable errors             |
///  | NS_FATAL             [x]       [x]        [x]         Non-recoverable errors         |
///  ----------------------------------------------------------------------------------------

#ifndef NS_INTERNAL_ASSERT
    #define NS_INTERNAL_ASSERT(expr) \
        NS_MACRO_BEGIN \
            if (NS_UNLIKELY(!(expr))) \
            { \
                if (Noesis::InvokeAssertHandler(__FILE__, __LINE__, #expr)) \
                { \
                    NS_DEBUG_BREAK; \
                } \
            } \
        NS_MACRO_END
#endif

#ifndef NS_ASSERT
    #ifdef _PREFAST_
        #define NS_ASSERT(expr) __analysis_assume(!!(expr))
    #elif defined(__clang_analyzer__)
        #include <assert.h>
        #define NS_ASSERT(expr) assert(expr)
    #elif defined(NS_DEBUG)
        #define NS_ASSERT(expr) NS_INTERNAL_ASSERT(expr)
    #else
        #define NS_ASSERT(expr) NS_UNUSED(expr)
    #endif
#endif

#ifndef NS_CHECK
    #ifdef _PREFAST_
        #define NS_CHECK(expr, ...) __analysis_assume(!!(expr))
    #elif defined(__clang_analyzer__)
        #include <assert.h>
        #define NS_CHECK(expr, ...) assert(expr)
    #elif defined(NS_PROFILE)
        #define NS_CHECK(expr, ...) \
            NS_MACRO_BEGIN \
                if (NS_UNLIKELY(!(expr))) \
                { \
                    Noesis::InvokeErrorHandler(__FILE__, __LINE__, false, nullptr, __VA_ARGS__); \
                } \
            NS_MACRO_END
    #else
        #define NS_CHECK(...) NS_UNUSED(__VA_ARGS__)
    #endif
#endif

#ifndef NS_ERROR
    #define NS_ERROR(...) Noesis::InvokeErrorHandler(__FILE__, __LINE__, false, nullptr, __VA_ARGS__)
#endif

#ifndef NS_FATAL
    #include <stdlib.h>
    #define NS_FATAL(...) \
        Noesis::InvokeErrorHandler(__FILE__, __LINE__, true, nullptr, __VA_ARGS__); \
        NS_DEBUG_BREAK; \
        abort()
#endif

#define NS_ASSERT_UNREACHABLE NS_ASSERT(false); NS_UNREACHABLE
#define NS_ASSERT_ASSUME(expr) NS_ASSERT(expr); NS_ASSUME(expr)

namespace Noesis
{

struct ErrorContext { const char* uri; uint32_t line; uint32_t column; };

typedef bool (*AssertHandler)(const char* file, uint32_t line, const char* expr);
typedef void (*ErrorHandler)(const char* file, uint32_t line, const char* message, bool fatal);
typedef void (*ErrorHandler2)(const char* file, uint32_t line, const char* message, bool fatal,
    ErrorContext* context, void* user);

struct ErrorHandlerData { ErrorHandler2 handler; void *user; };

/// Registers a handler function for all future asserts. The default handler raises an error.
/// Returns a pointer to the previous function registered so that it can be restored later
NS_CORE_KERNEL_API AssertHandler SetAssertHandler(AssertHandler handler);

/// Executes the registered assert handler and returns true if the handler requires a breakpoint
NS_CORE_KERNEL_API bool InvokeAssertHandler(const char* file, uint32_t line, const char* expr);

/// Registers a global handler function for all future errors. The default handler emits a log.
/// The global handler is invoked when no other handler has been defined for the thread.
/// Returns a pointer to the previous function registered so that it can be restored later
NS_CORE_KERNEL_API ErrorHandler SetErrorHandler(ErrorHandler handler);

/// Executes the registered error handler for this thread. If the thread does not have an
/// explicit error handler registered then the global handler is invoked
NS_CORE_KERNEL_API void InvokeErrorHandler(const char* file, uint32_t line, bool fatal,
    ErrorContext* context, NS_FORMAT_PRINTF const char* format, ...) NS_FORMAT_PRINTF_ATTR(5);

/// Registers a handler function for all future errors in this thread. Default value is null.
/// When this is null, the thread handler is disabled and the global function is used instead.
/// Returns a pointer to the previous handler registered so that it can be restored later
NS_CORE_KERNEL_API ErrorHandlerData SetThreadErrorHandler(void* user, ErrorHandler2 handler);

/// Execute the given thread error handler or the global handler if it is null
NS_CORE_KERNEL_API void InvokeThreadErrorHandler(void* user, ErrorHandler2 handler,
    const char* file, uint32_t line, bool fatal, ErrorContext* context, const char* message);

}

#endif
