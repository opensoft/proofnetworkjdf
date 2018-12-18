ProofNetworkJdf Changelog
=========================

## Not Released
#### Features
 * Component::length renamed to Component::depth
 * Short version of Component Dimensions attribute (with 2 parts) is now supported
 * Partitioned Layouts are now supported
 * Basic support for shearing with flipping in cut blocks added (only x; -1; -1; x and x; 1; 1; x are supported for now)

#### Bug Fixing
 * --

## 0.18.10.4
#### Features
 * CutBlock BlockTrf attribute x and y are always with 4 digits after decimal point now

#### Bug Fixing
 * --

## 0.17.9.26
#### Features
 * JDF: All find*() and findAll*() methods are BFS-based now
 * JDF: JdfNode::types()/setTypes() added
 * JDF: forceJobId argument added to JdfDocument::fromJdf for proper cache usage
 * JDF: header-only helpers added

#### Bug Fixing
 * JDF: proper ComponentRef parsing

## 0.17.8.25
#### Features
 * JDF: `findAll*()` methods added to JdfNode

#### Bug Fixing
 * --

## Changelog for releases older than 2018 can be found in main proof repository
