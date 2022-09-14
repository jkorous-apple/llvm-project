//===- CompileJobCacheKey.h -------------------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
///
/// \file Functions for working with compile job cache keys.
///
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_FRONTEND_COMPILEJOBCACHEKEY_H
#define LLVM_CLANG_FRONTEND_COMPILEJOBCACHEKEY_H

#include "llvm/ADT/ArrayRef.h"
#include "llvm/CAS/CASID.h"
#include "llvm/Support/Error.h"

namespace llvm {
namespace cas {
class ObjectStore;
}
class raw_ostream;
} // namespace llvm

namespace clang {

class CompilerInvocation;
class DiagnosticsEngine;

/// Create a cache key for the given \c CompilerInvocation as a \c CASID.
llvm::Optional<llvm::cas::CASID>
createCompileJobCacheKey(llvm::cas::ObjectStore &CAS, DiagnosticsEngine &Diags,
                         const CompilerInvocation &Invocation);

/// Perform any destructive changes needed to canonicalize \p Invocation for
/// caching, extracting the settings that affect compilation even if they do not
/// affect caching, and return the resulting cache key as a \c CASID.
llvm::Optional<llvm::cas::CASID> canonicalizeAndCreateCacheKey(
    llvm::cas::ObjectStore &CAS, DiagnosticsEngine &Diags,
    CompilerInvocation &Invocation, bool &WriteOutputAsCASID);

/// Print the structure of the cache key given by \p Key to \p OS. Returns an
/// error if the key object does not exist in \p CAS, or is malformed.
llvm::Error printCompileJobCacheKey(llvm::cas::ObjectStore &CAS,
                                    llvm::cas::CASID Key,
                                    llvm::raw_ostream &OS);

} // namespace clang

#endif // LLVM_CLANG_FRONTEND_COMPILEJOBCACHEKEY_H
