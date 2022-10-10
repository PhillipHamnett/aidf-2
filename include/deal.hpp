#ifndef DEAL
#define DEAL

#include <eosio/crypto.hpp>

class [[eosio::table("deal"), eosio::contract("escrowtest")]] deal {
  private:
    uint64_t id;
    eosio::name user1;
    eosio::name user2;
    eosio::extended_asset quantity1;
    eosio::extended_asset quantity2;
    eosio::time_point expiry;
    bool user1_done;
    bool user2_done;
  public:
    deal(){}
    deal(uint64_t _id, eosio::name _user1, eosio::name _user2, eosio::extended_asset _quantity1, eosio::extended_asset _quantity2, eosio::time_point _expiry){
      id = _id;
      user1 = _user1;
      user2 = _user2;
      quantity1 = _quantity1;
      quantity2 = _quantity2;
      expiry = _expiry;
      user1_done = false;
      user2_done = false;
    }

    eosio::name get_user1() const {return user1;}
    eosio::name get_user2() const {return user2;}
    eosio::extended_asset get_quantity1() const {return quantity1;}
    eosio::extended_asset get_quantity2() const {return quantity2;}
    eosio::time_point get_expiry() const {return expiry;}
    bool get_user1_done() const {return user1_done;}
    bool get_user2_done() const {return user2_done;}
    
    void set_id(uint64_t x){id = x;}
    void set_user1(eosio::name x){user1 = x;}
    void set_user2(eosio::name x){user2 = x;}
    void set_quantity1(eosio::extended_asset x){quantity1 = x;}
    void set_quantity2(eosio::extended_asset x){quantity2 = x;}
    void set_expiry(eosio::time_point x){expiry = x;}
    void set_user1_done(bool x){user1_done = x;}
    void set_user2_done(bool x){user2_done = x;}
    
    uint64_t primary_key() const {return id;}
    uint64_t secondary_key() const {return expiry.sec_since_epoch();}

    EOSLIB_SERIALIZE(deal, (id)(user1)(user2)(quantity1)(quantity2)(expiry)(user1_done)(user2_done));
};

typedef eosio::multi_index< "deal"_n, deal, eosio::indexed_by<"date"_n, eosio::const_mem_fun<deal, uint64_t, &deal::secondary_key> > > deal_table;

#endif
