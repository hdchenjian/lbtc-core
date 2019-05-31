#!/usr/bin/env python3
# encoding: utf-8

from bitcoinrpc.authproxy import AuthServiceProxy, JSONRPCException

def update_rpc_node():
    '''
    ./bitcoind -testnet -txreindex -rpcuser=luyao -rpcpassword=DONNNN
    '''
    rpc_connection = AuthServiceProxy("http://%s:%s@127.0.0.1:19332" % ('luyao', 'DONNNN'))
    print(rpc_connection.signmessagewithprivkey('cQ82WpB4FLdszixBJGbPkAEBVxwgaLJsPaUQxFduhMgYcTbAUzK5', 'hiiiiiiiiiiiiiiiiiiiiiiiii'))
    print(rpc_connection.verifymessage('mftBcEPBkrKZ8Gys5yyDfq8jXCydjf5MtZ',
                          'Hzbimu4CcxPujU4f9911jza4Ptkmpu4JZHKgYlPyHshnXfN4Mi0QLiy0xKD/a2tcWsEBCQEdxRg78uNnmlBMemQ=',
                          'hi'))
    #print(rpc_connection.getbestblockhash())
    #print(rpc_connection.getblock(rpc_connection.getbestblockhash()))
    #print(rpc_connection.addnode('47.96.169.139:19333', 'add'))
    #print(rpc_connection.addnode('192.168.1.139:19333', 'add'))
    #print(rpc_connection.addnode('192.168.1.139:19333', 'remove'))
    #print(rpc_connection.getpeerinfo())
    #print(rpc_connection.getnewaddress('lbtc'))
    #print(rpc_connection.getaccountaddress('lbtc'))
    #print(rpc_connection.getbalance())
    #print(rpc_connection.getwalletinfo())
    #print(rpc_connection.importprivkey('cQ82WpB4FLdszixBJGbPkAEBVxwgaLJsPaUQxFduhMgYcTbAUzK5', 'lbtc'))
    #print(rpc_connection.getaccount('mftBcEPBkrKZ8Gys5yyDfq8jXCydjf5MtZ'))
    #print(rpc_connection.listdelegates())
    #print(rpc_connection.register('mftBcEPBkrKZ8Gys5yyDfq8jXCydjf5MtZ', 'luyao'))
    #print(rpc_connection.vote('mftBcEPBkrKZ8Gys5yyDfq8jXCydjf5MtZ', 'luyao'))
    #print(rpc_connection.startforging('mftBcEPBkrKZ8Gys5yyDfq8jXCydjf5MtZ'))
    #print(rpc_connection.stopforging())
    #print(rpc_connection.sendtoaddress('mnDemujchwMCgDu7xCjDK7ZbsJqC32L1CG', 0.0001))
    #print(rpc_connection.dumpprivkey('mftBcEPBkrKZ8Gys5yyDfq8jXCydjf5MtZ'))

    #tx = rpc_connection.gettransactionnew('c30d4992d456efcc4bc390d3facaf68138fe0729d84d96cf1560d1e7479c2c57')
    # print(rpc_connection.help())
    # best_block_hash = rpc_connection.getbestblockhash()
    # blockhash = rpc_connection.getblockhash(2050113)
    # print(blockhash)
    # best_block = rpc_connection.getblock(best_block_hash)
    # print(best_block_hash, best_block)
    # tx_id = '163d33738e9f2fc4b3cdb860fe8fe3d16fcae6a9d3a8c805e8c8b6607fe14c53'
    # print(rpc_connection.gettxout(tx_id, 0))

    # print(rpc_connection.gettxoutproof([tx_id]))
    #print(rpc_connection.gettxoutsetinfo())

    # print(rpc_connection.gettransactionnew('45581dcfe9324bdee8bfed7a3cd20000839cfd836792fb116d9c2bfe187df67f'))

    # print(rpc_connection.getchaintips())
    # print(rpc_connection.getmempoolinfo())
    # print(rpc_connection.getrawmempool(True))

    # print(rpc_connection.listreceivedvotes('TestDelegates'))
    # print(rpc_connection.listvotercommittees('1CKbTd4ThjmRFhaGbGVfqa5B1ivLuxYHQD'))
    # print(rpc_connection.listcommitteevoters('TestCommitteesName'))
    # print(rpc_connection.listvoteddelegates('1LAMDkarMYfZXcRQX5ZKhSafQBJqcRf91v'))

    # print(rpc_connection.listcommitteebills('TestCommitteesName'))
    # print(rpc_connection.listvoterbills('1CKbTd4ThjmRFhaGbGVfqa5B1ivLuxYHQD'))

    '''
    print(rpc_connection.getmininginfo())
    print(rpc_connection.getblocktemplate())
    print(rpc_connection.getnetworkhashps(5031939))
    '''


if __name__ == '__main__':
    update_rpc_node()

