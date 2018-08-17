TARGET=network-jdf_tests
include (../tests/tests.pri)

QT += network xml
CONFIG += proofnetwork proofnetworkjdf

SOURCES += \
    tests/proofnetwork/jdf/main.cpp \
    tests/proofnetwork/jdf/cutblock_test.cpp \
    tests/proofnetwork/jdf/jdfdocument_test.cpp \
    tests/proofnetwork/jdf/foldingparams_test.cpp \
    tests/proofnetwork/jdf/resourcelinkpool_test.cpp \
    tests/proofnetwork/jdf/knowndevicesquery_test.cpp \
    tests/proofnetwork/jdf/jmfdocument_test.cpp \
    tests/proofnetwork/jdf/knowndevicesresponse_test.cpp \
    tests/proofnetwork/jdf/jdfhelpers_test.cpp

RESOURCES += \
    tests/proofnetwork/jdf/tests_resources.qrc

DISTFILES += \
    tests/proofnetwork/jdf/data/jdfdocument.jdf \
    tests/proofnetwork/jdf/data/jdfdocument2.jdf \
    tests/proofnetwork/jdf/data/cutblock.jdf \
    tests/proofnetwork/jdf/data/cutblock2.jdf \
    tests/proofnetwork/jdf/data/foldingparams.jdf \
    tests/proofnetwork/jdf/data/foldingparams2.jdf \
    tests/proofnetwork/jdf/data/jdfnested.jdf \
    tests/proofnetwork/jdf/data/knowndevicesquery.jmf \
    tests/proofnetwork/jdf/data/knowndevicesquery2.jmf \
    tests/proofnetwork/jdf/data/jmfdocument.jmf \
    tests/proofnetwork/jdf/data/jmfdocument2.jmf \
    tests/proofnetwork/jdf/data/knowndevicesresponse.jmf \
    tests/proofnetwork/jdf/data/knowndevicesresponse2.jmf
