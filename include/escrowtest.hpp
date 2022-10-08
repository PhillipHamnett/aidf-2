#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>

#include <string>

class [[eosio::contract("escrowtest")]] escrowtest : public eosio::contract {
  public:
    using eosio::contract::contract;

    [[eosio::action]] void setdeal(eosio::name user1, eosio::name user2, eosio::extended_asset quantity1, eosio::extended_asset quantity2, eosio::time_point expiration);
    [[eosio::on_notify("*::transfer")]] void on_transfer(eosio::name from, eosio::name to, eosio::asset quantity, std::string memo);
};
