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


#include "proofnetwork/xjdf/proofnetworkxjdf_global.h"

Q_LOGGING_CATEGORY(proofNetworkXJdfDataLog, "proof.network.xjdf.data")

PROOF_LIBRARY_INITIALIZER(libraryInit)
{
    // clang-format off
   

    qRegisterMetaType<Proof::XJdf::XJdfDocument *>("Proof::XJdf::XJdfDocument *");

    qRegisterMetaType<Proof::XJdf::XJdfNodeSP>("Proof::XJdf::XJdfNodeSP");
    qRegisterMetaType<Proof::XJdf::XJdfNodeWP>("Proof::XJdf::XJdfNodeWP");
    qRegisterMetaType<Proof::XJdf::XJdfDocumentSP>("Proof::XJdf::XJdfDocumentSP");
    qRegisterMetaType<Proof::XJdf::XJdfDocumentWP>("Proof::XJdf::XJdfDocumentWP");
    qRegisterMetaType<Proof::XJdf::XJmfDocumentSP>("Proof::XJdf::XJmfDocumentSP");
    qRegisterMetaType<Proof::XJdf::XJmfDocumentWP>("Proof::XJdf::XJmfDocumentWP");
    
    // clang-format on
}
