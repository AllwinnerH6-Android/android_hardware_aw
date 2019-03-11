/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/
/*
      File fieldpriv.h.   Version 20 September 2002

      Declarations for field routines which the application program
      doesn't need to know about.
*/

#ifndef __FIELDPRIV_H
#define __FIELDPRIV_H 1
#include "bigpriv.h"
#include "field.h"

ENTER_PK_NAMESPACE;

DRM_API DRM_BOOL DRM_CALL Kfdesc_initialize(field_desc_t*, const DRM_DWORD, struct bigctx_t *f_pBigCtx);

EXIT_PK_NAMESPACE;

#endif /* __FIELDPRIV_H */
