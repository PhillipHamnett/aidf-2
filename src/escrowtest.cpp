#include <escrowtest.hpp>
#include <deal.hpp>

#include <eosio/system.hpp>

void escrowtest::setdeal(eosio::name user1, eosio::name user2, eosio::extended_asset quantity1, eosio::extended_asset quantity2, eosio::time_point expiration){
  require_auth(user1);
  deal_table table(_self, _self.value);
  deal tmp_deal(table.available_primary_key(), user1, user2, quantity1, quantity2, expiration);
  table.emplace(_self, [&](auto & entry){
                entry = tmp_deal;
                });
  require_recipient(user1);
  require_recipient(user2);
}

void escrowtest::on_transfer(eosio::name from, eosio::name to, eosio::asset quantity, std::string memo){
  if(to != _self) return;
  uint64_t id = stoi(memo);
  deal_table table(_self, _self.value);
  auto itr = table.find(id);
  eosio::check(itr != table.end(), "A deal does not exist with this ID");
  eosio::check(itr->get_expiry() > eosio::current_time_point(), "This deal has expired");
  eosio::check(itr->get_user1() == from || itr->get_user2() == from, "You are not a part of this deal");
  if(from == itr->get_user1()){
    eosio::check(itr->get_quantity1().quantity.amount == quantity.amount, "Wrong asset provided, amount mismatch");
    eosio::check(itr->get_quantity1().quantity.symbol == quantity.symbol, "Wrong asset provided, symbol mismatch");
    eosio::check(itr->get_quantity1().contract == get_first_receiver(), "Wrong asset provided, contract mismatch");
    eosio::check(itr->get_user1_done() == false, "User has already paid");
    require_recipient(itr->get_user2());
    table.modify(itr, _self, [&](auto & entry){
                 entry.set_user1_done(true);
                 });
    if(itr->get_user2_done()) complete_deal(id);
  } else{
    eosio::check(itr->get_quantity2().quantity.amount == quantity.amount, "Wrong asset provided, amount mismatch");
    eosio::check(itr->get_quantity2().quantity.symbol == quantity.symbol, "Wrong asset provided, symbol mismatch");
    eosio::check(itr->get_quantity2().contract == get_first_receiver(), "Wrong asset provided, contract mismatch");
    eosio::check(itr->get_user2_done() == false, "User has already paid");
    require_recipient(itr->get_user1());
    table.modify(itr, _self, [&](auto & entry){
                 entry.set_user2_done(true);
                 });
    if(itr->get_user1_done()) complete_deal(id);
  }
}

void escrowtest::complete_deal(uint64_t id){
  deal_table table(_self, _self.value);
  auto itr = table.find(id);
  eosio::check(itr != table.end(), "A deal does not exist with this ID");
  eosio::action(eosio::permission_level(_self, eosio::name("active")), itr->get_quantity1().contract, eosio::name("transfer"), std::tuple(_self, itr->get_user2(), itr->get_quantity1().quantity, std::string("Deal complete"))).send();
  eosio::action(eosio::permission_level(_self, eosio::name("active")), itr->get_quantity2().contract, eosio::name("transfer"), std::tuple(_self, itr->get_user1(), itr->get_quantity2().quantity, std::string("Deal complete"))).send();
  table.erase(itr);
}

void escrowtest::canceldeal(uint64_t id){
  deal_table table(_self, _self.value);
  auto itr = table.find(id);
  eosio::check(itr != table.end(), "A deal does not exist with this ID");
  eosio::check(has_auth(itr->get_user1()) || has_auth(itr->get_user2()) || has_auth(_self), "Missing authority to cancel this deal");
  if(itr->get_user1_done()){
    eosio::action(eosio::permission_level(_self, eosio::name("active")), itr->get_quantity1().contract, eosio::name("transfer"), std::tuple(_self, itr->get_user1(), itr->get_quantity1().quantity, std::string("Deal cancelled"))).send();
  }
  if(itr->get_user2_done()){
    eosio::action(eosio::permission_level(_self, eosio::name("active")), itr->get_quantity2().contract, eosio::name("transfer"), std::tuple(_self, itr->get_user2(), itr->get_quantity2().quantity, std::string("Deal cancelled"))).send();
  }
  require_recipient(itr->get_user1());
  require_recipient(itr->get_user2());
  table.erase(itr);
}

void escrowtest::update(){
  require_auth(_self);
  deal_table table(_self, _self.value);
  auto sorted_table = table.get_index<"date"_n>();
  while(sorted_table.begin() != sorted_table.end() && sorted_table.begin()->get_expiry() < eosio::current_time_point()){
    canceldeal(sorted_table.begin()->primary_key());
  }
}
