/* $Id: lsass.h,v 1.4 2002/11/03 20:01:05 chorns Exp $
 *
 * COPYRIGHT:       See COPYING in the top level directory
 * PROJECT:         ReactOS system libraries
 * FILE:            include/lsass/lsass.h
 * PURPOSE:         LSASS API declarations
 * UPDATE HISTORY:
 *                  Created 05/08/00
 */

#ifndef __INCLUDE_LSASS_LSASS_H
#define __INCLUDE_LSASS_LSASS_H

#include <ntos.h>
#include <lsass/ntsecapi.h>
#include <napi/lpc.h>

#define LSASS_REQUEST_REGISTER_LOGON_PROCESS               (1)
#define LSASS_REQUEST_CALL_AUTHENTICATION_PACKAGE          (2)
#define LSASS_REQUEST_DEREGISTER_LOGON_PROCESS             (3)
#define LSASS_REQUEST_LOGON_USER                           (4)
#define LSASS_REQUEST_LOOKUP_AUTHENTICATION_PACKAGE        (5)
#define LSASS_REQUEST_MAXIMUM                              (6)

typedef struct _LSASS_LOOKUP_AUTHENTICATION_PACKAGE_REQUEST
{
   ULONG PackageNameLength;
   WCHAR PackageName[0];
} LSASS_LOOKUP_AUTHENTICATION_PACKAGE_REQUEST,
 *PLSASS_LOOKUP_AUTHENTICATION_PACKAGE_REQUEST;

typedef struct _LSASS_LOOKUP_AUTHENTICATION_PACKAGE_REPLY
{
   ULONG Package;
} LSASS_LOOKUP_AUTHENTICATION_PACKAGE_REPLY,
 *PLSASS_LOOKUP_AUTHENTICATION_PACKAGE_REPLY;

typedef struct _LSASS_DEREGISTER_LOGON_PROCESS_REQUEST
{
} LSASS_DEREGISTER_LOGON_PROCESS_REQUEST,
 *PLSASS_DEREGISTER_LOGON_PROCES_REQUEST;

typedef struct _LSASS_DEREGISTER_LOGON_PROCESS_REPLY
{   
} LSASS_DEREGISTER_LOGON_PROCESS_REPLY,
 *PLSASS_DEREGISTER_LOGON_PROCESS_REPLY;

typedef struct _LSASS_CALL_AUTHENTICATION_PACKAGE_REQUEST
{
   ULONG AuthenticationPackage;
   ULONG InBufferLength;
   UCHAR InBuffer[0];
} LSASS_CALL_AUTHENTICATION_PACKAGE_REQUEST,
*PLSASS_CALL_AUTHENTICATION_PACKAGE_REQUEST;

typedef struct _LSASS_CALL_AUTHENTICATION_PACKAGE_REPLY
{
   ULONG OutBufferLength;
   UCHAR OutBuffer[0];
} LSASS_CALL_AUTHENTICATION_PACKAGE_REPLY,
*PLSASS_CALL_AUTHENTICATION_PACKAGE_REPLY;

typedef struct _LSASS_LOGON_USER_REQUEST
{
   ULONG OriginNameLength;
   PWSTR OriginName;
   SECURITY_LOGON_TYPE LogonType;
   ULONG AuthenticationPackage;
   PVOID AuthenticationInformation;
   ULONG AuthenticationInformationLength;
   ULONG LocalGroupsCount;
   PSID_AND_ATTRIBUTES LocalGroups;
   TOKEN_SOURCE SourceContext;
   UCHAR Data[1];
} LSASS_LOGON_USER_REQUEST, *PLSASS_LOGON_USER_REQUEST;

typedef struct _LSASS_LOGON_USER_REPLY
{
   PVOID ProfileBuffer;
   ULONG ProfileBufferLength;
   LUID LogonId;
   HANDLE Token;
   QUOTA_LIMITS Quotas;
   NTSTATUS SubStatus;
   UCHAR Data[1];
} LSASS_LOGON_USER_REPLY, *PLSASS_LOGON_USER_REPLY;

typedef struct _LSASS_REGISTER_LOGON_PROCESS_REQUEST
{
   ULONG Length;
   WCHAR LogonProcessNameBuffer[127];
} LSASS_REGISTER_LOGON_PROCESS_REQUEST, *PLSASS_REGISTER_LOGON_PROCESS_REQUEST;

typedef struct _LSASS_REGISTER_LOGON_PROCESS_REPLY
{
   LSA_OPERATIONAL_MODE OperationalMode;
} LSASS_REGISTER_LOGON_PROCESS_REPLY, *PLSASS_REGISTER_LOGON_PROCESS_REPLY;

typedef struct _LSASS_REQUEST
{
   LPC_MESSAGE Header;
   ULONG Type;
   union
     {
	LSASS_REGISTER_LOGON_PROCESS_REQUEST RegisterLogonProcessRequest;
	LSASS_LOGON_USER_REQUEST LogonUserRequest;
	LSASS_CALL_AUTHENTICATION_PACKAGE_REQUEST 
	  CallAuthenticationPackageRequest;
	LSASS_DEREGISTER_LOGON_PROCESS_REPLY DeregisterLogonProcessRequest;
	LSASS_LOOKUP_AUTHENTICATION_PACKAGE_REQUEST
	  LookupAuthenticationPackageRequest;
     } d;
} LSASS_REQUEST, *PLSASS_REQUEST;

typedef struct _LSASS_REPLY
{
   LPC_MESSAGE Header;
   NTSTATUS Status;
   union
     {
	LSASS_REGISTER_LOGON_PROCESS_REPLY RegisterLogonProcessReply;
	LSASS_LOGON_USER_REPLY LogonUserReply;
	LSASS_CALL_AUTHENTICATION_PACKAGE_REPLY CallAuthenticationPackageReply;
	LSASS_DEREGISTER_LOGON_PROCESS_REPLY DeregisterLogonProcessReply;
	LSASS_LOOKUP_AUTHENTICATION_PACKAGE_REPLY 
	  LookupAuthenticationPackageReply;
     } d;
} LSASS_REPLY, *PLSASS_REPLY;

#endif /* __INCLUDE_LSASS_LSASS_H */
