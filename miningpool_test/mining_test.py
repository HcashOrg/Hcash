#encoding: utf8
import json
from rpc_client import RpcConnection

import time
import traceback
import pyblake2
import struct
import numpy
rpc_cli = None



def initConnect():
    global rpc_cli

    port = 12345
    user = 'a'
    password = 'b'
    rpc_cli = RpcConnection('127.0.0.1', port)
    rpc_cli.request("login", [user, password])
    rpc_cli.request("wallet_open", ["op"])
    rpc_cli.request("wallet_unlock", ["12345678", "12345678"])
    return rpc_cli





from ctypes import *
import binascii
main = R"F:\hshare\blake\blake_lib\Debug\blake_lib.dll"






def get_work():
    global rpc_cli
    resp = rpc_cli.request("get_work", [])
    print resp
    json_data = json.loads(resp)
    h = cdll.LoadLibrary(main)

    length = len(json_data["result"]["data"])
    noNoncedata_str = str(json_data["result"]["data"][0:length-16])


    target = int(json_data["result"]["target"],16)
    success = 0
    x = numpy.uint64(0)
    while True:

        temp_str = str(noNoncedata_str) + binascii.hexlify(struct.pack("<Q",x))
        print temp_str
        noNoncedata = binascii.a2b_hex(temp_str)
        data = noNoncedata
        print
        r = c_char_p( h.blake256_hash_hex(data,len(data)))
        hash = str(r.value)
        if int(hash,16)<=target:
            success = x
            break
        x=x+1
    print "success",success
    print "target",target
    print "hash",hash

    resp = rpc_cli.request("submit_block", [json_data["result"]["hashnoNonce"],int(success)])
    print resp
    #print noNoncedata





def send_transaction():
    initConnect()
    get_work()




if __name__ == "__main__":
    send_transaction()