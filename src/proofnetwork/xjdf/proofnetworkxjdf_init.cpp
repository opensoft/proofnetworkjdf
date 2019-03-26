/* Copyright 2018, OpenSoft Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted
 * provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright notice, this list of
 * conditions and the following disclaimer in the documentation and/or other materials provided
 * with the distribution.
 *     * Neither the name of OpenSoft Inc. nor the names of its contributors may be used to endorse
 * or promote products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include "proofcore/proofglobal.h"

#include "proofnetwork/xjdf/data/boxpackingparams.h"
#include "proofnetwork/xjdf/data/colorintent.h"
#include "proofnetwork/xjdf/data/component.h"
#include "proofnetwork/xjdf/data/cuttingparams.h"
#include "proofnetwork/xjdf/data/deliveryparams.h"
#include "proofnetwork/xjdf/data/foldingintent.h"
#include "proofnetwork/xjdf/data/media.h"
#include "proofnetwork/xjdf/data/xjdfdocument.h"
#include "proofnetwork/xjdf/proofnetworkxjdf_global.h"
#include "proofnetwork/xjdf/proofnetworkxjdf_types.h"

Q_LOGGING_CATEGORY(proofNetworkXJdfDataLog, "proof.network.xjdf.data")

PROOF_LIBRARY_INITIALIZER(libraryInit)
{
    // clang-format off
   

    qRegisterMetaType<Proof::XJdf::XJdfDocument *>("Proof::XJdf::XJdfDocument *");

    qRegisterMetaType<Proof::XJdf::XJdfDocumentSP>("Proof::XJdf::XJdfDocumentSP");
    qRegisterMetaType<Proof::XJdf::XJdfDocumentWP>("Proof::XJdf::XJdfDocumentWP");

    Proof::XJdf::Intent::registerIntentCreator<Proof::XJdf::ColorIntent>(QStringLiteral("ColorIntent"));
    Proof::XJdf::Intent::registerIntentCreator<Proof::XJdf::FoldingIntent>(QStringLiteral("FoldingIntent"));
    Proof::XJdf::Resource::registerResourceCreator<Proof::XJdf::Component>(QStringLiteral("Component"));
    Proof::XJdf::Resource::registerResourceCreator<Proof::XJdf::CuttingParams>(QStringLiteral("CuttingParams"));
    Proof::XJdf::Resource::registerResourceCreator<Proof::XJdf::DeliveryParams>(QStringLiteral("DeliveryParams"));
    Proof::XJdf::Resource::registerResourceCreator<Proof::XJdf::BoxPackingParams>(QStringLiteral("BoxPackingParams"));
    Proof::XJdf::Resource::registerResourceCreator<Proof::XJdf::Media>(QStringLiteral("Media"));
//     clang-format on
}
