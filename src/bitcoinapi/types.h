/**
 * @file    types.h
 * @author  Krzysztof Okupski
 * @date    29.10.2014
 * @version 1.0
 *
 * Type definitions for the JSON-RPC C++ interface.
 */

#ifndef BITCOIN_API_TYPES_H
#define BITCOIN_API_TYPES_H

#include <string>
#include <vector>

#include <jsoncpp/json/json.h>

	/* === General types === */
	struct getinfo_t{
		int version;
		int protocolversion;
		int walletversion;
		double balance;
		int blocks;
		int timeoffset;
		int connections;
		std::string proxy;
		double difficulty;
		bool testnet;
		int keypoololdest;
		int keypoolsize;
		double paytxfee;
		int unlocked_until;
		std::string errors;
	};


	/* === Node types === */
	struct netaddress_t{
		std::string address;
		std::string connected;
	};

	struct nodeinfo_t{
		std::string addednode;
		bool connected;
		std::vector<netaddress_t> addresses;
	};

	struct peerinfo_t{
		std::string addr;
		std::string services;
		int lastsend;
		int lastrecv;
		int bytessent;
		int bytesrecv;
		int conntime;
		double pingtime;
		int version;
		std::string subver;
		bool inbound;
		int startingheight;
		int banscore;
	};


	/* === Account, address types === */
	struct accountinfo_t{
		std::string account;
		double amount;
		int confirmations;
	};

	struct addressinfo_t: accountinfo_t{
		std::string address;
		std::vector<std::string> txids;
	};

	struct transactioninfo_t: accountinfo_t{
		bool involvesWatchonly;
		std::string address;
		std::string category;
		std::string blockhash;
		int blockindex;
		int blocktime;
		std::string txid;
		std::vector<std::string> walletconflicts;
		int time;
		int timereceived;
		double fee;
	};

	struct multisig_t{
		std::string address;
		std::string redeemScript;
	};

	struct validateaddress_t{
		bool isvalid;
		std::string address;
		bool ismine;
		bool isscript;
		std::string pubkey;
		bool iscompressed;
		std::string account;
		bool iswatchonly;
	};

	struct getaddressinfo_t {
		std::string address;
		std::string scriptPubKey;
		bool ismine;
		bool iswatchonly;
		bool isscript;
		bool iswitness;
		/*
		double witness_version;
		std::string witness_program;
		std::string script;
		std::string hex;
		std::vector<std::string> pubkeys;
		double sigsrequired;
		std::string pubkey;
		"embedded" : {...},           (object, optional) Information about the address embedded in P2SH or P2WSH, if relevant and known. It includes all getaddressinfo output fields for the embedded address, excluding metadata ("timestamp", "hdkeypath", "hdseedid") and relation to the wallet ("ismine", "iswatchonly", "account").
  "iscompressed" : true|false,  (boolean) If the address is compressed
  "label" :  "label"         (string) The label associated with the address, "" is the default account
  "account" : "account"         (string) DEPRECATED. This field will be removed in V0.18. To see this deprecated field, start bitcoind with -deprecatedrpc=accounts. The account associated with the address, "" is the default account
  "timestamp" : timestamp,      (number, optional) The creation time of the key if available in seconds since epoch (Jan 1 1970 GMT)
  "hdkeypath" : "keypath"       (string, optional) The HD keypath if the key is HD and available
  "hdseedid" : "<hash160>"      (string, optional) The Hash160 of the HD seed
  "hdmasterkeyid" : "<hash160>" (string, optional) alias for hdseedid maintained for backwards compatibility. Will be removed in V0.18.
  "labels"                      (object) Array of labels associated with the address.
    [
      { (json object of label data)
        "name": "labelname" (string) The label
        "purpose": "string" (string) Purpose of address ("send" for sending address, "receive" for receiving address)
      },...
    ]
		*/
	};

	struct addressgrouping_t{
		std::string address;
		double balance;
		std::string account;
	};

	/* === Transactions === */
	struct transactiondetails_t{
		std::string account;
		std::string address;
		std::string category;
		double amount;
		int vout;
		double fee;
	};

	struct gettransaction_t{
		double amount;
		double fee;
		int confirmations;
		std::string blockhash;
		int blockindex;
		int blocktime;
		std::string txid;
		std::vector<std::string> walletconflicts;
		int time;
		int timereceived;
		std::vector<transactiondetails_t> details;
		std::string hex;
	};

	struct decodescript_t{
		std::string assm;
		std::string type;
		std::string p2sh;

		int reqSigs;
		std::vector<std::string> addresses;
	};

	/* decoderawtransaction return type */
	struct scriptSig_t{
		std::string assm;
		std::string hex;
	};

	struct scriptPubKey_t{
		std::string assm;
		std::string hex;
		int reqSigs;
		std::string type;
		std::vector<std::string> addresses;
	};

	struct txout_t{
		std::string txid;
		unsigned int n;
	};

	struct vin_t: txout_t{
		scriptSig_t scriptSig;
		unsigned int sequence;
	};

	struct vout_t{
		double value;
		unsigned int n;
		scriptPubKey_t scriptPubKey;
	};

	struct decoderawtransaction_t{
		std::string txid;
		int version;
		int locktime;
		std::vector<vin_t> vin;
		std::vector<vout_t> vout;
	};



	/* getrawtransaction return type */
	struct getrawtransaction_t: decoderawtransaction_t{
		std::string hex;
		std::string blockhash;
		unsigned int confirmations;
		unsigned int time;
		unsigned int blocktime;
	};

	/* signrawtransaction return type */
	struct signrawtxin_t: txout_t{
		std::string scriptPubKey;
		std::string redeemScript;
	};

	/* signrawtransaction return type */
	struct signrawtransaction_t{
		std::string hex;
		bool complete;
	};





	/* === Other === */

	struct smartfee_t{
		double feerate;
		int blocks;
	};
	struct utxoinfo_t{
		std::string bestblock;
		int confirmations;
		double value;
		scriptPubKey_t scriptPubKey;
		int version;
		bool coinbase;
	};

	struct utxosetinfo_t{
		int height;
		std::string bestblock;
		int transactions;
		int txouts;
		int bytes_serialized;
		std::string hash_serialized;
		double total_amount;
	};

	struct unspenttxout_t: txout_t{
		std::string address;
		std::string account;
		std::string scriptPubKey;
		bool spendable;
		double amount;
		int confirmations;
	};

	#ifdef _OMNI_SUPPORT_

	struct omni_subsend_t {
    	int propertyid;
        bool divisible;
        double amount;
	};

	struct omni_transaction_t {
		std::string txid;
		std::string sendingaddress;
		std::string referenceaddress;
		int propertyid;
		bool ismine;
		int confirmations;
		double amount;
		std::string blockhash;
	    unsigned int block;
		double fee;
		unsigned int blocktime;
		bool valid;
		unsigned int positioninblock;
		int version;
		int type_int;
		std::string type;
		std::vector<omni_subsend_t> subsends;
	};

	

	struct omni_balance_t {
		double balance;
		double reserved;
		double frozen;
	};

	struct omni_detailed_balance_t: omni_balance_t{
		int propertyid;
		std::string name;
	};

	struct omni_address_balance_t{
		std::string address;
		std::vector<omni_detailed_balance_t> balances;
	};

	#endif


	/* === Unused yet === */
	struct blockinfo_t{
		std::string hash;
		int confirmations;
		int size;
		int height;
		int version;
		std::string merkleroot;
		std::vector<std::string> tx;
		unsigned int time;
		unsigned int nonce;
		std::string bits;
		double difficulty;
		std::string chainwork;
		std::string previousblockhash;
		std::string nextblockhash;
	};

	struct mininginfo_t{
		int blocks;
		int currentblocksize;
		int currentblocktx;
		double difficulty;
		std::string errors;
		int genproclimit;
		double networkhashps;
		int pooledtx;
		bool testnet;
		bool generate;
		int hashespersec;
	};

	struct workdata_t{
		std::string midstate;
		std::string data;
		std::string hash1;
		std::string target;
	};

	struct txsinceblock_t{
		std::vector<transactioninfo_t> transactions;
		std::string lastblock;
	};

#endif
