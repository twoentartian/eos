#include <eosiolib/eosio.hpp>
#include <unistd.h>
using namespace eosio;

extern void sleep(int msecs);

class tyd_test : public eosio::contract
{
  public:
    using contract::contract;

    /// @abi action 
    void hi( account_name user )
    {
      require_auth( user );
      print( "Tyd contract test successful, ", name{user} );
    }

    /// @abi action
    void countdown( uint64_t number)
    {
      while(number>0)
      {
        eosio::print(number--);
      }
    }
};

EOSIO_ABI( tyd_test, (hi) (countdown) )
