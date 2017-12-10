// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "db.h"


#ifndef WIN32
#include <sys/stat.h>
#endif

#include <boost/filesystem.hpp>
#include <boost/version.hpp>
#include <openssl/rand.h>
#include <boost/thread.hpp>
#ifdef WIN32
#include <ShlObj.h>
#endif
#include <fc/log/logger.hpp>

using namespace std;
using namespace boost;


unsigned int nWalletDBUpdated;



#ifdef WIN32
#define MSG_NOSIGNAL        0
#define MSG_DONTWAIT        0

#ifndef S_IRUSR
#define S_IRUSR             0400
#define S_IWUSR             0200
#endif
#else
#define MAX_PATH            1024
#endif

//
// CDB
//

inline void MilliSleep(int64_t n)
{
#if BOOST_VERSION >= 105000
	boost::this_thread::sleep_for(boost::chrono::milliseconds(n));
#else
	boost::this_thread::sleep(boost::posix_time::milliseconds(n));
#endif
}
inline int64_t GetTimeMillis()
{
	return (boost::posix_time::ptime(boost::posix_time::microsec_clock::universal_time()) -
		boost::posix_time::ptime(boost::gregorian::date(1970, 1, 1))).total_milliseconds();
}


#ifdef WIN32
boost::filesystem::path GetSpecialFolderPath(int nFolder, bool fCreate)
{
	namespace fs = boost::filesystem;

	char pszPath[MAX_PATH] = "";

	if (SHGetSpecialFolderPathA(NULL, pszPath, nFolder, fCreate))
	{
		return fs::path(pszPath);
	}

	dlog("SHGetSpecialFolderPathA() failed, could not obtain requested path.\n");
	return fs::path("");
}
#endif
boost::filesystem::path GetDefaultDataDir()
{
	namespace fs = boost::filesystem;
	// Windows < Vista: C:\Documents and Settings\Username\Application Data\HShare
	// Windows >= Vista: C:\Users\Username\AppData\Roaming\HShare
	// Mac: ~/Library/Application Support/HShare
	// Unix: ~/.hshare
#ifdef WIN32
	// Windows
	return GetSpecialFolderPath(CSIDL_APPDATA,true) / "HShare";
#else
	fs::path pathRet;
	char* pszHome = getenv("HOME");
	if (pszHome == NULL || strlen(pszHome) == 0)
		pathRet = fs::path("/");
	else
		pathRet = fs::path(pszHome);
#ifdef MAC_OSX
	// Mac
	pathRet /= "Library/Application Support";
	fs::create_directory(pathRet);
	return pathRet / "HShare";
#else
	// Unix
	return pathRet / ".hshare";
#endif
#endif
}

boost::filesystem::path GetDataDir()
{
	namespace fs = boost::filesystem;

	fs::path path;
	// This can be called during exceptions by dlogf(), so we cache the
	// value so we don't have to do memory allocations after that.

	path = GetDefaultDataDir();
	if(!fs::exists(path))
		fs::create_directory(path);
	path /= "hshareoldwallet";
	fs::create_directory(path);

	return path;
}




static const signed char phexdigit[256] =
{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
0,1,2,3,4,5,6,7,8,9,-1,-1,-1,-1,-1,-1,
-1,0xa,0xb,0xc,0xd,0xe,0xf,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,0xa,0xb,0xc,0xd,0xe,0xf,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, };

vector<unsigned char> ParseHex(const char* psz)
{
	// convert hex dump to vector
	vector<unsigned char> vch;
	while (true)
	{
		while (isspace(*psz))
			psz++;
		signed char c = phexdigit[(unsigned char)*psz++];
		if (c == (signed char)-1)
			break;
		unsigned char n = (c << 4);
		c = phexdigit[(unsigned char)*psz++];
		if (c == (signed char)-1)
			break;
		n |= c;
		vch.push_back(n);
	}
	return vch;
}

vector<unsigned char> ParseHex(const string& str)
{
	return ParseHex(str.c_str());
}




CDBEnv bitdb;



void CDBEnv::EnvShutdown()
{
	if (!fDbEnvInit)
		return;

	fDbEnvInit = false;
	int ret = dbenv.close(0);
	if (ret != 0)
		ulog("EnvShutdown exception: ${p} ${q}\n", (("p",DbEnv::strerror(ret)),("q", ret)));
	if (!fMockDb)
		DbEnv(0).remove(strPath.c_str(), 0);
}

CDBEnv::CDBEnv() : dbenv(DB_CXX_NO_EXCEPTIONS)
{
	fDbEnvInit = false;
	fMockDb = false;
}

CDBEnv::~CDBEnv()
{
	EnvShutdown();
}

void CDBEnv::Close()
{
	EnvShutdown();
}

bool CDBEnv::Open(boost::filesystem::path pathEnv_)
{
	if (fDbEnvInit)
		return true;

	boost::this_thread::interruption_point();

	pathEnv = pathEnv_;
	filesystem::path pathDataDir = pathEnv;
	strPath = pathDataDir.string();
	filesystem::path pathLogDir = pathDataDir / "database";
	filesystem::create_directory(pathLogDir);
	filesystem::path pathErrorFile = pathDataDir / "db.log";
	dlog("dbenv.open LogDir=%s ErrorFile=%s\n",( pathLogDir.string(), pathErrorFile.string()));

	unsigned int nEnvFlags = 0;
	nEnvFlags |= DB_PRIVATE;

	int nDbCache = 25;
	dbenv.set_lg_dir(pathLogDir.string().c_str());
	dbenv.set_cachesize(nDbCache / 1024, (nDbCache % 1024) * 1048576, 1);
	dbenv.set_lg_bsize(1048576);
	dbenv.set_lg_max(10485760);
	/*dbenv.set_lk_max_locks(10000);
	dbenv.set_lk_max_objects(10000);*/
	dbenv.set_errfile(fopen(pathErrorFile.string().c_str(), "a")); /// debug
	dbenv.set_flags(DB_AUTO_COMMIT, 1);
	dbenv.set_flags(DB_TXN_WRITE_NOSYNC, 1);
#ifdef DB_LOG_AUTO_REMOVE
	dbenv.log_set_config(DB_LOG_AUTO_REMOVE, 1);
#endif
	int ret = dbenv.open(strPath.c_str(),
		DB_CREATE |
		DB_INIT_LOCK |
		DB_INIT_LOG |
		DB_INIT_MPOOL |
		DB_INIT_TXN |
		DB_THREAD |
		DB_RECOVER |
		nEnvFlags,
		S_IRUSR | S_IWUSR);
	if (ret != 0)
	{
		dlog("CDB() : error %s (%d) opening database environment", (DbEnv::strerror(ret), ret));
		return false;
	}

	fDbEnvInit = true;
	fMockDb = false;

	return true;
}

void CDBEnv::MakeMock()
{
	if (fDbEnvInit)
		throw runtime_error("CDBEnv::MakeMock(): already initialized");

	boost::this_thread::interruption_point();

	dlog("CDBEnv::MakeMock()\n");

	dbenv.set_cachesize(1, 0, 1);
	dbenv.set_lg_bsize(10485760 * 4);
	dbenv.set_lg_max(10485760);
	dbenv.set_lk_max_locks(10000);
	dbenv.set_lk_max_objects(10000);
	dbenv.set_flags(DB_AUTO_COMMIT, 1);
#ifdef DB_LOG_IN_MEMORY
	dbenv.log_set_config(DB_LOG_IN_MEMORY, 1);
#endif
	int ret = dbenv.open(NULL,
		DB_CREATE |
		DB_INIT_LOCK |
		DB_INIT_LOG |
		DB_INIT_MPOOL |
		DB_INIT_TXN |
		DB_THREAD |
		DB_PRIVATE,
		S_IRUSR | S_IWUSR);
	if (ret > 0)
	{
		std::string error_message = "CDBEnv::MakeMock(): error " + to_string(ret) + " opening database environment";
		throw runtime_error(error_message);
	}
		
	fDbEnvInit = true;
	fMockDb = true;
}

CDBEnv::VerifyResult CDBEnv::Verify(std::string strFile, bool(*recoverFunc)(CDBEnv& dbenv, std::string strFile))
{
	LOCK(cs_db);
	assert(mapFileUseCount.count(strFile) == 0);

	Db db(&dbenv, 0);
	int result = db.verify(strFile.c_str(), NULL, NULL, 0);
	if (result == 0)
		return VERIFY_OK;
	else if (recoverFunc == NULL)
		return RECOVER_FAIL;

	// Try to recover:
	bool fRecovered = (*recoverFunc)(*this, strFile);
	return (fRecovered ? RECOVER_OK : RECOVER_FAIL);
}

bool CDBEnv::Salvage(std::string strFile, bool fAggressive,
	std::vector<CDBEnv::KeyValPair >& vResult)
{
	LOCK(cs_db);
	assert(mapFileUseCount.count(strFile) == 0);

	u_int32_t flags = DB_SALVAGE;
	if (fAggressive) flags |= DB_AGGRESSIVE;

	stringstream strDump;

	Db db(&dbenv, 0);
	int result = db.verify(strFile.c_str(), NULL, &strDump, flags);
	if (result == DB_VERIFY_BAD)
	{
		dlog("Error: Salvage found errors, all data may not be recoverable.\n");
		if (!fAggressive)
		{
			dlog("Error: Rerun with aggressive mode to ignore errors and continue.\n");
			return false;
		}
	}
	if (result != 0 && result != DB_VERIFY_BAD)
	{
		dlog("ERROR: db salvage failed: ${p}\n",("p", result));
		return false;
	}

	// Format of bdb dump is ascii lines:
	// header lines...
	// HEADER=END
	// hexadecimal key
	// hexadecimal value
	// ... repeated
	// DATA=END

	string strLine;
	while (!strDump.eof() && strLine != "HEADER=END")
		getline(strDump, strLine); // Skip past header

	std::string keyHex, valueHex;
	while (!strDump.eof() && keyHex != "DATA=END")
	{
		getline(strDump, keyHex);
		if (keyHex != "DATA=END")
		{
			getline(strDump, valueHex);
			vResult.push_back(make_pair(ParseHex(keyHex), ParseHex(valueHex)));
		}
	}

	return (result == 0);
}


void CDBEnv::CheckpointLSN(const std::string& strFile)
{
	dbenv.txn_checkpoint(0, 0, 0);
	if (fMockDb)
		return;
	dbenv.lsn_reset(strFile.c_str(), 0);
}


CDB::CDB(const std::string& strFilename, const char* pszMode) :
	pdb(NULL), activeTxn(NULL)
{
	int ret;
	fReadOnly = (!strchr(pszMode, '+') && !strchr(pszMode, 'w'));
	if (strFilename.empty())
		return;

	bool fCreate = strchr(pszMode, 'c');
	unsigned int nFlags = DB_THREAD;
	if (fCreate)
		nFlags |= DB_CREATE;

	{
		LOCK(bitdb.cs_db);
		if (!bitdb.Open(GetDataDir()))
			throw runtime_error("env open failed");

		strFile = strFilename;
		++bitdb.mapFileUseCount[strFile];
		pdb = bitdb.mapDb[strFile];
		if (pdb == NULL)
		{
			pdb = new Db(&bitdb.dbenv, 0);

			bool fMockDb = bitdb.IsMock();
			if (fMockDb)
			{
				DbMpoolFile*mpf = pdb->get_mpf();
				ret = mpf->set_flags(DB_MPOOL_NOFILE, 1);
				if (ret != 0)
					throw runtime_error("CDB : Failed to configure for no temp file backing for database "+strFile);
			}

			ret = pdb->open(NULL, // Txn pointer
				fMockDb ? NULL : strFile.c_str(), // Filename
				fMockDb ? strFile.c_str() : "main", // Logical db name
				DB_BTREE, // Database type
				nFlags, // Flags
				0);

			if (ret != 0)
			{
				delete pdb;
				pdb = NULL;
				--bitdb.mapFileUseCount[strFile];
				strFile = "";
					std::string error_message = "CDB : Error" + to_string(ret) + ", can't open database " + strFile ;
					throw runtime_error(error_message);
			}

			if (fCreate && !Exists(string("version")))
			{
				bool fTmp = fReadOnly;
				fReadOnly = false;
				WriteVersion(CLIENT_VERSION);
				fReadOnly = fTmp;
			}

			bitdb.mapDb[strFile] = pdb;
		}
	}
}

void CDB::Close()
{
	if (!pdb)
		return;
	if (activeTxn)
		activeTxn->abort();
	activeTxn = NULL;
	pdb = NULL;

	// Flush database activity from memory pool to disk log
	unsigned int nMinutes = 0;
	if (fReadOnly)
		nMinutes = 1;

	bitdb.dbenv.txn_checkpoint(nMinutes ? 100 * 1024 : 0, nMinutes, 0);

	{
		LOCK(bitdb.cs_db);
		--bitdb.mapFileUseCount[strFile];
	}
}

void CDBEnv::CloseDb(const string& strFile)
{
	{
		LOCK(cs_db);
		if (mapDb[strFile] != NULL)
		{
			// Close the database handle
			Db* pdb = mapDb[strFile];
			pdb->close(0);
			delete pdb;
			mapDb[strFile] = NULL;
		}
	}
}

bool CDBEnv::RemoveDb(const string& strFile)
{
	this->CloseDb(strFile);

	LOCK(cs_db);
	int rc = dbenv.dbremove(NULL, strFile.c_str(), NULL, DB_AUTO_COMMIT);
	return (rc == 0);
}

bool CDB::Rewrite(const string& strFile, const char* pszSkip)
{
	while (true)
	{
		{
			LOCK(bitdb.cs_db);
			if (!bitdb.mapFileUseCount.count(strFile) || bitdb.mapFileUseCount[strFile] == 0)
			{
				// Flush log data to the dat file
				bitdb.CloseDb(strFile);
				bitdb.CheckpointLSN(strFile);
				bitdb.mapFileUseCount.erase(strFile);

				bool fSuccess = true;
				dlog("Rewriting ${p}...\n", ("p",strFile));
				string strFileRes = strFile + ".rewrite";
				{ // surround usage of db with extra {}
					CDB db(strFile.c_str(), "r");
					Db* pdbCopy = new Db(&bitdb.dbenv, 0);

					int ret = pdbCopy->open(NULL,                 // Txn pointer
						strFileRes.c_str(),   // Filename
						"main",    // Logical db name
						DB_BTREE,  // Database type
						DB_CREATE,    // Flags
						0);
					if (ret > 0)
					{
						dlog("Cannot create database file ${p} \n", ("p", strFileRes));
						fSuccess = false;
					}

					Dbc* pcursor = db.GetCursor();
					if (pcursor)
						while (fSuccess)
						{
							CDataStream ssKey(SER_DISK, CLIENT_VERSION);
							CDataStream ssValue(SER_DISK, CLIENT_VERSION);
							int ret = db.ReadAtCursor(pcursor, ssKey, ssValue, DB_NEXT);
							if (ret == DB_NOTFOUND)
							{
								pcursor->close();
								break;
							}
							else if (ret != 0)
							{
								pcursor->close();
								fSuccess = false;
								break;
							}
							if (pszSkip &&
								strncmp(&ssKey[0], pszSkip, std::min(ssKey.size(), strlen(pszSkip))) == 0)
								continue;
							if (strncmp(&ssKey[0], "\x07version", 8) == 0)
							{
								// Update version:
								ssValue.clear();
								ssValue << CLIENT_VERSION;
							}
							Dbt datKey(&ssKey[0], ssKey.size());
							Dbt datValue(&ssValue[0], ssValue.size());
							int ret2 = pdbCopy->put(NULL, &datKey, &datValue, DB_NOOVERWRITE);
							if (ret2 > 0)
								fSuccess = false;
						}
					if (fSuccess)
					{
						db.Close();
						bitdb.CloseDb(strFile);
						if (pdbCopy->close(0))
							fSuccess = false;
						delete pdbCopy;
					}
				}
				if (fSuccess)
				{
					Db dbA(&bitdb.dbenv, 0);
					if (dbA.remove(strFile.c_str(), NULL, 0))
						fSuccess = false;
					Db dbB(&bitdb.dbenv, 0);
					if (dbB.rename(strFileRes.c_str(), NULL, strFile.c_str(), 0))
						fSuccess = false;
				}
				if (!fSuccess)
					dlog("Rewriting of ${p} FAILED!\n", ("p",strFileRes));
				return fSuccess;
			}
		}
		MilliSleep(100);
	}
	return false;
}


void CDBEnv::Flush(bool fShutdown)
{
	int64_t nStart = GetTimeMillis();
	// Flush log data to the actual data file
	//  on all files that are not in use
	//dlog( "Flush(%s)%s\n", fShutdown ? "true" : "false", fDbEnvInit ? "" : " db not started");
	if (!fDbEnvInit)
		return;
	{
		LOCK(cs_db);
		map<string, int>::iterator mi = mapFileUseCount.begin();
		while (mi != mapFileUseCount.end())
		{
			string strFile = (*mi).first;
			int nRefCount = (*mi).second;
			dlog( "${p} refcount=${q}\n",(("p", strFile),("q", nRefCount)));
			if (nRefCount == 0)
			{
				// Move log data to the dat file
				CloseDb(strFile);
				dlog( "${p} checkpoint\n", ("p", strFile));
				dbenv.txn_checkpoint(0, 0, 0);
				dlog( "${p} detach\n", ("p", strFile));
				if (!fMockDb)
					dbenv.lsn_reset(strFile.c_str(), 0);
				dlog( "${p} closed\n", ("p", strFile));
				mapFileUseCount.erase(mi++);
			}
			else
				mi++;
		}
		if (fShutdown)
		{
			char** listp;
			if (mapFileUseCount.empty())
			{
				dbenv.log_archive(&listp, DB_ARCH_REMOVE);
				Close();
			}
		}
	}
}
