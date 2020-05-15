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

#include "key_io.h"
#include "CCinclude.h"
#include "CCassets.h"
#include "CCfaucet.h"
#include "CCrewards.h"
#include "CCdice.h"
#include "CCauction.h"
#include "CClotto.h"
#include "CCfsm.h"
#include "CCHeir.h"
#include "CCchannels.h"
#include "CCOracles.h"
#include "CCPrices.h"
#include "CCPegs.h"
#include "CCMarmara.h"
#include "CCPayments.h"
#include "CCGateways.h"
#include "CCtokens.h"
#include "CCImportGateway.h"

/*
 CCcustom has most of the functions that need to be extended to create a new CC contract.
 
 A CC scriptPubKey can only be spent if it is properly signed and validated. By constraining the vins and vouts, it is possible to implement a variety of functionality. CC vouts have an otherwise non-standard form, but it is properly supported by the enhanced bitcoin protocol code as a "cryptoconditions" output and the same pubkey will create a different address.
 
 This allows creation of a special address(es) for each contract type, which has the privkey public. That allows anybody to properly sign and spend it, but with the constraints on what is allowed in the validation code, the contract functionality can be implemented.
 
 what needs to be done to add a new contract:
 1. add EVAL_CODE to eval.h
 2. initialize the variables in the CCinit function below
 3. write a Validate function to reject any unsanctioned usage of vin/vout
 4. make helper functions to create rawtx for RPC functions
 5. add rpc calls to rpcserver.cpp and rpcserver.h and in one of the rpc.cpp files
 6. add the new .cpp files to src/Makefile.am
 
 IMPORTANT: make sure that all CC inputs and CC outputs are properly accounted for and reconcile to the satoshi. The built in utxo management will enforce overall vin/vout constraints but it wont know anything about the CC constraints. That is what your Validate function needs to do.
 
 Generally speaking, there will be normal coins that change into CC outputs, CC outputs that go back to being normal coins, CC outputs that are spent to new CC outputs.
 
 Make sure both the CC coins and normal coins are preserved and follow the rules that make sense. It is a good idea to define specific roles for specific vins and vouts to reduce the complexity of validation.
 */

// to create a new CCaddr, add to rpcwallet the CCaddress and start with -pubkey= with the pubkey of the new address, with its wif already imported. set normaladdr and CChexstr. run CCaddress and it will print the privkey along with autocorrect the CCaddress. which should then update the CCaddr here

// Assets, aka Tokens
#define FUNCNAME IsAssetsInput
#define EVALCODE EVAL_ASSETS
const char *AssetsCCaddr = "RrCtUYHxW5jgJAhLfGoEcLogfCQdcJYuvz";
const char *AssetsNormaladdr = "RmfKYg6y2wF1X2Ksv8oXjm1LtKU433VU24";
char AssetsCChexstr[67] = { "023a80522f1bc5295211299e5b18b64343dd4fc7b4d29d47834a567995eca2d78e" };
uint8_t AssetsCCpriv[32] = { 0xd0, 0xf7, 0xf9, 0x89, 0x24, 0x38, 0xf0, 0x46, 0x81, 0x81, 0x10, 0x68, 0x3c, 0x22, 0x26, 0x63, 0xe7, 0xe6, 0x25, 0x24, 0xb0, 0x4f, 0xc4, 0xa0, 0xf4, 0x66, 0x7c, 0x12, 0x01, 0x96, 0x26, 0x78 };
#include "CCcustom.inc"
#undef FUNCNAME
#undef EVALCODE

// Faucet
#define FUNCNAME IsFaucetInput
#define EVALCODE EVAL_FAUCET
const char *FaucetCCaddr = "RkSFVecaZtHWjDj2rXMan8ESZak2Rm9cQm";
const char *FaucetNormaladdr = "RhFFFoMcz5zXrVq5C1b2Fywwj1oqtQib5f";
char FaucetCChexstr[67] = { "03542eb0bd968ee5de3b5803d6639511cb2055fb1de45ea6950b64c2a740c2b6b3" };
uint8_t FaucetCCpriv[32] = { 0x70, 0xcc, 0x51, 0xd4, 0x60, 0xa6, 0x5e, 0x71, 0xff, 0xea, 0x32, 0x6f, 0x67, 0xc8, 0x04, 0xe3, 0x15, 0x3e, 0xa7, 0xa8, 0x6e, 0x13, 0x92, 0xd2, 0x52, 0x2f, 0x88, 0x8f, 0xc7, 0x0b, 0xc8, 0x6a };
#include "CCcustom.inc"
#undef FUNCNAME
#undef EVALCODE

// Rewards
#define FUNCNAME IsRewardsInput
#define EVALCODE EVAL_REWARDS
const char *RewardsCCaddr = "RrKWCzjwgVW51pYcf713G2ofxM8iokg1EL";
const char *RewardsNormaladdr = "RZgNbmrRhXEbfg2Ug4P8fEaasZU7G4GxLk";
char RewardsCChexstr[67] = { "02ea73a10801fc32756cedc8787686206ec6717a2bc854ac08976cd79a296f1e3c" };
uint8_t RewardsCCpriv[32] = { 0xb8, 0xc4, 0x85, 0x1a, 0x47, 0x60, 0xd9, 0x10, 0x38, 0xd5, 0x4f, 0x63, 0x86, 0xd9, 0x25, 0x8a, 0x20, 0x08, 0x7b, 0x7e, 0xf9, 0xfc, 0x01, 0x45, 0xb3, 0x19, 0xc4, 0xad, 0x5c, 0x1a, 0xf7, 0x6b };
#include "CCcustom.inc"
#undef FUNCNAME
#undef EVALCODE

// Dice
#define FUNCNAME IsDiceInput
#define EVALCODE EVAL_DICE
const char *DiceCCaddr = "RbkaDYYaGbd6kBZvX6FT2MaZBFcyNH4GvA";
const char *DiceNormaladdr = "RpMHByaCzft3rox8wuG4DdTzjjtPgbGsiZ";
char DiceCChexstr[67] = { "02ad7593d4c3f2539c4bfa7aff13ea21b0a266c8f009d33455286487d9d7e255b2" };
uint8_t DiceCCpriv[32] = { 0xc0, 0x2a, 0xe7, 0x54, 0x99, 0x23, 0x3f, 0xca, 0x45, 0x06, 0xaa, 0xf8, 0x48, 0xad, 0x48, 0xa1, 0x4b, 0x29, 0x26, 0x17, 0x2e, 0x9d, 0xe0, 0x20, 0xa1, 0xe0, 0xa4, 0xba, 0x6a, 0xb2, 0xfd, 0x77 };
#include "CCcustom.inc"
#undef FUNCNAME
#undef EVALCODE

// Lotto
#define FUNCNAME IsLottoInput
#define EVALCODE EVAL_LOTTO
const char *LottoCCaddr = "ReRVCESNLZ2XUA8wfSaqKxLfzYzC6JjDwN";
const char *LottoNormaladdr = "RbVDmLiArqC5UwdRzR1hcgA6sr8WwP3Hgi";
char LottoCChexstr[67] = { "03048a975cb23730e6d2ed48baa3442b076e463c69d14d72beeafb2b81e57a6823" };
uint8_t LottoCCpriv[32] = { 0xc8, 0x56, 0xd1, 0x14, 0x79, 0xb9, 0xec, 0xac, 0x8a, 0x92, 0x73, 0xad, 0x99, 0x06, 0xf7, 0x53, 0xd2, 0x50, 0x1c, 0x1e, 0x5a, 0x42, 0x65, 0x24, 0x3e, 0x4c, 0xae, 0x36, 0x7e, 0x8c, 0xd2, 0x40 };
#include "CCcustom.inc"
#undef FUNCNAME
#undef EVALCODE

// Finite State Machine
#define FUNCNAME IsFSMInput
#define EVALCODE EVAL_FSM
const char *FSMCCaddr = "RfDqb2VYp2Uvc6CZhjtoVH3ob6BLuPkb1n";
const char *FSMNormaladdr = "RjnqBi57czidrAH7V8ZSw8KGmEtBLksDFF";
char FSMCChexstr[67] = { "033cfde6b8929b0e6d2c6c821c087033d26a3f6ac8508996bc45e9b912decd0746" };
uint8_t FSMCCpriv[32] = { 0x18, 0x8e, 0x55, 0x7c, 0xcd, 0x84, 0x51, 0x3d, 0x0a, 0x48, 0xa7, 0xe5, 0x36, 0x65, 0x93, 0x07, 0xef, 0x27, 0xf3, 0x92, 0x74, 0xc5, 0x19, 0x1a, 0x17, 0x0e, 0x40, 0xb9, 0xb5, 0x30, 0x56, 0x62 };
#include "CCcustom.inc"
#undef FUNCNAME
#undef EVALCODE

// Auction
#define FUNCNAME IsAuctionInput
#define EVALCODE EVAL_AUCTION
const char *AuctionCCaddr = "RnmNxFHdzYZbuP5uM9Evzboq9hX1fn2PMt";
const char *AuctionNormaladdr = "RdnWbgUiWBNh9fcEFX6Kk7yoaUUBtdE3tp";
char AuctionCChexstr[67] = { "029adf623311f5b91f8e15795bee5b2818d06ae2cf33ce70103cc174cfe006afe0" };
uint8_t AuctionCCpriv[32] = { 0xd0, 0xb3, 0x0a, 0xcc, 0x60, 0x74, 0xaa, 0xa8, 0xd7, 0xe6, 0xee, 0x33, 0xfd, 0x00, 0xca, 0x35, 0xe1, 0xaf, 0x9f, 0xc5, 0x11, 0x71, 0x6d, 0x7c, 0xd1, 0xd2, 0x6a, 0x51, 0x1a, 0xff, 0x36, 0x6d };
#include "CCcustom.inc"
#undef FUNCNAME
#undef EVALCODE

// Heir
#define FUNCNAME IsHeirInput
#define EVALCODE EVAL_HEIR
const char *HeirCCaddr = "RqGvzppM8S7kjrhBaFusQVqEqn2jcCQMFn";
const char *HeirNormaladdr = "Rbxt6QneETunaWZpCzQhGYAX83KL1Fmrim";
char HeirCChexstr[67] = { "0209a9715331f13db2f6d5c1522a0754c29c9087749bdce7d6324cb7aa88772463" };
uint8_t HeirCCpriv[32] = { 0xa0, 0x00, 0x20, 0xcc, 0xba, 0x24, 0x6d, 0x3e, 0x4c, 0x64, 0x5d, 0x43, 0xc2, 0x79, 0x8b, 0xad, 0x07, 0x72, 0x37, 0x0a, 0xae, 0x81, 0x7f, 0x72, 0xe2, 0xdb, 0x72, 0x44, 0xe3, 0xec, 0xe3, 0x68 };
#include "CCcustom.inc"
#undef FUNCNAME
#undef EVALCODE

// Channels
#define FUNCNAME IsChannelsInput
#define EVALCODE EVAL_CHANNELS
const char *ChannelsCCaddr = "Rg8TkYGgcbRhsxYMB8ehZ8JwsZaPi23RCN";
const char *ChannelsNormaladdr = "RjrNBM2pbw3X4ME6j5aKy5V5m9nLnx1zvu";
char ChannelsCChexstr[67] = { "03b77946b82303499af6718fdd2507285bd39a1066ee23f2f9ca22404cf0755569" };
uint8_t ChannelsCCpriv[32] = { 0x80, 0x43, 0x41, 0x7c, 0xe8, 0x43, 0xc2, 0x86, 0xbd, 0xec, 0x67, 0x6e, 0xa1, 0x15, 0xd9, 0xf6, 0xd7, 0x73, 0x9d, 0xc9, 0x51, 0xf0, 0x5b, 0xa4, 0xcb, 0xc4, 0x5e, 0x75, 0x99, 0x8b, 0x80, 0x6e };
#include "CCcustom.inc"
#undef FUNCNAME
#undef EVALCODE

// Oracles
#define FUNCNAME IsOraclesInput
#define EVALCODE EVAL_ORACLES
const char *OraclesCCaddr = "RnSNnG1xHLW4mgaonsuUxCJZSojvRBtcLJ";
const char *OraclesNormaladdr = "ReMfQ67NzZtiGhrFeCETjyFtpBs6XYRP61";
char OraclesCChexstr[67] = { "02697228bccebabf4264f02f806e288d9415319cf93159839f4169466444624d2c" };
uint8_t OraclesCCpriv[32] = { 0xc8, 0x8b, 0xdc, 0x0e, 0x2a, 0x1e, 0x29, 0x02, 0xd4, 0x3c, 0xc2, 0xe3, 0x26, 0xe3, 0x46, 0x14, 0x6d, 0xb9, 0x1a, 0xbb, 0x09, 0x52, 0x80, 0xdb, 0x87, 0xf7, 0x76, 0x13, 0xa7, 0xf7, 0x5d, 0x60 };
#include "CCcustom.inc"
#undef FUNCNAME
#undef EVALCODE

// Prices
#define FUNCNAME IsPricesInput
#define EVALCODE EVAL_PRICES
const char *PricesCCaddr = "RsjkDjpo7GoqGyUhDU9jMJYZmkXqFVw58R";
const char *PricesNormaladdr = "RmTAvrMD8jMGJj1SnKwqoacVtNqzZtr5X8";
char PricesCChexstr[67] = { "0301bfe25c7b04077f89b1201f235741a22e8d02a9d4077faa402e6d8a1a140251" };
uint8_t PricesCCpriv[32] = { 0x38, 0xf0, 0xa9, 0x7e, 0xf7, 0x84, 0x3c, 0x64, 0xd9, 0x23, 0x86, 0x69, 0x55, 0x6f, 0xfc, 0x42, 0xe1, 0x6a, 0xee, 0xec, 0x71, 0x7e, 0x7b, 0xa5, 0xca, 0xe6, 0xdf, 0x3a, 0x83, 0xae, 0xe2, 0x48 };
#include "CCcustom.inc"
#undef FUNCNAME
#undef EVALCODE

// Pegs
#define FUNCNAME IsPegsInput
#define EVALCODE EVAL_PEGS
const char *PegsCCaddr = "RvvxU5De8wjKoFo3ZQ3tm5DQwsyVqQAZG3";
const char *PegsNormaladdr = "RdMdT3muRHUmeXMjzA7izhyMKo6QaGkuMe";
char PegsCChexstr[67] = { "021ddad9aa2910b3583f314219252676996da16c455ac0c1cb1c9976b095d72478" };
uint8_t PegsCCpriv[32] = { 0xc0, 0x61, 0xf4, 0x67, 0x40, 0x08, 0x14, 0xe5, 0x74, 0xf3, 0x4a, 0x13, 0xe6, 0x62, 0xf8, 0x69, 0xbc, 0x20, 0x88, 0x8f, 0xec, 0xcc, 0x33, 0xba, 0xd4, 0x26, 0xad, 0x8d, 0xa0, 0xce, 0x11, 0x74 };
#include "CCcustom.inc"
#undef FUNCNAME
#undef EVALCODE

// Marmara
#define FUNCNAME IsMarmaraInput
#define EVALCODE EVAL_MARMARA
const char *MarmaraCCaddr = "RGLSRDnUqTB43bYtRtNVgmwSSd1sun2te8";
const char *MarmaraNormaladdr = "RhSuFNVKgqRUjc1uU6Ko5NGbVJmbXTTE7q";
char MarmaraCChexstr[67] = { "03a792df03f08bbb9852b723c55366b89c8005308f18d197c4373d71f866e94fa8" };
uint8_t MarmaraCCpriv[32] = { 0x7c, 0x0b, 0x54, 0x9b, 0x65, 0xd4, 0x89, 0x57, 0xdf, 0x05, 0xfe, 0xa2, 0x62, 0x41, 0xa9, 0x09, 0x0f, 0x2a, 0x6b, 0x11, 0x2c, 0xbe, 0xbd, 0x06, 0x31, 0x8d, 0xc0, 0xb9, 0x96, 0x76, 0x3f, 0x24 };
#include "CCcustom.inc"
#undef FUNCNAME
#undef EVALCODE

// Payments
#define FUNCNAME IsPaymentsInput
#define EVALCODE EVAL_PAYMENTS
const char *PaymentsCCaddr = "RaNJ5bsSqfX6iMxySrZteRSsBJS9u265mK";
const char *PaymentsNormaladdr = "Ro3PWA77ifX4LDLd8sgPgWpVcP6pJe7an3";
char PaymentsCChexstr[67] = { "0385e6e5e039a99f2c2f7d0154688ac367858669b6e7dd10eb8d1c9110fea6403b" };
uint8_t PaymentsCCpriv[32] = { 0x10, 0x98, 0xed, 0xb3, 0x91, 0xa4, 0x61, 0xd2, 0xbd, 0x26, 0xe3, 0x7b, 0xbe, 0x6b, 0xae, 0xeb, 0x31, 0x5b, 0xad, 0xb6, 0xfa, 0xd3, 0xda, 0x9e, 0xcb, 0xc6, 0x63, 0xf6, 0x99, 0x50, 0x87, 0x47 };
#include "CCcustom.inc"
#undef FUNCNAME
#undef EVALCODE

// Gateways
#define FUNCNAME IsGatewaysInput
#define EVALCODE EVAL_GATEWAYS
const char *GatewaysCCaddr = "RcDakt2SiQb9WmyzyuLfpEALQ4aUKKdBM4";
const char *GatewaysNormaladdr = "RZ2nsbBReLqPP3pJqEGivGqX8bUEZddWhE"; // wif UxJFYqEvLAjWPPRvn8NN1fRWscBxQZXZB5BBgc3HiapKVQBYNcmo
char GatewaysCChexstr[67] = { "03f89edede74cad0f9e8a8707a6ce0dd603e76e0d9eecb5cb0d8f7e053bb5cc78a" };
uint8_t GatewaysCCpriv[32] = { 0x10, 0x98, 0xed, 0xb3, 0x91, 0xa4, 0x61, 0xd2, 0xbd, 0x26, 0xe3, 0x7b, 0xbe, 0x6b, 0xae, 0xeb, 0x31, 0x5b, 0xad, 0xb6, 0xfa, 0xd3, 0xda, 0x9e, 0xcb, 0xc6, 0x63, 0xf6, 0x99, 0x50, 0x87, 0x47 };
#include "CCcustom.inc"
#undef FUNCNAME
#undef EVALCODE

// Tokens
#define FUNCNAME IsTokensInput
#define EVALCODE EVAL_TOKENS
const char *TokensCCaddr = "RhBYUNzSy8jGjLeYTuCJmJ9jqfwqEA5adm";
const char *TokensNormaladdr = "RpzoL1nvrCB5pk8BmdufMYbDvqkpYnVWKn"; 
char TokensCChexstr[67] = { "03552fdb156bdc58073a507c77ae9fbcbe0c9f7727f21bfd51178c99956be95166" };
uint8_t TokensCCpriv[32] = { 0x48, 0x40, 0x9a, 0x97, 0xe6, 0x7f, 0x06, 0xe3, 0x89, 0xf6, 0x91, 0x55, 0xa8, 0x31, 0x42, 0x25, 0xc2, 0xc5, 0xa3, 0xe1, 0xfd, 0x3a, 0x33, 0x05, 0x6e, 0x16, 0x6c, 0x42, 0xfd, 0x72, 0x24, 0x73 };
#include "CCcustom.inc"
#undef FUNCNAME
#undef EVALCODE

// FirstUser
#define FUNCNAME IsCClibInput
#define EVALCODE EVAL_FIRSTUSER
const char *CClibNormaladdr = "RvK2qRZmsUn7mKu2ybTyBWSP1XpvyQdBJh";
char CClibCChexstr[67] = { "03adfdca8877818360388f9983c7c40486969b634c67342e020e654c09bb9c8d34" };
uint8_t CClibCCpriv[32] = { 0xd8, 0x33, 0x84, 0x09, 0x13, 0x80, 0x8a, 0x5b, 0xb9, 0xc6, 0xb2, 0x99, 0xe0, 0x56, 0x40, 0x04, 0x19, 0x42, 0xf8, 0xa7, 0x90, 0xaf, 0x5c, 0x73, 0x0a, 0x70, 0x76, 0x26, 0x0c, 0x44, 0x8e, 0x53 };
#include "CCcustom.inc"
#undef FUNCNAME
#undef EVALCODE

// ImportGateway
#define FUNCNAME IsImportGatewayInput
#define EVALCODE EVAL_IMPORTGATEWAY
const char *ImportGatewayCCaddr = "RnBXorowSY6BB9S6uCpECLAuH5JdCLUFxp";
const char *ImportGatewayNormaladdr = "RnBXorowSY6BB9S6uCpECLAuH5JdCLUFxp"; 
char ImportGatewayCChexstr[67] = { "0377229de8322d25b62918af07487e46ba178db0ae91b3efd31f3e4fb1f570e1fe" };
uint8_t ImportGatewayCCpriv[32] = { 0x30, 0x73, 0x6d, 0x12, 0x38, 0xbc, 0x0d, 0x77, 0xe9, 0xee, 0x6c, 0x1e, 0x9a, 0x62, 0x72, 0x67, 0x7d, 0xa6, 0x47, 0x64, 0x93, 0x74, 0x24, 0xcc, 0x75, 0x6c, 0x3a, 0x8a, 0x93, 0x4c, 0x17, 0x72 };
#include "CCcustom.inc"
#undef FUNCNAME
#undef EVALCODE

int32_t CClib_initcp(struct CCcontract_info *cp,uint8_t evalcode)
{
    CPubKey pk; int32_t i; uint8_t pub33[33],check33[33],hash[32]; char CCaddr[64],checkaddr[64],str[67];
    cp->evalcode = evalcode;
    cp->ismyvin = IsCClibInput;
    memcpy(cp->CCpriv,CClibCCpriv,32);
    if ( evalcode == EVAL_FIRSTUSER ) // eventually make a hashchain for each evalcode
    {
        strcpy(cp->CChexstr,CClibCChexstr);
        decode_hex(pub33,33,cp->CChexstr);
        pk = buf2pk(pub33);
        Getscriptaddress(cp->normaladdr,CScript() << ParseHex(HexStr(pk)) << OP_CHECKSIG);
        if ( strcmp(cp->normaladdr,CClibNormaladdr) != 0 )
            fprintf(stderr,"CClib_initcp addr mismatch %s vs %s\n",cp->normaladdr,CClibNormaladdr);
        GetCCaddress(cp,cp->unspendableCCaddr,pk);
        if ( priv2addr(checkaddr,check33,cp->CCpriv) != 0 )
        {
            if ( buf2pk(check33) == pk && strcmp(checkaddr,cp->normaladdr) == 0 )
            {
                //fprintf(stderr,"verified evalcode.%d %s %s\n",cp->evalcode,checkaddr,pubkey33_str(str,pub33));
                return(0);
            } else fprintf(stderr,"CClib_initcp mismatched privkey -> addr %s vs %s\n",checkaddr,cp->normaladdr);
        }
    }
    else
    {
        for (i=EVAL_FIRSTUSER; i<evalcode; i++)
        {
            vcalc_sha256(0,hash,cp->CCpriv,32);
            memcpy(cp->CCpriv,hash,32);
        }
        if ( priv2addr(cp->normaladdr,pub33,cp->CCpriv) != 0 )
        {
            pk = buf2pk(pub33);
            for (i=0; i<33; i++)
                sprintf(&cp->CChexstr[i*2],"%02x",pub33[i]);
            cp->CChexstr[i*2] = 0;
            GetCCaddress(cp,cp->unspendableCCaddr,pk);
            //printf("evalcode.%d initialized\n",evalcode);
            return(0);
        }
    }
    return(-1);
}

struct CCcontract_info *CCinit(struct CCcontract_info *cp, uint8_t evalcode)
{
    // important to clear because not all members are always initialized!
    memset(cp, '\0', sizeof(*cp));

    cp->evalcode = evalcode;
    switch ( evalcode )
    {
        case EVAL_ASSETS:
            strcpy(cp->unspendableCCaddr,AssetsCCaddr);
            strcpy(cp->normaladdr,AssetsNormaladdr);
            strcpy(cp->CChexstr,AssetsCChexstr);
            memcpy(cp->CCpriv,AssetsCCpriv,32);
            cp->validate = AssetsValidate;
            cp->ismyvin = IsAssetsInput;
            break;
        case EVAL_FAUCET:
            strcpy(cp->unspendableCCaddr,FaucetCCaddr);
            strcpy(cp->normaladdr,FaucetNormaladdr);
            strcpy(cp->CChexstr,FaucetCChexstr);
            memcpy(cp->CCpriv,FaucetCCpriv,32);
            cp->validate = FaucetValidate;
            cp->ismyvin = IsFaucetInput;
            break;
        case EVAL_REWARDS:
            strcpy(cp->unspendableCCaddr,RewardsCCaddr);
            strcpy(cp->normaladdr,RewardsNormaladdr);
            strcpy(cp->CChexstr,RewardsCChexstr);
            memcpy(cp->CCpriv,RewardsCCpriv,32);
            cp->validate = RewardsValidate;
            cp->ismyvin = IsRewardsInput;
            break;
        case EVAL_DICE:
            strcpy(cp->unspendableCCaddr,DiceCCaddr);
            strcpy(cp->normaladdr,DiceNormaladdr);
            strcpy(cp->CChexstr,DiceCChexstr);
            memcpy(cp->CCpriv,DiceCCpriv,32);
            cp->validate = DiceValidate;
            cp->ismyvin = IsDiceInput;
            break;
        case EVAL_LOTTO:
            strcpy(cp->unspendableCCaddr,LottoCCaddr);
            strcpy(cp->normaladdr,LottoNormaladdr);
            strcpy(cp->CChexstr,LottoCChexstr);
            memcpy(cp->CCpriv,LottoCCpriv,32);
            cp->validate = LottoValidate;
            cp->ismyvin = IsLottoInput;
            break;
        case EVAL_FSM:
            strcpy(cp->unspendableCCaddr,FSMCCaddr);
            strcpy(cp->normaladdr,FSMNormaladdr);
            strcpy(cp->CChexstr,FSMCChexstr);
            memcpy(cp->CCpriv,FSMCCpriv,32);
            cp->validate = FSMValidate;
            cp->ismyvin = IsFSMInput;
            break;
        case EVAL_AUCTION:
            strcpy(cp->unspendableCCaddr,AuctionCCaddr);
            strcpy(cp->normaladdr,AuctionNormaladdr);
            strcpy(cp->CChexstr,AuctionCChexstr);
            memcpy(cp->CCpriv,AuctionCCpriv,32);
            cp->validate = AuctionValidate;
            cp->ismyvin = IsAuctionInput;
            break;
        case EVAL_HEIR:
            strcpy(cp->unspendableCCaddr,HeirCCaddr);
            strcpy(cp->normaladdr,HeirNormaladdr);
            strcpy(cp->CChexstr,HeirCChexstr);
            memcpy(cp->CCpriv,HeirCCpriv,32);
            cp->validate = HeirValidate;
            cp->ismyvin = IsHeirInput;
            break;
        case EVAL_CHANNELS:
            strcpy(cp->unspendableCCaddr,ChannelsCCaddr);
            strcpy(cp->normaladdr,ChannelsNormaladdr);
            strcpy(cp->CChexstr,ChannelsCChexstr);
            memcpy(cp->CCpriv,ChannelsCCpriv,32);
            cp->validate = ChannelsValidate;
            cp->ismyvin = IsChannelsInput;
            break;
        case EVAL_ORACLES:
            strcpy(cp->unspendableCCaddr,OraclesCCaddr);
            strcpy(cp->normaladdr,OraclesNormaladdr);
            strcpy(cp->CChexstr,OraclesCChexstr);
            memcpy(cp->CCpriv,OraclesCCpriv,32);
            cp->validate = OraclesValidate;
            cp->ismyvin = IsOraclesInput;
            break;
        case EVAL_PRICES:
            strcpy(cp->unspendableCCaddr,PricesCCaddr);
            strcpy(cp->normaladdr,PricesNormaladdr);
            strcpy(cp->CChexstr,PricesCChexstr);
            memcpy(cp->CCpriv,PricesCCpriv,32);
            cp->validate = PricesValidate;
            cp->ismyvin = IsPricesInput;
            break;
        case EVAL_PEGS:
            strcpy(cp->unspendableCCaddr,PegsCCaddr);
            strcpy(cp->normaladdr,PegsNormaladdr);
            strcpy(cp->CChexstr,PegsCChexstr);
            memcpy(cp->CCpriv,PegsCCpriv,32);
            cp->validate = PegsValidate;
            cp->ismyvin = IsPegsInput;
            break;
        case EVAL_MARMARA:
            strcpy(cp->unspendableCCaddr,MarmaraCCaddr);
            strcpy(cp->normaladdr,MarmaraNormaladdr);
            strcpy(cp->CChexstr,MarmaraCChexstr);
            memcpy(cp->CCpriv,MarmaraCCpriv,32);
            cp->validate = MarmaraValidate;
            cp->ismyvin = IsMarmaraInput;
            break;
        case EVAL_PAYMENTS:
            strcpy(cp->unspendableCCaddr,PaymentsCCaddr);
            strcpy(cp->normaladdr,PaymentsNormaladdr);
            strcpy(cp->CChexstr,PaymentsCChexstr);
            memcpy(cp->CCpriv,PaymentsCCpriv,32);
            cp->validate = PaymentsValidate;
            cp->ismyvin = IsPaymentsInput;
            break;
        case EVAL_GATEWAYS:
            strcpy(cp->unspendableCCaddr,GatewaysCCaddr);
            strcpy(cp->normaladdr,GatewaysNormaladdr);
            strcpy(cp->CChexstr,GatewaysCChexstr);
            memcpy(cp->CCpriv,GatewaysCCpriv,32);
            cp->validate = GatewaysValidate;
            cp->ismyvin = IsGatewaysInput;
            break;

		case EVAL_TOKENS:
			strcpy(cp->unspendableCCaddr, TokensCCaddr);
			strcpy(cp->normaladdr, TokensNormaladdr);
			strcpy(cp->CChexstr, TokensCChexstr);
			memcpy(cp->CCpriv, TokensCCpriv, 32);
			cp->validate = TokensValidate;
			cp->ismyvin = IsTokensInput;
			break;
        case EVAL_IMPORTGATEWAY:
			strcpy(cp->unspendableCCaddr, ImportGatewayCCaddr);
			strcpy(cp->normaladdr, ImportGatewayNormaladdr);
			strcpy(cp->CChexstr, ImportGatewayCChexstr);
			memcpy(cp->CCpriv, ImportGatewayCCpriv, 32);
			cp->validate = ImportGatewayValidate;
			cp->ismyvin = IsImportGatewayInput;
			break;
        default:
            if ( CClib_initcp(cp,evalcode) < 0 )
                return(0);
            break;
    }
    return(cp);
}

