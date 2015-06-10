#ifndef MEDIALINK_H
#define MEDIALINK_H

#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/data/abstractresourcelink.h"
#include "proofnetwork/jdf/data/media.h"

namespace Proof {
namespace Jdf {

class MediaLink : public AbstractResourceLink
{
    Q_OBJECT
public:
    explicit MediaLink(const MediaSP &media, QObject *parent = 0) :
        AbstractResourceLink( qSharedPointerCast<AbstractResource>(media), parent)
    {
    }
};

}
}

#endif // MEDIALINK_H
