/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef REPLAYENGINEDLL_EXPORT_H
#define REPLAYENGINEDLL_EXPORT_H

#if defined(REPLAYENGINEDLL_BUILDING_DLL)
    #define REPLAYENGINEDLL_API __declspec(dllexport)
#else
    #define REPLAYENGINEDLL_API __declspec(dllimport)
#endif

#endif /* REPLAYENGINEDLL_EXPORT_H */
