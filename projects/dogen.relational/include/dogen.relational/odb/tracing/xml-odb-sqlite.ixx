// -*- C++ -*-
//
// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

namespace odb
{
  // xml
  //

  inline
  bool access::composite_value_traits< ::dogen::relational::tracing::xml, id_sqlite >::
  get_null (const image_type& i)
  {
    bool r (true);
    r = r && i.value_null;
    return r;
  }

  inline
  void access::composite_value_traits< ::dogen::relational::tracing::xml, id_sqlite >::
  set_null (image_type& i,
            sqlite::statement_kind sk)
  {
    ODB_POTENTIALLY_UNUSED (sk);

    using namespace sqlite;

    i.value_null = true;
  }
}

