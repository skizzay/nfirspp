// vim: sw=3 ts=3 expandtab cindent
#pragma once

#include "business/events/firefighter_enrolled_into_fire_department.h"
#include "business/values/address.h"
#include "business/values/fdid.h"
#include "infrastructure/session.h"
#include "cqrs/artifact.h"
#include "cqrs/table.h"
#include <memory>
#include <vector>

namespace firepp {
namespace business {

class fire_station;

class fire_department final : public cddd::cqrs::artifact {
public:
   typedef boost::uuids::uuid id_type;

   fire_department(std::shared_ptr<infrastructure::session> session,
                   std::shared_ptr<cddd::messaging::dispatcher<>> dispatcher, const id_type &id);

   void enroll_firefighter(const id_type &id);

private:
   std::unique_ptr<id_collection> firefighters;
   std::unique_ptr<id_collection> stations;
   std::shared_ptr<infrastructure::session> session;
};

}
}
