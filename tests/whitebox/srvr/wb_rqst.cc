//: ----------------------------------------------------------------------------
//: Copyright (C) 2018 Verizon.  All Rights Reserved.
//: All Rights Reserved
//:
//: \file:    wb_nconn_pool.cc
//: \details: TODO
//: \author:  Reed P. Morrison
//: \date:    02/16/2016
//:
//:   Licensed under the Apache License, Version 2.0 (the "License");
//:   you may not use this file except in compliance with the License.
//:   You may obtain a copy of the License at
//:
//:       http://www.apache.org/licenses/LICENSE-2.0
//:
//:   Unless required by applicable law or agreed to in writing, software
//:   distributed under the License is distributed on an "AS IS" BASIS,
//:   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//:   See the License for the specific language governing permissions and
//:   limitations under the License.
//:
//: ----------------------------------------------------------------------------
//: ----------------------------------------------------------------------------
//: includes
//: ----------------------------------------------------------------------------
#include "catch/catch.hpp"
#include "is2/srvr/rqst.h"
#include "is2/support/nbq.h"
#include "support/ndebug.h"
#include <string.h>
//: ----------------------------------------------------------------------------
//: constants
//: ----------------------------------------------------------------------------
#define TEST_URI_1 "/cats/dogs?monkeys=cool&orangutans=not_cool"
//: ----------------------------------------------------------------------------
//: Tests
//: ----------------------------------------------------------------------------
TEST_CASE( "request test", "[rqst]" )
{
        SECTION("Basic Query Parsing Test")
        {
                INFO("Init");
                ns_is2::nbq *l_nbq = new ns_is2::nbq(4096);
                ns_is2::rqst *l_rqst = new ns_is2::rqst();
                int64_t l_written;
                l_written = l_nbq->write(TEST_URI_1, sizeof(TEST_URI_1));
                REQUIRE((l_written == sizeof(TEST_URI_1)));
                l_rqst->set_q(l_nbq);
                l_rqst->m_p_url.m_off = 0;
                l_rqst->m_p_url.m_len = sizeof(TEST_URI_1)-1;
                const ns_is2::data_t &l_data = l_rqst->get_url_path();
                REQUIRE((l_data.m_data != NULL));
                REQUIRE((strncmp(l_data.m_data, "/cats/dogs", strlen("/cats/dogs")) == 0));
                const ns_is2::data_t &l_q_str_data = l_rqst->get_url_query();
                REQUIRE((l_q_str_data.m_data != NULL));
                REQUIRE((strncmp(l_q_str_data.m_data, "monkeys=cool&orangutans=not_cool", strlen("monkeys=cool&orangutans=not_cool")) == 0));
#if 0
                const ns_is2::query_map_t &l_query_map = l_rqst->get_url_query_map();
                REQUIRE((l_query_map.size() == 2));
                REQUIRE((l_query_map.begin()->first == "monkeys"));
                const ns_is2::query_map_t &l_query_map_raw = l_rqst->get_raw_url_query_map();
                REQUIRE((l_query_map_raw.size() == 2));
                REQUIRE((l_query_map_raw.begin()->first == "monkeys"));
#endif
                if(l_rqst) { delete l_rqst; l_rqst = NULL; }
                if(l_nbq) { delete l_nbq; l_nbq = NULL; }
        }
}
