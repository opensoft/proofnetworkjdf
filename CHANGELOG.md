ProofNetworkJdf Changelog
=========================

## Not Released
#### Features
 * XJDF: Methods AuditPool::addNotification and AmountPool::addPart added
 * XJDF: Added return value for methods Document::addResourceSet, ProductList::addProduct and ResourceSet::addResource

#### Bug Fixing
 * XJDF: Fix missing namespaces (for updateFrom)
 * XJDF: Fix read and write DeviceID attribute

## 0.19.8.7
#### Features
 * XJDF initial support
 * JDF: CutBlock::transformationMatrix() returns QTransform now
 * JDF: CutBlock methods rotation(), x() and y() removed
 * JDF: CutBlock::boundingRect() method added, which returns final bounding rect of cutblock after transformation matrix was applied
 * `bool *ok` parameter removed from enum helper methods

#### Bug Fixing
 * --

## 0.19.4.2
#### Features
 * --

#### Bug Fixing
 * Fix missing cutBlocks of components with sanitize

## 0.18.12.24
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
