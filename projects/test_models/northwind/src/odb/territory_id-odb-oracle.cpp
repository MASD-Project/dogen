// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#include <odb/pre.hxx>

#include "dogen/test_models/northwind/odb/territory_id-odb-oracle.hxx"

#include <cassert>
#include <cstring>  // std::memcpy

#include <odb/schema-catalog-impl.hxx>

#include <odb/oracle/traits.hxx>
#include <odb/oracle/database.hxx>
#include <odb/oracle/transaction.hxx>
#include <odb/oracle/connection.hxx>
#include <odb/oracle/statement.hxx>
#include <odb/oracle/statement-cache.hxx>
#include <odb/oracle/container-statements.hxx>
#include <odb/oracle/exceptions.hxx>

namespace odb
{
  // territory_id
  //

  void access::composite_value_traits< ::dogen::test_models::northwind::territory_id, id_oracle >::
  bind (oracle::bind* b,
        image_type& i,
        oracle::statement_kind sk)
  {
    ODB_POTENTIALLY_UNUSED (b);
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (sk);

    using namespace oracle;

    std::size_t n (0);
    ODB_POTENTIALLY_UNUSED (n);

    // value_
    //
    b[n].type = oracle::bind::string;
    b[n].buffer = i.value_value;
    b[n].capacity = static_cast<ub4> (sizeof (i.value_value));
    b[n].size = &i.value_size;
    b[n].indicator = &i.value_indicator;
    n++;
  }

  void access::composite_value_traits< ::dogen::test_models::northwind::territory_id, id_oracle >::
  init (image_type& i,
        const value_type& o,
        oracle::statement_kind sk)
  {
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (o);
    ODB_POTENTIALLY_UNUSED (sk);

    using namespace oracle;

    // value_
    //
    {
      ::std::string const& v =
        o.value ();

      bool is_null (true);
      std::size_t size (0);
      oracle::value_traits<
          ::std::string,
          oracle::id_string >::set_image (
        i.value_value,
        sizeof (i.value_value),
        size,
        is_null,
        v);
      i.value_indicator = is_null ? -1 : 0;
      i.value_size = static_cast<ub2> (size);
    }
  }

  void access::composite_value_traits< ::dogen::test_models::northwind::territory_id, id_oracle >::
  init (value_type& o,
        const image_type&  i,
        database* db)
  {
    ODB_POTENTIALLY_UNUSED (o);
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (db);

    // value_
    //
    {
      ::std::string& v =
        o.value ();

      oracle::value_traits<
          ::std::string,
          oracle::id_string >::set_value (
        v,
        i.value_value,
        i.value_size,
        i.value_indicator == -1);
    }
  }
}

#include <odb/post.hxx>
