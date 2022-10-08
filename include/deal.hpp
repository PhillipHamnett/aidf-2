#ifndef DEAL
#define DEAL

#include <eosio/crypto.hpp>

class [[eosio::table("deal")]] deal {
  private:
    uint64_t id;
    eosio::name user1;
    eosio::name user2;
    eosio::extended_asset quantity1;
    eosio::extended_asset quantity2;
    eosio::time_point expiry;
  public:
    deal(){}
    deal(uint64_t _id, eosio::name _user1, eosio::name _user2, eosio::extended_asset _quantity1, eosio::extended_asset _quantity2, eosio::time_point _expiry){
      id = _id;
      user1 = _user1;
      user2 = _user2;
      quantity1 = _quantity1;
      quantity2 = _quantity2;
      expiry = _expiry;
    }

    eosio::name get_user1(){return user1;}
    eosio::name get_user2(){return user2;}
    eosio::extended_asset get_quantity1(){return quantity1;}
    eosio::extended_asset get_quantity2(){return quantity2;}
    eosio::time_point get_expiry(){return expiry;}
    
    void set_id(uint64_t x){id = x;}
    void set_user1(eosio::name x){user1 = x;}
    void set_user2(eosio::name x){user2 = x;}
    void set_quantity1(eosio::extended_asset x){quantity1 = x;}
    void set_quantity2(eosio::extended_asset x){quantity2 = x;}
    void set_expiry(eosio::time_point x){expiry = x;}
    
    uint64_t primary_key() const {return id;}

    EOSLIB_SERIALIZE(deal, (id)(user1)(user2)(quantity1)(quantity2)(expiry));
};

typedef eosio::multi_index< "deal"_n, deal> deal_table;

#endif
