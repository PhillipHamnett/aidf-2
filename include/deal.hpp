#ifndef DEAL
#define DEAL

class [[eosio::table("deal")]] deal {
  private:
    eosio::name user1;
    eosio::name user2;
    eosio::extended_asset quantity1;
    eosio::extended_asset quantity2;
    eosio::time_point expiry;
  public:
    eosio::name get_user1(){return user1;}
    eosio::name get_user2(){return user2;}
    eosio::extended_asset get_quantity1(){return quantity1;}
    eosio::extended_asset get_quantity2(){return quantity2;}
    eosio::time_point get_expiry(){return expiry;}
    
    void set_user1(eosio::name x){user1 = x;}
    void set_user2(eosio::name x){user2 = x;}
    void set_quantity1(eosio::extended_asset x){quantity1 = x;}
    void set_quantity2(eosio::extended_asset x){quantity2 = x;}
    void set_expiry(eosio::time_point x){expiry = x;}
    EOSLIB_SERIALIZE(deal, (user1)(user2)(quantity1)(quantity2)(expiry));
};

typedef eosio::multi_index< "deal"_n, deal> deal_table;

#endif
