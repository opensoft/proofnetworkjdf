cmake_minimum_required(VERSION 3.12.0)
project(ProofNetworkXJdfTest LANGUAGES CXX)

proof_add_target_sources(network-xjdf_tests
    xjdfdocument_test.cpp

)
proof_add_target_resources(network-xjdf_tests tests_resources.qrc)

proof_add_test(network-xjdf_tests
    PROOF_LIBS NetworkXJdf
)
