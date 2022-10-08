#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>

class [[eosio::contract("escrowtest")]] escrowtest : public eosio::contract {
  public:
    using eosio::contract::contract;

    [[eosio::action]] void setdeal(eosio::name user1, eosio::name user2, eosio::asset quantity1, eosio::asset quantity2, eosio::time_point expiration);
};
