#include "test/test_bitcoin.h"
#include "test/test_random.h"

#include <stdint.h>
#include <vector>
#include <boost/test/unit_test.hpp>

#include "base58.h"
#include "key.h"
#include "utilstrencodings.h"
#include "script/script.h"
#include "coins.h"
#include "consensus/consensus.h"
#include "core_io.h"
#include "keystore.h"
#include "validation.h"

#include <univalue.h>
#include "rpc/server.h"
#include "rpc/client.h"

#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>

// https://www.qiujiawei.com/crypto-1-ecc/
// https://www.cnblogs.com/X-knight/p/9153209.html

BOOST_FIXTURE_TEST_SUITE(me_tests, BasicTestingSetup)

using namespace std;

UniValue test_createrawtransaction() {
    std::string args = "createrawtransaction [{\"txid\":\"db949bca827cbe1f5f18848cf55cbc2eedd3cf9633fb9b88e546171087cef4ff\",\"vout\":0}] {\"mtUjv2TWT2wMQ86LoshoK5U8dPTL213Zep\":0.0001}";
    std::vector<std::string> vArgs;
    boost::split(vArgs, args, boost::is_any_of(" \t"));
    std::string strMethod = vArgs[0];
    vArgs.erase(vArgs.begin());
    JSONRPCRequest request;
    request.params = RPCConvertValues(strMethod, vArgs);
    
    RPCTypeCheck(request.params, boost::assign::list_of(UniValue::VARR)(UniValue::VOBJ)(UniValue::VNUM), true);
    if (request.params[0].isNull() || request.params[1].isNull())
        throw JSONRPCError(RPC_INVALID_PARAMETER, "Invalid parameter, arguments 1 and 2 must be non-null");

    UniValue inputs = request.params[0].get_array();
    UniValue sendTo = request.params[1].get_obj();

    CMutableTransaction rawTx;

    if (request.params.size() > 2 && !request.params[2].isNull()) {
        int64_t nLockTime = request.params[2].get_int64();
        if (nLockTime < 0 || nLockTime > std::numeric_limits<uint32_t>::max())
            throw JSONRPCError(RPC_INVALID_PARAMETER, "Invalid parameter, locktime out of range");
        rawTx.nLockTime = nLockTime;
    }

    for (unsigned int idx = 0; idx < inputs.size(); idx++) {
        const UniValue& input = inputs[idx];
        const UniValue& o = input.get_obj();

        uint256 txid = ParseHashO(o, "txid");

        const UniValue& vout_v = find_value(o, "vout");
        if (!vout_v.isNum())
            throw JSONRPCError(RPC_INVALID_PARAMETER, "Invalid parameter, missing vout key");
        int nOutput = vout_v.get_int();
        if (nOutput < 0)
            throw JSONRPCError(RPC_INVALID_PARAMETER, "Invalid parameter, vout must be positive");

        uint32_t nSequence = (rawTx.nLockTime ? std::numeric_limits<uint32_t>::max() - 1 : std::numeric_limits<uint32_t>::max());

        // set the sequence number if passed in the parameters object
        const UniValue& sequenceObj = find_value(o, "sequence");
        if (sequenceObj.isNum()) {
            int64_t seqNr64 = sequenceObj.get_int64();
            if (seqNr64 < 0 || seqNr64 > std::numeric_limits<uint32_t>::max())
                throw JSONRPCError(RPC_INVALID_PARAMETER, "Invalid parameter, sequence number is out of range");
            else
                nSequence = (uint32_t)seqNr64;
        }

        CTxIn in(COutPoint(txid, nOutput), CScript(), nSequence);

        rawTx.vin.push_back(in);
    }

    set<CBitcoinAddress> setAddress;
    vector<string> addrList = sendTo.getKeys();
    BOOST_FOREACH(const string& name_, addrList) {

        if (name_ == "data") {
            std::vector<unsigned char> data = ParseHexV(sendTo[name_].getValStr(),"Data");

            CTxOut out(0, CScript() << OP_RETURN << data);
            rawTx.vout.push_back(out);
        } else {
            CBitcoinAddress address(name_);
            if (!address.IsValid())
                throw JSONRPCError(RPC_INVALID_ADDRESS_OR_KEY, string("Invalid Bitcoin address: ")+name_);

            if (setAddress.count(address))
                throw JSONRPCError(RPC_INVALID_PARAMETER, string("Invalid parameter, duplicated address: ")+name_);
            setAddress.insert(address);

            CScript scriptPubKey = GetScriptForDestination(address.Get());
            CAmount nAmount = AmountFromValue(sendTo[name_]);

            CTxOut out(nAmount, scriptPubKey);
            rawTx.vout.push_back(out);
        }
    }

    return EncodeHexTx(rawTx);
}

BOOST_AUTO_TEST_CASE(me_1)
{
    CBitcoinSecret vchSecret;
    vchSecret.SetString("cQ82WpB4FLdszixBJGbPkAEBVxwgaLJsPaUQxFduhMgYcTbAUzK5");
    CKey key = vchSecret.GetKey();
    CPubKey pubKey = key.GetPubKey();
    std::cout << vchSecret.ToString() << " \nkey: " << HexStr(key.begin(), key.end())
              << " \npubKey: " << HexStr(pubKey.begin(), pubKey.end()) << std::endl;
    CKeyID keyID = pubKey.GetID();
    CBitcoinAddress address(keyID);
    std::cout << "address: " << address.ToString() << std::endl;

    std::vector<unsigned char> ret = ParseHex("03873f59bd3550ad4556651e0c1e08d6d10efde5fa120c24aa9fd4cd05097fe694");
    CPubKey pubKey1(ret);
    CBitcoinAddress address1(pubKey1.GetID());
    std::cout << "address: " << address1.ToString() << std::endl;

    CHashWriter ss(SER_GETHASH, 0);
    ss << strMessageMagic;
    std::string strMessage = "hi";
    ss << strMessage;
    std::vector<unsigned char> vchSig;
    key.SignCompact(ss.GetHash(), vchSig);
    std::cout << EncodeBase64(&vchSig[0], vchSig.size()) << std::endl;

    UniValue rawtransaction = test_createrawtransaction();
    std::cout << rawtransaction.get_str() << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()
