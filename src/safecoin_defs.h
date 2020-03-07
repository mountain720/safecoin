/******************************************************************************
 * Copyright © 2014-2019 The SuperNET Developers.                             *
 *                                                                            *
 * See the AUTHORS, DEVELOPER-AGREEMENT and LICENSE files at                  *
 * the top-level directory of this distribution for the individual copyright  *
 * holder information and the developer policies on copyright and licensing.  *
 *                                                                            *
 * Unless otherwise agreed in a custom licensing agreement, no part of the    *
 * SuperNET software, including this file may be copied, modified, propagated *
 * or distributed except according to the terms contained in the LICENSE file *
 *                                                                            *
 * Removal or modification of this copyright notice is prohibited.            *
 *                                                                            *
 ******************************************************************************/

#ifndef SAFECOIN_DEFS_H
#define SAFECOIN_DEFS_H
#include "arith_uint256.h"
#include "chain.h"
#include "safecoin_nk.h"

#define SAFECOIN_EARLYTXID_HEIGHT 100
//#define ADAPTIVEPOW_CHANGETO_DEFAULTON 1572480000
#define ASSETCHAINS_MINHEIGHT 128
#define ASSETCHAINS_MAX_ERAS 3
#define SAFECOIN_ELECTION_GAP 2000
#define ROUNDROBIN_DELAY 61
#define SAFECOIN_ASSETCHAIN_MAXLEN 65
#define SAFECOIN_LIMITED_NETWORKSIZE 4
#define IGUANA_MAXSCRIPTSIZE 10001
#define SAFECOIN_MAXMEMPOOLTIME 3600 // affects consensus
#define CRYPTO777_PUBSECPSTR "02004a23684b6e12441ac4c913775f4f74584c48a9167d2fb65da6a2ddc9852761"
#define SAFECOIN_FIRSTFUNGIBLEID 100

#define SAFECOIN_SAPLING_ACTIVATION 1551916800 // March 7th, 2019
#define SAFECOIN_SAPLING_DEADLINE 1551398400 // March 1st, 2019

#define COLLATERAL_MATURITY 4320 // one week => 10080, 3 days => 4320, n days => n * 1440
#define REGISTRATION_GAP 900 // min number of blocks allowed since last safenode registration
#define REGISTRATION_TRIGGER_DAYS 7 // number of days between two automatic safenode registrations
#define COLLATERAL_MIN_TIER_1 10000
#define COLLATERAL_MIN_TIER_2 50000
#define COLLATERAL_MIN_TIER_3 100000

#define ASSETCHAINS_STAKED_BLOCK_FUTURE_MAX 57
#define ASSETCHAINS_STAKED_BLOCK_FUTURE_HALF 27
#define ASSETCHAINS_STAKED_MIN_POW_DIFF 536900000 // 537000000 537300000

#define _COINBASE_MATURITY 100

// SafeNode Notary Seasons 
// 1: May 1st 2018 1530921600
// to add 2nd season, change NUM_SAFECOIN_SEASONS to 2, and add timestamp and height of activation to these arrays. 
#define NUM_SAFECOIN_SEASONS 1
#define NUM_SAFECOIN_NOTARIES 32
static const uint32_t SAFECOIN_SEASON_TIMESTAMPS[NUM_SAFECOIN_SEASONS] = {1525132800};
static const int32_t SAFECOIN_SEASON_HEIGHTS[NUM_SAFECOIN_SEASONS] = {((513000 / SAFECOIN_ELECTION_GAP) * SAFECOIN_ELECTION_GAP)};

// December Hardfork = ???
/*
extern const uint32_t nStakedDecemberHardforkTimestamp; //December 2019 hardfork
extern const int32_t nDecemberHardforkHeight;   //December 2019 hardfork

static const uint32_t KMD_SEASON_TIMESTAMPS[NUM_KMD_SEASONS] = {1525132800, 1563148800, nStakedDecemberHardforkTimestamp, 1751328000};
static const int32_t KMD_SEASON_HEIGHTS[NUM_KMD_SEASONS] = {814000, 1444000, nDecemberHardforkHeight, 7113400};
*/
// Era array of pubkeys. Add extra seasons to bottom as requried, after adding appropriate info above. 
static const char *notaries_elected[NUM_SAFECOIN_SEASONS][NUM_SAFECOIN_NOTARIES][2] =
{
    {
		{"0dev1_jj", "0333b9796526ef8de88712a649d618689a1de1ed1adf9fb5ec415f31e560b1f9a3" },
		{"0dev2_oleksandr", "03f5c47ec482fa1a57821edd0c492948aec9b22ab2b4e38e45fba34e4b6f697a29" },
		{"0dev3_arch", "0248c657bf46ff8b77c230134fc04482dd549b91d4fb2ba27414bec02edac4ae98" },
		{"0dev4_rag", "030ca5b3f0ad6eac4afd90b2be8e52a74df852960b9bb4b69bcd413ad2df6232fe" },
		{"bman_1", "02d3d47e14af1be6617c8e92dbab0537efb47f7732f5afb1024209b60a9d84a31c" },
		{"bman_2", "03608d2368b19ae3c47d9496283630953dfa85526fe1cad159d9ef8b796f3236be" },
		{"bman_3", "02448b40e1cca6367f6e10aaf00faabdcca9c219d453d67548f2e6fd08ce90c10f" },
		{"bman_4", "02e55b44a4ce698e0ee6fed3fc571e06d3939dc0537851dc23246734a2b181f1c4" },
		{"traysi_1", "0255895db02e46d65c6ad6313a467074949efa47feefc003b1d96ec309151c4340" },
		{"traysi_2", "0221fa83d4c5f04c63b9bb3a7085242e8daa83c9a97024a4f46720dd174ed1764a" },
		{"safenode_a", "031e332d04f067aad39553330d3dbb99deaaa97fac579e5633b6483abe3f503654" }, // 10
		{"safenode_b", "03f19b118737f54a586dd33e92dbb397fc29c88413b41ac21b87440bec58070ef9" },
		{"safenode_c", "02d72b424eee08eb333a9c95d8915bba4e5e05b9a42080eb6811907b73ea30b474" },
		{"safenode_d", "020cc2dd8eea9955f66eb127236763dd057a845d8f830c5357d90705f9d23797a6" },
		{"safenode_d", "025f1dde907090870289ee8f8ef7a870473c00080d344365efda5a23c4c305f93a" },
		{"safenode_e", "0328ac56b5835d03774724fadee4d1b09cea956515e57cbe95d599e6dd0caced4b" },
		{"safenode_f", "03433e564ba7287dce6883e9bc73354654e6d305204bcb1fab4bf1e42675eb4c2f" },
		{"safenode_g", "02c8431929d7493a7feb0e397c88a6a1651f1709cb2b420b55e7d732ebc31041e9" },
		{"safenode_h", "0318cf394b58e9b56ddd62fb03082e5382575a60e440a23fbb7380e7fd50b295eb" },
		{"safenode_i", "026676e7fa71ca8fd6436bb2a218500e82411d942e2f3dd46bbf31985654a569ed" },
		{"safenode_j", "02aa030a8bd00c430d2846ebad41af3ff12d5a4507ec12dcb3de485e2aa6bfd0a1" }, // 20
		{"safenode_k", "036fd60dcac267a26771093df5210511e0317031263d66ddf8d104813a3159d18d" },
		{"safenode_l", "02d300502f61150d580a42a09963e347a2ad3ce51f11960d358df8f394f9672a67" },
		{"safenode_m", "02412d9dd21f2457cba8533e08679898a2ffa48fe4c4691e2a696842749c80031f" },
		{"safenode_n", "0277b12ff3cd22325fde276e706d365b2757d5e27f3c23005dece66ebb0c58a0fe" },
		{"safenode_o", "0213671eba7c4c03e07629bc30b071571605a478f65b1dfff2343e5275b6974d7c" },
		{"safenode_p", "025bedc84e35a3bb89c3126656ad83854573928030bb313472e3a13cc52b2f8cf2" },
		{"safenode_q", "03f5c5dec766e84ac5a378650ed82ea0df459a0022d9f7a85e7f94426d01c7f128" },
		{"safenode_r", "0357a41230ffd72d1fd9379500ac97ac27d0b0a0a6e4197ba4d1f76ff4f88ff1e2" },
		{"safenode_s", "02380c684558673aa7cdc638fd8b2ca8f2b7ae5b7d15a622b10b2b406f43c7f1cc" },
		{"safenode_t", "02d8ddaa4d3dbb38cb1e3fd769f05efc8985243f414a045889be9ec5ad688a1dce" }, // 30
		{"safenode_u", "039846a7ae3bee6390ef7ee95769a7443aa1bb5d7e85afd676ebe7ad7420010135" }
    }
};

#define SETBIT(bits,bitoffset) (((uint8_t *)bits)[(bitoffset) >> 3] |= (1 << ((bitoffset) & 7)))
#define GETBIT(bits,bitoffset) (((uint8_t *)bits)[(bitoffset) >> 3] & (1 << ((bitoffset) & 7)))
#define CLEARBIT(bits,bitoffset) (((uint8_t *)bits)[(bitoffset) >> 3] &= ~(1 << ((bitoffset) & 7)))

#define SAFECOIN_MAXNVALUE (((uint64_t)1 << 63) - 1)
#define SAFECOIN_BIT63SET(x) ((x) & ((uint64_t)1 << 63))
#define SAFECOIN_VALUETOOBIG(x) ((x) > (uint64_t)10000000001*COIN)

//#ifndef TESTMODE
#define PRICES_DAYWINDOW ((3600*24/ASSETCHAINS_BLOCKTIME) + 1)
//#else
//#define PRICES_DAYWINDOW (7)
//#endif

extern uint8_t ASSETCHAINS_TXPOW,ASSETCHAINS_PUBLIC;
extern int8_t ASSETCHAINS_ADAPTIVEPOW;
int32_t MAX_BLOCK_SIZE(int32_t height);
extern char ASSETCHAINS_SYMBOL[SAFECOIN_ASSETCHAIN_MAXLEN];
extern uint16_t ASSETCHAINS_P2PPORT,ASSETCHAINS_RPCPORT;
extern uint32_t ASSETCHAIN_INIT, ASSETCHAINS_MAGIC;
extern int32_t VERUS_BLOCK_POSUNITS, ASSETCHAINS_LWMAPOS, ASSETCHAINS_SAPLING, ASSETCHAINS_OVERWINTER,ASSETCHAINS_BLOCKTIME;
extern uint64_t ASSETCHAINS_SUPPLY, ASSETCHAINS_FOUNDERS_REWARD;

extern uint64_t ASSETCHAINS_TIMELOCKGTE;
extern uint32_t ASSETCHAINS_ALGO, ASSETCHAINS_VERUSHASH,ASSETCHAINS_EQUIHASH,SAFECOIN_INITDONE;

extern int32_t SAFECOIN_MININGTHREADS,SAFECOIN_LONGESTCHAIN,ASSETCHAINS_SEED,IS_SAFECOIN_NOTARY,USE_EXTERNAL_PUBKEY,SAFECOIN_CHOSEN_ONE,SAFECOIN_ON_DEMAND,SAFECOIN_PASSPORT_INITDONE,ASSETCHAINS_STAKED,SAFECOIN_NSPV;
extern uint64_t ASSETCHAINS_COMMISSION, ASSETCHAINS_LASTERA,ASSETCHAINS_CBOPRET;
extern bool VERUS_MINTBLOCKS;
extern uint64_t ASSETCHAINS_REWARD[ASSETCHAINS_MAX_ERAS+1], ASSETCHAINS_NOTARY_PAY[ASSETCHAINS_MAX_ERAS+1], ASSETCHAINS_TIMELOCKGTE, ASSETCHAINS_NONCEMASK[],ASSETCHAINS_NK[2];
extern const char *ASSETCHAINS_ALGORITHMS[];
extern int32_t VERUS_MIN_STAKEAGE;
extern uint32_t ASSETCHAINS_VERUSHASH, ASSETCHAINS_VERUSHASHV1_1, ASSETCHAINS_NONCESHIFT[], ASSETCHAINS_HASHESPERROUND[];
extern std::string NOTARY_PUBKEY,ASSETCHAINS_OVERRIDE_PUBKEY,ASSETCHAINS_SCRIPTPUB;
extern uint8_t NOTARY_PUBKEY33[33],ASSETCHAINS_OVERRIDE_PUBKEY33[33],ASSETCHAINS_MARMARA;
extern std::vector<std::string> ASSETCHAINS_PRICES,ASSETCHAINS_STOCKS;

extern int32_t VERUS_BLOCK_POSUNITS, VERUS_CONSECUTIVE_POS_THRESHOLD, VERUS_NOPOS_THRESHHOLD;
extern uint256 SAFECOIN_EARLYTXID;

extern int32_t SAFECOIN_CONNECTING,SAFECOIN_CCACTIVATE,SAFECOIN_DEALERNODE;
extern uint32_t ASSETCHAINS_CC;
extern std::string CCerror,ASSETCHAINS_CCLIB;
extern uint8_t ASSETCHAINS_CCDISABLES[256];

extern int32_t USE_EXTERNAL_PUBKEY;
extern std::string NOTARY_PUBKEY,NOTARY_ADDRESS;
extern int32_t SAFECOIN_EXCHANGEWALLET;
extern int32_t VERUS_MIN_STAKEAGE;
extern std::string DONATION_PUBKEY;
extern uint8_t ASSETCHAINS_PRIVATE;
extern int32_t USE_EXTERNAL_PUBKEY;
extern char NOTARYADDRS[64][64];
extern char NOTARY_ADDRESSES[NUM_SAFECOIN_SEASONS][64][64];
extern int32_t SAFECOIN_TESTNODE, SAFECOIN_SNAPSHOT_INTERVAL,IS_STAKED_NOTARY,STAKED_ERA;
extern int32_t ASSETCHAINS_EARLYTXIDCONTRACT;
extern int32_t ASSETCHAINS_STAKED_SPLIT_PERCENTAGE;
int tx_height( const uint256 &hash );
extern std::vector<std::string> vWhiteListAddress;
extern std::map <std::int8_t, int32_t> mapHeightEvalActivate;
void safecoin_netevent(std::vector<uint8_t> payload);
int32_t getacseason(uint32_t timestamp);
int32_t getkmdseason(int32_t height);

#define IGUANA_MAXSCRIPTSIZE 10001
#define SAFECOIN_KVDURATION 1440
#define SAFECOIN_KVBINARY 2
#define PRICES_SMOOTHWIDTH 1
#define PRICES_MAXDATAPOINTS 8
uint64_t safecoin_paxprice(uint64_t *seedp,int32_t height,char *base,char *rel,uint64_t basevolume);
int32_t safecoin_paxprices(int32_t *heights,uint64_t *prices,int32_t max,char *base,char *rel);
int32_t safecoin_notaries(uint8_t pubkeys[64][33],int32_t height,uint32_t timestamp);
char *bitcoin_address(char *coinaddr,uint8_t addrtype,uint8_t *pubkey_or_rmd160,int32_t len);
int32_t safecoin_minerids(uint8_t *minerids,int32_t height,int32_t width);
int32_t safecoin_kvsearch(uint256 *refpubkeyp,int32_t current_height,uint32_t *flagsp,int32_t *heightp,uint8_t value[IGUANA_MAXSCRIPTSIZE],uint8_t *key,int32_t keylen);

uint32_t safecoin_blocktime(uint256 hash);
int32_t safecoin_longestchain();
int32_t safecoin_dpowconfs(int32_t height,int32_t numconfs);
int8_t safecoin_segid(int32_t nocache,int32_t height);
int32_t safecoin_heightpricebits(uint64_t *seedp,uint32_t *heightbits,int32_t nHeight);
char *safecoin_pricename(char *name,int32_t ind);
int32_t safecoin_priceind(const char *symbol);
int32_t safecoin_pricesinit();
int64_t safecoin_priceave(int64_t *tmpbuf,int64_t *correlated,int32_t cskip);
int64_t safecoin_pricecorrelated(uint64_t seed,int32_t ind,uint32_t *rawprices,int32_t rawskip,uint32_t *nonzprices,int32_t smoothwidth);
int32_t safecoin_nextheight();
uint32_t safecoin_heightstamp(int32_t height);
int64_t safecoin_pricemult(int32_t ind);
int32_t safecoin_priceget(int64_t *buf64,int32_t ind,int32_t height,int32_t numblocks);
uint64_t safecoin_accrued_interest(int32_t *txheightp,uint32_t *locktimep,uint256 hash,int32_t n,int32_t checkheight,uint64_t checkvalue,int32_t tipheight);
int32_t safecoin_currentheight();
int32_t safecoin_notarized_bracket(struct notarized_checkpoint *nps[2],int32_t height);
arith_uint256 safecoin_adaptivepow_target(int32_t height,arith_uint256 bnTarget,uint32_t nTime);
bool safecoin_hardfork_active(uint32_t time);
int32_t safecoin_newStakerActive(int32_t height, uint32_t timestamp);

uint256 Parseuint256(const char *hexstr);
void safecoin_sendmessage(int32_t minpeers, int32_t maxpeers, const char *message, std::vector<uint8_t> payload);
CBlockIndex *safecoin_getblockindex(uint256 hash);
int32_t safecoin_nextheight();
CBlockIndex *safecoin_blockindex(uint256 hash);
CBlockIndex *safecoin_chainactive(int32_t height);
int32_t safecoin_blockheight(uint256 hash);
bool safecoin_txnotarizedconfirmed(uint256 txid);
int32_t safecoin_blockload(CBlock& block, CBlockIndex *pindex);
uint32_t safecoin_chainactive_timestamp();
uint32_t GetLatestTimestamp(int32_t height);

#ifndef SAFECOIN_NSPV_FULLNODE
#define SAFECOIN_NSPV_FULLNODE (SAFECOIN_NSPV <= 0)
#endif // !SAFECOIN_NSPV_FULLNODE
#ifndef SAFECOIN_NSPV_SUPERLITE
#define SAFECOIN_NSPV_SUPERLITE (SAFECOIN_NSPV > 0)
#endif // !SAFECOIN_NSPV_SUPERLITE

#endif
