/////////////////////////////////////////////////////////
///                                                   ///
///    ░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒   ///
///   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒   ///
///   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒   ///
///   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓██████▓▒░   ///
///   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒   ///
///   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒   ///
///    ░▒▓██████▓▒░ ░▒▓██████▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒   ///
///      ░▒▓█▓▒░                                      ///
///       ░▒▓██▓▒░                                    ///
///                                                   ///
///   * This C (11) code was generated by the QUIXCC  ///
///     Language Compiler Suite.                      ///
///                                                   ///
///   Transcompiled source code may be encumbered by  ///
///   original source code licensing.                 ///
///                                                   ///
/////////////////////////////////////////////////////////

#include <stdint.h>
#include <stdbool.h>

#ifndef __QUIX_CODEGEN__
#define __QUIX_CODEGEN__

typedef uint8_t quint8;
typedef uint16_t quint16;
typedef uint32_t quint32;
typedef uint64_t quint64;
typedef int8_t qint8;
typedef int16_t qint16;
typedef int32_t qint32;
typedef int64_t qint64;
typedef bool qbool;
typedef float qfloat32;
typedef double qfloat64;
typedef void qvoid;

#ifndef __SIZEOF_INT128__
#error "QUIXCC requires support for __int128 to support qint128 and quint128 types."
#endif

typedef __int128 qint128;
typedef unsigned __int128 quint128;

/* Architecture-specific definitions */
#if UINTPTR_MAX == 0xFF
#define QPTRSIZE 8
#elif UINTPTR_MAX == 0xFFFF
#define QPTRSIZE 16
#elif UINTPTR_MAX == 0xFFFFFFFF
#define QPTRSIZE 32
#elif UINTPTR_MAX == 0xFFFFFFFFFFFFFFFFu
#define QPTRSIZE 64
#else
#error "Target architecture not supported by QUIXCC " \
       "because pointer size is unknown."
#endif

#if QPTRSIZE == 8
typedef quint8 quintptr;
typedef qint8 qintptr;
#elif QPTRSIZE == 16
typedef quint16 quintptr;
typedef qint16 qintptr;
#elif QPTRSIZE == 32
typedef quint32 quintptr;
typedef qint32 qintptr;
#elif QPTRSIZE == 64
typedef quint64 quintptr;
typedef qint64 qintptr;
#endif

/* Macro definitions */
#ifndef qexport
#if defined(__clang__)
#define qexport __attribute__((visibility("default")))
#elif defined(__GNUC__)
#define qexport __attribute__((visibility("default")))
#else
#error "Unsupported compiler; cannot define qexport."
#endif
#endif

#ifndef QROTL_EXPR
#define QROTL_EXPR(x, n) ((x << n) | (x >> (8 * sizeof(x) - n)))
#endif
#ifndef QROTR_EXPR
#define QROTR_EXPR(x, n) ((x >> n) | (x << (8 * sizeof(x) - n)))
#endif

#endif /* __QUIX_CODEGEN__ */

qexport qvoid main() {
  qint8 *mac1 = "macro_1() {\n} not implemented";
  return;
};
