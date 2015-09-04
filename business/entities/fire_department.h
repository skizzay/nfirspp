// vim: sw=3 ts=3 expandtab cindent
#pragma once

#include "business/events/firefighter_enrolled_into_fire_department.h"
#include "business/values/address.h"
#include "business/values/fdid.h"
#include "infrastructure/session.h"
#include "cqrs/artifact.h"
#include <memory>
#include <vector>

namespace firepp {
namespace business {

class fire_station;

class fire_department final : public cddd::cqrs::artifact {
public:
   using id_type = boost::uuids::uuid;
   using id_collection = std::vector<id_type>;

   fire_department(id_collection &firefighters,
                   id_collection &stations,
                   infrastructure::session &session,
                   const id_type &id);

   void enroll_firefighter(const id_type &firefighter_id, const boost::gregorian::date &effective_date);
   void acquire_station(const id_type &station_id);

private:
   id_collection &firefighters;
   id_collection &stations;
   infrastructure::session &session_;
};

}
}
