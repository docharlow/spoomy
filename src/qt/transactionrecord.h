// Copyright (c) 2009-2018 Satoshi Nakamoto
// Copyright (c) 2009-2018 The Bitcoin Developers
// Copyright (c) 2014-2018 The Dash Core Developers
// Copyright (c) 2016-2018 Duality Blockchain Solutions Developers
// Copyright (c) 2017-2018 Spoomy Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ZUMY_QT_TRANSACTIONRECORD_H
#define ZUMY_QT_TRANSACTIONRECORD_H

#include "amount.h"
#include "uint256.h"

#include <QList>
#include <QString>

class CWallet;
class CWalletTx;

/** UI model for transaction status. The transaction status is the part of a transaction that will change over time.
 */
class TransactionStatus
{
public:
    TransactionStatus():
        countsForBalance(false), sortKey(""),
        matures_in(0), status(Offline), depth(0), open_for(0), cur_num_blocks(-1)
    { }

    enum Status {
        Confirmed,          /**< Have 10 or more confirmations (normal tx) or fully mature (mined tx) **/
        /// Normal (sent/received) transactions
        OpenUntilDate,      /**< Transaction not yet final, waiting for date */
        OpenUntilBlock,     /**< Transaction not yet final, waiting for block */
        Offline,            /**< Not sent to any other nodes **/
        Unconfirmed,        /**< Not yet mined into a block **/
        Confirming,         /**< Confirmed, but waiting for the recommended number of confirmations **/
        Conflicted,         /**< Conflicts with other transaction or mempool **/
        /// Generated (mined) transactions
        Immature,           /**< Mined but waiting for maturity */
        MaturesWarning,     /**< Transaction will likely not mature because no nodes have confirmed */
        NotAccepted         /**< Mined but not accepted */
    };

    /// Transaction counts towards available balance
    bool countsForBalance;
    /// Sorting key based on status
    std::string sortKey;

    /** @name Generated (mined) transactions
       @{*/
    int matures_in;
    /**@}*/

    /** @name Reported status
       @{*/
    Status status;
    qint64 depth;
    qint64 open_for; /**< Timestamp if status==OpenUntilDate, otherwise number
                      of additional blocks that need to be mined before
                      finalization */
    /**@}*/

    /** Current number of blocks (to know whether cached status is still valid) */
    int cur_num_blocks;

    //** Know when to update transaction for is locks **/
    int cur_num_is_locks;
};

/** UI model for a transaction. A core transaction can be represented by multiple UI transactions if it has
    multiple outputs.
 */
class TransactionRecord
{
public:
    enum Type
    {
        Other,
        Generated,
        SendToAddress,
        SendToOther,
        RecvWithAddress,
        RecvFromOther,
        SendToSelf,
        RecvWithPrivateSend,
        PrivateSendDenominate,
        PrivateSendCollateralPayment,
        PrivateSendMakeCollaterals,
        PrivateSendCreateDenominations,
        PrivateSend
    };

    /** Number of confirmation recommended for accepting a transaction */
    static const int RecommendedNumConfirmations = 10;

    TransactionRecord():
            hash(), time(0), type(Other), address(""), debit(0), credit(0), idx(0)
    {
    }

    TransactionRecord(uint256 _hash, qint64 _time):
            hash(_hash), time(_time), type(Other), address(""), debit(0),
            credit(0), idx(0)
    {
    }

    TransactionRecord(uint256 _hash, qint64 _time,
                Type _type, const std::string &_address,
                const CAmount& _debit, const CAmount& _credit):
            hash(_hash), time(_time), type(_type), address(_address), debit(_debit), credit(_credit),
            idx(0)
    {
    }

    /** Decompose CWallet transaction to model transaction records.
     */
    static bool showTransaction(const CWalletTx &wtx);
    static QList<TransactionRecord> decomposeTransaction(const CWallet *wallet, const CWalletTx &wtx);

    /** @name Immutable transaction attributes
      @{*/
    uint256 hash;
    qint64 time;
    Type type;
    std::string address;
    CAmount debit;
    CAmount credit;
    /**@}*/

    /** Subtransaction index, for sort key */
    int idx;

    /** Status: can change with block chain update */
    TransactionStatus status;

    /** Whether the transaction was sent/received with a watch-only address */
    bool involvesWatchAddress;

    /** Return the unique identifier for this transaction (part) */
    QString getTxID() const;

    /** Format subtransaction id */
    static QString formatSubTxId(const uint256 &hash, int vout);

    /** Update status from core wallet tx.
     */
    void updateStatus(const CWalletTx &wtx);

    /** Return whether a status update is needed.
     */
    bool statusUpdateNeeded();
};

#endif // ZUMY_QT_TRANSACTIONRECORD_H
