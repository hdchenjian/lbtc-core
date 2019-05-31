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

BOOST_FIXTURE_TEST_SUITE(me_tests, BasicTestingSetup)

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
}

BOOST_AUTO_TEST_SUITE_END()
