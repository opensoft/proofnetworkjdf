#ifndef PROOFNETWORKJDF_GLOBAL_H
#define PROOFNETWORKJDF_GLOBAL_H

#ifdef PROOF_NETWORK_JDF_LIB
#    define PROOF_NETWORK_JDF_EXPORT Q_DECL_EXPORT
#else
#    define PROOF_NETWORK_JDF_EXPORT Q_DECL_IMPORT
#endif

#include "proofnetwork/proofnetwork_global.h"

#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(proofNetworkJdfDataLog);

namespace Proof {
constexpr long NETWORK_JDF_MODULE_CODE = 304;
}
#endif // PROOFNETWORKJDF_GLOBAL_H
