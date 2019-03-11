/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMTOOLSKB_H__
#define __DRMTOOLSKB_H__

#include <oemaeskeywrap.h>

DRM_RESULT DRM_CALL DRMTOOLS_BuildLPKB(
    __in                                             const OEM_AES_KEY_CONTEXT  *f_pDerivedEncryptionKey,
    __in                                             const OEM_AES_KEY_CONTEXT  *f_pDerivedSigningKey,
    __in                                                   DRM_DWORD             f_cDeviceKeys,
    __in_ecount( OEM_AESKEYWRAP_RANDOMLEN_IN_BYTES ) const DRM_BYTE             *f_rgbKeyRand1,
    __in_ecount( OEM_AESKEYWRAP_RANDOMLEN_IN_BYTES ) const DRM_BYTE             *f_rgbKeyRand2,
    __in_ecount( 2 )                                 const PRIVKEY_P256         *f_rgoDevicePrivkeys,
    __inout                                                DRM_DWORD            *f_pcbDeviceCertProtectedKeys,
    __out_ecount( *f_pcbDeviceCertProtectedKeys )          DRM_BYTE             *f_rgbDeviceCertProtectedKeys );

#endif /* __DRMTOOLSKB_H__ */

