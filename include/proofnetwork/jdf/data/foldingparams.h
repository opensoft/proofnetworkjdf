#ifndef FOLDINGPARAMS_H
#define FOLDINGPARAMS_H

#include "proofnetwork/jdf/data/abstractresource.h"

#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class FoldingParamsPrvate;
class PROOF_NETWORK_JDF_EXPORT FoldingParams : public AbstractResource
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(FoldingParams)
public:
    QString foldCatalog() const;
    // Describes the type of fold according to the folding catalog
    // Value format is: " Fn-i " where “n” is the number of finished
    // pages and “i” is either an integer, which identifies a particular
    // fold or the letter "X" , which identifies a generic fold.
    // E.g., "F6-2" describes a Z-fold of 6 finished pages, and "F6-X . "
    // describes a generic fold with 6 finished pages.
    // Reference: http://www.cip4.org/documents/jdf_specifications/html/Resources.html#0_FoldingParams
    void setFoldCatalog(const QString &foldCatalog);

    static FoldingParamsSP create();

    static FoldingParamsSP fromJdf(QXmlStreamReader &xmlReader);
    void toJdf(QXmlStreamWriter &jdfWriter);
    static FoldingParamsSP defaultObject();

signals:
    void foldCatalogChanged(const QString &arg);

protected:
    explicit FoldingParams();

};


}
}

#endif // FOLDINGPARAMS_H
