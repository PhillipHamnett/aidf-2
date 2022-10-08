#include <escrowtest.hpp>
#include <deal.hpp>

void escrowtest::setdeal(eosio::name user1, eosio::name user2, eosio::extended_asset quantity1, eosio::extended_asset quantity2, eosio::time_point expiration){
  require_auth(user1);
  deal_table table(_self, _self.value);
  deal tmp_deal(table.available_primary_key(), user1, user2, quantity1, quantity2, expiration);
  table.emplace(_self, [&](auto & entry){
                entry = tmp_deal;
                });
}

void escrowtest::on_transfer(eosio::name from, eosio::name to, eosio::asset quantity, std::string memo){
}
