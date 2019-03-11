/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_TOOLS_NETIO_H
#define __DRM_TOOLS_NETIO_H

#include <drmtypes.h>

ENTER_PK_NAMESPACE;

typedef enum __tageDRM_TOOLS_NET_ACTION {
    eDRM_TOOLS_NET_UNKNOWN               = 0,
    eDRM_TOOLS_NET_LEGACY                = 1,
    eDRM_TOOLS_NET_LICGET                = 2,
    eDRM_TOOLS_NET_LICACK                = 4,
    eDRM_TOOLS_NET_DOMLEAVE              = 8,
    eDRM_TOOLS_NET_DOMJOIN               = 16,
    eDRM_TOOLS_NET_DOWNLOAD              = 32,
    eDRM_TOOLS_NET_METERCERT             = 64,
    eDRM_TOOLS_NET_METERDATA             = 128,
    eDRM_TOOLS_NET_SERVERMETERING        = 256,
    eDRM_TOOLS_NET_ACTIVATIONGET         = 512,
    eDRM_TOOLS_NET_ACTIVATIONPOST        = 1024,
    eDRM_TOOLS_NET_LICGET_LEGACY         = eDRM_TOOLS_NET_LICGET         | eDRM_TOOLS_NET_LEGACY,
    eDRM_TOOLS_NET_METERCERT_LEGACY      = eDRM_TOOLS_NET_METERCERT      | eDRM_TOOLS_NET_LEGACY,
    eDRM_TOOLS_NET_METERDATA_LEGACY      = eDRM_TOOLS_NET_METERDATA      | eDRM_TOOLS_NET_LEGACY,
    eDRM_TOOLS_NET_SERVERMETERING_LEGACY = eDRM_TOOLS_NET_SERVERMETERING | eDRM_TOOLS_NET_LEGACY,
    eDRM_TOOLS_NET_SECURETIME_POST,
    eDRM_TOOLS_NET_SECURESTOP_POST,
} eDRM_TOOLS_NET_ACTION;


DRM_API DRM_BOOL DRM_CALL DRM_TOOLS_NETIO_IsNetIOSupported( DRM_VOID );
DRM_API DRM_BOOL DRM_CALL DRM_TOOLS_NETIO_IsNetIOUnsupported( DRM_VOID );

DRM_API DRM_RESULT DRM_CALL DRM_TOOLS_NETIO_SendData(
    __in_z                                    const DRM_CHAR              *f_pszUrl,
    __in                                            eDRM_TOOLS_NET_ACTION  f_eAction,
    __in_bcount( f_cbChallenge )              const DRM_BYTE              *f_pbChallenge,
    __in                                            DRM_DWORD              f_cbChallenge,
    __deref_out_bcount( *f_pcbResponse )            DRM_BYTE             **f_ppbResponse,
    __out_ecount( 1 )                               DRM_DWORD             *f_pcbResponse );

DRM_API DRM_RESULT DRM_CALL DRM_TOOLS_NETIO_SendDataProvisioning(
    __in_z                                      const DRM_CHAR              *f_pszServerUrl,
    __in_bcount( f_cbChallenge )                const DRM_BYTE              *f_pbChallenge,
    __in                                              DRM_DWORD              f_cbChallenge,
    __in                                        const DRM_UINT64            *f_pqwCorrelationID,
    __deref_out_bcount( *f_pcbResponse )              DRM_BYTE             **f_ppbResponse,
    __out_ecount( 1 )                                 DRM_DWORD             *f_pcbResponse,
    __deref_opt_out_bcount_opt( *f_pcbServerBlobOut ) DRM_BYTE             **f_ppbServerBlobOut,
    __out_ecount_opt( 1 )                             DRM_DWORD             *f_pcbServerBlobOut );

EXIT_PK_NAMESPACE;

#endif /* __DRM_TOOLS_NETIO_H */
