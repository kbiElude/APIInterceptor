/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef APIDUMPREPLAYER_EXPORT_H
#define APIDUMPREPLAYER_EXPORT_H

#if defined(APIDUMPREPLAYER_BUILDING_DLL)
    #define APIDUMPREPLAYER_API __declspec(dllexport)
#else
    #define APIDUMPREPLAYER_API __declspec(dllimport)
#endif

#endif /* APIDUMPREPLAYER_EXPORT_H */
