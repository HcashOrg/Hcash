Hcash Projects information:
=====================================

The official website of Hcash Https://h.cash
wallet use tutorial:
English : https://github.com/HcashOrg/Hcash/blob/master/wallet%20use%20tutorial.docx
Chinese : https://github.com/HcashOrg/Hcash/blob/master/%E9%92%B1%E5%8C%85%E4%BD%BF%E7%94%A8%E6%95%99%E7%A8%8B.docx

What is Hcash?
--------------
### Introduction of Project Background

After the implementation of Hcash, it has been expanding Hcash ecosystem positively. After upgrading the main chain, Hcash ecosystem will reach a brand new phrase. After upgrading, Hcash will allow a variety of projects to issue blockchain assets on its main chain. The safety and high efficiency of Hcash will build a solid foundation for the future ecosystem.

Hcash aims at building a bridge of value communication. Through tireless efforts of Hcash teams, the anti-quantum scheme of Hcash has been completed. Hcash teams will continue to focus on technology development. Besides safety, Hcash technology team will work hard on the function and application of Hcash. The medium of blockchain system value and information exchange will be established, and be applied in finance, IoT, bit data and other areas. Having been developed in a high speed for a few months, Hcash has become a magnate with a top 30 market value in digital currency area. Thanks to the cooperation of Shanghai Jiao Tong University, The Hong Kong Polytechnic University and Monash University in Australia, Hcash also made huge progresses in technology.

### Technology Advantages
Hcash is very safe. It aims at building a bridge of value communication. On the basis of anti-quantum algorithm, Hcash has the downward compatibility with ECDSA signature scheme, which means that when quantum computers are really popularized, the safety of Hcash and its cross-chain feature will make it the “Noah's ark” for almost all digital currencies. Hcash will lead most digital currencies to survive quantum computers’ attack, and keep them safe until their anti-quantum feature is completed or bear them directly on the main chain.

Hcash chooses the Diffie-Hellman method prospectively, which enables the Key to pass insecure network safely; thus avoiding safety problems during transmission process and decreasing safety risks that are generated during the transmission process.

Hcash is a double-chain of block chain and DAG system. It realized the interconnection of information and value that bases on or does not base on blockchain. Hcash acts as the medium here, and the Hcash platform itself is the carrier of cross-platform information exchange. A fully encrypted communication among Hcash clients can be realized at the basis of zero-knowledge proof.

Intelligent contract is an indispensable part in digital currency ecosystem. Hcash puts a lot of efforts and develops the intelligent contract that is highly programmable and has a high load carrying capacity, which decreases the rate of problems such as ETH network congestion. The intelligent contract that uses C++11 and glua that are easy to program also make it easy for small-and-medium-sized enterprises to issue digital assets on Hcash conveniently, or to use as commercial private chain.

Network congestion has always been the biggest problem that digital currency faces. Bitcoin and ETH has small handling capacity, which causes network congestion to happen frequently. However, Hcash is prepared for large-scale commercial use. After upgrade, Hcash will have a handling capacity as high as 500tps, which is 70 times higher than that of BTC (6.99). This builds a solid foundation for small-scale uses with high frequency after large-scale uses.

Hcash will officially adopt the PoW+PoS mechanism in this upgrade. The mining processes of PoW and POS are organically combined to ensure the safety of the system. Besides, PoS lowers the threshold for participates and increases the number of deep participants. PoW can also attract geeks of digital currency to take part in Hcash’s ecosystem, which helps to open a new chapter for Hcash mining.

We want to thank community participants for their support and attention of Hcash, and thank Hcash teams and laboratories around the world for their hard work on day and night. After changing the main chain, Hcash will continue to cooperate with global R&D teams and use top-end cryptography knowledge; thus make the technology strength of Hcash stay in the lead in cryptocurrency.



Development Process
-------------------

The Hcash is being developed by cryptography labs in one of the China’s most prestigious university as well as other famous universities in Australia. We will periodically update you with the progress on this over time, and we expected the first release upgrade will happen soon at Dec 2017. Thanks for your attention and stay tuned for the further update from Hcash dev team.

Build on Linux
-------------------

update apt get and install addtional libraries

```
apt-get update
apt-get install -y git cmake libboost1.58-dev libboost1.58-all-dev autoconf
```

download code

```
git clone https://github.com/HcashOrg/Hcash.git --recursive
cd ./Hcash
git submodule update --init --recursive
```

building openssl

```
cd dependence/openssl1.0.2/
./config
make -j
sudo make install
```

building miniupnp

```
cd ../miniupnp/miniupnpc
cmake .
make
```

building leveldb

```
cd ../../leveldb
chmod u+x build_detect_platform
make
```

building berkeleyDB

```
cd ../db-5.3.28.NC/build_unix/
chmod u+x ../dist/configure
../dist/configure --enable-cxx
make -j
```

building fc

```
cd ../../fc
export OPENSSL_ROOT_DIR=”/usr/local/ssl/”
cmake .
chmod u+x ./vendor/scrypt-jane/test-speed.sh
chmod u+x ./vendor/scrypt-jane/test.sh
chmod u+x ./vendor/cyoencode-1.0.2/src/build.sh
chmod u+x ./vendor/secp256k1-zkp/configure
chmod u+x ./vendor/secp256k1-zkp/autogen.sh
cd ./vendor/secp256k1-zkp/
./autogen.sh
cd ../../
make
```

building hsrcore

```
cd ../../
cmake .
make
```

Build on Mac
-------------------


install homebrew

```
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```

install addtional libraries

```
brew update
sudo xcode-select --install
sudo xcodebuild -license accept
brew install cmake
brew install git
brew link --overwrite git
brew install boost@1.57
brew install autoconf
brew install automake
brew install libtool
```

download code

```
git clone https://github.com/HcashOrg/Hcash.git --recursive
cd ./Hcash
git submodule update --init --recursive
```

building openssl

```
cd dependence/openssl1.0.2/
./Configure darwin64-x86_64-cc
make -j
sudo make install
```

building miniupnp

```
cd ../miniupnp/miniupnpc
cmake .
make
```

building leveldb

```
cd ../../leveldb
chmod u+x build_detect_platform
make
```

building berkeleyDB

```
cd ../db-5.3.28.NC/build_unix/
chmod u+x ../dist/configure
../dist/configure --enable-cxx
make -j
```
if build error see https://lists.freebsd.org/pipermail/freebsd-current/2012-May/033615.html

building fc

```
cd ../../fc
export OPENSSL_ROOT_DIR="/usr/local/ssl/"
brew link boost\@1.57 --force
cmake .
chmod u+x ./vendor/scrypt-jane/test-speed.sh
chmod u+x ./vendor/scrypt-jane/test.sh
chmod u+x ./vendor/cyoencode-1.0.2/src/build.sh
chmod u+x ./vendor/secp256k1-zkp/configure
chmod u+x ./vendor/secp256k1-zkp/autogen.sh
cd ./vendor/secp256k1-zkp/
./autogen.sh
cd ../../
make
```

building hsrcore
```
cd ../../
cmake .
make -j3
make
```

License
-------

Hcash is released under the terms of the MIT license. To get more information please refer to  https://opensource.org/licenses/MIT.
