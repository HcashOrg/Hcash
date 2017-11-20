#!/usr/bin/env python
# encoding: utf-8

__author__ = 'hasee'

import socket
import json

class RpcConnection(object):
    request_template = '''{"jsonrpc":"2.0","id":"1","method":"%s","params":%s}'''
    ReadBufSize = 4096

    def __init__(self, ip, port):
        self.rpc_server_ip = ip
        self.rpc_server_port = port
        #self.request_template = request_template
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect((self.rpc_server_ip, self.rpc_server_port))

    def __del__(self):
        self.close()

    def request(self, method, args, log=False):
        args_str = ''.join(['[', ','.join(['"' + str(arg) + '"' for arg in args]), ']'])
        data_to_send = RpcConnection.request_template % (method, args_str)
        if log:
          print("cmd: %s" % data_to_send)
        #print RpcConnection.request_payload_template % (method, args_str)
        self.sock.send(data_to_send)

        resp_str_all = ''
        while True:
            resp_str = self.sock.recv(RpcConnection.ReadBufSize)
            if len(resp_str) != 0:
                resp_str_all = resp_str_all + resp_str
                try:
                    json.loads(resp_str_all)
                except:
                    continue
            break

        return resp_str_all

    def close(self):
        self.sock.close()


def create_btc_rpc_client():
    port = 10086
    user = 'admin'
    password = 'admin'
    conn = RpcConnection('127.0.0.1', port)
    conn.request("login", [user, password])
    return conn


def create_eth_rpc_client():
    port = 8545

    conn = RpcConnection('192.168.10.208', port)
    return conn

if __name__ == '__main__':
    pass

