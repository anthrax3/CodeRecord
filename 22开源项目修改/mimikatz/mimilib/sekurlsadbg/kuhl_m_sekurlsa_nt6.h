/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "kwindbg.h"
#include <bcrypt.h>

typedef struct _KIWI_HARD_KEY {
	ULONG cbSecret;
	BYTE data[ANYSIZE_ARRAY]; // etc...
} KIWI_HARD_KEY, *PKIWI_HARD_KEY;

typedef struct _KIWI_BCRYPT_KEY {
	ULONG size;
	ULONG tag;	// 'MSSK'
	ULONG type;
	ULONG unk0;
	ULONG unk1;
	ULONG unk2;
	KIWI_HARD_KEY hardkey;
} KIWI_BCRYPT_KEY, *PKIWI_BCRYPT_KEY;

typedef struct _KIWI_BCRYPT_KEY8 {
	ULONG size;
	ULONG tag;	// 'MSSK'
	ULONG type;
	ULONG unk0;
	ULONG unk1;
	ULONG unk2;
	ULONG unk3;
	PVOID unk4;	// before, align in x64
	KIWI_HARD_KEY hardkey;
} KIWI_BCRYPT_KEY8, *PKIWI_BCRYPT_KEY8;

typedef struct _KIWI_BCRYPT_KEY81 {
	ULONG size;
	ULONG tag;	// 'MSSK'
	ULONG type;
	ULONG unk0;
	ULONG unk1;
	ULONG unk2; 
	ULONG unk3;
	ULONG unk4;
	PVOID unk5;	// before, align in x64
	ULONG unk6;
	ULONG unk7;
	ULONG unk8;
	ULONG unk9;
	KIWI_HARD_KEY hardkey;
} KIWI_BCRYPT_KEY81, *PKIWI_BCRYPT_KEY81;

typedef struct _KIWI_BCRYPT_HANDLE_KEY {
	ULONG size;
	ULONG tag;	// 'UUUR'
	PVOID hAlgorithm;
	PKIWI_BCRYPT_KEY key;
	PVOID unk0;
} KIWI_BCRYPT_HANDLE_KEY, *PKIWI_BCRYPT_HANDLE_KEY;

typedef struct _KIWI_BCRYPT_GEN_KEY {
	BCRYPT_ALG_HANDLE hProvider;
	BCRYPT_KEY_HANDLE hKey;
	PBYTE pKey;
	ULONG cbKey;
} KIWI_BCRYPT_GEN_KEY, *PKIWI_BCRYPT_GEN_KEY;

typedef NTSTATUS	(WINAPI * PBCRYPT_OPEN_ALGORITHM_PROVIDER)	(__out BCRYPT_ALG_HANDLE  *phAlgorithm, __in LPCWSTR pszAlgId, __in_opt LPCWSTR pszImplementation, __in ULONG dwFlags);
typedef NTSTATUS	(WINAPI * PBCRYPT_SET_PROPERTY)				(__inout BCRYPT_HANDLE hObject, __in LPCWSTR pszProperty, __in_bcount(cbInput) PUCHAR pbInput, __in ULONG cbInput, __in ULONG dwFlags);
typedef NTSTATUS	(WINAPI * PBCRYPT_GET_PROPERTY)				(__in BCRYPT_HANDLE hObject, __in LPCWSTR pszProperty, __out_bcount_part_opt(cbOutput, *pcbResult) PUCHAR pbOutput, __in ULONG cbOutput, __out ULONG *pcbResult, __in ULONG dwFlags);
typedef NTSTATUS	(WINAPI * PBCRYPT_GENERATE_SYMMETRIC_KEY)	(__inout BCRYPT_ALG_HANDLE hAlgorithm, __out BCRYPT_KEY_HANDLE *phKey, __out_bcount_full_opt(cbKeyObject) PUCHAR pbKeyObject, __in ULONG cbKeyObject, __in_bcount(cbSecret) PUCHAR pbSecret, __in ULONG cbSecret, __in ULONG dwFlags);
typedef NTSTATUS	(WINAPI * PBCRYPT_DESTROY_KEY)				(__inout BCRYPT_KEY_HANDLE hKey);
typedef NTSTATUS	(WINAPI * PBCRYPT_CLOSE_ALGORITHM_PROVIDER)	(__inout BCRYPT_ALG_HANDLE hAlgorithm, __in ULONG dwFlags);
typedef NTSTATUS	(WINAPI * PBCRYPT_ENCRYPT)					(__inout BCRYPT_KEY_HANDLE hKey, __in_bcount_opt(cbInput) PUCHAR pbInput, __in ULONG cbInput, __in_opt VOID *pPaddingInfo, __inout_bcount_opt(cbIV) PUCHAR pbIV, __in ULONG cbIV, __out_bcount_part_opt(cbOutput, *pcbResult) PUCHAR pbOutput, __in ULONG cbOutput, __out ULONG *pcbResult, __in ULONG dwFlags);

NTSTATUS kuhl_m_sekurlsa_nt6_init();
NTSTATUS kuhl_m_sekurlsa_nt6_clean();

NTSTATUS kuhl_m_sekurlsa_nt6_LsaInitializeProtectedMemory();
VOID kuhl_m_sekurlsa_nt6_LsaCleanupProtectedMemory();
VOID WINAPI kuhl_m_sekurlsa_nt6_LsaUnprotectMemory (IN PVOID Buffer, IN ULONG BufferSize);

NTSTATUS kuhl_m_sekurlsa_nt6_acquireKeys(ULONG_PTR pInitializationVector, ULONG_PTR phAesKey, ULONG_PTR ph3DesKey);
BOOL kuhl_m_sekurlsa_nt6_acquireKey(ULONG_PTR phKey, PKIWI_BCRYPT_GEN_KEY pGenKey);