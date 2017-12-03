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

    port = 44443
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
    begin_str = str(json_data["result"]["data"][0:280])
    end_str = str(json_data["result"]["data"][312:361])


    target = int(json_data["result"]["target"],16)
    success = 0
    x = numpy.uint64(0)
    y = numpy.uint64(0)
    while True:

        temp_str = str(begin_str) + binascii.hexlify(struct.pack("<Q",x)) +binascii.hexlify(struct.pack("<Q",y))+str(end_str)

        noNoncedata = binascii.a2b_hex(temp_str)
        data = noNoncedata
        r = c_char_p( h.blake256_hash_hex(data,len(data)))
        hash = str(r.value)
        if int(hash,16)<=target:
            success = x
            break
        x=x+1
    print "success",success
    print "target",target
    print "hash",hash

    resp = rpc_cli.request("submit_block", [json_data["result"]["hashnoNonce"],int(success),int(y)])
    print resp
    #print noNoncedata





def get_workex():
    global rpc_cli
    resp = rpc_cli.request("get_work", [])
    print resp
    json_data = json.loads(resp)
    h = cdll.LoadLibrary(main)

    length = len(json_data["result"]["data"])
    begin_str = str(json_data["result"]["data"][0:280])
    end_str = str(json_data["result"]["data"][312:361])


    target = int(json_data["result"]["target"],16)
    success = 0
    x = numpy.uint64(0)
    y = numpy.uint64(0)
    while True:

        temp_str = str(begin_str) + binascii.hexlify(struct.pack("<Q",x)) +binascii.hexlify(struct.pack("<Q",y))+str(end_str)

        noNoncedata = binascii.a2b_hex(temp_str)
        data = noNoncedata
        r = c_char_p( h.blake256_hash_hex(data,len(data)))
        hash = str(r.value)
        if int(hash,16)<=target:
            success = x
            break
        x=x+1
    print "success",success
    print "target",target
    print "hash",hash

    resp = rpc_cli.request("submit_blockex", [temp_str])
    print resp
    #print noNoncedata




def send_transaction():
    initConnect()
    get_work()
    get_workex()




if __name__ == "__main__":
    send_transaction()