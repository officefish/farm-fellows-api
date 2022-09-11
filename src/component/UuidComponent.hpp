#ifndef FARM_FELLOWS_UUID_COMPONENT_HPP
#define FARM_FELLOWS_UUID_COMPONENT_HPP

#include <random>
#include "uuid.h"

class UUID_Generator {

private:
    typedef uuids::basic_uuid_random_generator<std::ranlux48_base> Ranlux48;
    typedef uuids::uuid_random_generator MT19937;  

private:
    std::shared_ptr<Ranlux48> m_basic_uuid_random_genenerator;
    std::shared_ptr<MT19937> m_uuid_random_generator; 

public:
    
    static std::shared_ptr<UUID_Generator> createShared()
    {
        return std::make_shared<UUID_Generator>();
    }

    UUID_Generator()
    {
        std::random_device rd_ranlux48;
        auto seed_data_ranlux48 = std::array<int, 6> {};
        std::generate(std::begin(seed_data_ranlux48), std::end(seed_data_ranlux48), std::ref(rd_ranlux48));
        std::seed_seq ranlux48_seq(std::begin(seed_data_ranlux48), std::end(seed_data_ranlux48));
        std::ranlux48_base ranlux48_generator(ranlux48_seq);

        Ranlux48 ranlux48_generate{ ranlux48_generator };
        m_basic_uuid_random_genenerator = std::make_shared<Ranlux48>(ranlux48_generate);

        std::random_device rd_mt19937;
        auto mt19937_seed_data = std::array<int, std::mt19937::state_size> {};
        std::generate(std::begin(mt19937_seed_data), std::end(mt19937_seed_data), std::ref(rd_mt19937));
        std::seed_seq mt19937_seq(std::begin(mt19937_seed_data), std::end(mt19937_seed_data));
        std::mt19937 mt19937_generator(mt19937_seq);

        MT19937 mt19937_generate{ mt19937_generator };
        m_uuid_random_generator = std::make_shared<MT19937>(mt19937_generate);
    }

    uuids::uuid basic_uuid_random_generator()
    {
        return (*m_basic_uuid_random_genenerator)();
    }

    std::string basic_uuid_random_generator_str()
    {
        auto id = basic_uuid_random_generator();
        return uuids::to_string(id);
    }
    
    uuids::uuid uuid_random_generator()
    {
       return (*m_uuid_random_generator)();
    }

    std::string uuid_random_generator_str()
    {
        auto id = uuid_random_generator();
        return uuids::to_string(id);
    } 
};

class UuidComponent {
public:
    OATPP_CREATE_COMPONENT(std::shared_ptr<UUID_Generator>, uuidGenerator)([]{
        return UUID_Generator::createShared();
    }());
};

#endif // FARM_FELLOWS_UUID_COMPONENT_HPP
