/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/
#pragma once

ENTER_PK_NAMESPACE;

#define CallXmlBuilder(context, fn)   {\
    DRM_FOR_INFINITE\
    {\
        dr = (fn);\
        if ( dr == DRM_E_BUFFERTOOSMALL )\
        {\
            ChkDR(DRMTOOLS_ReallocXmlContext(&(context)));\
            continue;\
        }\
        ChkDR(dr);\
        break;\
    }\
}

#define DRM_TOOLS_COPY_DRM_CONST_STRING(dst,psrc)                                                              \
    DRM_DO {                                                                                                   \
            DRM_DWORD __cch = (psrc)->cchString < DRM_NO_OF( dst ) ? (psrc)->cchString : DRM_NO_OF( dst ) - 1; \
            MEMCPY( (dst), (psrc)->pwszString, __cch * sizeof(DRM_WCHAR) );                                    \
            ( dst )[ __cch ] = g_wchNull;                                                                      \
    } DRM_WHILE_FALSE

#define MAX_FILENAME 1023
#define XML_INIT_SIZE   1024

EXIT_PK_NAMESPACE;
