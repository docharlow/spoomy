// Copyright (c) 2009-2018 Satoshi Nakamoto
// Copyright (c) 2009-2018 The Bitcoin Developers
// Copyright (c) 2014-2018 The Dash Core Developers
// Copyright (c) 2017-2018 Spoomy Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ZUMY_CORE_MEMUSAGE_H
#define ZUMY_CORE_MEMUSAGE_H

#include "memusage.h"

#include "primitives/block.h"
#include "primitives/transaction.h"

static inline size_t RecursiveSpoomyUsage(const CScript& script) {
    return memusage::SpoomyUsage(*static_cast<const CScriptBase*>(&script));
}

static inline size_t RecursiveSpoomyUsage(const COutPoint& out) {
    return 0;
}

static inline size_t RecursiveSpoomyUsage(const CTxIn& in) {
    return RecursiveSpoomyUsage(in.scriptSig) + RecursiveSpoomyUsage(in.prevout);
}

static inline size_t RecursiveSpoomyUsage(const CTxOut& out) {
    return RecursiveSpoomyUsage(out.scriptPubKey);
}

static inline size_t RecursiveSpoomyUsage(const CTransaction& tx) {
    size_t mem = memusage::SpoomyUsage(tx.vin) + memusage::SpoomyUsage(tx.vout);
    for (std::vector<CTxIn>::const_iterator it = tx.vin.begin(); it != tx.vin.end(); it++) {
        mem += RecursiveSpoomyUsage(*it);
    }
    for (std::vector<CTxOut>::const_iterator it = tx.vout.begin(); it != tx.vout.end(); it++) {
        mem += RecursiveSpoomyUsage(*it);
    }
    return mem;
}

static inline size_t RecursiveSpoomyUsage(const CMutableTransaction& tx) {
    size_t mem = memusage::SpoomyUsage(tx.vin) + memusage::SpoomyUsage(tx.vout);
    for (std::vector<CTxIn>::const_iterator it = tx.vin.begin(); it != tx.vin.end(); it++) {
        mem += RecursiveSpoomyUsage(*it);
    }
    for (std::vector<CTxOut>::const_iterator it = tx.vout.begin(); it != tx.vout.end(); it++) {
        mem += RecursiveSpoomyUsage(*it);
    }
    return mem;
}

static inline size_t RecursiveSpoomyUsage(const CBlock& block) {
    size_t mem = memusage::SpoomyUsage(block.vtx);
    for (std::vector<CTransaction>::const_iterator it = block.vtx.begin(); it != block.vtx.end(); it++) {
        mem += RecursiveSpoomyUsage(*it);
    }
    return mem;
}

static inline size_t RecursiveSpoomyUsage(const CBlockLocator& locator) {
    return memusage::SpoomyUsage(locator.vHave);
}

#endif // ZUMY_CORE_MEMUSAGE_H
